#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

void p(void) {
	char buff[76];
	uint unaff_retaddr;

	fflush(stdout);
	gets(buff);
	if ((unaff_retaddr & 0) == 0) {
		printf("(%p)\n", unaff_retaddr);
		/* WARNING: Subroutine does not return */
		_exit(1);
	}
	puts(buff);
	strdup(buff);
	return;
}

void main(void) {
	p();
	return;
}
