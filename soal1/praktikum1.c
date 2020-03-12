#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int isNumber(char number[])
{
  int i = 0;

    //checking for negative numbers
  for (; number[i] != '\0'; i++)
  {
    //if (number[i] > '9' || number[i] < '0')
    if (!isdigit(number[i]))
      return 0;
    }
    return 1;
}

int main(int argc,char* argv[]) {
  struct tm* loc_time;
  time_t curtime;
  int detik=61,menit=61,jam=25;

  if(*argv[1]=='*'){
    detik = -1;
  } else if (isNumber(argv[1])) {
    detik = atoi(argv[1]);
  }
    
  if(*argv[2]=='*'){
    menit = -1;
  } else if (isNumber(argv[2])){
    menit = atoi(argv[2]);
  }
    
  if (*argv[3]=='*'){
    jam = -1;
  } else if (isNumber(argv[3])){
    jam = atoi(argv[3]);
  }
  if(detik>59 || menit>59 || jam > 23 || jam<-1 || menit<-1 || detik<-1){
    detik=61;menit=61;jam=25;
  }
  if(detik==61 || menit==61 || jam==25){
    printf("Arguments passed were wrong\n");
    return 0;
  }
  printf("%d->%d->%d->%s",detik,menit,jam,argv[4]);

  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
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

  while (1) {
    // Tulis program kalian di sini
    time(&curtime);
    loc_time = localtime(&curtime);
    
    if(detik==-1 && menit==-1 && jam==-1){        
      if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
    }
    if(detik==-1 && menit==-1 && jam!=-1){
      if(loc_time->tm_hour==jam){
        if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
      }
    }
    if(detik==-1 && menit!=-1 && jam==-1){
      if(loc_time->tm_min==menit){
        if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
      }
    }
    if (detik==-1 && menit!=-1 && jam!=-1){
      if(loc_time->tm_hour==jam && loc_time->tm_min==menit){
        if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
      }
    }
    if (detik!=-1 && menit==-1 && jam==-1){
      if(loc_time->tm_sec==detik){
        if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
      }
    }
    if (detik!=-1 && menit==-1 && jam!=-1){
      if(loc_time->tm_hour==jam && loc_time->tm_sec==detik){
        if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
      }
    }
    if(detik!=-1 && menit!=-1 && jam==-1){
      if(loc_time->tm_min==menit){
        if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
      }
    }
    if (detik!=-1 && menit!=-1 && jam!=-1){
      if(loc_time->tm_min==menit && loc_time->tm_hour==jam && loc_time->tm_sec==detik){
        if(fork()==0){
                char *args[] = {"bash",argv[4],NULL};
                execv("/bin/bash",args);
            } else ;
      }
    }

    sleep(1);
  }
}