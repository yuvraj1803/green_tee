.section ".text.boot"

.globl get_cpu_id
get_cpu_id:
    mrs x0, mpidr_el1
    and x1,x0,0xff
    and x0,x0,0xff00
    add x0,x1,x0, lsr #4
    ret