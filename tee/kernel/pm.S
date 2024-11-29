#include "smc/green_tee_smc.h"

.section ".text.asm"

.globl pm_cpu_on_entry
pm_cpu_on_entry:
	bl setup_stack
	bl setup_vector_table
	
    bl secondary_main
    bl green_tee_smc_pm_ack
    b .

.globl pm_cpu_off_entry
pm_cpu_off_entry:
    b green_tee_smc_pm_ack

.globl pm_cpu_resume_entry
pm_cpu_resume_entry:
    b green_tee_smc_pm_ack

.globl pm_cpu_suspend_entry
pm_cpu_suspend_entry:
    b green_tee_smc_pm_ack

.globl pm_cpu_system_off_entry
pm_cpu_system_off_entry:
    b green_tee_smc_pm_ack

.globl pm_cpu_system_reset_entry
pm_cpu_system_reset_entry:
    b green_tee_smc_pm_ack

