#include <exports.h>
#include <arm/timer.h>

extern volatile unsigned long system_time;

unsigned long time()
{
        printf("%lu\n",system_time);
	return system_time*TIMER_RESOLUTION;
}
