#include "../../include/instructions/conversions.hpp"
#include <iostream>
#include <iomanip>

/**
 * @brief Convert int to long
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void i2l(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._long = value._int;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[I2L] long value: " << top_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Convert int to float
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void i2f(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._float = value._int;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[I2F] float value: " << setprecision(15) << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Convert int to double
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void i2d(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._double = value._int;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[I2D] double value: " << setprecision(15) << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Convert long to int
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void l2i(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._int = value._long;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[L2I] int value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Convert long to float
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void l2f(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._float = value._long;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[L2F] float value: " << setprecision(15) << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Convert long to double
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void l2d(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._double = value._long;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[L2D] double value: " << setprecision(15) << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Convert float to int
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void f2i(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._int = value._float;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[F2I] int value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Convert float to long
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void f2l(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._long = value._float;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[F2L] long value: " << top_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Convert float to double
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void f2d(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._double = value._float;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[F2D] double value: " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Convert double to int
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void d2i(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._int = value._double;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[D2I] int value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Convert double to long
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void d2l(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._long = value._double;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[D2L] long value: " << top_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Convert double to float
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void d2f(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._float = value._double;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[D2F] float value: " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Convert int to byte
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void i2b(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._byte = value._int;
    value._int = (s4) value._byte;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[I2B] byte value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Convert int to char
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void i2c(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._char = value._int;
    value._int = (s4) value._char;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[I2C] char value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Convert int to short
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void i2s(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    value._short = value._int;
    value._int = (s4) value._short;

    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[I2S] short value: " << top_frame.operand_stack.top()._int << endl;
}
