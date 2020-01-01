#include "vm.h"

#include <assert.h>

void w_vm_init(w_vm_t *vm, w_array_t blocks, void *stack) {
    vm->blocks = blocks;
    vm->stack.data.ptr = stack;
    vm->stack.pos.num = 0;
}

static void w_vm_push(w_vm_t *vm, w_val_t value) {
    w_val_t *values = vm->stack.data.ptr;
    values[vm->stack.pos.num++] = value;
}

static w_val_t w_vm_pop(w_vm_t *vm) {
    w_val_t *values = vm->stack.data.ptr;
    return values[--vm->stack.pos.num];
}

static w_val_t w_vm_pop_at(w_vm_t *vm, size_t idx) {
    w_val_t *values = vm->stack.data.ptr;
    size_t pos = vm->stack.pos.num - idx - 1;
    w_val_t result = values[pos];

    // Shift values
    for (size_t i = 0; i < idx; i++) {
        values[pos + i] = values[pos + i + 1];
    }

    vm->stack.pos.num--;
    return result;
}

static w_val_t w_vm_peek(w_vm_t *vm, size_t idx) {
    w_val_t *values = vm->stack.data.ptr;
    return values[vm->stack.pos.num - idx - 1];
}

#define ARITH_CASE(opcode, op) \
    case opcode: { \
        w_val_t b = w_vm_pop(vm); \
        w_val_t a = w_vm_pop(vm); \
        w_vm_push(vm, W_NUM(a.num op b.num)); \
        i += 1; \
        break; \
    }

void w_vm_run(w_vm_t *vm, size_t block_id) {
    w_block_t block = ((w_block_t *)vm->blocks.data.ptr)[block_id];
    w_opcode_t* ops = (w_opcode_t *)block.body.data.ptr;
    size_t size = (size_t)block.body.size.num;
    
    for (size_t i = 0; i < size; ) {
        switch (ops[i]) {
        case W_OPCODE_INT8: {
            w_vm_push(vm, W_NUM(ops[i + 1]));
            i += 2;
            break;
        }
        case W_OPCODE_PICK: {
            w_vm_push(vm, w_vm_peek(vm, ops[i + 1]));
            i += 2;
            break;
        }
        case W_OPCODE_ROLL: {
            w_val_t val = w_vm_pop_at(vm, ops[i + 1]);
            w_vm_push(vm, val);
            i += 2;
            break;
        }
        ARITH_CASE(W_OPCODE_ADD, +)
        ARITH_CASE(W_OPCODE_SUB, -)
        ARITH_CASE(W_OPCODE_MUL, *)
        ARITH_CASE(W_OPCODE_DIV, /)
        ARITH_CASE(W_OPCODE_MOD, %)
        case W_OPCODE_CALL: {
            size_t new_block_id = w_vm_pop(vm).num;
            w_vm_run(vm, new_block_id);
            i += 1;
            break;
        }
        default:
            assert(0 && "unknown opcode");
        }
    }
}
