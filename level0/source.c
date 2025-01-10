#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char** av) {
  int nb;
  char* args[2];
  int local_1c;
  uid_t uid;
  gid_t gid;

  nb = atoi(av[1]);
  if (nb == 423) {
    args[0] = strdup("/bin/sh");
    args[1] = NULL;

    gid = getegid();
    uid = geteuid();
    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);
    execv("/bin/sh",args);
  }
  else {
    fwrite("No !\n",1,5,(FILE *)stderr);
  }
  return 0;
}
