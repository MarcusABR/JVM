/**
 * @file frame.hpp
 * @brief Declaration of frame and auxiliary structures
 */

#ifndef _FRAME_HPP
#define _FRAME_HPP

#include "class_file.hpp"
#include "types.hpp"
#include <cstddef>
#include <stack>
#include <string>
#include <vector>

struct operand_t;
struct reference;

/// A single local variable can hold a value of type boolean, byte, char, short, int,
/// float, reference, or returnAddress. A pair of local variables can hold a value
/// of type long or double.
typedef struct operand_t {
    union {
        u1 _boolean;
        u1 _byte;
        u1 _char;
        s2 _short;
        s4 _int;
        s8 _long;
        float _float;
        double _double;
        // string* _string;

        // u4 *_return_address;
        // reference *_reference;
    };
} operand_t;

typedef struct reference {
    vector<operand_t> array;
} reference;

/**
 * @brief A frame with local variables array, operand stack and reference to run-time constant pool 
 */
typedef struct frame_t {
    frame_t(cp_info_vector* constant_pool);
    vector<operand_t> local_variables_array = {};
    stack<operand_t> operand_stack = {};
    cp_info_vector* run_time_constant_pool;
    u4 pc = 0;
    void execute_frame(method_info, stack<frame_t>*);
    void insert_into_local(u4, operand_t&);
} frame_t;

#endif // _FRAME_HPP