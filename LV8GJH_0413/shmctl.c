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

	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Az shmget() system-call sikertelen!\n");
	    exit(-1);
	}

		rtn = shmctl(shmid, IPC_STAT, buf);
		printf("Szegmens merete: %d\n",buf->shm_segsz);
		printf("Utolso shmop()-os processz pid-je: %d\n",buf->shm_lpid);

	exit(0);

}
