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
extern void S_Handler();
ssize_t write(int fd, void* buf, size_t count);
extern int user_mode();

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	unsigned * swivec = (unsigned *)0x08;
	//printf("*swivec: %x\n", *swivec);
	unsigned oldvec1, oldvec2;
	int *uboot_swi;
	unsigned offset;
	int *swiaddr;
	//int *uboot_swi = (int *)0x5c0009c0;
	int result = 0;
	// check ldr pc, [pc, #imm12]
	offset = ((unsigned int)(*swivec) - 0xe51FF000);
	//printf("offset: %x\n", offset);

	//int i =0;
	//for (i=0; i<argc; i++)
	//	printf("argvs: %s\n", argv[i]);

	if((offset & 0xFFFFF000) == 0x800000){
		uboot_swi = (int *)((int)swivec + (offset & 0xFFF) + 0x8);
		//printf("uboot_swi: %x %x %x\n", uboot_swi, swivec, (offset &0xFFF));
	}else if((offset & 0xFFFFF000) == 0x0) {
		uboot_swi = (int *)((int)swivec - (offset & 0xFFF) + 0x8);
		//printf("uboot_swi: %x\n", uboot_swi);
	}
	else{
		printf("Installation of handler failed.\n");
		return 0x0badc0de;
	}
	//store old swi addresses
	swiaddr =(int *) *uboot_swi;
	oldvec1 = *swiaddr;
	oldvec2 = *(swiaddr + 1);
	//printf("oldvec1 oldvec2: %x %x\n", oldvec1, oldvec2);
	//new swi address
	*swiaddr = 0xe51ff004; //ldr pc,[pc,#-4]
	*(swiaddr + 1) =(int) &S_Handler;
	//printf("new ubootswi: %x %x\n", *swiaddr, *(swiaddr+1));
	//user mode
	//printf("Switch to User mode.......................\n");
	result = user_mode(argc, argv);

	//restore
	*swiaddr = oldvec1;
	*(swiaddr + 1)= oldvec2;
	//printf("swivec: %x\n", *swivec);
	return err;
}
