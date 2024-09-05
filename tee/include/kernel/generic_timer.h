#ifndef __GENERIC_TIMER_H__
#define __GENERIC_TIMER_H__

#include <stdint.h>

#define CNTPS_CTL_EL1_ENABLE     (1 << 0)
#define CNTPS_CTL_EL1_IMASK      (1 << 1)
#define CNTPS_CTL_EL1_ISTATUS    (1 << 2)

#define GENERIC_TIMER_FREQ_SEC  (1)

void write_cntps_ctl_el1(uint64_t cntps_ctl_el1);
uint64_t read_cntps_ctl_el1();


void write_cntps_tval_el1(uint64_t cntps_tval_el1);
uint64_t read_cntps_tval_el1();


uint32_t read_cntfrq_el0();

void generic_timer_init(void);

#endif
