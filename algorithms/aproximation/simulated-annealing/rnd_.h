uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
int rndD(int a, int b)
{
    srand(rdtsc());
    return (rand() % b + a);
}
float rndF(float a, float b)
{
    srand(rdtsc());
    float scale = rand() / (float) RAND_MAX; 
    return a + scale * (b - a);
}