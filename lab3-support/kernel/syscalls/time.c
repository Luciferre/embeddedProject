#include <exports.h>

extern volatile unsigned long system_time;

unsigned long time()
{
	return system_time;
}
