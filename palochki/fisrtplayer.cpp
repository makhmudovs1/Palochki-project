#include <iostream>
#include "senpal.h"
int main() {
	Sender a("pal", 'A');
	int k, n = 11, ch = 2, l1, l2, pid = getpid();
	//char b[100];
	char *b = (char *)malloc(100 * sizeof(char));
	unsigned char e, f;
	its(pid, b);
	l1 = 0;
	while(b[l1] != '\0')
			l1++;
	a.send(b, l1, 1);
	a.read(b, 2);
	l2 = sti(b);
	free(b);
	//////
	//////
	//cout << "Start\n";
	while(n >= 0){
		char *b = (char *)malloc(100 * sizeof(char));
		cin >> k;
		n-=k;
		if (n == 0){
			ch = 2;
			break;
		}
		its(k, b);
		l1 = 0;
		while(k > 0){
			l1++;
			k/=10;
		}
		a.send(b, l1, 1);
		a.read(b, 2);
		k = sti(b);
		cout << "My pid is " << l2 << " there is " << n << " sticks on the table and I take " << k << "\n";
		n -= k;
		if (!n){
			ch = 1;
			break;
		}
		free(b);
	}
	cout << ch << "\n";
	if (ch == 2){
		cout << "You win!!!\n";
		a.delQueue();
	}
	else {
		cout << "You lose:(\n";
		a.delQueue();
	}
	return 0;
}