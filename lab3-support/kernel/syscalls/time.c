#include <exports.h>

extern volatile unsigned long sys_time;

unsigned long time()
{
	return sys_time;
}
