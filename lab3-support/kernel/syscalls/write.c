/*
 * Author: shang <shang@andrew.cmu.edu>
 *        
 * Date:   2014-10-30
 */

#include "bits/errno.h"
#include "bits/swi.h"
#include "bits/fileno.h"
#include <exports.h>

#define SDRAMStart 0xa0000000
#define SDRAMEnd 0xa3ffffff
#define ROMStart 0x00000000
#define ROMEnd 0x00ffffff

ssize_t write(int fd, const void *buf, size_t count)
{
	unsigned i;
	char *buffer = (char *) buf;

	if(fd != STDOUT_FILENO)
	{	
		//printf("error ebadf");
		return -EBADF;
	}
	if(( (((unsigned)buf >ROMEnd)&&((unsigned)buf < SDRAMStart)) || ((unsigned)buf > SDRAMEnd) || ( (((unsigned)buf + count) > ROMEnd)&&(((unsigned)buf + count) < SDRAMStart)) ) || (((unsigned)buf + count) > SDRAMEnd))
	{
		//printf("error efault");
		return -EFAULT;
	}	
	for( i = 0; i < count; i++)
	{
		putc(buffer[i]);
	}
	return count;
}
