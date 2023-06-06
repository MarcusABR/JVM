/**
 * @file stack.hpp
 * @brief Declaration of the instructions of type stack
 */

#ifndef _STACK_HPP
#define _STACK_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void dup(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dup_x1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dup_x2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dup2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dup2_x1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dup2_x2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void pop(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void pop2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void swap(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // _STACK_HPP