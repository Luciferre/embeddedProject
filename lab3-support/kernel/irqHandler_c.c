#include <types.h>
#include <arm/reg.h>
#include <arm/timer.h>

volatile unsigned int system_time;
volatile unsigned int time_drift;
void irqHandler(){
    unsigned int oscrValue;
    system_time++;

    oscrValue = reg_read(OSTMR_OSCR_ADDR);

    time_drift = oscrValue - OSTMR_COUNT;

    if(time_drift >= OSTMR_COUNT){
        system_time++;
        time_drift -= OSTMR_COUNT;
    }

    /*achknowledge the IRQ and clear it*/
    reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);

}
