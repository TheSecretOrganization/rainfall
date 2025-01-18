#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void p(char *param_1, char *param_2) {
	char *str;
	char buffer [4104];

	puts(param_2);
	read(0, buffer, 4096);
	str = strchr(buffer, '\n');
	*str = '\0';
	strncpy(param_1, buffer, 20);
	return;
}

void pp(char *param_1) {
	char cVar1;
	uint len;
	char input1 [20];
	char input2 [20];

	p(input1, " - ");
	p(input2, " - ");
	strcpy(param_1, input1);
	len = strlen(param_1);
	param_1[len] = 0x20; // ' '
	strcat(param_1, input2);
	return;
}

int main(void) {
	char buffer[54];

	pp(buffer);
	puts(buffer);
	return 0;
}
