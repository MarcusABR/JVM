/**
 * @file method_area.hpp
 * @brief Declaration of method area structures and mapping
 */

#ifndef _METHOD_AREA_HPP
#define _METHOD_AREA_HPP

#include "frame.hpp"
#include <map>

/**
 * @brief A class container with constant pool, method data, attributes and constructor code
 */
typedef struct class_container {
    cp_info_vector constant_pool;
    map<string, method_info> methods;
} class_container;

/**
 * @brief A mapping of class name to its content 
 */
typedef map<string, class_container> method_area;

#endif // _METHOD_AREA_HPP