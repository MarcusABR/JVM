#include "../../include/instructions/comparisons.hpp"
#include <iostream>

/**
 * @brief Compare double
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dcmpl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    if(value1._double > value2._double)
        result._int = 1;
    else if(value1._double == value2._double)
        result._int = 0;
    else if(value1._double < value2._double)
        result._int = -1;
    else
        result._int = -1;

    top_frame.operand_stack.push(result);
    top_frame.pc++;
    
    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DCMPL] value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Compare float
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fcmpg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    if(value1._float > value2._float)
        result._int = 1;
    else if(value1._float == value2._float)
        result._int = 0;
    else if(value1._float < value2._float)
        result._int = -1;
    else
        result._int = 1;

    top_frame.operand_stack.push(result);
    top_frame.pc++;
    
    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FCMPG] value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Compare float
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void fcmpl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    if(value1._float > value2._float)
        result._int = 1;
    else if(value1._float == value2._float)
        result._int = 0;
    else if(value1._float < value2._float)
        result._int = -1;
    else
        result._int = -1;

    top_frame.operand_stack.push(result);
    top_frame.pc++;
    
    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[FCMPL] value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Compare long
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void lcmp(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    if(value1._long > value2._long)
        result._int = 1;
    else if(value1._long == value2._long)
        result._int = 0;
    else if(value1._long < value2._long)
        result._int = -1;

    top_frame.operand_stack.push(result);
    top_frame.pc++;
    
    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[LCMP] value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Compare double
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void dcmpg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();

    operand_t result;
    if(value1._double > value2._double)
        result._int = 1;
    else if(value1._double == value2._double)
        result._int = 0;
    else if(value1._double < value2._double)
        result._int = -1;
    else
        result._int = 1;

    top_frame.operand_stack.push(result);
    top_frame.pc++;
    
    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[DCMPG] value: " << top_frame.operand_stack.top()._int << endl;
}

/**
 * @brief Branch if int comparison equals 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ifeq(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    auto offset = (branchbyte1 << 8) | branchbyte2;

    if (value._int == 0)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IFEQ] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison not equals 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ifne(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    auto offset = (branchbyte1 << 8) | branchbyte2;

    if (value._int != 0)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IFNE] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison less than 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void iflt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    auto offset = (branchbyte1 << 8) | branchbyte2;

    if (value._int < 0)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IFLT] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison greater or equal 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ifge(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    auto offset = (branchbyte1 << 8) | branchbyte2;

    if (value._int >= 0)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IFGE] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison greater than 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ifgt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    auto offset = (branchbyte1 << 8) | branchbyte2;

    if (value._int > 0)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IFGT] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison less or equal 0
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void ifle(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value = top_frame.operand_stack.top();
    top_frame.operand_stack.pop();
    
    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 offset = (branchbyte1 << 8) | branchbyte2;

    if (value._int <= 0)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IFLE] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison value1 = value2 succeeds
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void if_icmpeq(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();

    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 offset = (branchbyte1 << 8) | branchbyte2;

    if (value1._int == value2._int)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IF_ICMPEQ] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison value1 != value2 succeeds
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void if_icmpne(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();

    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 offset = (branchbyte1 << 8) | branchbyte2;

    if (value1._int != value2._int)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IF_ICMPNE] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison value1 < value2 succeeds
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void if_icmplt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();

    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 offset = (branchbyte1 << 8) | branchbyte2;

    if (value1._int < value2._int)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IF_ICMPLT] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison value1 >= value2 succeeds
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void if_icmpge(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();

    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 offset = (branchbyte1 << 8) | branchbyte2;

    if (value1._int >= value2._int)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IF_ICMPGE] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison value1 > value2 succeeds
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void if_icmpgt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();

    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 offset = (branchbyte1 << 8) | branchbyte2;

    if (value1._int > value2._int)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IF_ICMPGT] pc: " << top_frame.pc << endl;
}

/**
 * @brief Branch if int comparison value1 <= value2 succeeds
 * @param constant_pool the run time constant pool
 * @param code the opcode vector
 * @param stack_f a reference to the stack frame
 */
void if_icmple(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    auto value1 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();
    auto value2 = top_frame.operand_stack.top();
    top_frame.operand_stack.top();

    auto branchbyte1 = code[++top_frame.pc];
    auto branchbyte2 = code[++top_frame.pc];
    s2 offset = (branchbyte1 << 8) | branchbyte2;

    if (value1._int <= value2._int)
        top_frame.pc += offset - 2;
    else
        top_frame.pc++;

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[IF_ICMPLE] pc: " << top_frame.pc << endl;
}

void if_acmpeq(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void if_acmpne(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}
