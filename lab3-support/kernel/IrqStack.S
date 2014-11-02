@ IrqStack.S: This file is the assembly code is to Prepare
@ the stack for IRQ mode
@ Authors: Group Member 1: jian wang <jianw3>
@ Group Member 2: shan gao<>
@ Date: Oct 30, 2014 11:00 PM
#include <asm.h>
    .file "IrqStack.S"
    FUNC(prepareIrqStack)
prepareIrqStack:
    STMFD sp!, {r1,r2}
    mov r2,#0x1
    mrs r1, cpsr  @swich to IRQ mode
    EOR r1,r2
    msr cpsr,r1
    mov sp,r0  @set the IRQ mode stack
    ORR r1,r2 @switch back to SVC mode
    EOR r1,#0x80
    msr cpsr,r1
    LDMFD sp!,{r1,r2}
    mov pc,lr
