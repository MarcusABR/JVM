#include "../../include/instructions/stack.hpp"
#include <iostream>

/**
 * @brief Pop the top operand stack value
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void pop(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    top_frame.operand_stack.pop();
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[POP]" << endl;
}

void pop2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Duplicate the top operand stack value
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dup(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DUP]" << endl; 
}

/**
 * @brief Duplicate the top operand stack value and insert two values down
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dup_x1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    top_frame.operand_stack.push(value1);
    top_frame.operand_stack.push(value2);
    top_frame.operand_stack.push(value1);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DUP_X1]" << endl;
}

void dup_x2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void dup2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void dup2_x1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void dup2_x2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Swap the top two operand stack values
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void swap(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    top_frame.operand_stack.push(value1);
    top_frame.operand_stack.push(value2);    
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[SWAP]" << endl;
}
