#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

int main() {
  pid_t pid, sid;

  int status;

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

  if ((chdir(".")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

//Soal 5 Bagian A
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  int a = 1;
  DIR *sip;

  char waktu[30];
  char folder[50]="/home/tieria21/modul2/log/";
  snprintf(waktu, sizeof waktu, "%02d:%02d:%04d-%02d:%02d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,tm.tm_hour,tm.tm_min);
  strcat(folder,waktu);

  if(fork()==0){
    execlp("mkdir","mkdir","-p",folder,NULL);
  }
  
  else{
    while(wait(&status)>0);
  }

  while(1) {
    // main program here
    sip = opendir(folder);

    if(a>=2 || !sip){
    a = 1;
    t = time(NULL);
    tm = *localtime(&t);
    
    memset(folder,0,sizeof(folder));
    strcpy(folder, "/home/tieria21/modul2/log/");
    snprintf(waktu, sizeof waktu, "%02d:%02d:%04d-%02d:%02d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,tm.tm_hour,tm.tm_min);
    strcat(folder,waktu);
    
    if(!fork())
    {
      execlp("mkdir","mkdir","-p",folder,NULL);
    }
    else
    {
      while(wait(&status)>0);
    }  
  }
  
    if(fork()==0){
      char log[30];
      snprintf(log, sizeof log, "/log%d.log", a);
      strcat(folder, log);
      execlp("cp", "cp", "/var/log/syslog", folder, NULL);
    }
    closedir(sip);
    
    a++;

    sleep(60);
  } exit(EXIT_SUCCESS);
}