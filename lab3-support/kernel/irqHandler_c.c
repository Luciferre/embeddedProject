#include <types.h>
#include <arm/reg.h>
#include <arm/timer.h>
#include <exports.h>
#include <arm/interrupt.h>

volatile unsigned int system_time;
volatile unsigned int time_drift;
void irqHandler(){
    unsigned volatile int oscrValue, icprValue;
    
    icprValue = reg_read(INT_ICPR_ADDR);
    
    printf("irq %d\n",icprValue);
    //if((icprValue & (1<<INT_OSTMR_0)) == 0)
     //   return;
    system_time++;

    oscrValue = reg_read(OSTMR_OSCR_ADDR);

    time_drift = oscrValue - OSTMR_COUNT;

    if(time_drift >= OSTMR_COUNT){
        system_time++;
        time_drift -= OSTMR_COUNT;
    }
    reg_write(OSTMR_OSCR_ADDR,0); 
    /*achknowledge the IRQ and clear it*/
    reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);

}
