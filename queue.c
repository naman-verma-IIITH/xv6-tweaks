#if SCHEDULER == MLFQ

#include "param.h"


#define NUM_Q 5

int q_front[NUM_Q];
int q_rear[NUM_Q];
int q_size[NUM_Q];
int q_pid[NUM_Q][NPROC];



void qinit(){
    int i=0;
    for(i=0;i<NUM_Q;i++){
        q_front[i]=0;
        q_rear[i]=NPROC-1;
        q_size[i]=0;
        int j=0;
        for(j=0;j<NPROC;j++){
            q_pid[i][j]=-1;
        }
    }
}

int isQFull(int q){
    if(q_size[q]>=NPROC) return 1;
    return 0;
}

int isQEmpty(int q){
    if(q_size[q]<=0) return 1;
    return 0;
}

int push(int q, int pid){
    if(isQFull(q)) return -1;

    q_rear[q] = (q_rear[q]+1)%NPROC;
    q_pid[q][q_rear[q]] = pid;
    q_size[q]++;
    return pid;
}

int pop(int q){
    if(isQEmpty(q)) return -1;

    int pid = q_pid[q][q_front[q]];
    q_pid[q][q_front[q]] = -1;
    q_front[q] = (q_front[q]+1)%NPROC;
    q_size[q]--;
    return pid;
}

int removeq(int q, int pid){
    if(isQEmpty(q)) return -1;

    int i = q_front[q];

    while(pid != q_pid[q][i]){
        i=(i+1)%NPROC;
        if(i==q_front[q])return -1;
    }
    while(i!=q_rear[q]){
        q_pid[q][i]=q_pid[q][(i+1)%NPROC];
        i=(i+1)%NPROC;
    }
    q_pid[q][q_rear[q]] = -1;
    q_rear[q]=(q_rear[q]+NPROC-1)%NPROC;
    q_size[q]--;
    return pid;
}

int front(int q){
    if(isQEmpty(q)) return -1;

    return q_pid[q][q_front[q]];
}

int rear(int q){
    if(isQEmpty(q)) return -1;

    return q_pid[q][q_rear[q]];
}

#endif