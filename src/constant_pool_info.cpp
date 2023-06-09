#include "../include/constant_pool_info.hpp"
#include "../include/class_file.hpp"
#include "../include/dump_class_file.hpp"
#include "../include/utils.hpp"
#include <string>

extern ofstream outfile;

/**
 * @brief Construct a new cp_item object
 * @param tag a valid value of the CONSTANT_Types enum
 */
CP_Item::CP_Item(u1 tag) : tag((CONSTANT_Types)tag) {}

/**
 * @brief Construct a new cp_info object
 * @param tag a valid value of the CONSTANT_Types enum
 * @param file the input .class file
 */
CP_Info::CP_Info(u1 tag, ifstream &file)
: CP_Item(tag)
{
    switch (this->tag) 
    {
        case CONSTANT_Utf8:
            _utf8 = new CONSTANT_utf8_info(file);
            break;
        case CONSTANT_Integer:
            _integer = new CONSTANT_integer_info(file);
            break;
        case CONSTANT_Float:
            _float = new CONSTANT_float_info(file);
            break;
        case CONSTANT_Long:
            _long = new CONSTANT_long_info(file);
            break;
        case CONSTANT_Double:
            _double = new CONSTANT_double_info(file);
            break;
        case CONSTANT_Class:
            _class = new CONSTANT_class_info(file);
            break;
        case CONSTANT_String:
            _string = new CONSTANT_string_info(file);
            break;
        case CONSTANT_Fieldref:
            _fieldref = new CONSTANT_fieldref_info(file);
            break;
        case CONSTANT_Methodref:
            _methodref = new CONSTANT_methodref_info(file);
            break;
        case CONSTANT_InterfaceMethodref:
            _interface_methodref = new CONSTANT_interface_methodref_info(file);
            break;
        case CONSTANT_NameAndType:
            _name_and_type = new CONSTANT_name_and_type_info(file);
            break;
        case CONSTANT_MethodHandle:
            _method_handle = new CONSTANT_method_handle_info(file);
            break;
        case CONSTANT_MethodType:
            _method_type = new CONSTANT_method_type_info(file);
            break;
        case CONSTANT_InvokeDynamic:
            _invoke_dynamic= new CONSTANT_invoke_dynamic_info(file);
            break; 
        default:
            break;
    }
}

/**
 * @brief Destroy the cp_info object
 */
CP_Info::~CP_Info() 
{
    switch (tag) 
    {
        case CONSTANT_Utf8: delete _utf8; break;
        case CONSTANT_Integer: delete _integer; break;
        case CONSTANT_Float: delete _float; break;
        case CONSTANT_Long: delete _long; break;
        case CONSTANT_Double: delete _double; break;
        case CONSTANT_Class: delete _class; break;
        case CONSTANT_String: delete _string; break;
        case CONSTANT_Fieldref: delete _fieldref; break;
        case CONSTANT_Methodref: delete _methodref; break;
        case CONSTANT_InterfaceMethodref: delete _interface_methodref; break;
        case CONSTANT_NameAndType: delete _name_and_type; break;
        case CONSTANT_MethodHandle: delete _method_handle; break;
        case CONSTANT_MethodType: delete _method_type; break;
        case CONSTANT_InvokeDynamic: delete _invoke_dynamic; break;
        default: break;
    }
}

/**
 * @brief  Dump CP_Info specific information to the markdown outfile
 * @param constant_pool the class_file object constant pool
 * @param counter a reference to the current constant pool index
 */
