#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


#define MSGKEY 20010606

struct msgbuf1 {
	long mtype;
	char mtext[512];
} sendbuf, *msgp;

main()
{
	int msgid;
	key_t key;
	int msgflg;
	int ret, msgsz;

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget(key, msgflg);
	char msg[512];

 	if (msgid == -1) {
                perror(": msgget() nem sikerult!");
                exit(-1);
        }
	printf("Az msgid letrejott: %d, %x\n", msgid,msgid);

	do{

	printf("Adja meg a szöveget!");
	scanf("%[^\n]", msg);
    while(getchar() != '\n');

	if (strcmp("exit",msg) == 0){exit(0);}
    else{

        msgp        = &sendbuf;
        msgp->mtype = 1;
        strcpy(msgp->mtext , msg);
        msgsz       = strlen(msgp->mtext) + 1;

        ret = msgsnd(msgid,(struct msgbuf *)msgp, msgsz, msgflg);

        printf("A msgsnd() visszaadott: %d\n", ret);
        printf("A kikuldott uzenet: %s\n", msgp->mtext);

        }
	}
	while(1);

	exit(0);
}
