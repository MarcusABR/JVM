#include "../../include/instructions/loads.hpp"
#include <iostream>

void aaload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void aload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void aload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void aload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void aload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void aload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void baload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void caload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void daload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Load double from local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto index = code[++top_frame.pc];
    auto value = top_frame.local_variables_array[index];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DLOAD] index: " << (u4) index << " value: " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Load double from local variable at index 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[0];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DLOAD_0] " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Load double from local variable at index 1
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[1];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DLOAD_1] " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Load double from local variable at index 2
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[2];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DLOAD_2] " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Load double from local variable at index 3
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[3];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DLOAD_3] " << top_frame.operand_stack.top()._double << endl;
}

void faload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Load float from local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto index = code[++top_frame.pc];

    top_frame.operand_stack.push(top_frame.local_variables_array[index]);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FLOAD] index: " << (u4) index << " value: " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Load float from local variable at index 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[0];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FLOAD_0] " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Load float from local variable at index 1
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[1];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FLOAD_1] " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Load float from local variable at index 2
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[2];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FLOAD_2] " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Load float from local variable at index 3
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[3];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FLOAD_3] " << top_frame.operand_stack.top()._float << endl;
}

void iaload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Load int from local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto index = code[++top_frame.pc];
    auto value = top_frame.local_variables_array[index];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ILOAD] index: " << (u4) index << " value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Load int from local variable at index 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[0];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ILOAD_0] " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Load int from local variable at index 1
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[1];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ILOAD_1] " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Load int from local variable at index 2
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[2];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ILOAD_2] " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Load int from local variable at index 3
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[3];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ILOAD_3] " << top_frame.operand_stack.top()._int << endl;
}

void laload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Load long from local variable
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto index = code[++top_frame.pc];
    auto value = top_frame.local_variables_array[index];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LLOAD] index: " << (u4) index << " value: " << top_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Load long from local variable at index 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[0];
    
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LLOAD_0] value: " << value._long << endl;
}

/**
 * @brief Load long from local variable at index 1
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[1];
    
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LLOAD_1] value: " << value._long << endl;
}

/**
 * @brief Load long from local variable at index 2
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[2];
    
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LLOAD_2] value: " << value._long << endl;
}

/**
 * @brief Load long from local variable at index 3
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.local_variables_array[3];
    
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LLOAD_3] value: " << value._long << endl;
}

void saload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}