/*
 *kerner.c Kernel main (entry) function
 *
 * Author: shang <shang@andrew.cmu.edu>
 *
 * Date:   2014-10-30
 */

#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <bits/swi.h>
#include <exports.h>

uint32_t global_data;

int ksp = 0;
int r8 =0;
int err =0;
unsigned int irqStack[1024];
unsigned long irqStackTop;
extern void S_Handler();
extern void irqHandlerAsm();
ssize_t write(int fd, void* buf, size_t count);
extern int user_mode();
extern void prepareIrqStack(unsigned long);
extern void timerIrqSetup();

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;
	//printf("Switch to User mode.......................\n");

	unsigned * swivec = (unsigned *)(EX_SWI*4);
    unsigned *irqVec = (unsigned *)(EX_IRQ*4);
	unsigned oldvec1, oldvec2;
    unsigned oldIrqVec1, oldIrqVec2;
	int *uboot_swi;
    int *uboot_irq;
	unsigned offset;
	int *swiaddr;
    int *irqAddr;
	int result = 0;
    irqStackTop = (unsigned long)(irqStack+1024-1);
	offset = ((unsigned int)(*swivec) - 0xe51FF000);

	if((offset & 0xFFFFF000) == 0x800000){
		uboot_swi = (int *)((int)swivec + (offset & 0xFFF) + 0x8);
	}else if((offset & 0xFFFFF000) == 0x0) {
		uboot_swi = (int *)((int)swivec - (offset & 0xFFF) + 0x8);
	}
	else{
		printf("Installation of handler failed.\n");
		return 0x0badc0de;
	}
	//store old swi addresses
	swiaddr =(int *) *uboot_swi;
	oldvec1 = *swiaddr;
	oldvec2 = *(swiaddr + 1);
	//new swi address
	*swiaddr = 0xe51ff004; //ldr pc,[pc,#-4]
	*(swiaddr + 1) =(int) &S_Handler;
    /*wire in the irq handler*/
    offset = ((unsigned int)(*irqVec) - 0xe51FF000);
    if((offset & 0xFFFFF000) == 0x800000){
        uboot_irq = (int *)((int)irqVec + (offset & 0xFFF) + 0x8);
    }
    else if((offset & 0xFFFFF000) == 0x0) {
        uboot_irq = (int *)((int)irqVec - (offset & 0xFFF) + 0x8);
   }
   else{
        printf("Installation of handler failed.\n");
        return 0x0badc0de;
   }
   //store old swi addresses
   irqAddr =(int *) *uboot_irq;
   oldIrqVec1 = *irqAddr;
   oldIrqVec2 = *(irqAddr + 1);
   //new swi address
   *irqAddr = 0xe51ff004; //ldr pc,[pc,#-4]
   *(irqAddr + 1) =(int) &irqHandlerAsm;

   prepareIrqStack(irqStackTop);
   timerIrqSetup();
	//user mode
	result = user_mode(argc, argv);

	//restore
	*swiaddr = oldvec1;
	*(swiaddr + 1)= oldvec2;
    *irqAddr = oldIrqVec1;
    *(irqAddr + 1) = oldIrqVec2;
	//printf("swivec: %x\n", *swivec);
	return err;
}
