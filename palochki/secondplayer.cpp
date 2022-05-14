#include <iostream>
#include "senpal.h"
int main() {
	Sender a("pal", 'A', 5);
	int n = 11, k, ch = 1, l1, l2, pid = getpid();
	char *d = (char *)malloc(100 * sizeof(char));
	unsigned char e, f;
	a.read(d, 1);
	l2 = sti(d);
	its(pid, d);
	l1 = 0;
	while(d[l1] != '\0')
			l1++;
	a.send(d, l1, 2);
	free(d);
	//////
	//////
	//cout << "Start\n";
	while(n >= 0){
		//k = sti(&d[0]);
		char *b = (char *)malloc(100 * sizeof(char));
		e = a.read(d, 1);
		k = sti(d);
		cout << "My pid is " << l2 << " there is " << n << " sticks on the table and I take " << d[0] << "\n";
		n-=k;
		if (n == 0){
			ch = 2;
			break;
		}
		cin >> k;
		n-=k;
		if (n == 0){
			ch = 1;
			break;
		}
		its(k, d);
		l1 = 0;
		while(d[l1] != '\0')
			l1++;
		a.send(d, l1, 2);
		free(d);
	}
	cout << ch  << "\n";
	if (ch == 1){
		cout << "You win!!!\n";
		a.delQueue();
	}
	else{
		cout << "You lose:(\n";
	}
	return 0;
}