#include "../include/constant_pool_info.hpp"
#include "../include/class_file.hpp"
#include "../include/leitor_exibidor.hpp"
#include "../include/utils.hpp"
#include <string>

extern ofstream arquivo_saida;


CP_Item::CP_Item(u1 tag) : tag((CONSTANT_Types)tag) {}

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


void CP_Info::exibir_info(cp_info_vector &constant_pool, unsigned int &counter)
{
    switch (tag) 
    {
        case CONSTANT_Utf8:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Utf8_info*" << endl;
            _utf8->exibir();
            break;
        case CONSTANT_Integer:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Integer_info*" << endl;
            _integer->exibir();
            break;
        case CONSTANT_Float:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Float_info*" << endl;
            _float->exibir();
            break;
        case CONSTANT_Long:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Long_info*" << endl;
            _long->exibir();
            break;
        case CONSTANT_Double:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Double_info*" << endl;
            _double->exibir();
            break;
        case CONSTANT_Class:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Class_info*" << endl;
            _class->exibir(constant_pool);
            break;
        case CONSTANT_String:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_String_info*" << endl;
            _string->exibir(constant_pool);
            break;
        case CONSTANT_Fieldref:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Fieldref_info*" << endl;
            _fieldref->exibir(constant_pool);
            break;
        case CONSTANT_Methodref:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_Methodref_info*" << endl;
            _methodref->exibir();
            break;
        case CONSTANT_InterfaceMethodref:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_InterfaceMethodref_info*" << endl;
            _interface_methodref->exibir();
            break;
        case CONSTANT_NameAndType:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_NameAndType_info*" << endl;
            _name_and_type->exibir();
            break;
        case CONSTANT_MethodHandle:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_MethodHandle_info*" << endl;
            _method_handle->exibir();
            break;
        case CONSTANT_MethodType:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_MethodType_info*" << endl;
            _method_type->exibir();
            break;
        case CONSTANT_InvokeDynamic:
            arquivo_saida << "--> [" << counter++ << "] *CONSTANT_InvokeDynamic_info*" << endl;
            _invoke_dynamic->exibir();
            break;
        case CONSTANT_Continuation:
            arquivo_saida << "--> [" << counter++ << "] *(large numeric continued)*" << endl << endl;
            break;
    }
}

string CP_Info::get_conteudo(cp_info_vector &constant_pool)
{
    switch (tag) 
    {
        case CONSTANT_Integer: return _integer->get_conteudo();
        case CONSTANT_Float: return _float->get_conteudo();
        case CONSTANT_Long: return _long->get_conteudo();
        case CONSTANT_Double: return _double->get_conteudo();
        case CONSTANT_String: return _string->get_conteudo(constant_pool);
        case CONSTANT_Methodref: return _methodref->get_conteudo(constant_pool);
        case CONSTANT_Fieldref: return _fieldref->get_conteudo(constant_pool);
        case CONSTANT_Class: return _class->get_conteudo(constant_pool);
        default: return "Invalid tag";
    }
}


CONSTANT_utf8_info::CONSTANT_utf8_info(ifstream &file) 
{
    length = ler_bytes_big_endian<u2>(file);

    for (int i = 0; i < length; i++)
        bytes.push_back(ler_bytes_big_endian<u1>(file));
}

void CONSTANT_utf8_info::exibir()
{
    arquivo_saida << "- Length '" << length << "'" << endl;
    arquivo_saida << "- Bytes [ '" << exibir_utf8(*this) << "']" << endl << endl;
}

string CONSTANT_utf8_info::get_conteudo()
{
    return exibir_utf8(*this);
}

CONSTANT_integer_info::CONSTANT_integer_info(ifstream &file) 
{
    bytes = ler_bytes_big_endian<u4>(file);
}

void CONSTANT_integer_info::exibir()
{
    arquivo_saida << "- Bytes '" << bytes << "'" << endl;
    arquivo_saida << endl;
}

string CONSTANT_integer_info::get_conteudo()
{
    return to_string(bytes);
}

CONSTANT_float_info::CONSTANT_float_info(ifstream &file) 
{
    bytes = ler_bytes_big_endian<u4>(file);
}

void CONSTANT_float_info::exibir()
{
    ios_base::fmtflags f(arquivo_saida.flags());
    arquivo_saida << "- Bytes '0x" << hex << bytes << "'" << endl;
    arquivo_saida.flags(f);
    arquivo_saida << "- Float '" << ler_float(bytes) << "'" << endl;
    arquivo_saida << endl;
}

