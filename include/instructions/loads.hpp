/**
 * @file laods.hpp
 * @brief Declaration of the instructions of type load
 */

#ifndef LOADS_HPP
#define LOADS_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void aaload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void aload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void aload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void aload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void aload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void aload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void baload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void caload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void daload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void iaload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void iload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void laload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void faload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fload_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fload_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fload_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fload_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void saload(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // LOADS_HPP