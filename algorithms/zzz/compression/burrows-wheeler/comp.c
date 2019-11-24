#include <stdlib.h>	
#include <string.h>

/* Coder.h */

#define BIPSHO  8 * sizeof(short)

#define LOGSIZ  15
#define BSIZE   (1 << LOGSIZ)

#define BITBUFSIZE      2048
#define UNDOBUF         3       /* max unget in shorts */
unsigned short  Bitbuff[BITBUFSIZE + UNDOBUF];
int     inshctr = BITBUFSIZE + UNDOBUF - 1, inbitrem = 0;

long    getbits();

/* BSIZE must be divisible by sizeof(short) ! */

/*
 * Need to handle byte order or compressed files
 * won't be portable across hosts.
 */
int     Swabbing = 0;

void ungetbits(int cnt)
{
        inbitrem += cnt;
        while (inbitrem >= BIPSHO) {
                inbitrem -= BIPSHO;
                inshctr -= 1;
        }
}

void setswab()
{
        union {
                char    c[2];
                short   s;
        } u;

        if (u.s = 1, u.c[0] == 1)
                Swabbing ^= 1;
}

void cswab(short *sp, int cnt)
{
        register unsigned x;

        if (Swabbing) while (cnt--) {
                x = *sp;
                *sp++ = x >> 8 & 0xff | (x & 0xff) << 8;
        }
}

/* IO subroutines that work with pipes */
int p_write(int fd, char *buf, int cnt)
{
        int     acnt, tcnt;

        for (acnt = 0; acnt < cnt; acnt += tcnt) {
                tcnt = write(fd, buf + acnt, cnt - acnt);
                if (tcnt <= 0) {
                        perror("write");
                        exit(1);
                }
        }
        return acnt;
}

int p_read(int fd, char *buf, int cnt)
{
        int     acnt, tcnt = 1;

        for (acnt = 0; acnt < cnt && tcnt; acnt += tcnt) {
                tcnt = read(fd, buf + acnt, cnt - acnt);
                if (tcnt < 0) {
                        perror("read");
                        exit(1);
                }
        }
        return acnt;
}

#ifdef  COMPRESSOR

u_char  Decbuff[BSIZE + BSIZE];
u_char  Encbuff[BSIZE];
u_short Sindex, Leng;
u_char  *Ptab[BSIZE];

int ptcomp(const void *pp1, const void *pp2)
{
        register u_char *p1 = *(u_char **)pp1, *p2 = *(u_char **)pp2;
        register c, len = Leng;

        do
                c = *p1++ - (int)*p2++;
        while (c == 0 && --len);
        return c;
}

void bwt_encode()
{
        int     i;

        memcpy(Decbuff + Leng, Decbuff, Leng);
        for (i = 0; i < Leng; i++)
                Ptab[i] = Decbuff + i;
        qsort(Ptab, Leng, sizeof(u_char *), ptcomp);
        for (i = 0; i < Leng; i++) {
                Encbuff[i] = Ptab[i][Leng - 1];
                if (Ptab[i] == Decbuff)
                        Sindex = i;
        }
}

u_char  Mtftab[256];

int mtf_encode(u_char din)
{
        register        i, resu;

        for (resu = 0; Mtftab[resu] != din; resu++)
                ;
        for (i = resu; i; i--)
                Mtftab[i] = Mtftab[i - 1];
        Mtftab[0] = din;
        return resu;
}

void eg_encode(int datum)
{
        int     n, nn;

        ++datum;
        for (n = 1, nn = 2; nn <= datum; n += 2, nn += nn)
                ;
        putbits((long)datum, n);
}

int     Numzeros = 0;

/*
 * Modified Elias_gamma code for run-lengths is defined by the code-lengths
 *         1  2  4  4  6  6  6  6  8  8  8  8  8  8  8 ...
 * Modified Elias_gamma code for positive MTF is defined by the code-lengths
 *         2  2  4  4  4  4  6  6  6  6  6  6  6  6  8 ...
 */
void zr_encode(int datum)
{
        if (datum == 0)
                ++Numzeros;
        else {
                if (Numzeros) {
                        putbits(1L, 1);
                        eg_encode(Numzeros - 1);
                } else
                        putbits(0L, 1);
                Numzeros = 0;
                eg_encode(datum - 1 >> 1);
                putbits(!((long)datum & 1), 1);
        }
}

int     outshctr, outbitctr;

int putbits(unsigned long dval, int cnt)
{
        if (cnt < 0) {
                /* Termination code */
                putbits(0L, BIPSHO - 1);
                goto forcewrite;
        }
        if (cnt > BIPSHO) {
                putbits(dval >> BIPSHO, cnt - BIPSHO);
                cnt = BIPSHO;
                dval &= (1L << BIPSHO) - 1;
        }
        dval <<= BIPSHO * 2 - outbitctr - cnt;
        Bitbuff[outshctr] |= dval >> BIPSHO;
        outbitctr += cnt;
        if (outbitctr >= BIPSHO) {
                outbitctr -= BIPSHO;
                outshctr += 1;
                if (outshctr >= BITBUFSIZE) {
                forcewrite:
                        cswab((short *)Bitbuff, outshctr);
                        p_write(1, (char *)Bitbuff, outshctr * sizeof(short));
                        outshctr = 0;
                }
                Bitbuff[outshctr] = dval;
        }
}

