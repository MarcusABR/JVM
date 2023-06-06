/**
 * @file extended.hpp
 * @brief Declaration of the instructions of type extended
 */

#ifndef _EXTENDED_HPP
#define _EXTENDED_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void ifnonnull(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ifnull(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void goto_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void jsr_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void multianewarray(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void wide(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // _EXTENDED_HPP