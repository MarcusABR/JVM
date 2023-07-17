#include "../hpp/class_file.hpp"
#include "../hpp/constant_pool_info.hpp"
#include "../hpp/attributes.hpp"
#include "../hpp/utils.hpp"

using namespace std;

attr_info::attr_info(ifstream &file) 
{
    attr_name_idx = ler_bytes_big_endian<u2>(file);
    attr_length = ler_bytes_big_endian<u4>(file);

    for (int i = 0; i < attr_length; i++) 
        info.push_back(ler_bytes_big_endian<u1>(file));
}

attr_info::attr_info(bytestream_it &iterator) 
{
    attr_name_idx = ler_bytes_little_endian<u2>(iterator);
    attr_length = ler_bytes_little_endian<u4>(iterator);
    for (int i = 0; i < attr_length; i++)
        info.push_back(ler_bytes_little_endian<u1>(iterator));
}

field_info::field_info(ifstream &file, cp_info_vector &constant_pool) 
{
    access_flags = ler_bytes_big_endian<u2>(file);
    name_idx = ler_bytes_big_endian<u2>(file);
    descriptor_idx = ler_bytes_big_endian<u2>(file);
    attr_count = ler_bytes_big_endian<u2>(file);

    for (int i = 0; i < attr_count; i++)
    {
        shared_ptr<Attribute> new_attr(new Attribute_Info(file, constant_pool));
        attr.push_back(new_attr);
    }
}

method_info::method_info(ifstream &file, cp_info_vector &constant_pool) 
{
    access_flags = ler_bytes_big_endian<u2>(file);
    name_idx = ler_bytes_big_endian<u2>(file);
    descriptor_idx = ler_bytes_big_endian<u2>(file);
    attr_count = ler_bytes_big_endian<u2>(file);

    for (int i = 0; i < attr_count; i++)
    {
        shared_ptr<Attribute> new_attr(new Attribute_Info(file, constant_pool));
        attr.push_back(new_attr);
    }
}

void class_file::setMagic(u4 v){
    this->magic = magic;
};
void class_file::setMajorVersion(u2 major_version){
    this->major_version = major_version;
};
void class_file::setMinor(u2 minor_version){
    this->minor_version = minor_version;
};
void class_file::setConstantPoolCount(u2 constant_pool_count){
    this->constant_pool_count = constant_pool_count;
};
void class_file::pushConstantPool(shared_ptr<CP_Info> ptr){
    this->constant_pool.push_back(ptr);
};
void class_file::setAccessFlags(u2 access_flag){
    this->access_flag = access_flag;
};
void class_file::setThisClass(u2 this_class){
    this->this_class = this_class;
};
void class_file::setSuperClass(u2 super_class){
    this->super_class = super_class;
};
void class_file::setInterfacesCount(u2 interfaces_count){
    this->interfaces_count = interfaces_count;
};
void class_file::pushInterfaces(u2 interface){
    this->interfaces.push_back(interface);
};
void class_file::setFieldsCount(u2 fields_count){
    this->fields_count = fields_count;
};
void class_file::pushFields(field_info field){
    this->fields.push_back(field);
};
void class_file::setMethodsCount(u2 methods_count){
    this->methods_count = methods_count;
};
void class_file::pushMethods(method_info method){
    this->methods.push_back(method);
};
void class_file::setAttributesCount(u2 attributes_count){
    this->attributes_count = attributes_count;
};
void class_file::pushAttributes(shared_ptr<Attribute> attribute){
    this->attributes.push_back(attribute);
};

// void ClassFile::setMagic(FILE * fp) {
//     ByteReader<typeof(magic)> magicReader;
//     magic = magicReader.byteCatch(fp);
// }
