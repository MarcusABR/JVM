/**
 * @file references.hpp
 * @brief Declaration of the instructions of type reference
 */

#ifndef REFERENCES_HPP
#define REFERENCES_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void _new(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void anewarray(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void arraylength(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void athrow(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void checkcast(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void getfield(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void getstatic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void instanceof(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void invokedynamic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void invokeinterface(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void invokespecial(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void invokestatic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void invokevirtual(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void monitorenter(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void monitorexit(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void newarray(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void putfield(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void putstatic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // REFERENCES_HPP