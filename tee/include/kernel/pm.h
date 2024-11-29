#ifndef __PM_H__
#define __PM_H__

#include <stdint.h>

uint64_t pm_cpu_on_entry();
uint64_t pm_cpu_off_entry();
uint64_t pm_cpu_resume_entry();
uint64_t pm_cpu_suspend_entry();
uint64_t pm_cpu_system_off_entry();
uint64_t pm_cpu_system_reset_entry();


#endif