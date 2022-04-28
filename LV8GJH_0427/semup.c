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


	if ((id = semget(KEY, 1, 0)) < 0) {
		perror(" Még nem létezik a szemafor. ");
		exit(-1);
	}

	puts(" Itt fut a nem kritikus szakasz. ");

	puts("    Itt fut a kritikus szakasz. ");
	semop(id, &up, 1);

	puts(" Itt ismét nem kritikus szakasz fut. ");

	exit(0);
}