void CP_Info::dump_info_to_file(cp_info_vector &constant_pool, unsigned int &counter)
{
    switch (tag) 
    {
        case CONSTANT_Utf8:
            outfile << "--> [" << counter++ << "] *CONSTANT_Utf8_info*" << endl;
            _utf8->dump_to_file();
            break;
        case CONSTANT_Integer:
            outfile << "--> [" << counter++ << "] *CONSTANT_Integer_info*" << endl;
            _integer->dump_to_file();
            break;
        case CONSTANT_Float:
            outfile << "--> [" << counter++ << "] *CONSTANT_Float_info*" << endl;
            _float->dump_to_file();
            break;
        case CONSTANT_Long:
            outfile << "--> [" << counter++ << "] *CONSTANT_Long_info*" << endl;
            _long->dump_to_file();
            break;
        case CONSTANT_Double:
            outfile << "--> [" << counter++ << "] *CONSTANT_Double_info*" << endl;
            _double->dump_to_file();
            break;
        case CONSTANT_Class:
            outfile << "--> [" << counter++ << "] *CONSTANT_Class_info*" << endl;
            _class->dump_to_file(constant_pool);
            break;
        case CONSTANT_String:
            outfile << "--> [" << counter++ << "] *CONSTANT_String_info*" << endl;
            _string->dump_to_file(constant_pool);
            break;
        case CONSTANT_Fieldref:
            outfile << "--> [" << counter++ << "] *CONSTANT_Fieldref_info*" << endl;
            _fieldref->dump_to_file(constant_pool);
            break;
        case CONSTANT_Methodref:
            outfile << "--> [" << counter++ << "] *CONSTANT_Methodref_info*" << endl;
            _methodref->dump_to_file();
            break;
        case CONSTANT_InterfaceMethodref:
            outfile << "--> [" << counter++ << "] *CONSTANT_InterfaceMethodref_info*" << endl;
            _interface_methodref->dump_to_file();
            break;
        case CONSTANT_NameAndType:
            outfile << "--> [" << counter++ << "] *CONSTANT_NameAndType_info*" << endl;
            _name_and_type->dump_to_file();
            break;
        case CONSTANT_MethodHandle:
            outfile << "--> [" << counter++ << "] *CONSTANT_MethodHandle_info*" << endl;
            _method_handle->dump_to_file();
            break;
        case CONSTANT_MethodType:
            outfile << "--> [" << counter++ << "] *CONSTANT_MethodType_info*" << endl;
            _method_type->dump_to_file();
            break;
        case CONSTANT_InvokeDynamic:
            outfile << "--> [" << counter++ << "] *CONSTANT_InvokeDynamic_info*" << endl;
            _invoke_dynamic->dump_to_file();
            break;
        case CONSTANT_Continuation:
            outfile << "--> [" << counter++ << "] *(large numeric continued)*" << endl << endl;
            break;
    }
}

/**
 * @brief Function that retrieves the relevent content of a CP_Info object as a string
 * @param constant_pool the class_file object constant pool
 * @return the string representing the CP_Info content
 */
string CP_Info::get_content(cp_info_vector &constant_pool)
{
    switch (tag) 
    {
        case CONSTANT_Integer: return _integer->get_content();
        case CONSTANT_Float: return _float->get_content();
        case CONSTANT_Long: return _long->get_content();
        case CONSTANT_Double: return _double->get_content();
        case CONSTANT_String: return _string->get_content(constant_pool);
        case CONSTANT_Methodref: return _methodref->get_content(constant_pool);
        case CONSTANT_Fieldref: return _fieldref->get_content(constant_pool);
        case CONSTANT_Class: return _class->get_content(constant_pool);
        default: return "Invalid tag";
    }
}

/**
 * @brief Construct a new Constant_UTF8_Info object
 * @param file the input .class file
 */
CONSTANT_utf8_info::CONSTANT_utf8_info(ifstream &file) 
{
    length = read_bytes<u2>(file);

    for (int i = 0; i < length; i++)
        bytes.push_back(read_bytes<u1>(file));
}

/**
 * @brief Dump Constant_UTF8 specfic information to the markdown outfile
 */
void CONSTANT_utf8_info::dump_to_file()
{
    outfile << "- Length '" << length << "'" << endl;
    outfile << "- Bytes [ '" << get_utf8_content(*this) << "']" << endl << endl;
}

/**
 * @brief Function that retrieves the bytes stored in Constant_Utf8_Info as a string
 * @return the UTF-8 string 
 */
string CONSTANT_utf8_info::get_content()
{
    return get_utf8_content(*this);
}

/**
 * @brief Construct a new Constant_Float_Info object
 * @param file the input .class file
 */
CONSTANT_integer_info::CONSTANT_integer_info(ifstream &file) 
{
    bytes = read_bytes<u4>(file);
}

/**
 * @brief Dump Constant_integer specfic information to the markdown outfile
 */
void CONSTANT_integer_info::dump_to_file()
{
    outfile << "- Bytes '" << bytes << "'" << endl;
    outfile << endl;
}

