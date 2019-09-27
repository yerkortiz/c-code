#include <stdio.h>
#include <unistd.h>
int main() {
    char *name[] = {
        "/bin/bash",
        "-c",
        "echo 'Hello World'",
        NULL
    };
    execvp(name[0], name);
    return 0;
}