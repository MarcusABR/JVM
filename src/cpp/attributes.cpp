#include "../hpp/attributes.hpp"
#include "../hpp/leitor_exibidor.hpp"
#include "../hpp/utils.hpp"
#include <iomanip>
#include <iostream>

using namespace std;
extern ofstream arquivo_saida;

Attribute::Attribute(ifstream &arquivo, cp_info_vector &constant_pool)
{
    attribute_nome_index = ler_bytes_big_endian<u2>(arquivo);
    attribute_length = ler_bytes_big_endian<u4>(arquivo);
    string attribute_nome = exibir_utf8(*(to_cp_info(constant_pool[attribute_nome_index - 1])->_utf8));

    if (attribute_nome == "ConstantValue")
        tag = ConstantValue;
    else if (attribute_nome == "Code" )
        tag = Code;
    else if (attribute_nome == "LineNumberTable" )
        tag = LineNumberTable;
    else if (attribute_nome == "StackMapTable" )
        tag = StackMapTable;
    else if (attribute_nome == "Exception" )
        tag = Exception;
    else if (attribute_nome == "BootstrapMethods" )
        tag = BootstrapMethods;
    else if (attribute_nome == "SourceFile" )
        tag = SourceFile;
    else
        tag = Unknown;
}

Attribute_Info::Attribute_Info(ifstream &arquivo, cp_info_vector &constant_pool)
: Attribute(arquivo, constant_pool)
{
    switch (tag)
    {
        case ConstantValue:
            _constantvalue = new ConstantValue_attribute(arquivo, constant_pool);
            break;
        case Code:
            _code = new Code_attribute(arquivo, constant_pool);
            break;
        case LineNumberTable:
            _linenumbertable = new LineNumberTable_attribute(arquivo, constant_pool);
            break;
        case StackMapTable:
            // StackMapTable
            break;
        case Exception:
            _exception = new Exception_attribute(arquivo, constant_pool);
            break;
        case BootstrapMethods:
            _bootstrapmethods = new BootstrapMethods_attribute(arquivo, constant_pool);
            break;
        case SourceFile:
            _sourcefile = new SourceFile_attribute(arquivo, constant_pool);
            break;
        case Unknown:
            _unknown = new Unknown_attribute(arquivo, attribute_length);
            break;
    }
}

Attribute_Info::~Attribute_Info()
{
    switch (tag)
    {
        case ConstantValue: delete _constantvalue; break;
        case Code: delete _code; break;
        case LineNumberTable: delete _linenumbertable; break;
        case StackMapTable: /* delete _stackmaptable */; break;
        case Exception: delete _exception; break;
        case BootstrapMethods: delete _bootstrapmethods; break;
        case SourceFile: delete _sourcefile; break;
        case Unknown: delete _unknown; break;
    }
}
 

void Attribute_Info::exibir_info(cp_info_vector &constant_pool, unsigned int &counter) 
{
    auto attribute_name = *(to_cp_info(constant_pool[attribute_nome_index - 1])->_utf8);

    arquivo_saida << "--> [" << counter++ << "] " << exibir_utf8(attribute_name) << endl;

    arquivo_saida << "- Generic info " << endl;
    arquivo_saida << "  - Attribute name index '" << attribute_nome_index << "'";
    arquivo_saida << " '<" << exibir_utf8(attribute_name) << ">'" << endl;
    arquivo_saida << "  - Attribute length '" << attribute_length << "'" << endl << endl;
    arquivo_saida << "- Specific info" << endl;
    
    switch (tag) 
    {
        case ConstantValue: _constantvalue->exibir_arquivo(constant_pool); break;
        case Code: _code->exibir_arquivo(constant_pool); break;
        case LineNumberTable: _linenumbertable->exibir_arquivo(constant_pool); break;
        case StackMapTable: /* _stackmaptable->print(constant_pool); */ break;
        case Exception: _exception->exibir_arquivo(constant_pool); break;
        case BootstrapMethods: _bootstrapmethods->exibir_arquivo(constant_pool); break;
        case SourceFile: _sourcefile->exibir_arquivo(constant_pool); break;
        default: break;
    }
}


exception_table_info::exception_table_info(ifstream &file)
{
    start_pc = ler_bytes_big_endian<u2>(file);
    end_pc = ler_bytes_big_endian<u2>(file); 
    handler_pc = ler_bytes_big_endian<u2>(file);
    catch_type = ler_bytes_big_endian<u2>(file); 
}


bootstrap_methods_info::bootstrap_methods_info(ifstream &file)
{
    bootstrap_method_ref = ler_bytes_big_endian<u2>(file);
    num_bootstrap_arguments = ler_bytes_big_endian<u2>(file);

    for (int i = 0; i < num_bootstrap_arguments; i++)
        bootstrap_arguments.push_back(ler_bytes_big_endian<u2>(file));
}