/**
 * @brief Function that retrieves the bytes stored in Constant_Integer_Info as a string
 * @return integer converted to a string 
 */
string CONSTANT_integer_info::get_content()
{
    return to_string(bytes);
}

/**
 * @brief Construct a new Constant_Float_Info object
 * @param file the input .class file
 */
CONSTANT_float_info::CONSTANT_float_info(ifstream &file) 
{
    bytes = read_bytes<u4>(file);
}

/**
 * @brief Dump Constant_float specfic information to the markdown outfile
 */
void CONSTANT_float_info::dump_to_file()
{
    ios_base::fmtflags f(outfile.flags());
    outfile << "- Bytes '0x" << hex << bytes << "'" << endl;
    outfile.flags(f);
    outfile << "- Float '" << calc_float(bytes) << "'" << endl;
    outfile << endl;
}

/**
 * @brief Function that retrieves the bytes stored in Constant_Float_Info as a string
 * @return float converted to a string 
 */
string CONSTANT_float_info::get_content()
{
    return to_string(calc_float(bytes));
}

/**
 * @brief Construct a new Constant_Long_Info object
 * @param file the input .class file
 */
CONSTANT_long_info::CONSTANT_long_info(ifstream &file) 
{
    high_bytes = read_bytes<u4>(file);
    low_bytes = read_bytes<u4>(file);
}

/**
 * @brief Dump Constant_long specfic information to the markdown outfile
 */
void CONSTANT_long_info::dump_to_file()
{
    ios_base::fmtflags f(outfile.flags());
    outfile << "- High Bytes '0x" << hex << high_bytes << "'" << endl;
    outfile << "- Low Bytes '0x" << hex << low_bytes << "'" << endl;
    outfile.flags(f);
    outfile << "- Long '" << calc_long(high_bytes, low_bytes) << "'" << endl;
    outfile << endl;
}

/**
 * @brief Function that retrieves the bytes stored in Constant_Long_Info as a string
 * @return long converted to a string 
 */
string CONSTANT_long_info::get_content()
{
    return to_string(calc_long(high_bytes, low_bytes));
}

/**
 * @brief Construct a new Constant_Double_Info object
 * @param file the input .class file
 */
CONSTANT_double_info::CONSTANT_double_info(ifstream &file) 
{
    high_bytes = read_bytes<u4>(file);
    low_bytes = read_bytes<u4>(file);
}

/**
 * @brief Dump Constant_double specfic information to the markdown outfile
 */
void CONSTANT_double_info::dump_to_file()
{
    ios_base::fmtflags f(outfile.flags());
    outfile << "- High Bytes '0x" << hex << high_bytes << "'" << endl;
    outfile << "- Low Bytes '0x" << hex << low_bytes << "'" << endl;
    outfile.flags(f);
    outfile << "- Double '" << calc_double(high_bytes, low_bytes) << "'" << endl;
    outfile << endl;
}

/**
 * @brief Function that retrieves the bytes stored in Constant_Double_Info as a string
 * @return double converted to a string 
 */
string CONSTANT_double_info::get_content()
{
    return to_string(calc_double(high_bytes, low_bytes));
}

/**
 * @brief Construct a new Constant_Class_Info object
 * @param file the input .class file
 */
