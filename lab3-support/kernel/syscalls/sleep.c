/*
 * Author: shang <shang@andrew.cmu.edu>
 *        
 * Date:   2014-10-30
 */

#include <exports.h>

extern volatile unsigned long sys_time;

void sleep(unsigned long millis)
{
    unsigned int end_time = sys_time + (unsigned int) millis;
    while (sys_time < end_time);
    return;
}
