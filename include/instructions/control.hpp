/**
 * @file control.hpp
 * @brief Declaration of the instructions of type control
 */

#ifndef _CONTROL_HPP
#define _CONTROL_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void _goto(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void _return(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void areturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void dreturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void freturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void ireturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void jsr(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void lookupswitch(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lreturn(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void ret(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void tableswitch(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif //_CONTROL_HPP