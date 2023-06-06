#include "../../include/instructions/stores.hpp"
#include <iostream>
#include <iterator>
#include <list>

void astore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void astore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void astore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void astore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void astore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Store double into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dstore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    top_frame.insert_into_local(0, value);
    top_frame.insert_into_local(1, value);
    
    top_frame.operand_stack.pop();
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DSTORE_0] value: " << top_frame.local_variables_array[0]._double << endl;
}

/**
 * @brief Store double into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dstore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    top_frame.insert_into_local(1, value);
    top_frame.insert_into_local(2, value);
    
    top_frame.operand_stack.pop();
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DSTORE_1] value: " << top_frame.local_variables_array[1]._double << endl;
}

/**
 * @brief Store double into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dstore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    top_frame.insert_into_local(2, value);
    top_frame.insert_into_local(3, value);
    
    top_frame.operand_stack.pop();
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DSTORE_2] value: " << top_frame.local_variables_array[2]._double << endl;
}

/**
 * @brief Store double into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dstore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    top_frame.insert_into_local(3, value);
    top_frame.insert_into_local(4, value);
    
    top_frame.operand_stack.pop();
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DSTORE_3] value: " << top_frame.local_variables_array[3]._double << endl;
}

void lstore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Store long into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lstore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();

    top_frame.operand_stack.pop();
    top_frame.insert_into_local(1, value);
    top_frame.insert_into_local(2, value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LSTORE_1] value: " << top_frame.local_variables_array[1]._long << endl;
}

void lstore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void lstore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void fstore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void fstore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void fstore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void fstore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void iastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void lastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void fastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void dastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void aastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void bastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void castore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void sastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Store integer into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void istore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto index = code[++top_frame.pc];
    auto value = top_frame.operand_stack.top();

    top_frame.operand_stack.pop();
    top_frame.insert_into_local(index, value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISTORE] value: " << top_frame.local_variables_array[index]._int << endl;
}

void lstore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Store float into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fstore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto index = code[++top_frame.pc];
    auto value = top_frame.operand_stack.top();

    top_frame.operand_stack.pop();
    top_frame.insert_into_local(index, value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FSTORE] index: " << (u4) index << " value: " << top_frame.local_variables_array[index]._float << endl;
}

void dstore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Store integer into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void istore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    top_frame.operand_stack.pop();
    top_frame.insert_into_local(0, value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISTORE_0]" << endl;
}

/**
 * @brief Store integer into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void istore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    top_frame.operand_stack.pop();
    top_frame.insert_into_local(1, value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISTORE_1]" << endl;
}

/**
 * @brief Store integer into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void istore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    top_frame.operand_stack.pop();
    top_frame.insert_into_local(2, value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISTORE_2]" << endl;
}

/**
 * @brief Store integer into local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void istore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    top_frame.operand_stack.pop();
    top_frame.insert_into_local(3, value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISTORE_3]" << endl;
}