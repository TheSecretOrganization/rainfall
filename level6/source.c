#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void n() {
	system("/bin/cat /home/user/level7/.pass");
	return;
}

void m() {
	puts("Nope");
	return;
}

int main(int ac,char **av) {
	char *str;
	void (*func)();

	str = (char *)malloc(64);
	func = malloc(4);
	func = &m;
	strcpy(str, av[1]);
	func();
	return 0;
}
