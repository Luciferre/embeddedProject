/*
 *
 * Author: shang <shang@andrew.cmu.edu>
 *         jian wang <jianw3@andrew.cmu.edu>
 *
 *
 * Date:   9:08	OCT 15 2014
 */
#include <bits/fileno.h>
#include <exports.h>
#include <bits/swi.h>
void exit(int status);
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, void* buf, size_t count);
unsigned long time(void);
void sleep(unsigned long millis);

void C_SWI_Handler(unsigned num, unsigned* regs)
{
	switch(num)
	{
		//exit
		case EXIT_SWI:
			exit(regs[0]);
			break;
		//read
		case READ_SWI:
			regs[0] = read((int)regs[0], (void *)regs[1], (size_t)regs[2]);
			break;
		//write
		case WRITE_SWI:
			regs[0] = write((int)regs[0], (void *)regs[1], (size_t)regs[2]);
			break;
		case TIME_SWI:
			regs[0] = time();
			break;
		case SLEEP_SWI:
			sleep((unsigned long)regs[0]);
			break;
		default:
			puts("instruction is unrecognized\n");
			exit(0x0badc0de);
			break;
	}
}
