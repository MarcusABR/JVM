#ifndef _UTILS_HPP
#define _UTILS_HPP

#include "types.hpp"
#include "constant_pool_info.hpp"

double ler_double(u4 high, u4 low);
float ler_float(u4 bytes);
long long ler_long(u4 high, u4 low);
ifstream abrir_arquivo(string &filename);
string ler_nome(cp_info_vector&, u2);
bool existe(string &name);


template <typename T>
T ler_bytes_big_endian(ifstream &arquivo) 
{
    u1 byte = 0;
    T data = 0;
    for (int i = 0; i < sizeof(T); i++) 
    {
        arquivo.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        data <<= 8;
        data |= byte;
    }
    return data;
}

template <typename T>
T ler_bytes_little_endian(bytestream_it &iterator)
{
    T valor = 0;
    for (int i = 1; i <= sizeof(T); i++)
    {
        valor <<= 8;
        valor |= *iterator;
        iterator++;
    }
    return valor;
}

#endif // _UTILS_HPP