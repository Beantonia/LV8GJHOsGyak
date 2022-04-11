#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    int fd, ret;
    char buf[32];
    buf[0] = 0;

    fd = open("LV8GJH.txt", O_RDWR);

    if(fd == -1)
    {
        perror("open() hiba");
        exit(-1);
    }

    ret = read(fd,buf,32);
    printf("read() olvasott %d byteot, ami a következő %s\n",ret,buf);
    strcpy(buf,"Neptun");

    ret = lseek(fd,0,SEEK_SET);
    printf("lseek() mondja: %d\n",ret);

    ret = write(fd,buf,6);
    printf("write() mondja: %d\n",ret);

    return 0;

}
