#include <types.h>
#include <arm/reg.h>
#include <arm/timer.h>
#include <exports.h>
#include <arm/interrupt.h>

volatile unsigned long system_time=0;
volatile unsigned long time_drift=0;
void irqHandler(){
    unsigned volatile int oscrValue, icprValue;
    
    icprValue = reg_read(INT_ICPR_ADDR);
    
    if((icprValue & (1<<INT_OSTMR_0)) == 0)
       return;
    system_time++;

    oscrValue = reg_read(OSTMR_OSCR_ADDR);

    system_time += oscrValue/OSTMR_COUNT;

    time_drift += oscrValue % OSTMR_COUNT;

    if(time_drift >= OSTMR_COUNT){
        system_time++;
        time_drift -= OSTMR_COUNT;
    }
    //printf("%d\n",system_time); 
    reg_write(OSTMR_OSCR_ADDR,0); 
    /*achknowledge the IRQ and clear it*/
    reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);

}
