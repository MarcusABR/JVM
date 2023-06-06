/**
 * @file stores.hpp
 * @brief Declaration of the instructions of type store
 */

#ifndef _STORES_HPP
#define _STORES_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void aastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void astore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void astore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void astore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void astore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void astore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void bastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void castore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void dastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dstore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dstore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dstore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dstore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void dstore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void fastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fstore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fstore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fstore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fstore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void fstore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void iastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void istore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void istore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void istore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void istore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void istore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void lastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lstore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lstore_0(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lstore_1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lstore_2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void lstore_3(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

void sastore(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // _STORES_HPP