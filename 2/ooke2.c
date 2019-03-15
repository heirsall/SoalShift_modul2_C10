#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here

    char *tempat = "/home/tieria21/hatiku/elen.ku";
    
    stat(tempat, &elen);

    struct stat elen;
    struct x *a;
    struct y *b;

    a = getpwuid(elen.st_uid);
    b = getgrgid(elen.st_gid);

    char perm[]="0777";
    int c;

    c = strtol(perm,0,8);    
    chmod(tempat, c);

    if(strcmp(own->pw_name, "www-data")==0 && strcmp(grp->gr_name, "www-data")==0) 
        remove(tempat);

    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
