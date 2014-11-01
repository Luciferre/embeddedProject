/*
 * Author: shang <shang@andrew.cmu.edu>
 *        
 * Date:   2014-10-30
 */

#include <exports.h>

extern volatile unsigned long system_time;

void sleep(unsigned long millis)
{
    unsigned int end_time = system_time + (unsigned int) millis;
    while (system_time < end_time);
    return;
}
