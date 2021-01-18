#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
using namespace std;


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


int main(int argc, char* argv[], char *envp[]){
	for(int i = 1; i < argc; i++){
		switch (fork()) {
			case -1:
				cout << "Ne mogu kreirati novi proces" << endl;
			break;
			case 0:
				execl("./proizvodac",argv[i],NULL);
				exit(1);
			default:
				wait(NULL);
		}
	}	
}
