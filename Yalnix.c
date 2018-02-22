#include <stdlib.h>
#include <stdio.h>

#include <comp421/loadinfo.h>
#include <comp421/yalnix.h>
#include <comp421/hardware.h>

/* Kernel Calls */
extern int Fork(void);
extern int Exec(char *, char **);
extern void Exit(int) __attribute__ ((noreturn));
extern int Wait(int *);
extern int GetPid(void);
extern int Brk(void *);
extern int Delay(int clock_ticks);
extern int TtyRead(int, void *, int);
extern int TtyWrite(int, void *, int);

void TrapKernel(ExceptionInfo *info);
void TrapClock(ExceptionInfo *info);
void TrapIllegal(ExceptionInfo *info);
void TrapMemory(ExceptionInfo *info);
void TrapMath(ExceptionInfo *info);
void TrapTTYReceive(ExceptionInfo *info);
void TrapTTYTransmit(ExceptionInfo *info);

#define REGION_0 0
#define REGION_1 1

#define PCB_TERMINATED  -1
#define PCB_RUNNING 0
#define PCB_READY 1
#define PCB_WAITBLOC 2



typedef struct pcb {
    SavedContext *ctx;
    int pid;
    int state; //TERMINATED is -1, RUNNING is 0, READY is 1, WAITBLOCK is 2
    int nchild;
    struct pcb *next;
    struct pcb *parent;
    struct pcb *child;
    struct pcb *sibling;
} pcb;

typedef struct line {
    void *buf;
    int cur;
    int len;
    struct line *next;
} line;

pcb **tty_head, **tty_tail; // first NUM_TERMINALS are for receiving; second NUM_TERMINALS are for transmiting
pcb **tty_transmiting;  // pcbs that are transmitting to terminal (haven't received interrupt)
pcb *idle_pcb = NULL;

line **line_head, **line_tail;  // input buffers for each terminal

/* Switch Function*/
SavedContext *MySwitchFunc(SavedContext *ctxp, void *p1, void *p2);

void KernelStart(ExceptionInfo *info, unsigned int pmem_size, void *orig_brk, char **cmd_args){

    init_terminals();


}


void init_terminals() {
    tty_head = (pcb **)calloc(2 * NUM_TERMINALS, sizeof(pcb *));
    if (tty_head == NULL) {
        fprintf(stderr, "KERNEL_START_ERROR\n");
        return;
    }
    tty_tail = (pcb **)calloc(2 * NUM_TERMINALS, sizeof(pcb *));
    if (tty_tail == NULL) {
        fprintf(stderr, "KERNEL_START_ERROR\n");
        return;
    }
    tty_transmiting = (pcb **)calloc(NUM_TERMINALS, sizeof(pcb *));
    if (tty_transmiting == NULL) {
        fprintf(stderr, "KERNEL_START_ERROR\n");
        return;
    }
    line_head = (line **)calloc(NUM_TERMINALS, sizeof(line *));
    if (line_head == NULL) {
        fprintf(stderr, "KERNEL_START_ERROR\n");
        return;
    }
    line_tail = (line **)calloc(NUM_TERMINALS, sizeof(line *));
    if (line_tail == NULL) {
        fprintf(stderr, "KERNEL_START_ERROR\n");
        return;
    }
}

extern int SetKernelBrk(void *addr){}