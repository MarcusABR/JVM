#include "../include/utils.hpp"
#include "../include/class_file.hpp"
#include "../include/dump_class_file.hpp"
#include <cmath>
#include <limits>
#include <sys/stat.h>

/**
* @brief Calculate to double
* @param high the most significant bit
* @param low the least significant bit
*/
double calc_double(u4 high, u4 low)
{
    u8 bits = calc_long(high, low);
    if (bits == 0x7ff0000000000000L)
        return numeric_limits<double>::infinity();
    else if (bits == 0xfff0000000000000L)
        return -numeric_limits<double>::infinity();
    else if (bits >= 0x7ff0000000000001L && bits <= 0x7fffffffffffffffL)
        return numeric_limits<double>::quiet_NaN();
    else if (bits >= 0xfff0000000000001L && bits <= 0xffffffffffffffffL)
        return numeric_limits<double>::quiet_NaN();
    else
    {
        int s = ((bits >> 63) == 0) ? 1 : -1;
        int e = (bits >> 52) & 0x7ffL;
        u8 m = (e == 0) ? ((bits & 0xfffffffffffffL) << 1) : ((bits & 0xfffffffffffffL) | 0x10000000000000L);
        return s * m * pow(2, e - 1075);
    }
}

/**
 * @brief Calculate to float
 * @param bytes the run time constant pool
 */
float calc_float(u4 bytes)
{
    if (bytes == 0x7f800000)
        return numeric_limits<float>::infinity();
    else if (bytes == 0xff800000)
        return -numeric_limits<float>::infinity();
    else if (bytes >= 0x7f800001 && bytes <= 0x7fffffff)
        return numeric_limits<float>::signaling_NaN();
    else if (bytes >= 0xff800001 && bytes <= 0xffffffff)
        return numeric_limits<float>::signaling_NaN();
    else
    {
        int s = ((bytes >> 31) == 0) ? 1 : -1;
        int e = ((bytes >> 23) & 0xff);
        int m = (e == 0) ? 
            (bytes & 0x7fffff) << 1 :
            (bytes & 0x7fffff) | 0x800000;

        return s * m * pow(2, e - 150);
    }
}

/**
* @brief Calculate to long
* @param high the most significant bit
* @param low the least significant bit
*/
long long calc_long(u4 high, u4 low)
{
    auto l = ((u8) high << 32) | low;
    return (long long) l;
}

/**
 * @brief Creates a file descriptor
 * @param filename the name of the file
 * @return ifstream the file descriptor
 */
ifstream open_file(string &filename)
{
    ifstream file(filename, ios::binary);
    return file;
}

/**
 * @brief Retrieves the name stored in a Constant_Class_Info instance in the constant pool
 * @param constant_pool a reference to the class_file constant pool
 * @param idx index of the constant pool item
 * @return the name of the class 
 */
string get_name(cp_info_vector &constant_pool, u2 idx)
{
    return to_cp_info(constant_pool[idx - 1])->_class->get_content(constant_pool);
}

/**
 * @brief Checks existence of a file
 * @param name the file name
 * @return true if file exists
 * @return false if file doesnt exists
 */
bool exists(string &name)
{
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}