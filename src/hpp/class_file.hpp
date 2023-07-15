#ifndef _CLASS_FILE_HPP
#define _CLASS_FILE_HPP

#include "attributes.hpp"

using namespace std;

#define ACC_PUBLIC     0x0001 
#define ACC_FINAL      0x0010 
#define ACC_SUPER      0x0020 
#define ACC_INTERFACE  0x0200 
#define ACC_ABSTRACT   0x0400 
#define ACC_SYNTHETIC  0x1000 
#define ACC_ANNOTATION 0x2000 
#define ACC_ENUM       0x4000 
#define ACC_PUBLIC    0x0001 
#define ACC_PRIVATE   0x0002 
#define ACC_PROTECTED 0x0004 
#define ACC_STATIC    0x0008 
#define ACC_FINAL     0x0010 
#define ACC_VOLATILE  0x0040 
#define ACC_TRANSIENT 0x0080 
#define ACC_SYNTHETIC 0x1000 
#define ACC_ENUM      0x4000 
#define ACC_PUBLIC        0x0001
#define ACC_PRIVATE       0x0002 
#define ACC_PROTECTED     0x0004 
#define ACC_STATIC        0x0008 
#define ACC_FINAL         0x0010 
#define ACC_SYNCHRONIZED  0x0020 
#define ACC_BRIDGE        0x0040 
#define ACC_VARARGS       0x0080 
#define ACC_NATIVE        0x0100 
#define ACC_ABSTRACT      0x0400 
#define ACC_STRICT        0x0800 
#define ACC_SYNTHETIC     0x1000 

typedef struct attr_info {
    attr_info(ifstream &file);
    attr_info(bytestream_it &iterator);
    u2 attr_name_idx;
    u4 attr_length;
    vector<u1> info;
} attr_info;

typedef struct field_info {
    field_info(ifstream&, cp_info_vector&);
    u2 access_flags;
    u2 name_idx;
    u2 descriptor_idx;
    u2 attr_count;
    attr_info_vector attr;
} field_info;

typedef struct method_info {
    method_info() = default;
    method_info(ifstream&, cp_info_vector&);
    u2 access_flags;
    u2 name_idx;
    u2 descriptor_idx;
    u2 attr_count;
    attr_info_vector attr;
} method_info;

typedef struct class_file {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info_vector constant_pool;
    u2 access_flag;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    vector<u2> interfaces;
    u2 fields_count;
    vector<field_info> fields;
    u2 methods_count;
    vector<method_info> methods;
    u2 attributes_count;
    attr_info_vector attributes;
} class_file;

#endif // _CLASS_FILE_HPP