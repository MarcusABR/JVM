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

// typedef struct class_file {
//     u4 magic;
//     u2 minor_version;
//     u2 major_version;
//     u2 constant_pool_count;
//     cp_info_vector constant_pool;
//     u2 access_flag;
//     u2 this_class;
//     u2 super_class;
//     u2 interfaces_count;
//     vector<u2> interfaces;
//     u2 fields_count;
//     vector<field_info> fields;
//     u2 methods_count;
//     vector<method_info> methods;
//     u2 attributes_count;
//     attr_info_vector attributes;
// } class_file;

using namespace std;
/** @class class_file
*   @brief Classe que contém toda a estrutura do .class
*/

class class_file {
private:
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    // vector<CPInfo*> constantPool;
    cp_info_vector constant_pool;
    u2 access_flag;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    vector<u2> interfaces;
    u2 fields_count;
    vector<field_info> fields;
    // vector<FieldInfo*> fields;
    u2 methods_count;
    vector<method_info> methods;
    // vector<MethodInfo*> methods;
    u2 attributes_count;
    uint16_t attributesCount;
    // AttributeInfo* attributes;
    attr_info_vector attributes;

    
public:
    // static const uint32_t MAGIC_NUMBER = 0xCAFEBABE;
    // static const uint16_t ACC_PUBLIC = 0x0001;
    // static const uint16_t ACC_FINAL = 0x0010;
    // static const uint16_t ACC_SUPER = 0x0020;
    // static const uint16_t ACC_INTERFACE = 0x0200;
    // static const uint16_t ACC_ABSTRACT = 0x0400;
    // static const uint16_t ACC_SYNTHETIC = 0x1000;
    // static const uint16_t ACC_ANNOTATION = 0x2000;
    // static const uint16_t ACC_ENUM = 0x4000;
    class_file();
    ~class_file();

    u4 getMagic() {
        return magic;
    }
    u2 getMajorVersion() {
        return major_version;
    }
    u2 getMinorVersion() {
        return minor_version;
    }
    u2 getConstantPoolCount() {
        return constant_pool_count;
    }
    cp_info_vector getConstantPool() {
        return constant_pool;
    }

    u2 getAccessFlags() {
        return access_flag;
    }
    u2 getThisClass() {
        return this_class;
    }
    u2 getSuperClass() {
        return super_class;
    }
    u2 getInterfacesCount() {
        return interfaces_count;
    }

    vector<u2> getInterfaces() {
        return interfaces;
    }

    u2 getFieldsCount() {
        return fields_count;
    }

    vector<field_info> getFields() {
        return fields;
    }

    u2 getMethodsCount() {
        return methods_count;
    }

    vector<method_info> getMethods() {
        return methods;
    }

    u2 getAttributesCount() {
        return attributes_count;
    }

    attr_info_vector getAttributes() {
        return attributes;
    }

    void setMagic(u4 magic);
    void setMajorVersion(u2 major_version);
    void setMinor(u2 minor_version);
    void setConstantPoolCount(u2 constant_pool_count); 
    void pushConstantPool(shared_ptr<CP_Info> ptr); //diferente
    void setAccessFlags(u2 access_flag);
    void setThisClass(u2 this_class);
    void setSuperClass(u2 super_class);
    void setInterfacesCount(u2 interfaces_count);
    void pushInterfaces(u2 interface); //diferente
    void setFieldsCount(u2 fields_count);
    void pushFields(field_info field); //diferente
    void setMethodsCount(u2 methods_count);
    void pushMethods(method_info method); //diferente
    void setAttributesCount(u2 attributes_count);
    void pushAttributes(shared_ptr<Attribute> attribute); //diferente
};


#endif // _CLASS_FILE_HPP