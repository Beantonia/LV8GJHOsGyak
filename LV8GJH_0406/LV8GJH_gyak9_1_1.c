#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


void do_nothing(int pid);


int main(void) {
    printf("PID = %d\n",getpid());
    signal(SIGTERM,do_nothing);
    printf("Varakozas\n");
    pause();
    printf("Megjott az alarm\n");
    return 0;
}
void do_nothing(int pid)
{
    printf("do_nothing() fut");
}
