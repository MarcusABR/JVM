/**
 * @file utils.hpp
 * @brief Declaration of auxiliary functions 
 */

#ifndef _UTILS_HPP
#define _UTILS_HPP

#include "../include/types.hpp"
#include "constant_pool_info.hpp"

double calc_double(u4 high, u4 low);
float calc_float(u4 bytes);
long long calc_long(u4 high, u4 low);
ifstream open_file(string &filename);
string get_name(cp_info_vector&, u2);
bool exists(string &name);

/**
 * @brief A template to read u1, u2, u4 or u8 bytes in big-endian order
 * @tparam T type of byte
 * @param file the class file
 * @return T data read from file
 */
template <typename T>
T read_bytes(ifstream &file) 
{
    u1 byte = 0;
    T data = 0;
    for (int i = 0; i < sizeof(T); i++) 
    {
        file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        data <<= 8;
        data |= byte;
    }
    return data;
}

/**
 * @brief A template to convert u1, u2, u4 or u8 bytes to little-endian order
 * @tparam T type of byte
 * @param iterator bytestream iterator
 * @return T the size of data
 */
template <typename T>
T get_bytes(bytestream_it &iterator)
{
    T return_value = 0;
    for (int i = 1; i <= sizeof(T); i++)
    {
        return_value <<= 8;
        return_value |= *iterator;
        iterator++;
    }
    return return_value;
}

#endif // _UTILS_HPP