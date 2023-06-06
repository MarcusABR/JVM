/**
 * @file math.hpp
 * @brief Declaration of the instructions of type math
 */

#ifndef _MATH_HPP
#define _MATH_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void dadd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fadd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iadd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ladd(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void isub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lsub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fsub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dsub(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void imul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lmul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fmul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dmul(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void idiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ldiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fdiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ddiv(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void irem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lrem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void frem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void drem(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void ineg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lneg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fneg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dneg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void ishl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lshl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ishr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lshr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void iushr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lushr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void iand(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void land(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void ior(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lor(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ixor(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lxor(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void iinc(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f); 

#endif // _MATH_HPP