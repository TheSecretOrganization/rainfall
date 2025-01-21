#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
    int n;
	char str[40];

	n = atoi(argv[1]);
    if (n > 9)
        return 1;

    memcpy(str, argv[2], n * 4);
    if (n == 0x574f4c46)
        execl("/bin/sh", "sh", NULL);

    return 0;
}