ConstantValue_attribute::ConstantValue_attribute(ifstream &file, cp_info_vector& constant_pool) 
{
    constantvalue_index = ler_bytes_big_endian<u2>(file);
}

void ConstantValue_attribute::exibir_arquivo(cp_info_vector &constant_pool)
{
    arquivo_saida << "  - Constant value index '" << constantvalue_index << "'" << endl;
}


Code_attribute::Code_attribute(ifstream &file, cp_info_vector& constant_pool)
{
    max_stack = ler_bytes_big_endian<u2>(file);
    max_locals = ler_bytes_big_endian<u2>(file);
    code_length = ler_bytes_big_endian<u4>(file);

    for (int i = 1; i <= code_length; i++)
        code.push_back(ler_bytes_big_endian<u1>(file));

    exception_table_length = ler_bytes_big_endian<u2>(file);
    attributes_count = ler_bytes_big_endian<u2>(file);

    for (int i = 0; i < attributes_count; i++)
    {
        shared_ptr<Attribute> new_el(new Attribute_Info(file, constant_pool));
        attributes.push_back(new_el);
    }
}

void Code_attribute::exibir_arquivo(cp_info_vector &constant_pool)
{
    arquivo_saida << "  - Maximum stack size '" << max_stack << "'" << endl;
    arquivo_saida << "  - Maximum local variables '" << max_locals << "'" << endl;
    arquivo_saida << "  - Code length '" << code_length << "'" << endl;

    unsigned int attr_counter = 0;
    for (auto attr : attributes)
    {
        auto attr_info = to_attr_info(attr);
        attr_info->exibir_info(constant_pool, attr_counter);
    }
}

LineNumberTable_attribute::LineNumberTable_attribute(ifstream &file, cp_info_vector &constant_pool)
{
    line_number_table_length = ler_bytes_big_endian<u2>(file);

    for (int i = 0; i < line_number_table_length; i++)
    {
        line_num_table_item item;
        item.start_pc = ler_bytes_big_endian<u2>(file);
        item.line_number = ler_bytes_big_endian<u2>(file);
        line_number_table.push_back(item);
    }
}

void LineNumberTable_attribute::exibir_arquivo(cp_info_vector &constant_pool)
{
    arquivo_saida << "  --- Line number table length: '" << line_number_table_length << "---  " << endl << endl;
    unsigned int counter = 0;
    for (auto line_number_table_item : line_number_table)
    {
        arquivo_saida << " Number: " << setw(8) << setfill(' ') << counter++;
        arquivo_saida << " Start PC: " << setw(10) << setfill(' ') << line_number_table_item.start_pc;
        arquivo_saida << " Line Number: " << setw(13) << setfill(' ') << line_number_table_item.line_number << "  " << endl;
    }
    arquivo_saida << endl;
}

Exception_attribute::Exception_attribute(ifstream &file, cp_info_vector& constant_pool)
{
    number_of_exceptions = ler_bytes_big_endian<u2>(file);
    
    for (int i = 1; i <= sizeof(u2); i++)
        exception_index_table.push_back(ler_bytes_big_endian<u2>(file));
}

void Exception_attribute::exibir_arquivo(cp_info_vector &constant_pool)
{
    arquivo_saida << "  - Number of exceptions: " << number_of_exceptions << endl;
}

BootstrapMethods_attribute::BootstrapMethods_attribute(ifstream &file, cp_info_vector& constant_pool) 
{
    num_bootstrap_methods = ler_bytes_big_endian<u2>(file);
    
    for (int i = 0; i < num_bootstrap_methods; i++)
       bootstrap_methods.push_back(bootstrap_methods_info(file)); 
}

void BootstrapMethods_attribute::exibir_arquivo(cp_info_vector &constant_pool)
{
    arquivo_saida << "  - Number of bootstrap methods: " << num_bootstrap_methods << endl;
}

SourceFile_attribute::SourceFile_attribute(ifstream &file, cp_info_vector& constant_pool)
{
    sourcefile_index = ler_bytes_big_endian<u2>(file);
}

void SourceFile_attribute::exibir_arquivo(cp_info_vector &constant_pool)
{
    auto sourcefile_name = *(to_cp_info(constant_pool[sourcefile_index - 1])->_utf8);
    arquivo_saida << "  - Source file name index '" << sourcefile_index << "'";
    arquivo_saida << " '<" << exibir_utf8(sourcefile_name) << ">'" << endl;
}

Unknown_attribute::Unknown_attribute(ifstream &file, u4 length)
{
    for (int i = 0; i < length; i++)
        info.push_back(ler_bytes_big_endian<u1>(file));
}