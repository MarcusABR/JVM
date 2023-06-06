/**
 * @file comparisons.hpp
 * @brief Declaration of the instructions of type comparison
 */

#ifndef COMPARISONS_HPP
#define COMPARISONS_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void dcmpg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dcmpl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void fcmpg(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fcmpl(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void ifeq(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ifge(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ifgt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ifle(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iflt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ifne(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void lcmp(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void if_acmpeq(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void if_acmpne(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void if_icmpeq(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void if_icmpge(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void if_icmpgt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void if_icmple(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void if_icmplt(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void if_icmpne(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // COMPARISONS_HPP