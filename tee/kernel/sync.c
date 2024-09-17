#include <kernel/sync.h>
#include <stdint.h>
#include <kernel/exceptions.h>
#include <lib/stdio.h>
#include <kernel/panic.h>

#define ESR_EC_SHIFT                          26

uint8_t get_exception_class(uint64_t esr_el1){
    return (esr_el1 >> ESR_EC_SHIFT) & 0b111111;
}

const char *sync_info[] = {
    "Unknown reason.",
    "Trapped WFI or WFE instruction execution.",
    "(unknown)",
    "Trapped MCR or MRC access with (coproc==0b1111).",
    "Trapped MCRR or MRRC access with (coproc==0b1111).",
    "Trapped MCR or MRC access with (coproc==0b1110).",
    "Trapped LDC or STC access.",
    "Access to SVE, Advanced SIMD, or floating-point functionality trapped by CPACR_EL1.FPEN, CPTR_EL2.FPEN, CPTR_EL2.TFP, or CPTR_EL3.TFP control.",
    "Trapped VMRS access, from ID group trap.",
    "Trapped use of a Pointer authentication instruction because HCR_EL2.API == 0 || SCR_EL3.API == 0.",
    "(unknown)",
    "(unknown)",
    "Trapped MRRC access with (coproc==0b1110).",
    "Branch Target Exception.",
    "Illegal Execution state.",
    "(unknown)",
    "(unknown)",
    "SVC instruction execution in AArch32 state.",
    "HVC instruction execution in AArch32 state.",
    "SMC instruction execution in AArch32 state.",
    "(unknown)",
    "SVC instruction execution in AArch64 state.",
    "HVC instruction execution in AArch64 state.",
    "SMC instruction execution in AArch64 state.",
    "Trapped MSR, MRS or System instruction execution in AArch64 state.",
    "Access to SVE functionality trapped as a result of CPACR_EL1.ZEN, CPTR_EL2.ZEN, CPTR_EL2.TZ, or CPTR_EL3.EZ.",
    "Trapped ERET, ERETAA, or ERETAB instruction execution.",
    "(unknown)",
    "Exception from a Pointer Authentication instruction authentication failure.",
    "(unknown)",
    "(unknown)",
    "(unknown)",
    "Instruction Abort from a lower Exception level.",
    "Instruction Abort taken without a change in Exception level.",
    "PC alignment fault exception.",
    "(unknown)",
    "Data Abort from a lower Exception level.",
    "Data Abort without a change in Exception level, or Data Aborts taken to EL2 as a result of accesses generated associated with VNCR_EL2 as part of nested virtualization support.",
    "SP alignment fault exception.",
    "(unknown)",
    "Trapped floating-point exception taken from AArch32 state.",
    "(unknown)",
    "(unknown)",
    "(unknown)",
    "Trapped floating-point exception taken from AArch64 state.",
    "(unknown)",
    "(unknown)",
    "SError interrupt.",
    "Breakpoint exception from a lower Exception level.",
    "Breakpoint exception taken without a change in Exception level.",
    "Software Step exception from a lower Exception level.",
    "Software Step exception taken without a change in Exception level.",
    "Watchpoint from a lower Exception level.",
    "Watchpoint exceptions without a change in Exception level, or Watchpoint exceptions taken to EL2 as a result of accesses generated associated with VNCR_EL2 as part of nested virtualization support.",
    "(unknown)",
    "(unknown)",
    "BKPT instruction execution in AArch32 state.",
    "(unknown)",
    "Vector Catch exception from AArch32 state.",
    "(unknown)",
    "BRK instruction execution in AArch64 state.",
};

void __handle_unsupported_exception(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type){
    printf("[PANIC]: Unsupported Exception Occurred: %s\n", sync_info[get_exception_class(esr_el1)]);
    halt();
}

void handle_sync(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type){

}

