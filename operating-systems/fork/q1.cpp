#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main(){
pid_t pid = fork();

cout<<"hello"<<endl;

return 0;
}