int main(int argc, char **argv)
{
        int     i, ix;

        setswab();
        for (i = 0; i < 256; i++)
                Mtftab[i] = i;
        /* Loop through blocks */
        do {
                Leng = p_read(0, Decbuff, BSIZE);
                if (Leng == BSIZE)
                        putbits(1L, 1);
                else
                        putbits((long)Leng, LOGSIZ + 1);
                if (Leng == 0)
                        break;
                bwt_encode();
                putbits((long)Sindex, LOGSIZ);
                for (i = 0; i < Leng; i++)
                        zr_encode(mtf_encode(Encbuff[i]));
                zr_encode(1);
        } while (Leng == BSIZE);
        /* special Code to flush output buffer */
        putbits(0L, -1);
        exit(0);
}

#else

u_char  Decbuff[BSIZE + BSIZE];
u_char  Encbuff[BSIZE];
u_char  Sorted[BSIZE];
u_short Sindex, Leng;
u_short Dchart[256];
u_short Echart[256];
u_short Link[BSIZE];

int charcomp(const void *p1, const void *p2)
{
        return *(u_char *)p1 - (int)*(u_char *)p2;
}

/* This is the fabulous Burrows-Wheeler decoder. */
void bwt_decode()
{
        register int    i, m;
        register u_char b;

        memcpy(Sorted, Encbuff, Leng);
        qsort(Sorted, Leng, sizeof(u_char), charcomp);
        for (i = 0; i < 256; i++)
                Echart[i] = 0;
        for (m = -1, i = 0; i < Leng; i++) {
                if ((b = Sorted[i]) != m)
                        Dchart[m = b] = i;
        }
        for (i = 0; i < Leng; i++) {
                b = Encbuff[i];
                Link[Dchart[b] + Echart[b]++] = i;
        }
        for (m = Sindex, i = 0; i < Leng; i++) {
                Decbuff[i] = Sorted[m];
                m = Link[m];
        }
}

u_char  Mtftab[256];

int mtf_decode(int ix)
{
        u_char  resu;

        for (resu = Mtftab[ix]; ix > 0; ix--)
                Mtftab[ix] = Mtftab[ix-1];
        return Mtftab[0] = resu;
}

int     Numzeros = -1;

int zr_decode()
{
        int     res;

        if (Numzeros-- > 0)
                return 0;
        if (Numzeros != -1) {
                if (getbits(1)) {
                        Numzeros = eg_decode();
                        return 0;
                } else
                        Numzeros = -1;
        }
        res = (eg_decode() << 1) + 1;
        return res + getbits(1);
}

int eg_decode()
{
        int     n;

        switch (getbits(3)) {
        case 0:
                for (n = 3; getbits(1) == 0; n++)
                        ;
                return (1 << n) + getbits(n) - 1;
        case 1:
                return 3 + getbits(2);
        case 2:
                return 1;
        case 3:
                return 2;
        case 4: case 5: case 6: case 7:
                ungetbits(2);
                return 0;
        }
}

long getbits(int cnt)
{
        long    result;
        int     x;

        if (cnt > BIPSHO) {
                result = getbits(cnt - BIPSHO) << BIPSHO;
                return result | getbits(BIPSHO);
        } else if (cnt <= inbitrem) {
                result = Bitbuff[inshctr] >> inbitrem - cnt;
                inbitrem -= cnt;
        } else {
                result = (long)Bitbuff[inshctr] << cnt - inbitrem;
                if (++inshctr >= BITBUFSIZE + UNDOBUF) {
                        for (x = 0; x < UNDOBUF; x++)
                                Bitbuff[x] = Bitbuff[BITBUFSIZE + x];
                        p_read(0, (char *)(Bitbuff + UNDOBUF),
                                (inshctr - UNDOBUF) * sizeof(short));
                        /* We assume the input file is valid;
                         * Thus no need to check its length!
                         */
                        cswab((short *)Bitbuff + UNDOBUF,
                                inshctr - UNDOBUF);
                        inshctr = UNDOBUF;
                }
                result |= Bitbuff[inshctr] >> BIPSHO - cnt + inbitrem;
                inbitrem -= cnt - BIPSHO;
        }
        return result & (1L << cnt) - 1;
}

int main(int argc, char **argv)
{
        int     i;

        setswab();
        for (i = 0; i < 256; i++)
                Mtftab[i] = i;
        /* Loop through blocks */
        do {
                Leng = getbits(1) ? BSIZE : getbits(LOGSIZ);
                if (Leng == 0)
                        break;
                Sindex = getbits(LOGSIZ);
                for (i = 0; i < Leng; i++)
                        Encbuff[i] = mtf_decode(zr_decode());
                zr_decode();
                bwt_decode();
                p_write(1, Decbuff, Leng);
        } while (Leng == BSIZE);
        exit(0);
}
#endif