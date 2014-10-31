/*
 *
 * Author: shang <shang@andrew.cmu.edu>
 *        
 * Date:   9:08	OCT 15
 */
#include <bits/fileno.h>
#include <exports.h>
#include <bits/swi.h>
void exit(int status);
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, void* buf, size_t count);

void C_SWI_Handler(unsigned num, unsigned* regs) 
{
	//printf("Enter handler......\n");
	switch(num)
	{
		//exit
		case EXIT_SWI:
			//printf("exit......%x\n", (int) regs[0]);
			exit(regs[0]);
			break;
		//read
		case READ_SWI:
			//printf("Read: %x %x %d \n", (int)regs[0], (int )regs[1], (int )regs[2]);
			regs[0] = read((int)regs[0], (void *)regs[1], (size_t)regs[2]);
			break;
		//write
		case WRITE_SWI:
			//printf("Write: %x %x %d \n", (int)regs[0], (int )regs[1], (int )regs[2]);
			regs[0] = write((int)regs[0], (void *)regs[1], (size_t)regs[2]);
			break;
	
		default:
			puts("instruction is unrecognized\n");
			exit(0x0badc0de);
			break;
	}
}