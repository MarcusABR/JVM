#ifndef _METHOD_AREA_HPP
#define _METHOD_AREA_HPP

#include <map>

typedef struct class_container {
    cp_info_vector constant_pool;
    map<string, method_info> methods;
} class_container;

typedef map<string, class_container> method_area;

#endif // _METHOD_AREA_HPP