string CONSTANT_float_info::get_conteudo()
{
    return to_string(ler_float(bytes));
}

CONSTANT_long_info::CONSTANT_long_info(ifstream &file) 
{
    high_bytes = ler_bytes_big_endian<u4>(file);
    low_bytes = ler_bytes_big_endian<u4>(file);
}

void CONSTANT_long_info::exibir()
{
    ios_base::fmtflags f(arquivo_saida.flags());
    arquivo_saida << "- High Bytes '0x" << hex << high_bytes << "'" << endl;
    arquivo_saida << "- Low Bytes '0x" << hex << low_bytes << "'" << endl;
    arquivo_saida.flags(f);
    arquivo_saida << "- Long '" << ler_long(high_bytes, low_bytes) << "'" << endl;
    arquivo_saida << endl;
}

string CONSTANT_long_info::get_conteudo()
{
    return to_string(ler_long(high_bytes, low_bytes));
}

CONSTANT_double_info::CONSTANT_double_info(ifstream &file) 
{
    high_bytes = ler_bytes_big_endian<u4>(file);
    low_bytes = ler_bytes_big_endian<u4>(file);
}

void CONSTANT_double_info::exibir()
{
    ios_base::fmtflags f(arquivo_saida.flags());
    arquivo_saida << "- High Bytes '0x" << hex << high_bytes << "'" << endl;
    arquivo_saida << "- Low Bytes '0x" << hex << low_bytes << "'" << endl;
    arquivo_saida.flags(f);
    arquivo_saida << "- Double '" << ler_double(high_bytes, low_bytes) << "'" << endl;
    arquivo_saida << endl;
}

string CONSTANT_double_info::get_conteudo()
{
    return to_string(ler_double(high_bytes, low_bytes));
}

CONSTANT_class_info::CONSTANT_class_info(ifstream &file) 
{
    name_idx = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_class_info::exibir(cp_info_vector &constant_pool)
{
    auto class_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    arquivo_saida << "- Name Index '" << name_idx << "'" << endl;
    arquivo_saida << "- Class Name '<" << exibir_utf8(class_name) << ">'";
    arquivo_saida << endl << endl;
}

string CONSTANT_class_info::get_conteudo(cp_info_vector &constant_pool)
{
    auto class_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    return exibir_utf8(class_name);
}

CONSTANT_string_info::CONSTANT_string_info(ifstream &file) 
{
    str_idx = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_string_info::exibir(cp_info_vector &constant_pool)
{
    auto str = *(to_cp_info(constant_pool[str_idx - 1])->_utf8);
    arquivo_saida << "- String Index '" << str_idx << "'" << endl;
    arquivo_saida << "- String '<" << exibir_utf8(str) << ">'";
    arquivo_saida << endl << endl;
}

string CONSTANT_string_info::get_conteudo(cp_info_vector &constant_pool)
{
    auto string_utf8 = *(to_cp_info(constant_pool[str_idx - 1])->_utf8);
    return exibir_utf8(string_utf8);
}

CONSTANT_fieldref_info::CONSTANT_fieldref_info(ifstream &file) 
{
    class_idx = ler_bytes_big_endian<u2>(file);
    name_and_type_idx = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_fieldref_info::exibir(cp_info_vector &constant_pool)
{
    auto class_name_index = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_index - 1])->_utf8);
    arquivo_saida << "- Class Index '" << class_idx << "'" << endl;
    arquivo_saida << "- Class Name '<" << exibir_utf8(class_name) << ">'" << endl;
    
    auto nt_name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto nt_name = *(to_cp_info(constant_pool[nt_name_idx - 1])->_utf8);
    auto nt_descriptor_index = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto nt_descriptor = *(to_cp_info(constant_pool[nt_descriptor_index - 1])->_utf8);
    arquivo_saida << "- Name And Type Index '" << name_and_type_idx << "'" << endl;
    arquivo_saida << "- Name And Type '<" << exibir_utf8(nt_name) << ":" << exibir_utf8(nt_descriptor) << ">'";
    arquivo_saida << endl << endl;
}

string CONSTANT_fieldref_info::get_conteudo(cp_info_vector &constant_pool)
{
    auto class_name_idx = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_idx - 1])->_utf8);
    auto name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto descriptor_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto method_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    auto method_descriptor = *(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8);
    return (exibir_utf8(class_name) + "." + exibir_utf8(method_name) + " : " + exibir_utf8(method_descriptor));
}

