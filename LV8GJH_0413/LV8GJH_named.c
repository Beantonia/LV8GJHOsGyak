#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int fd, ret, cpid;
    char buf[32];

    buf[0]=0;

        ret=mkfifo("LV8GJH",00666);	// fifo letrehozas
        if (ret == -1) {
	    perror("mkfifo()");
	    exit(-1);
        }

        cpid = fork();
        if (cpid == -1) {
        perror("fork");
        exit(-1);
        }


     if (cpid == 0) {    // gyerek
	   printf("%d: <-- gyerek PID \n",getpid());

        fd=open("LV8GJH",O_RDWR);	//fifo megnyitás
        if (fd == -1) {
	    perror("open() hiba!");
	    exit(-1);
        }

        strcpy(buf,"Berecz Antónia\0");
        printf("Fifo tartalma: %s:%d\n",buf,strlen(buf));
        write(fd,buf,strlen(buf)); // fifoba írás

        close(fd);

   	   exit(0);

     } else {	// szulo
	   printf("%d: <-- szulo PID \n",getpid());

        fd=open("LV8GJH",O_RDONLY);	//fifo megnyitás
        if (fd == -1) {
	    perror("open() hiba!");
	    exit(-1);
        }

        ret=read(fd,buf,32);
        printf("read() olvasott %d byteot, ami a kovetkezo: %s\n",ret,buf);

        close(fd);

        unlink("LV8GJH");

        wait(NULL);

        exit(0);
     }
}
