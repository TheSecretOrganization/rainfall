#include <stdio.h>
#include <stdlib.h>

void run() {
  fwrite("Good... Wait what?\n", 1, 19, stdout);
  system("/bin/sh");
  return;
}

void main() {
  char buff[76];

  gets(buff);
  return;
}
