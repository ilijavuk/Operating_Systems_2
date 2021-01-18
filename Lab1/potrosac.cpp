#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
using namespace std;

struct my_msgbuf {
    long mtype;
    char mtext[1];
};

struct data {
    long type;
    string value;
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

    data strings[20];
    for(int i = 0; i < 20; i++){
        strings[i].type = -1;
        strings[i].value = "";
    }

    struct my_msgbuf buf;
    key_t key;

    key = atoi(val);
    
    if ((msqid = msgget(key, 0600 | IPC_CREAT)) == -1) { 
        perror("msgget");
        exit(1);
    }
    
    sigset(SIGINT, retreat);
    int counter = 0;
    for(;;) { 
        if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf)-sizeof(long), 0, IPC_NOWAIT) == -1) {
            if (errno == ENOMSG)
            {
                counter++;
                sleep(1);
                if(counter == 10)
                    break;
            }
            else
            {
                perror("msgrcv");
                exit(1);
            }
        }
        else{
            counter = 0;
            if(buf.mtext[0] != ' '){
                int i = 0;
                for(i; i < 20; i++){
                    if(strings[i].type == -1 || strings[i].type == buf.mtype)
                        break;
                }
                strings[i].type = buf.mtype;
                strings[i].value += buf.mtext[0];

                cout << "[Potrosac] primio: " << buf.mtext[0] << " od " << buf.mtype << endl;
            }
            else{
            for(int i = 0; i < 20; i++){
                if(strings[i].type == buf.mtype){
                        cout << strings[i].value << endl;
                        break;
                }
            }
            }  
        } 
    }
    cout << "[Potrosac] zavrsavam" <<endl;
    
    msgctl(key, IPC_RMID, NULL);

    return 0;
}
