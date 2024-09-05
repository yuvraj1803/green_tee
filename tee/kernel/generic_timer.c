#include <kernel/generic_timer.h>


void generic_timer_enable(){
    uint64_t cntps = read_cntps_ctl_el1();
    write_cntps_ctl_el1((cntps & ~CNTPS_CTL_EL1_IMASK) | CNTPS_CTL_EL1_ENABLE);
}

void generic_timer_disable(){
    uint64_t cntps = read_cntps_ctl_el1();
    write_cntps_ctl_el1((cntps & ~CNTPS_CTL_EL1_ENABLE) | CNTPS_CTL_EL1_IMASK);
}

void generic_timer_reset(){
    write_cntps_tval_el1(read_cntfrq_el0() / GENERIC_TIMER_FREQ_SEC);
}

void generic_timer_init(void){

    generic_timer_reset();
    generic_timer_enable();
}
