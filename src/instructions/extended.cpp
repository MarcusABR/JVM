#include "../../include/instructions/extended.hpp"
#include <iostream>

/**
 * @brief Branch always (wide index)
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void goto_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    auto branchbyte3 = code[++top_frame.pc];
    auto branchbyte4 = code[++top_frame.pc];
    s4 branchoffset = (branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4;

    top_frame.pc += branchoffset - 4;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[GOTO_W] branchoffset: " << branchoffset << endl;
}

void ifnull(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void jsr_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void ifnonnull(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void multianewarray(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void wide(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}
