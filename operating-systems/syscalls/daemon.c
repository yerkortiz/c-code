/*
 * DAEMON CREATION
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char* argv[])
{
    FILE *fp= NULL;
    pid_t process_id = 0;
    pid_t sid = 0;
    process_id = fork();
    if (process_id < 0) {
        perror("FORK ERROR\n");
        exit(EXIT_FAILURE);
    } else if (process_id > 0) {
        printf("process_id of child process %d \n", process_id);
        exit(EXIT_SUCCESS);
    }
    umask(0); // file mode
    sid = setsid(); // se convierte en el root de un grupo de procesos.
    if(sid < 0) {
        perror("SID ERROR\n");
        exit(EXIT_FAILURE);
    }
    //chdir("/");
    close(STDIN_FILENO); 
    close(STDOUT_FILENO); 
    close(STDERR_FILENO);
    fp = fopen ("Log.txt", "w+");
    for(int i = 0; i < 8; ++i) {
        sleep(3);
        fprintf(fp, "%d\n", i);
        fflush(fp);
    }
    fprintf(fp, "DAEMON TERMINATED\n");
    fclose(fp);
    exit(EXIT_SUCCESS);
}