#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include <errno.h>
using namespace std;

int main(int argc, char* argv[], char *envp[]){
	int key = getuid();
	ostringstream ss;
    ss << key;
	string temp_str = ss.str();
	const char* key_in_string = temp_str.c_str();

	setenv("MSG_KEY", key_in_string, true);

	msgget(key, 0600 | IPC_CREAT);

	
    struct msqid_ds tmpbuf;
	msgctl(key, IPC_STAT, &tmpbuf); 
	tmpbuf.msg_qbytes = 5;
	msgctl(key, IPC_SET, &tmpbuf); 

	if(fork() == 0) 
		execl("./potrosac", "potrosac", NULL);

	for(int i = 1; i <= argc-1; i+=2){
		switch (fork()) {
			case -1:
				cout << "Ne mogu kreirati novi proces" << endl;
			break;
			case 0:	
				execl("./proizvodac", "proizvodac", argv[i], argv[i+1], NULL);
				if (errno != 0)
				{
					cout << "Error launching child process: " << endl;
					return 1;
				}
				exit(1);
			default: continue;
		}
	}	
	return 0;
}