CONSTANT_class_info::CONSTANT_class_info(ifstream &file) 
{
    name_idx = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_class specfic information to the markdown outfile
 * @param constant_pool the class_file constant pool
 */
void CONSTANT_class_info::dump_to_file(cp_info_vector &constant_pool)
{
    auto class_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    outfile << "- Name Index '" << name_idx << "'" << endl;
    outfile << "- Class Name '<" << get_utf8_content(class_name) << ">'";
    outfile << endl << endl;
}

/**
 * @brief Function that retrieves the name of the class stored in Constant_Class_Info as a string
 * @param constant_pool the class_file constant pool
 * @return the name of the class 
 */
string CONSTANT_class_info::get_content(cp_info_vector &constant_pool)
{
    auto class_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    return get_utf8_content(class_name);
}

/**
 * @brief Construct a new Constant_String_Info object
 * @param file the input .class file
 */
CONSTANT_string_info::CONSTANT_string_info(ifstream &file) 
{
    str_idx = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_string specfic information to the markdown outfile
 * @param constant_pool the class_file constant pool
 */
void CONSTANT_string_info::dump_to_file(cp_info_vector &constant_pool)
{
    auto str = *(to_cp_info(constant_pool[str_idx - 1])->_utf8);
    outfile << "- String Index '" << str_idx << "'" << endl;
    outfile << "- String '<" << get_utf8_content(str) << ">'";
    outfile << endl << endl;
}

/**
 * @brief Function that retrieves the string stored in Constant_String_Info
 * @param constant_pool the class_file constant pool
 * @return the string stored
 */
string CONSTANT_string_info::get_content(cp_info_vector &constant_pool)
{
    auto string_utf8 = *(to_cp_info(constant_pool[str_idx - 1])->_utf8);
    return get_utf8_content(string_utf8);
}

/**
 * @brief Construct a new Constant_Fieldref_Info object
 * @param file the input .class file
 */
CONSTANT_fieldref_info::CONSTANT_fieldref_info(ifstream &file) 
{
    class_idx = read_bytes<u2>(file);
    name_and_type_idx = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_fieldref specfic information to the markdown outfile
 * @param constant_pool the class_file constant pool
 */
void CONSTANT_fieldref_info::dump_to_file(cp_info_vector &constant_pool)
{
    auto class_name_index = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_index - 1])->_utf8);
    outfile << "- Class Index '" << class_idx << "'" << endl;
    outfile << "- Class Name '<" << get_utf8_content(class_name) << ">'" << endl;
    
    auto nt_name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto nt_name = *(to_cp_info(constant_pool[nt_name_idx - 1])->_utf8);
    auto nt_descriptor_index = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto nt_descriptor = *(to_cp_info(constant_pool[nt_descriptor_index - 1])->_utf8);
    outfile << "- Name And Type Index '" << name_and_type_idx << "'" << endl;
    outfile << "- Name And Type '<" << get_utf8_content(nt_name) << ":" << get_utf8_content(nt_descriptor) << ">'";
    outfile << endl << endl;
}

/**
 * @brief Function that retrieves the name and descriptor stored in Constant_Fieldref_Info concatenated in a string
 * @param constant_pool the class_file constant pool
 * @return the formated string containing the name and descriptor
 */
string CONSTANT_fieldref_info::get_content(cp_info_vector &constant_pool)
{
    auto class_name_idx = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_idx - 1])->_utf8);
    auto name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto descriptor_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto method_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    auto method_descriptor = *(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8);
    return (get_utf8_content(class_name) + "." + get_utf8_content(method_name) + " : " + get_utf8_content(method_descriptor));
}

/**
 * @brief Construct a new Constant_Methodref_Info object
 * @param file the input .class file
 */
CONSTANT_methodref_info::CONSTANT_methodref_info(ifstream &file) 
{
    class_idx = read_bytes<u2>(file);
    name_and_type_idx = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_methodref specfic information to the markdown outfile
 */
void CONSTANT_methodref_info::dump_to_file()
{
    outfile << "- Class Index '" << class_idx << "'" << endl;
    outfile << "- Name And Type Index '" << name_and_type_idx << "'" << endl;
    outfile << endl;
}

/**
 * @brief Function that retrieves the name and descriptor stored in Constant_Methodref_Info concatenated in a string
 * @param constant_pool the class_file constant pool
 * @return the formated string containing the name and descriptor
 */
string CONSTANT_methodref_info::get_content(cp_info_vector &constant_pool)
{
    auto class_name_idx = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_idx - 1])->_utf8);
    auto name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto descriptor_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto method_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    auto method_descriptor = *(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8);
    return (get_utf8_content(class_name) + "." + get_utf8_content(method_name) + " : " + get_utf8_content(method_descriptor));
}

/**
 * @brief Retrieves the string representing the class name of the class_index stored in a instance of Constant_Methodref_Info
 * @param constant_pool the class_file constant pool
 * @return the name of the class 
 */
string CONSTANT_methodref_info::get_class_name(cp_info_vector &constant_pool)
{
    auto class_name_idx = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_idx - 1])->_utf8);
    return get_utf8_content(class_name);
}

/**
 * @brief Retrives the string representing the method name of name_index stored in a instance of Constant_Methodref_Info
 * @param constant_pool the class_file constant pool
 * @return the name of the method 
 */