CONSTANT_methodref_info::CONSTANT_methodref_info(ifstream &file) 
{
    class_idx = ler_bytes_big_endian<u2>(file);
    name_and_type_idx = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_methodref_info::exibir()
{
    arquivo_saida << "- Class Index '" << class_idx << "'" << endl;
    arquivo_saida << "- Name And Type Index '" << name_and_type_idx << "'" << endl;
    arquivo_saida << endl;
}

string CONSTANT_methodref_info::get_conteudo(cp_info_vector &constant_pool)
{
    auto class_name_idx = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_idx - 1])->_utf8);
    auto name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto descriptor_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto method_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    auto method_descriptor = *(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8);
    return (exibir_utf8(class_name) + "." + exibir_utf8(method_name) + " : " + exibir_utf8(method_descriptor));
}

string CONSTANT_methodref_info::get_class_name(cp_info_vector &constant_pool)
{
    auto class_name_idx = to_cp_info(constant_pool[class_idx - 1])->_class->name_idx;
    auto class_name = *(to_cp_info(constant_pool[class_name_idx - 1])->_utf8);
    return exibir_utf8(class_name);
}

string CONSTANT_methodref_info::get_method_name(cp_info_vector &constant_pool)
{
    auto name_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->name_idx;
    auto method_name = *(to_cp_info(constant_pool[name_idx - 1])->_utf8);
    return exibir_utf8(method_name);
}

string CONSTANT_methodref_info::get_method_descriptor(cp_info_vector &constant_pool)
{
    auto descriptor_idx = to_cp_info(constant_pool[name_and_type_idx - 1])->_name_and_type->descriptor_idx;
    auto method_descriptor = *(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8);
    return exibir_utf8(method_descriptor);
}

CONSTANT_interface_methodref_info::CONSTANT_interface_methodref_info(ifstream &file) 
{
    class_idx = ler_bytes_big_endian<u2>(file);
    name_and_type_idx = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_interface_methodref_info::exibir()
{
    arquivo_saida << "- Class Index '" << class_idx << "'" << endl;
    arquivo_saida << "- Name And Type Index '" << name_and_type_idx << "'" << endl;
    arquivo_saida << endl;
}

CONSTANT_name_and_type_info::CONSTANT_name_and_type_info(ifstream &file) 
{
    name_idx = ler_bytes_big_endian<u2>(file);
    descriptor_idx = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_name_and_type_info::exibir()
{
    arquivo_saida << "- Name Index '" << name_idx << "'" << endl;
    arquivo_saida << "- Descriptor Index '" << descriptor_idx << "'" << endl;
    arquivo_saida << endl;
}

string CONSTANT_name_and_type_info::get_name(cp_info_vector &constant_pool)
{
    return exibir_utf8(*(to_cp_info(constant_pool[name_idx - 1])->_utf8));
}

string CONSTANT_name_and_type_info::get_descriptor(cp_info_vector &constant_pool)
{
    return exibir_utf8(*(to_cp_info(constant_pool[descriptor_idx - 1])->_utf8));
}


CONSTANT_method_handle_info::CONSTANT_method_handle_info(ifstream &file) 
{
    reference_kind = ler_bytes_big_endian<u1>(file);
    reference_index = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_method_handle_info::exibir()
{
    arquivo_saida << "- Reference Kind '" << reference_kind << "'" << endl;
    arquivo_saida << "- Reference Index '" << reference_index << "'" << endl;
    arquivo_saida << endl;
}

CONSTANT_method_type_info::CONSTANT_method_type_info(ifstream &file) 
{
    descriptor_index = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_method_type_info::exibir()
{
    arquivo_saida << "- Descriptor Index '" << descriptor_index << "'" << endl;
}

CONSTANT_invoke_dynamic_info::CONSTANT_invoke_dynamic_info(ifstream &file) 
{
    bootstrap_method_attr_index = ler_bytes_big_endian<u2>(file);
    name_and_type_index = ler_bytes_big_endian<u2>(file);
}

void CONSTANT_invoke_dynamic_info::exibir()
{
    arquivo_saida << "- Bootstrap Method Attribute Index '" << bootstrap_method_attr_index << "'" << endl;
    arquivo_saida << "- Name and Type Index '" << name_and_type_index << "'" << endl;
    arquivo_saida << endl;
}