#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <wait.h>

void makefolder(struct tm* loc_time,char *filename){
    sprintf(filename,"%d-%d-%d_%d:%d:%d",(loc_time->tm_year)+1900,loc_time->tm_mon,loc_time->tm_mday,
        loc_time->tm_hour,loc_time->tm_min,loc_time->tm_sec);
    if(fork()==0){
        char *args[] = {"mkdir",filename,NULL};
        execv("/bin/mkdir",args);
    } else ;
}

void download(struct tm* loc_time,time_t epoch,time_t *curtime,char *filename){
    char pictname[100],source_pic[100],target_folder[150];
    sprintf(target_folder,"/home/edo/Kuliah/Sisop/SoalShiftSISOP20_modul2_E09/soal2/%s",filename);
    int pixel = (epoch%1000)+100;
    sprintf(source_pic,"https://picsum.photos/%d",pixel);
    for(int i=0;i<20;i++){
        sprintf(pictname,"%d-%d-%d_%d:%d:%d",(loc_time->tm_year)+1900,loc_time->tm_mon,loc_time->tm_mday,
            loc_time->tm_hour,loc_time->tm_min,loc_time->tm_sec);
        if(fork()==0){
            char *args[]={"wget","-O",pictname,source_pic,NULL};
            execv("/usr/bin/wget",args);
        } else {
            sleep(5);
            time(curtime);
            loc_time = localtime(curtime);
        }
    }
}

int main(){
    struct tm* loc_time;
    time_t curtime,epoch;
    char filename[100];
    int status;
    //while (1){
        time(&curtime);
        epoch = curtime;
        loc_time = localtime(&curtime);
        pid_t child_id = fork();
        if(child_id==0){
            makefolder(loc_time,filename);
        } else {
            while ((wait(&status))>0);
            download(loc_time,epoch,&curtime,filename);
            sleep(30);
        }
    //}
    
    return 0;
}