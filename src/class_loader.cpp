#include "../include/class_loader.hpp"
#include "../include/cmd_arguments.hpp"
#include "../include/class_file.hpp"
#include "../include/utils.hpp"

/**
 * @brief Loads the .class input file and parses it into a class_file object
 * @param filename the path to the .class file
 */
class_file* ClassLoader::load(string &filename)
{
    class_file *class_f = new class_file;
    file = open_file(filename);

    get_metadata(class_f);
    get_constant_pool(class_f);
    get_class_data(class_f);
    get_interfaces(class_f);
    get_fields(class_f);
    get_methods(class_f);
    get_attributes(class_f);

    return class_f;
}

/**
 * @brief Retrives CAFEBABE, minor and major versions of the .class file and inserts it to a instance of class_file
 * @param class_f a reference to the class_file object
 */
void ClassLoader::get_metadata(class_file *class_f)
{
    class_f->magic         = read_bytes<u4>(file); // signature (0xCAFEBABE) 
    class_f->minor_version = read_bytes<u2>(file);
    class_f->major_version = read_bytes<u2>(file);
}

/**
 * @brief Retrives constant pool data from the .class file and inserts it to a instance of class_file
 * @param class_f a reference to the class_file object
 */
void ClassLoader::get_constant_pool(class_file *class_f)
{
    class_f->constant_pool_count = read_bytes<u2>(file); 
    int iteration_counter = class_f->constant_pool_count - 1;
    while (iteration_counter--)
    {
        u1 tag = read_bytes<u1>(file);
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

/**
 * @brief Retrives the access flags, class name and super_class from the .class file and inserts it to a instance of class_file
 * @param class_f a reference to the class_file object
 */
void ClassLoader::get_class_data(class_file *class_f)
{
    class_f->access_flag = read_bytes<u2>(file);
    class_f->this_class  = read_bytes<u2>(file);
    class_f->super_class = read_bytes<u2>(file);
}

/**
 * @brief Retrives interfaces data from the .class file and inserts it to a instance of class_file
 * @param class_f a reference to the class_file object
 */
void ClassLoader::get_interfaces(class_file *class_f)
{
    class_f->interfaces_count = read_bytes<u2>(file);
    
    for (int i = 0; i < class_f->interfaces_count; i++)
        class_f->interfaces.push_back(read_bytes<u2>(file));
}

/**
 * @brief Retrives fields data from the .class file and inserts it to a instance of class_file
 * @param class_f a reference to the class_file object
 */
void ClassLoader::get_fields(class_file *class_f)
{
    class_f->fields_count = read_bytes<u2>(file);

    for(int i = 0; i < class_f->fields_count; i++)
        class_f->fields.push_back(field_info(file, class_f->constant_pool));
}

/**
 * @brief Retrives methods data from the .class file and inserts it to a instance of class_file
 * @param class_f a reference to the class_file object
 */
void ClassLoader::get_methods(class_file *class_f)
{
    class_f->methods_count = read_bytes<u2>(file);

    for(int i = 0; i < class_f->methods_count; i++)
        class_f->methods.push_back(method_info(file, class_f->constant_pool));
}

/**
 * @brief Retrives attributes data from the .class file and inserts it to a instance of class_file
 * @param class_f a reference to the class_file object
 */
void ClassLoader::get_attributes(class_file *class_f)
{
    class_f->attributes_count = read_bytes<u2>(file);

    for (int i = 0; i < class_f->attributes_count; i++)
    {
        shared_ptr<Attribute> new_attr(new Attribute_Info(file, class_f->constant_pool));
        class_f->attributes.push_back(new_attr);
    }
}
