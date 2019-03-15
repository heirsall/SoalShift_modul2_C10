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
  int counter=1;

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

  if ((chdir("/home/zahrul/praktikum2/4/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    char namafile[99999];    
    struct stat fstatus;
 
    time_t now;
    struct tm *now_tm;
    struct tm *now_tm2;
    int jam,detik,menit;
    int jam1,detik1,menit1;
    
	
    now = time(NULL);
    now_tm = localtime(&now);
    detik = now_tm->tm_sec;
    menit = now_tm->tm_min;
    jam = now_tm->tm_hour;

    stat("makan_enak.txt",&fstatus);

    now_tm2 = localtime(&fstatus.st_atim.tv_sec);
    
    detik1 = now_tm2->tm_sec;
    menit1 = now_tm2->tm_min;
    jam1   = now_tm2->tm_hour;

    if(jam1==jam){
        if(menit==menit1){
            if((detik-detik1)<=30){
                
    			sprintf(namafile, "makan_sehat%d.txt", counter);
   			FILE* file_ptr = fopen(namafile, "w");
    			fclose(file_ptr);
 
                counter++;
            };
        }
        else if((((menit-menit1)*60)-detik1)<=30)
		if((((menit-menit1)*60)-detik1)>=0){
    			sprintf(namafile, "makan_sehat%d.txt", counter);
    			FILE* file_ptr = fopen(namafile, "w");
    			fclose(file_ptr);
                
		counter++;
            }
    }


    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
