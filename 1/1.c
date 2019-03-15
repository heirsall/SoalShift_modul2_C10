
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/home/zahrul/modul2/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
   DIR *folder;
    struct dirent *dir;
    folder = opendir("/home/zahrul/modul2/");

    if (folder)
    {
        while ((dir = readdir(folder)) != NULL)
        {
	    int len = (int) strlen(dir->d_name);

	    char *name = dir->d_name;

	   	if(name[len-1] == 'g')
        	if(name[len-2] == 'n' )
		if(name[len-3] == 'p' )
		if(name[len-4] == '.'){
	    	
		char nFile[1024];

		strcpy(nFile, "/home/zahrul/modul2/gambar/");

		strcat(nFile, name);
		
		len = (int)strlen(nFile);

		nFile[len-4] = '\0';
		
		strcat(nFile, "_grey.png");

						if(fork()==0){

		 execlp("mv", "mv",name,nFile,(char*) NULL); 


		}
	    }
        }
        closedir(folder);
    }
 	sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
