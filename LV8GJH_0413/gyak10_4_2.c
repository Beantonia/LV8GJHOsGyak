#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define MSGKEY 20010606

struct msgbuf1 {
	long mtype;
	char mtext[512];
} recvbuf, *msgp;

struct msqid_ds ds, *buf;

int main()
{
	int msgid;
	key_t key;
	int mtype, msgflg;
	int ret, msgsz;
    int msg = 0;

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror("msgget() nem sikerult");
                exit(-1);
        }
	printf("Az msgid: %d\n",msgid);


    do{
    printf("\n\n");
	printf("Mit szeretne valasztani?!\n");
	printf("1 - Üzenetek darabszamanak kiirasa!\n");
	printf("2 - 1 üzenet kiolvasása!\n");
	printf("3 - Összes üzenet kiolvasása!\n");
	printf("4 - Üzenetsor megszüntetése!\n");
    printf("5 - Kilepes\n\n");

	scanf("%d", &msg);

	if (msg == 1){

        msgp = &recvbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;

        ret = msgctl(msgid, IPC_STAT, buf);
        printf("Az uzenetek szama az uzenetsorban: %d\n", buf->msg_qnum);

	}
    else if (msg == 2){

        msgp = &recvbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;

        ret = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
		printf("msgrcv() visszaadta: %d, a kapott uzenet: %s\n",ret, msgp->mtext);
		ret = msgctl(msgid, IPC_STAT, buf);
    }
    else if (msg == 3){

        msgp = &recvbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;
        while (buf->msg_qnum) {

		ret = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
		printf("msgrcv() visszaadta: %d, a kapott uzenet: %s\n",ret, msgp->mtext);
		ret = msgctl(msgid, IPC_STAT, buf);
        }
    }
    else if (msg == 4){

        msgp = &recvbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;

        ret = msgctl(msgid, IPC_RMID, NULL);
        printf ("\n Visszatert: %d\n", ret);

    }
    else {exit(0);}

	}
        while(1);
}
