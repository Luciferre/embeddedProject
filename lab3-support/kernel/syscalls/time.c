#include <exports.h>
#include <arm/timer.h>

extern volatile unsigned long system_time;

unsigned long time()
{
	return system_time*((unsigned long)TIMER_RESOLUTION);
}
