#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#define EXIT_PROGRAM return 0;
#define EXIT_SUCCESS exit(0);
#define EXIT_FAILURE exit(1);
void parentPID(void);
void ownPID(void);