#include "../hpp/class_loader.hpp"
#include "../hpp/class_file.hpp"
#include "../hpp/utils.hpp"


class_file* ClassLoader::carregar(string &filename)
{
    class_file *class_f = new class_file;
    file = abrir_arquivo(filename);

    get_metadata(class_f);
    get_constant_pool(class_f);
    get_class_data(class_f);
    get_interfaces(class_f);
    get_fields(class_f);
    get_methods(class_f);
    get_attributes(class_f);

    return class_f;
}

void ClassLoader::get_metadata(class_file *class_f)
{
    class_f->magic         = ler_bytes_big_endian<u4>(file); // signature (0xCAFEBABE) 
    class_f->minor_version = ler_bytes_big_endian<u2>(file);
    class_f->major_version = ler_bytes_big_endian<u2>(file);
}

void ClassLoader::get_constant_pool(class_file *class_f)
{
    class_f->constant_pool_count = ler_bytes_big_endian<u2>(file); 
    int iteration_counter = class_f->constant_pool_count - 1;
    while (iteration_counter--)
    {
        u1 tag = ler_bytes_big_endian<u1>(file);
        shared_ptr<CP_Info> new_el(new CP_Info(tag, file));
        class_f->constant_pool.push_back(new_el);
        if ((CONSTANT_Types)tag == CONSTANT_Double || (CONSTANT_Types)tag == CONSTANT_Long)
        {
            iteration_counter--;
            shared_ptr<CP_Info> continuation_el(new CP_Info(CONSTANT_Continuation, file));
            class_f->constant_pool.push_back(continuation_el);
        }
    }
}

void ClassLoader::get_class_data(class_file *class_f)
{
    class_f->access_flag = ler_bytes_big_endian<u2>(file);
    class_f->this_class  = ler_bytes_big_endian<u2>(file);
    class_f->super_class = ler_bytes_big_endian<u2>(file);
}

void ClassLoader::get_interfaces(class_file *class_f)
{
    class_f->interfaces_count = ler_bytes_big_endian<u2>(file);
    
    for (int i = 0; i < class_f->interfaces_count; i++)
        class_f->interfaces.push_back(ler_bytes_big_endian<u2>(file));
}

void ClassLoader::get_fields(class_file *class_f)
{
    class_f->fields_count = ler_bytes_big_endian<u2>(file);

    for(int i = 0; i < class_f->fields_count; i++)
        class_f->fields.push_back(field_info(file, class_f->constant_pool));
}

void ClassLoader::get_methods(class_file *class_f)
{
    class_f->methods_count = ler_bytes_big_endian<u2>(file);

    for(int i = 0; i < class_f->methods_count; i++)
        class_f->methods.push_back(method_info(file, class_f->constant_pool));
}

void ClassLoader::get_attributes(class_file *class_f)
{
    class_f->attributes_count = ler_bytes_big_endian<u2>(file);

    for (int i = 0; i < class_f->attributes_count; i++)
    {
        shared_ptr<Attribute> new_attr(new Attribute_Info(file, class_f->constant_pool));
        class_f->attributes.push_back(new_attr);
    }
}
