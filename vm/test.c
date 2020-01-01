#include "greatest.h"
#include "vm.h"

TEST test_basic(void) {
    w_opcode_t main_ops[] = {
        W_OPCODE_INT8, 2,
        W_OPCODE_INT8, 2,
        W_OPCODE_ADD,
    };

    w_block_t blocks[] = {
        { W_ARRAY("main"), W_ARRAY(main_ops) },
    };

    w_val_t stack[100];
    w_vm_t vm;

    w_vm_init(&vm, W_ARRAY(blocks), &stack);
    w_vm_run(&vm, 0);

    ASSERT_EQ(4, stack[0].num);
    PASS();
}

TEST test_calls(void) {
    w_opcode_t double_data[] = {
        W_OPCODE_INT8, 2,
        W_OPCODE_MUL,
    };

    w_opcode_t main_ops[] = {
        W_OPCODE_INT8, 5,
        W_OPCODE_INT8, 1,
        W_OPCODE_CALL,
    };

    w_block_t blocks[] = {
        { W_ARRAY("main"), W_ARRAY(main_ops) },
        { W_ARRAY("double"), W_ARRAY(double_data) },
    };

    w_val_t stack[100];
    w_vm_t vm;

    w_vm_init(&vm, W_ARRAY(blocks), &stack);
    w_vm_run(&vm, 0);

    ASSERT_EQ(10, stack[0].num);
    PASS();
}

TEST test_stack_manip(void) {
        w_opcode_t main_ops[] = {
        W_OPCODE_INT8, 1,
        W_OPCODE_INT8, 2,
        W_OPCODE_INT8, 3,
        W_OPCODE_INT8, 4,
        W_OPCODE_PICK, 1, // This should copy the "3" value
        W_OPCODE_ROLL, 3, // This should move the "2" value
    };

    w_block_t blocks[] = {
        { W_ARRAY("main"), W_ARRAY(main_ops) },
    };

    w_val_t stack[100];
    w_vm_t vm;

    w_vm_init(&vm, W_ARRAY(blocks), &stack);
    w_vm_run(&vm, 0);

    ASSERT_EQ(1, stack[0].num);
    ASSERT_EQ(3, stack[1].num);
    ASSERT_EQ(4, stack[2].num);
    ASSERT_EQ(3, stack[3].num);
    ASSERT_EQ(2, stack[4].num);
    PASS();
}


GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_TEST(test_basic);
  RUN_TEST(test_calls);
  RUN_TEST(test_stack_manip);

  GREATEST_MAIN_END();
}

