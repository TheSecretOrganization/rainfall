#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int language = 0;

int greetuser(char *user) {
    char buf[64];

    if (language == 1)
        memcpy(&buf, "\x48\x79\x76\xc3\xa4\xc3\xa4\x20\x70\xc3\xa4\x69\x76\xc3\xa4\xc3\xa4\x20", 0x12);
    else if (language == 2)
        strcpy(buf, "Goedemiddag! ");
    else if (!language)
        strncpy(buf, "Hello ", 7);

    strcat(buf, user);
    return puts(buf);
}

int main(int argc, char** argv, char** envp) {
    char buf[72];
	char *env = NULL;

	if (argc != 3)
		return 1;

	memset(buf, 0, 72);
	strncpy(buf, argv[1], 40);
	strncpy(&buf[40], argv[2], 32);
	env = getenv("LANG");
	if (env != 0) {
		if (memcmp(env, "fi", 2) == 0)
			language = 1;
		else if (memcmp(env, "nl", 2) == 0)
			language = 2;
	}

	greetuser(buf);
	return 0;
}
