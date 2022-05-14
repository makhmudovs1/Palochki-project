#include "senpal.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#define PERM 0666
int n = 11;
Sender::Sender(const char *s, char A){
	pid = getpid();
	if ((key = ftok( s, A ) ) < 0 ){
		cout <<"Can't get key\n";
		exit(1);
	}
	if( ( mesid = msgget(key, PERM|IPC_CREAT ) ) < 0 ){
		cout << "Can't create message's queue\n";
		exit(1);
	}
	//cout << "created queue " << mesid << "\n";
};

Sender::Sender(const char *s, char A, int a){
	pid = getpid();
	if ( ( key = ftok(s, A ) ) < 0 ){
		cout << "Can't get key\n";
		exit(1);
	}
	if( ( mesid = msgget( key, 0 ) ) < 0 ){
		cout << "Can't get message's queue\n";
		exit(1);
	}
};
Sender::~Sender(){
	pid = -1;
	mesid = -1;
	key = -1;
};
unsigned char Sender::read(void* ms, long long type){
	
	/**Mess *m = (Mess *)ms;
	m->type = type;**/
	Mess a;
	char *m = (char *)ms;
	a.type = type;
	int n = msgrcv( mesid, &a, sizeof(Mess), type, 0);
	a.buf[n] = '\0';
	int len = sprintf(m, "%s", a.buf);
	if (len > 0)
		return 0;
	return 1;
// для печати - 0 в конце
	
};
unsigned char Sender::send(void *ms, int len, long long type){
	Mess a;
	char *m = (char *)ms;
	int lng = sprintf(a.buf, "%s", m);
	a.buf[lng] = '\0';
	a.type = type;
	//cout << a.buf << "ap\n";
	if ( msgsnd( mesid, (void*)&a, len, 0) < 0 ){
		cout << "Can't write message\n";
		return 1;
	}
	return 0;
};
void Sender::delQueue(){
	if( msgctl( mesid, IPC_RMID, 0 ) < 0 ){
		cout << "Can't delete queue\n";
		exit(1);
	}
};
int sti(char *a){
	const char *b = "0123456789";
	int i = 0, s = 0;
	while(a[i] != '\0'){
		for (int j = 0; j <= 9; j++){
			if (a[i] == b[j]){
				s*=10;
				s+=j;
				j = 10;
			}
		}
		i++;
	}
	return s;
}
void its(int a, char *b){
	const char *c = "0123456789";
	int i = 0, k = a;
	while(k > 0){
		i++;
		k/=10;
	}
	while(a > 0){
		b[i - k - 1] = c[a % 10];
		a/=10;
		k++;
	}
	b[k] = '\0';
}