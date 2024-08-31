

// dont mind the decimal notation ;)

#define GREEN_TEED_SP_CONTEXT_X19    8*0
#define GREEN_TEED_SP_CONTEXT_X20    8*1
#define GREEN_TEED_SP_CONTEXT_X21    8*2
#define GREEN_TEED_SP_CONTEXT_X22    8*3
#define GREEN_TEED_SP_CONTEXT_X23    8*4
#define GREEN_TEED_SP_CONTEXT_X24    8*5
#define GREEN_TEED_SP_CONTEXT_X25    8*6
#define GREEN_TEED_SP_CONTEXT_X26    8*7
#define GREEN_TEED_SP_CONTEXT_X27    8*8
#define GREEN_TEED_SP_CONTEXT_X28    8*9
#define GREEN_TEED_SP_CONTEXT_X29    8*10
#define GREEN_TEED_SP_CONTEXT_X30    8*11
#define GREEN_TEED_SP_CONTEXT_SIZE   8*12

#ifndef __ASSEMBLER__
#include <stdint.h>
#include <context.h>

typedef struct{
	uint64_t mpidr_el1;
	uint64_t stack;
	cpu_context_t cpu_context;
} green_tee_cpu_context_t;

typedef struct green_tee_vector_table{
    uint64_t current_el_sp0_sync;
    uint64_t current_el_sp0_irq;
    uint64_t current_el_sp0_fiq;
    uint64_t current_el_sp0_serror;

    uint64_t current_el_spx_sync;
    uint64_t current_el_spx_irq;
    uint64_t current_el_spx_fiq;
    uint64_t current_el_spx_serror;

    uint64_t lower_el_64_sync;
    uint64_t lower_el_64_irq;
    uint64_t lower_el_64_fiq;
    uint64_t lower_el_64_serror;

    uint64_t lower_el_32_sync;
    uint64_t lower_el_32_irq;
    uint64_t lower_el_32_fiq;
    uint64_t lower_el_32_serror;

} green_tee_vector_table_t;

uint64_t green_teed_enter_sp(uint64_t* stack);
uint64_t green_teed_exit_sp(uint64_t stack);
void green_tee_init_vector_table(uint64_t vbar_el1, int cpu);

#endif  /* __ASSEMBLER__ */
