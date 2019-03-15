#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <time.h>
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

  if ((chdir("/home/zahrul/praktikum2/4j/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int nomer=1;
  while(1) 
  {
	struct stat title;
    FILE *filenak;

    char folder[]="makan_enak.txt";
    
    stat(folder, &title);
    time_t wakses = title.st_atime; 
    time_t wakprogjal = time(NULL); 
    double time = difftime(wakprogjal, wakses)
    if(time)<=30) 
    {
	char wakses[100];
      sprintf(wakses, "%d.txt", nomer);

      char folder2[]="makan_sehat";
      
	strcat(folder2, wakses);
                  

      filenak = fopen(folder2, "w"); 

      fclose(filenak);
      nomer=nomer+1;
    }
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
