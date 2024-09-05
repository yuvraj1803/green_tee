.section ".text.asm"

.globl write_cntps_ctl_el1
write_cntps_ctl_el1:
    msr cntps_ctl_el1, x0
    isb
    ret

.globl read_cntps_ctl_el1
read_cntps_ctl_el1:
    mrs x0, cntps_ctl_el1
    isb
    ret

.globl write_cntps_tval_el1
write_cntps_tval_el1:
    msr cntps_tval_el1, x0
    isb
    ret

.globl read_cntps_tval_el1
read_cntps_tval_el1:
    mrs x0, cntps_tval_el1
    isb
    ret

.globl read_cntfrq_el0
read_cntfrq_el0:
    mrs x0, cntfrq_el0
    isb
    ret
