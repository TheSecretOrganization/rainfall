#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
	FILE *f = fopen("/home/user/end/.pass", "r");
	char buffer[132];

	memset(buffer, 0, 132);
	if ((!f) || (ac != 2))
		return(-1);

	fread(buffer, 1, 66, f);
	buffer[65] = 0;
	buffer[atoi(av[1])] = 0;
	fread(&buffer[66], 1, 65, f);
	fclose(f);

	if (strcmp(buffer, av[1]) == 0)
		execl("/bin/sh", "sh", NULL);
	else
		puts(&buffer[66]);

	return (0);
}
