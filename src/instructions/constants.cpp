#include "../../include/instructions/constants.hpp"
#include "../../include/utils.hpp"
#include <iostream>

void aconst_null(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Push byte onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void bipush(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;

    value._int = code[++top_frame.pc];

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[BIPUSH] value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Push double constant 0 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t dconst;

    dconst._double = 0.0;

    top_frame.operand_stack.push(dconst);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DCONST_0] " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Push double constant 1 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t dconst;

    dconst._double = 1.0;

    top_frame.operand_stack.push(dconst);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DCONST_1] " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Push float constant 0 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t fconst_0;

    fconst_0._float = 0.0;

    top_frame.operand_stack.push(fconst_0);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FCONST_0] " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Push float constant 1 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t fconst_1;

    fconst_1._float = 1.0;

    top_frame.operand_stack.push(fconst_1);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FCONST_1] " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Push float constant 2 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fconst_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t fconst_2;

    fconst_2._float = 2.0;

    top_frame.operand_stack.push(fconst_2);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FCONST_2] " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Push int constant -1 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iconst_m1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._int = -1;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ICONST_M1]" << endl;
}

/**
 * @brief Push int constant 0 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._int = 0;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ICONST_0]" << endl;
}

/**
 * @brief Push int constant 1 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._int = 1;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ICONST_1]" << endl;
}

/**
 * @brief Push int constant 2 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iconst_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._int = 2;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ICONST_2]" << endl;
}

/**
 * @brief Push int constant 3 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iconst_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._int = 3;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ICONST_3]" << endl;
}

/**
 * @brief Push int constant 4 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iconst_4(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._int = 4;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ICONST_4]" << endl;
}

/**
 * @brief Push int constant 5 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iconst_5(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._int = 5;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ICONST_5]" << endl;
}

/**
 * @brief Push long constant 0 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._long = 0;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LCONST_0] " << top_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Push long constant 1 onto the operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    operand_t value;
    value._long = 1;

    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LCONST_1] " << top_frame.operand_stack.top()._long << endl;
}

void ldc(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void ldc_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

/**
 * @brief Push long or double from run-time constant pool (wide index)
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ldc2_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto indexbyte1 = code[++top_frame.pc];
    auto indexbyte2 = code[++top_frame.pc];
    auto index = (indexbyte1 << 8) | indexbyte2;

    auto reference = to_cp_info(constant_pool[index - 1]);

    operand_t value;
    if (reference->tag == CONSTANT_Double)
        value._double = calc_double(reference->_double->high_bytes, reference->_double->low_bytes);
    if (reference->tag == CONSTANT_Long)
        value._long = calc_long(reference->_long->high_bytes, reference->_long->low_bytes);
    
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LDC2_W] ";

    if (reference->tag == CONSTANT_Double)
        cout << "double value: " << top_frame.operand_stack.top()._double << endl;
    if (reference->tag == CONSTANT_Long)
        cout << "long value: " << top_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Do nothing
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void nop(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    cout << "[NOP] Mi nombre is nop :)" << endl;
    return;
}

/**
 * @brief Push short
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void sipush(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto byte1 = code[++top_frame.pc];
    auto byte2 = code[++top_frame.pc];
    s2 short_value = (byte1 << 8) | byte2;

    operand_t value;
    value._int = short_value;
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[SIPUSH] value: " << top_frame.operand_stack.top()._int << endl;
}
