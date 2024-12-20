#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__



#define CURRENT_EL_SP0_SYNC     0
#define CURRENT_EL_SP0_IRQ      1
#define CURRENT_EL_SP0_FIQ      2
#define CURRENT_EL_SP0_SERROR   3

#define CURRENT_EL_SPX_SYNC     4
#define CURRENT_EL_SPX_IRQ      5
#define CURRENT_EL_SPX_FIQ      6
#define CURRENT_EL_SPX_SERROR   7

#define LOWER_EL_64_SYNC        8
#define LOWER_EL_64_IRQ         9
#define LOWER_EL_64_FIQ         10
#define LOWER_EL_64_SERROR      11

#define LOWER_EL_32_SYNC        12
#define LOWER_EL_32_IRQ         13
#define LOWER_EL_32_FIQ         14
#define LOWER_EL_32_SERROR      15

#ifndef __ASSEMBLER__
#include <stdint.h>

typedef struct green_tee_vector_table{
   	uint64_t yield_smc_entry;
	uint64_t fast_smc_entry;
	uint64_t cpu_on_entry;
	uint64_t cpu_off_entry;
	uint64_t cpu_resume_entry;
	uint64_t cpu_suspend_entry;
	uint64_t fiq_entry;
	uint64_t system_off_entry;
	uint64_t system_reset_entry;

} green_tee_vector_table_t;


#endif /* __ASSEMBLER__*/

#endif
