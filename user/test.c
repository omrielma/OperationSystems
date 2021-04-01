#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/perf.h"

// System call numbers
#define SYS_fork    1
#define SYS_exit    2
#define SYS_wait    3
#define SYS_pipe    4
#define SYS_read    5
#define SYS_kill    6
#define SYS_exec    7
#define SYS_fstat   8
#define SYS_chdir   9
#define SYS_dup    10
#define SYS_getpid 11
#define SYS_sbrk   12
#define SYS_sleep  13
#define SYS_uptime 14
#define SYS_open   15
#define SYS_write  16
#define SYS_mknod  17
#define SYS_unlink 18
#define SYS_link   19
#define SYS_mkdir  20
#define SYS_close  21
#define SYS_trace  22

void print_perf(struct perf *performance) {
    fprintf(1, "pref:\n");
    fprintf(1, "\tctime: %d\n", performance->ctime);
    fprintf(1, "\tttime: %d\n", performance->ttime);
    fprintf(1, "\tstime: %d\n", performance->stime);
    fprintf(1, "\tretime: %d\n", performance->retime);
    fprintf(1, "\trutime: %d\n", performance->rutime);
    fprintf(1, "\n\tTurnaround time: %d\n", (performance->ttime - performance->ctime));
}



int main(int argc, char** argv){
    // int mask=(1<< SYS_fork)|( 1<< SYS_kill)| ( 1<< SYS_sbrk) | ( 1<< SYS_write);
    // trace(mask,2);
    int cpid=fork();
    int *stat = (int*)malloc(sizeof(int));
    struct perf* perf = (struct perf*)malloc(sizeof(perf));
    if (cpid != 0){
        int ret = wait_stat(stat,perf);
        fprintf(2, "return value: %s %d\n", "wait_stat", ret);
        fprintf(2,"Sleep: %d Running: %d Runnable: %d Status: %d Creation: %d Termination: %d\n",perf->stime,perf->rutime,perf->retime,*stat, perf->ctime, perf->ttime);
    } else{
        sleep(20);
        mkdir("a");
        mkdir("b");
        mkdir("c");
        mkdir("d");
        mkdir("e");
        mkdir("f");
        sleep(10);
    }
    exit(0);
}