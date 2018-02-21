


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

typedef struct pcb {

} pcb;


void KernelStart(ExceptionInfo *info,
                 unsigned int pmem_size, void *orig_brk, char **cmd_args){}

extern int SetKernelBrk(void *addr){}