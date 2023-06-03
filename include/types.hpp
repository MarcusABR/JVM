/**
 * @file types.hpp
 * @brief Declaration of unsigned and signed types, dynamic pointer cast
 */

#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <fstream>
#include <vector>
#include <cstdint>

#define to_cp_info dynamic_pointer_cast<CP_Info>
#define to_attr_info dynamic_pointer_cast<Attribute_Info>

using namespace std;

/// Unsigned types
typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

/// Signed types
typedef int8_t  s1;
typedef int16_t s2; 
typedef int32_t s4;
typedef int64_t s8;

typedef vector<u1> bytestream;
typedef vector<u1>::iterator bytestream_it;

#endif // _TYPES_HPP
