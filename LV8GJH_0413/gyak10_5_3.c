#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 20010606

int main()
{
	int shmid;
	key_t key;
	int size=512;
	int shmflg;
	int rtn;

	struct shmid_ds shmid_ds, *buf;
	buf = &shmid_ds;

	key = SHMKEY;

	int msg = 0;

	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   printf("Nincs meg szegmens! Keszitsuk el!\n");
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	} else printf("Van mar ilyen shm szegmens!\n");

	printf("\nAz shm szegmens azonositoja %d: \n", shmid);

	do{
    printf("\n\n");
	printf("Mit szeretne valasztani?!\n");
	printf("1 - Státusz lekérdezése\n");
	printf("2 - Osztott memória megszüntetése\n");
	printf("3 - Kilépés\n");

	scanf("%d", &msg);

	if(msg == 1){

        rtn = shmctl(shmid, IPC_STAT, buf);
		printf("Szegmens merete: %d\n",buf->shm_segsz);
		printf("Utolso shmop()-os processz pid-je: %d\n",buf->shm_lpid);
	}
    else if(msg == 2){

        rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("Szegmens torolve. Hibakod: %d\n", rtn);
    }

	else {exit(0);}

	}while(1);
}
