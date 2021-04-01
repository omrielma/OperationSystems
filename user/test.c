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

    // int pid1, status1;
    // struct perf perf2;
    // pid1 = fork();
    // if (pid1 > 0) {
    //     wait_stat(&status1, &perf2);
    //     print_perf(&perf2);
    // } else {
    //     for (int a = 0; a < 10; ++a) {
    //       sleep(1);
    //     }
    // }

    // int mask=(1<< SYS_fork)|( 1<< SYS_kill)| ( 1<< SYS_sbrk) | ( 1<< SYS_write);
    // trace(mask,2);


    // int cpid=fork();
    // int *stat = (int*)malloc(sizeof(int));
    // struct perf* perf = (struct perf*)malloc(sizeof(perf));
    // if (cpid != 0){
    //     int ret = wait_stat(stat,perf);
    //     fprintf(2, "return value: %s %d\n", "wait_stat", ret);
    //     fprintf(2,"Sleep: %d Running: %d Runnable: %d Status: %d Creation: %d Termination: %d Burst: %d\n",perf->stime,perf->rutime,perf->retime,*stat, perf->ctime, perf->ttime, perf->average_bursttime);
    // } else{
    //     sleep(20);
    //     mkdir("a");
    //     mkdir("b");
    //     mkdir("c");
    //     mkdir("d");
    //     mkdir("e");
    //     mkdir("f");
    //     sleep(10);
    // }
    // exit(0);

    int mask = 1<<6 | 1 <<16; //trace kill and write
    trace(mask, getpid());
    int pid = fork();
    int status;
    if (pid > 0){ //parent
        wait(&status);
        int pid2 = fork();
        if (pid2 == 0){ //child2
            trace(1<<6, getpid()); //trace kill
            int pid4 = fork();
            wait(&status);
            if (pid4 >0){ //child 2
                kill(pid4); //should be traced
                write(1, "child2\n", 7);  //shouldnt be traced
            }
        }
        else{ //parent
            wait(&status);
            write(1, "parent\n", 7); //should be traced
            open("/path", 0); //shouldn't be traced
        }
  }
  else{ //child1
    write(1, "child1\n", 7);  //should be traced
    int pid3 = fork(); //shouldnt be traced
    if (pid3 >0){ //child1
      wait(&status);
      kill(pid3);  //should be traced
    }
  }

  exit(0);

}