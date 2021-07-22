#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv){
    if(argc < 2){
        printf(2, "Invalid number of arguments!\n");
        exit();
    }
    int forkReturn = fork();
    if(forkReturn<0){
        printf(2, "Fork didn't work!\n");
        exit();
    }
    if(forkReturn > 0){
        int wtime, rtime;
        if(waitx(&wtime, &rtime)<0){
            printf(2,"waitx didn't work!\n");
            exit();
        }
        printf(2,"Waiting ticks = %d & Running ticks = %d\n",wtime,rtime);
        exit();
    }
    else{
        if(exec(argv[1],argv+1)<0){
            printf(2, "exec didn't work!\n");
            exit();
        }
        exit();
    }
}