#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;

struct my_msgbuf {
    long mtype;
    char mtext[1];
};

int main(int argc, char* argv[], char *envp[])
{
	char *val = getenv("MSG_KEY");
    if (val!=NULL)
	    cout << "[S] pronasao " << val << endl;
    else
        exit(0);

    if(argc < 3){
        cout << "Nedovoljno argumenata " << endl;
        exit(0);
    }

    struct my_msgbuf buf;
    int msqid;
    key_t key;
    key = atoi(val);
    cout << "[proizvodac] id: " << argv[2] << endl; 
    
    if ((msqid = msgget(key, 0600 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    struct msqid_ds tmpbuf;
	msgctl(msqid, IPC_STAT, &tmpbuf); 
	tmpbuf.msg_qbytes = 5;
	msgctl(msqid, IPC_SET, &tmpbuf); 

    buf.mtype = atoi(argv[2]);
    for(int i = 0; argv[1][i] != '\0'; i++) {
        buf.mtext[0] = argv[1][i];
        if (msgsnd(msqid, (struct msgbuf *)&buf, 1, 0) == -1)
            perror("msgsnd");
    }
    buf.mtext[0] = ' ';
    if (msgsnd(msqid, (struct msgbuf *)&buf, 1, 0) == -1)
        perror("msgsnd");
    cout << "[Proizvodac] " << buf.mtype << " završio s radom " << endl; 
   
    return 0;
}


