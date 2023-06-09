#include "../include/attributes.hpp"
#include "../include/dump_class_file.hpp"
// #include "../include/bytecode.hpp"
#include "../include/utils.hpp"
#include <iomanip>
#include <iostream>

using namespace std;
extern ofstream outfile;

/**
 * @brief Construct a new Attribute:: Attribute object
 * @param file the class file
 * @param constant_pool the class constant pool
 */
Attribute::Attribute(ifstream &file, cp_info_vector &constant_pool)
{
    attribute_name_index = read_bytes<u2>(file);
    attribute_length = read_bytes<u4>(file);
    string attribute_name = get_utf8_content(*(to_cp_info(constant_pool[attribute_name_index - 1])->_utf8));

    if (attribute_name == "ConstantValue")
        tag = ConstantValue;
    else if (attribute_name == "Code" )
        tag = Code;
    else if (attribute_name == "LineNumberTable" )
        tag = LineNumberTable;
    else if (attribute_name == "StackMapTable" )
        tag = StackMapTable;
    else if (attribute_name == "Exception" )
        tag = Exception;
    else if (attribute_name == "BootstrapMethods" )
        tag = BootstrapMethods;
    else if (attribute_name == "SourceFile" )
        tag = SourceFile;
    else
        tag = Unknown;
}

/**
 * @brief Construct a new Attribute_Info::Attribute_Info object
 * @param file the class file
 * @param constant_pool the class file constant pool
 */
Attribute_Info::Attribute_Info(ifstream &file, cp_info_vector &constant_pool)
: Attribute(file, constant_pool)
{
    switch (tag)
    {
        case ConstantValue:
            _constantvalue = new ConstantValue_attribute(file, constant_pool);
            break;
        case Code:
            _code = new Code_attribute(file, constant_pool);
            break;
        case LineNumberTable:
            _linenumbertable = new LineNumberTable_attribute(file, constant_pool);
            break;
        case StackMapTable:
            // StackMapTable
            break;
        case Exception:
            _exception = new Exception_attribute(file, constant_pool);
            break;
        case BootstrapMethods:
            _bootstrapmethods = new BootstrapMethods_attribute(file, constant_pool);
            break;
        case SourceFile:
            _sourcefile = new SourceFile_attribute(file, constant_pool);
            break;
        case Unknown:
            _unknown = new Unknown_attribute(file, attribute_length);
            break;
    }
}

/**
 * @brief Destroy the Attribute_Info::Attribute_Info object
 */
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
 
/**
 * @brief Attribute_Info:: Dump info to file
 * @param constant_pool the class file constant pool
 * @param counter 
 */
void Attribute_Info::dump_info_to_file(cp_info_vector &constant_pool, unsigned int &counter) 
{
    auto attribute_name = *(to_cp_info(constant_pool[attribute_name_index - 1])->_utf8);

    outfile << "--> [" << counter++ << "] " << get_utf8_content(attribute_name) << endl;

    outfile << "- Generic info " << endl;
    outfile << "  - Attribute name index '" << attribute_name_index << "'";
    outfile << " '<" << get_utf8_content(attribute_name) << ">'" << endl;
    outfile << "  - Attribute length '" << attribute_length << "'" << endl << endl;
    outfile << "- Specific info" << endl;
    
    switch (tag) 
    {
        case ConstantValue: _constantvalue->dump_to_file(constant_pool); break;
        case Code: _code->dump_to_file(constant_pool); break;
        case LineNumberTable: _linenumbertable->dump_to_file(constant_pool); break;
        case StackMapTable: /* _stackmaptable->print(constant_pool); */ break;
        case Exception: _exception->dump_to_file(constant_pool); break;
        case BootstrapMethods: _bootstrapmethods->dump_to_file(constant_pool); break;
        case SourceFile: _sourcefile->dump_to_file(constant_pool); break;
        default: break;
    }
}

/**
 * @brief Construct a new exception table info::exception table info object
 * @param file the class file
 */
exception_table_info::exception_table_info(ifstream &file)
{
    start_pc = read_bytes<u2>(file);
    end_pc = read_bytes<u2>(file); 
    handler_pc = read_bytes<u2>(file);
    catch_type = read_bytes<u2>(file); 
}

/**
 * @brief Construct a new bootstrap methods info::bootstrap methods info object
 * @param file the class file
 */
bootstrap_methods_info::bootstrap_methods_info(ifstream &file)
{
    bootstrap_method_ref = read_bytes<u2>(file);
    num_bootstrap_arguments = read_bytes<u2>(file);

    for (int i = 0; i < num_bootstrap_arguments; i++)
        bootstrap_arguments.push_back(read_bytes<u2>(file));
}

/**
 * @brief Construct a new ConstantValue_attribute::ConstantValue_attribute object
 * @param file the class file
 * @param constant_pool the class file constant pool
 */
ConstantValue_attribute::ConstantValue_attribute(ifstream &file, cp_info_vector& constant_pool) 
{
    constantvalue_index = read_bytes<u2>(file);
}

/**
 * @brief Dumps ConstantValue info into the outfile
 * @param constant_pool the class constant pool
 */
void ConstantValue_attribute::dump_to_file(cp_info_vector &constant_pool)
{
    outfile << "  - Constant value index '" << constantvalue_index << "'" << endl;
}

/**
 * @brief Construct a new Code_attribute::Code_attribute object
 * @param file the class file
 * @param constant_pool the class file constant pool
 */
