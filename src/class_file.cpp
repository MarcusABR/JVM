#include "../include/class_file.hpp"
#include "../include/constant_pool_info.hpp"
#include "../include/attributes.hpp"
#include "../include/utils.hpp"

using namespace std;

/**
 * @brief Construct a new attr_info object
 * @param file the input .class file
 */
attr_info::attr_info(ifstream &file) 
{
    attr_name_idx = read_bytes<u2>(file);
    attr_length = read_bytes<u4>(file);

    for (int i = 0; i < attr_length; i++) 
        info.push_back(read_bytes<u1>(file));
}

/**
 * @brief Construct a new attr_info object
 * @param iterator the iterator of a byte vector (bytestream)
 */
attr_info::attr_info(bytestream_it &iterator) 
{
    attr_name_idx = get_bytes<u2>(iterator);
    attr_length = get_bytes<u4>(iterator);
    for (int i = 0; i < attr_length; i++)
        info.push_back(get_bytes<u1>(iterator));
}

/**
 * @brief Construct a new field_info object
 * @param file the input .class file
 * @param constant_pool the class_file object constant pool
 */
field_info::field_info(ifstream &file, cp_info_vector &constant_pool) 
{
    access_flags = read_bytes<u2>(file);
    name_idx = read_bytes<u2>(file);
    descriptor_idx = read_bytes<u2>(file);
    attr_count = read_bytes<u2>(file);

    for (int i = 0; i < attr_count; i++)
    {
        shared_ptr<Attribute> new_attr(new Attribute_Info(file, constant_pool));
        attr.push_back(new_attr);
    }
}

/**
 * @brief Construct a new method_info object
 * @param file the input .class file
 * @param constant_pool the class_file object constant pool 
 */
method_info::method_info(ifstream &file, cp_info_vector &constant_pool) 
{
    access_flags = read_bytes<u2>(file);
    name_idx = read_bytes<u2>(file);
    descriptor_idx = read_bytes<u2>(file);
    attr_count = read_bytes<u2>(file);

    for (int i = 0; i < attr_count; i++)
    {
        shared_ptr<Attribute> new_attr(new Attribute_Info(file, constant_pool));
        attr.push_back(new_attr);
    }
}
