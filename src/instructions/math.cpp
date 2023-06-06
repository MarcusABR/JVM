#include "../../include/instructions/math.hpp"
#include <iostream>
#include <math.h>

/**
 * @brief Add two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iadd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1._int + value2._int;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IADD] value1: " << value1._int << " value2: " << value2._int << " result: " << result._int << endl; 
}

/**
 * @brief Add two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ladd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1._long + value2._long;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LADD] value1: " << value1._long << " value2: " << value2._long << " result: " << result._long << endl; 
}

/**
 * @brief Add two float top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fadd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    result._float = value1._float + value2._float;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FADD] value1: " << value1._float << " value2: " << value2._float << " result: " << result._float << endl; 
}

/**
 * @brief Add two double top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dadd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    result._double = value1._double + value2._double;

    top_frame.operand_stack.push(result);

    top_frame.pc++;
    stack_f->pop();
    stack_f->push(top_frame);
    
    cout << "[DADD] value1: " << value1._double << " value2: " << value2._double << " result: " << result._double << endl;     cout << "[DADD] result: " << result._double << endl;
}

/**
 * @brief Subtract two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void isub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1 - value2;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISUB] value1: " << value1 << " value2: " << value2 << " result: " << result._int << endl; 
}

/**
 * @brief Subtract two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lsub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1 - value2;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LSUB] value1: " << value1 << " value2: " << value2 << " result: " << result._long << endl; 
}

/**
 * @brief Subtract two float top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fsub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    operand_t result;
    result._double = value1 - value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FSUB] value1: " << value1 << " value2: " << value2;
    cout << " result: " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Subtract two double top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dsub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();

    operand_t result;
    result._double = value1 - value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DSUB] value1: " << value1 << " value2: " << value2;
    cout << " result: " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Multiply two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void imul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1 * value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IMUL] result: " << result._int << endl;
}

/**
 * @brief Multiply two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lmul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1 * value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LMUL] result: " << result._long << endl;
}

/**
 * @brief Multiply two float top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fmul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    operand_t result;
    result._float = value1 * value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FMUL] result: " << result._float << endl;
}

/**
 * @brief Multiply two double top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dmul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();

    operand_t result;
    result._double = value1 * value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DMUL] result: " << result._double << endl;
}

/**
 * @brief Divide two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void idiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1 / value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IDIV] result: " << result._int << endl;
}

/**
 * @brief Divide two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ldiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1 / value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LDIV] result: " << result._long << endl;
}

/**
 * @brief Divide two float top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fdiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    operand_t result;
    result._float = value1 / value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FDIV] result: " << result._float << endl;
}

/**
 * @brief Divide two double top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ddiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();
    
    auto value2 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();

    operand_t result;
    result._double = value2 / value1;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DDIV] result: " << result._double << endl;
}

/**
 * @brief Remainder of two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void irem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1 - (value1 / value2) * value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IREM] result: " << result._int << endl;
}

/**
 * @brief Remainder of two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lrem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1 - (value1 / value2) * value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LREM] result: " << result._long << endl;
}

/**
 * @brief Remainder of two float top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void frem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    double value1 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    double value2 = top_frame.operand_stack.top()._float;
    top_frame.operand_stack.pop();

    operand_t result;
    result._float = fmod(value1, value2);
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FREM] result: " << result._float << endl;
}

/**
 * @brief Remainder of two double top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void drem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    double value1 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();

    double value2 = top_frame.operand_stack.top()._double;
    top_frame.operand_stack.pop();

    operand_t result;
    result._double = fmod(value1, value2);
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DREM] result: " << result._double << endl;
}

/**
 * @brief Negate top int value from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ineg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    value._int = -value._int;
    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[INEG] value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Negate top long value from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lneg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    value._long = -value._long;
    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LNEG] value: " << top_frame.operand_stack.top()._long << endl;
}

/**
 * @brief Negate top float value from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fneg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    value._float = -value._float;
    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FNEG] value: " << top_frame.operand_stack.top()._float << endl;
}

/**
 * @brief Negate top double value from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dneg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    
    value._double = -value._double;
    top_frame.operand_stack.pop();
    top_frame.operand_stack.push(value);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DNEG] value: " << top_frame.operand_stack.top()._double << endl;
}

/**
 * @brief Shift left int
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ishl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();
    
    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto s = value2 & 31; // lower 5 bits => value2 & 11111

    operand_t result;
    result._int = value1 << s;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISHL] result: " << result._int << endl;
}

/**
 * @brief Shift left long
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lshl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();
    
    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto s = value2 & 63; // lower 6 bits => value2 & 111111

    operand_t result;
    result._long = value1 << s;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LSHL] result: " << result._long << endl;
}

/**
 * @brief Shift right int
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ishr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();
    
    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto s = value2 & 31; // lower 5 bits => value2 & 11111

    operand_t result;
    result._int = value1 >> s;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[ISHR] result: " << result._int << endl;
}

/**
 * @brief Shift right long
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lshr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();
    
    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto s = value2 & 63; // lower 6 bits => value2 & 111111

    operand_t result;
    result._long = value1 >> s;

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LSHR] result: " << result._long << endl;
}

/**
 * @brief Logical shif right int
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iushr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();
    
    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto s = value2 & 31; // lower 5 bits => value2 & 11111

    operand_t result;

    if (value1 > 0)
        result._int = value1 >> s;
    else
        result._int = (value1 >> s) + (2 << ~s);

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IUSHR] result: " << result._int << endl;
}

/**
 * @brief Logical shif right long
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lushr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    
    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();
    
    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto s = value2 & 63; // lower 6 bits => value2 & 111111

    operand_t result;

    if (value1 > 0)
        result._long = value1 >> s;
    else
        result._long = (value1 >> s) + (2L << ~s);

    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LUSHR] result: " << result._long << endl;
}

/**
 * @brief Boolean and of two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iand(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1 & value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IAND] result: " << result._int << endl;
}

/**
 * @brief Boolean and of two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void land(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1 & value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LAND] result: " << result._long << endl;
}

/**
 * @brief Boolean or of two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ior(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1 | value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IOR] result: " << result._int << endl;
}

/**
 * @brief Boolean or of two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lor(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1 | value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LOR] result: " << result._long << endl;
}

/**
 * @brief Boolean xor of two int top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ixor(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._int;
    top_frame.operand_stack.pop();

    operand_t result;
    result._int = value1 ^ value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IXOR] result: " << result._int << endl;
}

/**
 * @brief Boolean xor of two long top values from operand stack
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lxor(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto value1 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    auto value2 = top_frame.operand_stack.top()._long;
    top_frame.operand_stack.pop();

    operand_t result;
    result._long = value1 ^ value2;
    top_frame.operand_stack.push(result);
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LXOR] result: " << result._long << endl;
}

/**
 * @brief Increment local variable by constant
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iinc(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto index = code[++top_frame.pc];
    auto const_byte = (s4) code[++top_frame.pc];

    top_frame.local_variables_array[index]._int += const_byte;
    top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IINC] index: " << (u4) index << " const: " << const_byte << endl;
}