Code_attribute::Code_attribute(ifstream &file, cp_info_vector& constant_pool)
{
    max_stack = read_bytes<u2>(file);
    max_locals = read_bytes<u2>(file);
    code_length = read_bytes<u4>(file);

    for (int i = 1; i <= code_length; i++)
        code.push_back(read_bytes<u1>(file));

    exception_table_length = read_bytes<u2>(file);
    attributes_count = read_bytes<u2>(file);

    for (int i = 0; i < attributes_count; i++)
    {
        shared_ptr<Attribute> new_el(new Attribute_Info(file, constant_pool));
        attributes.push_back(new_el);
    }
}

/**
 * @brief Dumps Code info into the outfile
 * @param constant_pool the class constant pool
 */
void Code_attribute::dump_to_file(cp_info_vector &constant_pool)
{
    outfile << "  - Maximum stack size '" << max_stack << "'" << endl;
    outfile << "  - Maximum local variables '" << max_locals << "'" << endl;
    outfile << "  - Code length '" << code_length << "'" << endl;
    outfile << "- Bytecode" << endl;
    outfile << "'''" << endl;

    for (int i = 0; i < code_length; i++)
    {
        // if (mnemonic.count(code[i])) 
        // {
        //     auto bytecode = code[i];
        //     outfile << i << " " << mnemonic.at(bytecode);
        //     if (debug.count(bytecode))
        //     {
        //         auto print_instr = debug.at(bytecode);
        //         print_instr(i, constant_pool, code);
        //     } 
        //     outfile << endl;
        // } 
        // else
        // {
            ios_base::fmtflags f(cout.flags());
            cout << "Bytecode nao encontrado: 0x" << hex << (int) code[i] <<  endl;
            cout.flags(f);
        // }
    }
    outfile << "'''" << endl;

    unsigned int attr_counter = 0;
    for (auto attr : attributes)
    {
        auto attr_info = to_attr_info(attr);
        attr_info->dump_info_to_file(constant_pool, attr_counter);
    }
}

/**
 * @brief Construct a new LineNumberTable_attribute::LineNumberTable_attribute object
 * @param file the class file
 * @param constant_pool the class constant pool
 */
LineNumberTable_attribute::LineNumberTable_attribute(ifstream &file, cp_info_vector &constant_pool)
{
    line_number_table_length = read_bytes<u2>(file);

    for (int i = 0; i < line_number_table_length; i++)
    {
        line_num_table_item item;
        item.start_pc = read_bytes<u2>(file);
        item.line_number = read_bytes<u2>(file);
        line_number_table.push_back(item);
    }
}

/**  
* @brief Dumps to file LineNumberTable_attribute::
* @param constant_pool the class constant pool
*/
void LineNumberTable_attribute::dump_to_file(cp_info_vector &constant_pool)
{
    outfile << "  - Line number table length '" << line_number_table_length << "'  " << endl << endl;
    outfile << "| Number | Start PC | Line Number |  " << endl;
    outfile << "|--------|----------|-------------|  " << endl;
    unsigned int counter = 0;
    for (auto line_number_table_item : line_number_table)
    {
        outfile << "|" << setw(8) << setfill(' ') << counter++;
        outfile << "|" << setw(10) << setfill(' ') << line_number_table_item.start_pc;
        outfile << "|" << setw(13) << setfill(' ') << line_number_table_item.line_number << "|  " << endl;
    }
    outfile << endl;
}

/**
 * @brief Construct a new Exception_attribute::Exception_attribute object
 * @param file the class file
 * @param constant_pool the class constant pool
 */
Exception_attribute::Exception_attribute(ifstream &file, cp_info_vector& constant_pool)
{
    number_of_exceptions = read_bytes<u2>(file);
    
    for (int i = 1; i <= sizeof(u2); i++)
        exception_index_table.push_back(read_bytes<u2>(file));
}

/**
 * @brief Dump Exception info into the outfile
 * @param constant_pool the class constant pool
 */
void Exception_attribute::dump_to_file(cp_info_vector &constant_pool)
{
    outfile << "  - Number of exceptions: " << number_of_exceptions << endl;
}

/**
 * @brief Construct a new BootstrapMethods_attribute::BootstrapMethods_attribute object
 * @param file the class file
 * @param constant_pool the class file constant pool
 */
BootstrapMethods_attribute::BootstrapMethods_attribute(ifstream &file, cp_info_vector& constant_pool) 
{
    num_bootstrap_methods = read_bytes<u2>(file);
    
    for (int i = 0; i < num_bootstrap_methods; i++)
       bootstrap_methods.push_back(bootstrap_methods_info(file)); 
}

/**
 * @brief Dump BoostrapMethods info into outfile
 * @param constant_pool the class file constant pool
 */
void BootstrapMethods_attribute::dump_to_file(cp_info_vector &constant_pool)
{
    outfile << "  - Number of bootstrap methods: " << num_bootstrap_methods << endl;
}

/**
 * @brief Construct a new SourceFile_attribute::SourceFile_attribute object
 * @param file the class file
 * @param constant_pool the class file constant pool
 */
SourceFile_attribute::SourceFile_attribute(ifstream &file, cp_info_vector& constant_pool)
{
    sourcefile_index = read_bytes<u2>(file);
}

/**
 * @brief Dump SourceFile info into outfile
 * @param constant_pool the class file constant pool
 */
void SourceFile_attribute::dump_to_file(cp_info_vector &constant_pool)
{
    auto sourcefile_name = *(to_cp_info(constant_pool[sourcefile_index - 1])->_utf8);
    outfile << "  - Source file name index '" << sourcefile_index << "'";
    outfile << " '<" << get_utf8_content(sourcefile_name) << ">'" << endl;
}

/**
 * @brief Construct a new Unknown_attribute::Unknown_attribute object
 * @param file the class file 
 * @param length the length of the attribute
 */
Unknown_attribute::Unknown_attribute(ifstream &file, u4 length)
{
    for (int i = 0; i < length; i++)
        info.push_back(read_bytes<u1>(file));
}