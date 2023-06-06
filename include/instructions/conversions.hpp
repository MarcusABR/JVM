/**
 * @file conversions.hpp
 * @brief Declaration of the instructions of type conversions
 */

#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void d2i(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void d2f(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void d2l(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void i2d(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void i2f(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void i2l(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void f2d(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void f2i(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void f2l(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void i2b(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void i2c(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void i2s(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void l2d(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void l2f(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void l2i(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // CONVERSIONS_HPP