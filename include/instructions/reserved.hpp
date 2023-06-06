/**
 * @file reserved.hpp
 * @brief Declaration of the instructions of type reserved
 */

#ifndef _RESERVED_HPP
#define _RESERVED_HPP

#include "../frame.hpp"
#include "../constant_pool_info.hpp"

void breakpoint(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void impdep1(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);
void impdep2(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f);

#endif // _RESERVED_HPP