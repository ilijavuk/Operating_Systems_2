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
    if(argc < 1)
        exit(0);
    struct my_msgbuf buf;
    int msqid;
    key_t key;
    char text[]="tekst";
    strcpy(text,argv[1]);
    cout << text << endl;

    key = 12345;
    int id = getuid();
    
    if ((msqid = msgget(key, 0600 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    /*
       
    memcpy(buf.mtext, text, strlen(text)+1);
    buf.mtype = 1;
    
    if (msgsnd(msqid, (struct msgbuf *)&buf, strlen(text)+1, 0) == -1)
            perror("msgsnd");
    cout << id << " završio slanje " <<endl;
    */

        memcpy(buf.mtext, text, strlen(text)+1);
        buf.mtype = 1;
	//for(int i = 0; i < strlen(text)-1; i++){
        //buf.mtext[0] = text[i];;
        
     //   if (msgsnd(msqid, (struct msgbuf *)&buf, strlen(text)+1, 0) == -1)
       //     perror("msgsnd");
	//}
    
  
    cout << id << " završio slanje " <<endl;
    return 0;
}


