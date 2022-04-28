#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 20010606
#define PERM 00666

int main() {

int 	id;
struct sembuf up  =  {0,  1, 0};
struct sembuf down = {0, -1, 0};

	if ((id = semget(KEY, 1, 0)) < 0) {
		perror("A szemafor nem létezik!");
		exit(-1);
	}

	printf("A szemafor létezik!\n\n");

	int i = 0;

	for(i = 0; i<5; i++){

	semop(id, &down, 1);

	sleep(2);
	printf("PID = %d\n", getpid());

	semop(id, &up, 1);

	}

	exit(0);
}
