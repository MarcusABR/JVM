/**
 * @file constants.hpp
 * @brief Declaration of the instructions of type constants
 */

#ifndef _CONSTANTS_HPP
#define _CONSTANTS_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void aconst_null(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void bipush(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void dconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void fconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fconst_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void iconst_m1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iconst_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iconst_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iconst_4(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iconst_5(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void lconst_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lconst_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ldc(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ldc_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void ldc2_w(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void nop(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void sipush(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif //_CONSTANTS_HPP