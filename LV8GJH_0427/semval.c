#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 20010606
#define PERM 00666

int main() {

        int 	id;
        int ertek;

	if ((id = semget(KEY, 1, 0)) < 0) {
		perror(" Már nem létezik a szemafor. ");
		exit(-1);
	}

    if ((ertek = semctl(id, 0, GETVAL)) < 0) {
		perror(" Nem lehetett lekérdezni az értékét. ");
	} else {
		printf(" Kész és a szemafor értéke %d. ", ertek);
	}


	exit(0);
}
