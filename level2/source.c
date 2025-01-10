#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void p(void) {
	uint unaff_retaddr;
	char buff[76];

	fflush(stdout);
	gets(buff);
	if ((unaff_retaddr & 0) == 0) {
		printf("(%p)\n", unaff_retaddr);
		/* WARNING: Subroutine does not return */
		exit(1);
	}
	puts(buff);
	strdup(buff);
	return;
}

void main(void) {
	p();
	return;
}
