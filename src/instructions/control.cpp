#include "../../include/instructions/control.hpp"
#include <iostream>

/**
 * @brief Branch always
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void _goto(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 branchoffset = (branchbyte1 << 8) | branchbyte2;

    top_frame.pc += branchoffset - 2;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[GOTO] branchoffset: " << branchoffset << endl;
}

void jsr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void ret(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void tableswitch(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void lookupswitch(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Return int from method
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ireturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    stack_f->pop();
    auto called_frame = stack_f->top();
    called_frame.operand_stack.push(value);

    cout << "[IRETURN] value: " << called_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Return long from method
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lreturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    stack_f->pop();
    auto called_frame = stack_f->top();
    called_frame.operand_stack.push(value);

    cout << "[LRETURN] value: " << called_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Return float from method
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void freturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    stack_f->pop();
    auto called_frame = stack_f->top();
    called_frame.operand_stack.push(value);

    cout << "[FRETURN] value: " << called_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Return double from method
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dreturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    stack_f->pop();
    auto called_frame = stack_f->top();
    called_frame.operand_stack.push(value);

    cout << "[DRETURN] value: " << called_frame.operand_stack.top()._double << endl;
}

void areturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Return void from method
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void _return(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    stack_f->top().pc++;
    stack_f->pop();

    cout << "[RETURN]" << endl;
}
