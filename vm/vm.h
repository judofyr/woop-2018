
#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

enum W_OPCODE {
    // Literals
    W_OPCODE_INT8,

    // Stack manipulation
    W_OPCODE_PICK,
    W_OPCODE_ROLL,

    // Arithmetic
    W_OPCODE_ADD,
    W_OPCODE_SUB,
    W_OPCODE_MUL,
    W_OPCODE_DIV,
    W_OPCODE_MOD,

    // Calling blocks
    W_OPCODE_CALL,
};

typedef int8_t w_opcode_t;

typedef union w_val {
    void *ptr;
    intptr_t num;
} w_val_t;

#define W_NUM(v) ((w_val_t) { .num = (v) })
#define W_PTR(v) ((w_val_t) { .ptr = (v) })

typedef struct w_array {
    w_val_t data;
    w_val_t size;
} w_array_t;

#define W_ARRAY(arr) \
    ((w_array_t) { W_PTR(arr), W_NUM(sizeof(arr) / sizeof(*(arr))) })

typedef struct w_block {
    w_array_t name;
    w_array_t body;
} w_block_t;

typedef struct w_stack {
    w_val_t data;
    w_val_t pos;
} w_stack_t;

typedef struct w_vm {
    w_array_t blocks;
    w_stack_t stack;
} w_vm_t;

void w_vm_init(w_vm_t *, w_array_t blocks, void *stack);
void w_vm_run(w_vm_t *, size_t block_id);