string CONSTANT_methodref_info::get_method_name(cp_info_vector &constant_pool)
{
    auto name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto method_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    return get_utf8_content(method_name);
}

/**
 * @brief Retrives the string representing the method descriptor of descriptor_index stored in a instance of Constant_Methodref_Info
 * @param constant_pool the class_file constant pool
 * @return the string representing the method descriptor
 */
string CONSTANT_methodref_info::get_method_descriptor(cp_info_vector &constant_pool)
{
    auto descriptor_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto method_descriptor = *(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8);
    return get_utf8_content(method_descriptor);
}

/**
 * @brief Construct a new Constant_Interface_Methodref_Info object
 * @param file the input .class file
 */
CONSTANT_interface_methodref_info::CONSTANT_interface_methodref_info(ifstream &file) 
{
    class_idx = read_bytes<u2>(file);
    name_and_type_idx = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_interface_methodref specfic information to the markdown outfile
 */
void CONSTANT_interface_methodref_info::dump_to_file()
{
    outfile << "- Class Index '" << class_idx << "'" << endl;
    outfile << "- Name And Type Index '" << name_and_type_idx << "'" << endl;
    outfile << endl;
}

/**
 * @brief Construct a new Constant_Name_And_Type_Info object
 * @param file the input .class file
 */
CONSTANT_name_and_type_info::CONSTANT_name_and_type_info(ifstream &file) 
{
    name_idx = read_bytes<u2>(file);
    descriptor_idx = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_name_and_type specfic information to the markdown outfile
 */
void CONSTANT_name_and_type_info::dump_to_file()
{
    outfile << "- Name Index '" << name_idx << "'" << endl;
    outfile << "- Descriptor Index '" << descriptor_idx << "'" << endl;
    outfile << endl;
}

/**
 * @brief Retrieves the string representing the class name of the class_index stored in a instance of Constant_Name_And_Index_Info
 * @param constant_pool the class_file constant pool
 * @return the name of the class 
 */
string CONSTANT_name_and_type_info::get_name(cp_info_vector &constant_pool)
{
    return get_utf8_content(*(to_cp_info(constant_pool[name_idx - 1])->_utf8));
}

/**
 * @brief Retrives the string representing the method descriptor of descriptor_index stored in a instance of Constant_Name_And_Type_Info
 * @param constant_pool the class_file constant pool
 * @return the string representing the method descriptor
 */
string CONSTANT_name_and_type_info::get_descriptor(cp_info_vector &constant_pool)
{
    return get_utf8_content(*(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8));
}

/**
 * @brief Construct a new Constant_Method_Handle_Info object
 * @param file the input .class file
 */
CONSTANT_method_handle_info::CONSTANT_method_handle_info(ifstream &file) 
{
    reference_kind = read_bytes<u1>(file);
    reference_index = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_method_handle specfic information to the markdown outfile
 */
void CONSTANT_method_handle_info::dump_to_file()
{
    outfile << "- Reference Kind '" << reference_kind << "'" << endl;
    outfile << "- Reference Index '" << reference_index << "'" << endl;
    outfile << endl;
}

/**
 * @brief Construct a new Constant_Method_Type_Info object
 * @param file the input .class file
 */
CONSTANT_method_type_info::CONSTANT_method_type_info(ifstream &file) 
{
    descriptor_index = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_method_type specfic information to the markdown outfile
 */
void CONSTANT_method_type_info::dump_to_file()
{
    outfile << "- Descriptor Index '" << descriptor_index << "'" << endl;
}

/**
 * @brief Construct a new Constant_Invoke_Dynamic_Info object
 * @param file the input .class file
 */
CONSTANT_invoke_dynamic_info::CONSTANT_invoke_dynamic_info(ifstream &file) 
{
    bootstrap_method_attr_index = read_bytes<u2>(file);
    name_and_type_index = read_bytes<u2>(file);
}

/**
 * @brief Dump Constant_invoke_dynamic specfic information to the markdown outfile
 */
void CONSTANT_invoke_dynamic_info::dump_to_file()
{
    outfile << "- Bootstrap Method Attribute Index '" << bootstrap_method_attr_index << "'" << endl;
    outfile << "- Name and Type Index '" << name_and_type_index << "'" << endl;
    outfile << endl;
}