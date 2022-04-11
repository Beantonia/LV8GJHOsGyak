#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


int main(int argc, char **argv) {
    int pid;
    if(argc<1)
    {
        perror("Nincs kinek");
    }

    pid = atoi(argv[1]);
    kill(pid,SIGTERM);
}
