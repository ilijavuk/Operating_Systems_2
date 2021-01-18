#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <iostream>
using namespace std;

struct my_msgbuf {
    long mtype;
    char mtext[1];
};

int msqid;

void retreat(int failure) 
{
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    exit(0);
}

int main(int argc, char* argv[], char *envp[])
{
	char *val = getenv("MSG_KEY");
    if (val!=NULL)
	    printf("[R] pronasao %s\n", val);
    else 
        exit(0);

    struct my_msgbuf buf;
    key_t key;

    key = atoi(val);
    
    if ((msqid = msgget(key, 0600 | IPC_CREAT)) == -1) { 
        perror("msgget");
        exit(1);
    }
    
    sigset(SIGINT, retreat);
    
    for(;;) { 
        if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf)-sizeof(long), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        cout << "[Potrosac] primio: " << buf.mtext << " od " << buf.mtype << endl;
    }

    return 0;
}
