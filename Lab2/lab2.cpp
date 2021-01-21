#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <cstring>
#include <wait.h>
#include <fstream>
using namespace std;

#define CITANJE 0
#define PISANJE 1

int main(void) {
    fstream dat;
    dat.open("podatci.txt", ios::in);
    int broj;
    //srand(time(NULL));

    int pipe1[2];
    int pipe2[2];
    char rezultat[20];
    char unos[50];

    if(pipe(pipe1) == -1 || pipe(pipe2) == -1)
        exit(1);

    switch(fork()){
        case -1: {
            cout << "Ne mogu kreirati novi proces" << endl;
            exit(0);
        }
        case 0:{
            close(pipe1[CITANJE]);
            close(pipe2[PISANJE]);
            for(int i = 0; i < 3; i++){
                dat >> broj;
                //broj = rand()%11;
                cout << broj << " = ";
                cin >> unos;
                strcat(unos, "\n");

                write(pipe1[PISANJE], unos, strlen(unos));
                if(read(pipe2[CITANJE], rezultat, sizeof(rezultat)) != -1) {
                    int tmp_rez = atoi(rezultat);
                    if(tmp_rez!=0){
                        if(tmp_rez == broj){
                            cout << "Točno!" << endl;
                        }
                        else{
                            cout << "Netočno " << endl;
                        }
                    }
                    else{
                        cout << "Pogrešan unos" << endl;
                    }
                }
            }
            close(pipe1[PISANJE]);
            close(pipe2[CITANJE]);
            
            break;
        }

        default: {
            close(pipe1[PISANJE]);
            close(pipe2[CITANJE]);
            dup2(pipe1[CITANJE], 0);
            dup2(pipe2[PISANJE], 1);
            dup2(pipe2[PISANJE], 2);
            close(pipe1[CITANJE]);
            close(pipe2[PISANJE]);
            execlp("bc", "bc", NULL);
        }
    }   
    
    wait(NULL);   
        
    return 0;
}