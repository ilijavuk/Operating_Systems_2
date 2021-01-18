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
			default:
				wait(NULL);
		}
	}	
	execl("./potrosac", "potrosac", NULL);
}

void proizvodac(string niz, int id){
	/*
	for(int i = 0; i < niz.length(); i++){
		posalji_poruku(niz[i],id);
	}
	posalji_poruku(NULL, id);
	*/
}

void potrosac(){/*
	string poruka = "";
	while(IMA PORUKA){
		let string nova_poruka = procitaj_poruku();
		if(nova_poruka == NULL){
			cout << "Proces " << id << " " << poruka << endl;
		}
	}	
	*/
}