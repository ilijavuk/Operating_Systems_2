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
    char mtext[200];
};

int main(int argc, char* argv[], char *envp[])
{
	char *val = getenv("MSG_KEY");
    if (val!=NULL)
	    cout << "[S] pronasao " << val << endl;

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

   for(int i = 0; true; i++) {
       if(argv[1][i] == '\0'){
            buf.mtext[0] = ' ';
            if (msgsnd(msqid, (struct msgbuf *)&buf, 1, 0) == -1)
                perror("msgsnd");
            break;
        }
        buf.mtext[0] = argv[1][i];
        buf.mtype = atoi(argv[2]);
        
        if (msgsnd(msqid, (struct msgbuf *)&buf, 1, 0) == -1)
            perror("msgsnd");
    }
   
    return 0;
}


