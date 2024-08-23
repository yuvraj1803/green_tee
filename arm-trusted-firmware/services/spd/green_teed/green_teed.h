

// dont mind the decimal notation ;)
#define GREEN_TEED_SP_CONTEXT_X0     0
#define GREEN_TEED_SP_CONTEXT_X1     8
#define GREEN_TEED_SP_CONTEXT_X2     16
#define GREEN_TEED_SP_CONTEXT_X3     24
#define GREEN_TEED_SP_CONTEXT_X4     32
#define GREEN_TEED_SP_CONTEXT_X5     40
#define GREEN_TEED_SP_CONTEXT_X6     48
#define GREEN_TEED_SP_CONTEXT_X7     56
#define GREEN_TEED_SP_CONTEXT_X8     64
#define GREEN_TEED_SP_CONTEXT_X9     72
#define GREEN_TEED_SP_CONTEXT_X10    80
#define GREEN_TEED_SP_CONTEXT_X11    88
#define GREEN_TEED_SP_CONTEXT_X12    96
#define GREEN_TEED_SP_CONTEXT_X13    104
#define GREEN_TEED_SP_CONTEXT_X14    112
#define GREEN_TEED_SP_CONTEXT_X15    120
#define GREEN_TEED_SP_CONTEXT_X16    128
#define GREEN_TEED_SP_CONTEXT_X17    136
#define GREEN_TEED_SP_CONTEXT_X18    144
#define GREEN_TEED_SP_CONTEXT_X19    152
#define GREEN_TEED_SP_CONTEXT_X20    160
#define GREEN_TEED_SP_CONTEXT_X21    168
#define GREEN_TEED_SP_CONTEXT_X22    176
#define GREEN_TEED_SP_CONTEXT_X23    184
#define GREEN_TEED_SP_CONTEXT_X24    192
#define GREEN_TEED_SP_CONTEXT_X25    200
#define GREEN_TEED_SP_CONTEXT_X26    208
#define GREEN_TEED_SP_CONTEXT_X27    216
#define GREEN_TEED_SP_CONTEXT_X28    224
#define GREEN_TEED_SP_CONTEXT_X29    232
#define GREEN_TEED_SP_CONTEXT_X30    240
#define GREEN_TEED_SP_CONTEXT_SIZE   248

#ifndef __ASSEMBLER__
#include <stdint.h>
#include <context.h>

typedef struct{
    uint64_t mpidr_el1;
    cpu_context_t cpu_context;
} green_teed_cpu_context_t;

uint64_t green_teed_enter_sp(cpu_context_t* context);

#endif  /* __ASSEMBLER__ */