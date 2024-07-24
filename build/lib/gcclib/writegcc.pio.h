// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// -------- //
// writegcc //
// -------- //

#define writegcc_wrap_target 0
#define writegcc_wrap 18

static const uint16_t writegcc_program_instructions[] = {
            //     .wrap_target
    0xe080, //  0: set    pindirs, 0                 
    0xe047, //  1: set    y, 7                       
    0x2720, //  2: wait   0 pin, 0               [7] 
    0x4901, //  3: in     pins, 1                [9] 
    0x0082, //  4: jmp    y--, 2                     
    0x8000, //  5: push   noblock                    
    0x80a0, //  6: pull   block                      
    0x6024, //  7: out    x, 4                       
    0xe881, //  8: set    pindirs, 1             [8] 
    0xe047, //  9: set    y, 7                       
    0x80a0, // 10: pull   block                      
    0xe300, // 11: set    pins, 0                [3] 
    0xa607, // 12: mov    pins, osr              [6] 
    0x6061, // 13: out    null, 1                    
    0xe201, // 14: set    pins, 1                [2] 
    0x008b, // 15: jmp    y--, 11                    
    0x0049, // 16: jmp    x--, 9                     
    0xe300, // 17: set    pins, 0                [3] 
    0xe001, // 18: set    pins, 1                    
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program writegcc_program = {
    .instructions = writegcc_program_instructions,
    .length = 19,
    .origin = -1,
};

static inline pio_sm_config writegcc_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + writegcc_wrap_target, offset + writegcc_wrap);
    return c;
}
#endif
