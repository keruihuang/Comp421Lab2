#include <stdlib.h>
#include <stdio.h>

#include <comp421/loadinfo.h>
#include <comp421/yalnix.h>
#include <comp421/hardware.h>

void TrapKernel(ExceptionInfo *info);
void TrapClock(ExceptionInfo *info);
void TrapIllegal(ExceptionInfo *info);
void TrapMemory(ExceptionInfo *info);
void TrapMath(ExceptionInfo *info);
void TrapTTYReceive(ExceptionInfo *info);
void TrapTTYTransmit(ExceptionInfo *info);

void (*IntVectorTable[TRAP_VECTOR_SIZE])(ExceptionInfo *);  /* Global Interrupt Vetor Table*/
struct pte PageTable0[PAGE_TABLE_LEN];  /* Page Table for Region 0*/
struct pte PageTable1[PAGE_TABLE_LEN];  /* Page Table for Region 1*/


void KernelStart(ExceptionInfo *info, unsigned int pmem_size, void *orig_brk, char **cmd_args){
    int i;
    unsigned int HeapEnd, StackStart, StackEnd, TextEnd;
    /*Init Vector Table and point the reg to it*/
    IntVectorTable[TRAP_KERNEL] = TrapKernel;
    IntVectorTable[TRAP_CLOCK] = TrapClock;
    IntVectorTable[TRAP_ILLEGAL] = TrapIllegal;
    IntVectorTable[TRAP_MEMORY] = TrapMemory;
    IntVectorTable[TRAP_MATH] = TrapMath;
    IntVectorTable[TRAP_TTY_RECEIVE] = TrapTTYReceive;
    IntVectorTable[TRAP_TTY_TRANSMIT] = TrapTTYTransmit;
    WriteRegister(REG_VECTOR_BASE, (RCS421RegVal)IntVectorTable);
    
    /*Build the initial page tables and enavle virtual memory*/
    WriteRegister(REG_PTR0, (RCS421RegVal)PageTable0);
    WriteRegister(REG_PTR1, (RCS421RegVal)PageTable1);

    TextEnd = (UP_TO_PAGE(&_etext) >> PAGESHIFT) - PAGE_TABLE_LEN; /* Mark the end of the Text segment*/
    HeapEnd = (UP_TO_PAGE(orig_brk)>> PAGESHIFT) - PAGE_TABLE_LEN; /* Mark the end of the data segment*/
    TracePrintf(1,"TextEnd = %u",TextEnd);
    TracePrintf(1,"HeapEnd = %u",HeapEnd);
    printf("fuck!!!!!!!!!!!");

    /*Init Text seg*/
    for(i = 0; i < TextEnd; i++){
        PageTable1[i].pfn = i + PAGE_TABLE_LEN;
        PageTable1[i].uprot = PROT_NONE;
        PageTable1[i].kprot = PROT_READ|PROT_EXEC;
        PageTable1[i].valid = 1;
    }

    /*Init Data seg*/
    for(i = TextEnd; i < HeapEnd; i++){
        PageTable1[i].pfn = i + PAGE_TABLE_LEN;
        PageTable1[i].uprot = PROT_NONE;
        PageTable1[i].kprot = PROT_READ|PROT_WRITE;
        PageTable1[i].valid = 1;
    }

    StackStart = KERNEL_STACK_LIMIT >> PAGESHIFT; /* Mark the highest addr of the stack*/
    StackEnd = KERNEL_STACK_BASE >> PAGESHIFT;  /* Mark the lowest addr of the stack*/
    TracePrintf(1,"StackStart = %u",StackStart);
    TracePrintf(1,"StackEnd = %u",StackEnd);
    
    /*Init Kernel Stack*/ 
   for(i = StackEnd; i < StackStart; i++){
        PageTable0[i].pfn = i;
        PageTable0[i].uprot = PROT_NONE;
        PageTable0[i].kprot = PROT_READ|PROT_WRITE;
        PageTable0[i].valid = 1;
    }
    
    WriteRegister(REG_VM_ENABLE, 1);
    
    return;
}

int SetKernelBrk(void *addr){
    Halt();
}


void TrapKernel(ExceptionInfo *info){
    TracePrintf(1,"TrapKernel");
    Halt();
}
void TrapClock(ExceptionInfo *info){
    TracePrintf(1,"TrapClock");
    Halt();
}
void TrapIllegal(ExceptionInfo *info){
    TracePrintf(1,"TrapIllegal");
    Halt();
}
void TrapMemory(ExceptionInfo *info){
    TracePrintf(1,"TrapMemory");
    Halt();
}
void TrapMath(ExceptionInfo *info){
    TracePrintf(1,"TrapMath");
    Halt();
}
void TrapTTYReceive(ExceptionInfo *info){
    TracePrintf(1,"TrapTTYReceive");
    Halt();
}
void TrapTTYTransmit(ExceptionInfo *info){
    TracePrintf(1,"TrapTTYTransimit");
    Halt();
}
