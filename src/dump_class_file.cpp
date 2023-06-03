#include "../include/dump_class_file.hpp"
#include "../include/windows.hpp"
#include <iomanip>
#include <regex>
#include <iostream>

using namespace std;

unsigned int pos_counter = 0;

/**
 * @brief Global file used to dump information stored in the .class file in Markdown format
 */
ofstream outfile;

/**
 * @brief Function that opens the outfile
 * @param filename the name of the .class file
 */
void open_outfile(string filename)
{
    create_dir();
    outfile = ofstream("./out/" + filename + ".md");
}

/**
 * @brief Function responsible for calling all functions that dump information to the outfile
 * @param class_f a reference to the class_file instance
 * @param filepath the name of the .class
 */
void print_all(class_file &class_f, string filepath)
{
    smatch m;
    regex regexp("[a-zA-Z0-9_]+.class");
    regex_search(filepath, m, regexp);
    
    string filename = m[0];
    filename = filename.substr(0, filename.find('.')); 
    open_outfile(filename);

    outfile << "# **" << filename << "**" << endl << endl;
    print_general_info(class_f);
    print_pool(class_f.constant_pool);
    print_interfaces(class_f);
    print_fields(class_f);
    print_methods(class_f);
    print_class_attributes(class_f);
    outfile.close();
    pos_counter = 0;

    cout << "Generated \"" << filename + ".md\" at /out/" << endl;
}

/**
 * @brief Function responsible for printing to the outfile the .class file "metadata", such as minor and major versions, access flags, etc.
 * @param class_f a reference to the class_file instance
 */
void print_general_info(class_file &class_f)
{
    outfile << "## **General Information**" << endl;
    ios_base::fmtflags f(outfile.flags());
    outfile << "Magic " << "`0x" << uppercase << hex << class_f.magic << "`  " << endl;
    outfile.flags(f);
    
    outfile << "Minor version `" << class_f.minor_version << "`  " << endl;
    outfile << "Major version `" << class_f.major_version << "`";
    outfile << "[`" << get_version(class_f.major_version, class_f.minor_version) << "`]  " << endl;
    
    outfile << "Constant Pool Count `" << class_f.constant_pool_count << "`  " << endl;
    
    ios_base::fmtflags g(outfile.flags());
    outfile << "Access Flags `0x" << setw(4) << setfill('0') << hex << class_f.access_flag << "`";
    outfile << " [`" << get_access_flags(class_f.access_flag, CLASS) << "`]  " << endl;
    outfile.flags(g);
    
    auto this_class = to_cp_info(class_f.constant_pool[class_f.this_class - 1])->_class->name_idx;
    auto this_class_name = *(to_cp_info(class_f.constant_pool[this_class - 1])->_utf8);
    outfile << "This Class `" << class_f.this_class << "` ";
    outfile << "`<" << get_utf8_content(this_class_name)  << ">`  " << endl;
    
    auto super_class = to_cp_info(class_f.constant_pool[class_f.super_class - 1])->_class->name_idx;
    auto super_class_name = *(to_cp_info(class_f.constant_pool[super_class - 1])->_utf8);
    outfile << "Super Class `" << class_f.super_class << "` ";
    outfile << "`<" << get_utf8_content(super_class_name) << ">`  " << endl;

    outfile << "Interfaces Count `" << class_f.interfaces_count << "`  " << endl;
    outfile << "Fields Count `" << class_f.fields_count << "`  " << endl;
    outfile << "Methods Count `" << class_f.methods_count << "`  " << endl;
    outfile << "Attributes Count `" << class_f.attributes_count << "`" << endl;
    outfile << endl;
}

/**
 * @brief Parses the Major and Minor versions to interpret the Java version
 * @param major 2 bytes representing the class_file major version
 * @param minor 2 bytes representing the class_file minor version
 * @return the parsed version as a string 
 */
string get_version(u2 major, u2 minor)
{
    if (major >= 45 && major <= 48)
        return "1." + to_string(major - 45 + 1);
    return to_string(major - 49 + 5);
}

/**
 * @brief Data structure that divides a hexadecimal number into 4 parts
 */
union Nibble
{
    u2 h16;
    struct {
        unsigned int n0 : 4;
        unsigned int n1 : 4;
        unsigned int n2 : 4;
        unsigned int n3 : 4;
    } nb;
};

/**
 * @brief Parses the class_file access flags
 * @param access_flags 2 bytes representig the class_file access flags
 * @param type the type of access flag (class, method or field)
 * @return the string representng the access flag 
 */
string get_access_flags(u2 access_flags, int type)
{
    string class_access = " ";
    
    Nibble n;
    n.h16 = access_flags;

    unsigned int t3 = n.nb.n3 << 12;
    unsigned int t2 = n.nb.n2 << 8;
    unsigned int t1 = n.nb.n1 << 4;
    unsigned int t0 = n.nb.n0;
    vector<unsigned int> flag_v = {t3, t2, t1, t0};

    for (auto flag : flag_v)
    {
        switch (flag)
        {
            case ACC_PUBLIC:
                class_access += "ACC_PUBLIC ";
                break;
            case ACC_FINAL:
                class_access += "ACC_FINAL ";
                break;
            case ACC_SYNTHETIC:
                class_access += "ACC_SYNTHETIC ";
                break;
        }
        if (type == CLASS)
        {
            switch (flag)
            {
                case ACC_SUPER:
                    class_access += "ACC_SUPER ";
                    break;
                case ACC_INTERFACE:
                    class_access += "ACC_INTERFACE ";
                    break;
                case ACC_ABSTRACT:
                    class_access += "ACC_ABSTRACT ";
                    break;
                case ACC_ANNOTATION:
                    class_access += "ACC_ANNOTATION ";
                    break;
                case ACC_ENUM:
                    class_access += "ACC_ENUM ";
                    break;
                default:
                    break;
            }
        }
        else if (type == FIELD)
        {
            switch (flag)
            {
                case ACC_ENUM:
                    class_access += "ACC_ENUM ";
                    break;
                case ACC_PRIVATE:
                    class_access += "ACC_PRIVATE ";
                    break;
                case ACC_PROTECTED:
                    class_access += "ACC_PROTECTED ";
                    break;
                case ACC_STATIC:
                    class_access += "ACC_STATIC ";
                    break;
                case ACC_VOLATILE:
                    class_access += "ACC_VOLATILE ";
                    break;
                case ACC_TRANSIENT:
                    class_access += "ACC_TRANSIENT ";
                    break;
                default:
                    break;
            }
        }
        else if (type == METHOD)
        {
            switch (flag)
            {
                case ACC_ABSTRACT:
                    class_access += "ACC_ABSTRACT ";
                    break;
                case ACC_PRIVATE:
                    class_access += "ACC_PRIVATE ";
                    break;
                case ACC_PROTECTED:
                    class_access += "ACC_PROTECTED ";
                    break;
                case ACC_STATIC:
                    class_access += "ACC_STATIC ";
                    break;
                case ACC_SYNCHRONIZED:
                    class_access += "ACC_SYNCHRONIZED ";
                    break;
                case ACC_BRIDGE:
                    class_access += "ACC_BRIDGE ";
                    break;
                case ACC_VARARGS:
                    class_access += "ACC_VARARGS ";
                    break;
                case ACC_NATIVE:
                    class_access += "ACC_NATIVE ";
                    break;
                case ACC_STRICT:
                    class_access += "ACC_STRICT ";
                    break;
                default:
                    break;
            }
        }
        else
            cout << "INVALID FLAG TYPE" << endl;
    }
    return class_access;
}

/**
 * @brief Function responsible for printing to the outfile the .class file constant pool, including its items and indexes
 * @param class_f a reference to the class_file instance
 */
void print_pool(cp_info_vector &constant_pool)
{
    unsigned int cp_counter = 1;
    outfile << "## **Constant Pool**  " << endl << endl;
    outfile << "<details> <summary>Show more</summary> <hr>" << endl << endl;

    for (auto cp_item : constant_pool) 
    {
        auto cp_info = to_cp_info(cp_item);
        cp_info->dump_info_to_file(constant_pool, cp_counter);
    }
    outfile << "</details> <br>" << endl << endl;
}

/**
 * @brief Get the utf8 content from a Constant_UTF8_Info instance in the constant pool
 * @param utf8 a reference to a Constant_UTF8_Info reference
 * @return the UTF8 string
 */
string get_utf8_content(CONSTANT_utf8_info &utf8)
{
    string out = "";
    for (auto j : utf8.bytes)
         out += j;
    return out;
}

/**
 * @brief Function responsible for printing to the outfile the .class file interfaces
 * @param class_f a reference to the class_file instance
 */
void print_interfaces(class_file &class_f)
{
    outfile << "## **Interfaces**" << endl << endl;
    outfile << "<details> <summary>Show more</summary> <hr>" << endl << endl;

    for (auto interface : class_f.interfaces)
    {
        auto interface_name_index = to_cp_info(class_f.constant_pool[interface - 1])->_class->name_idx;
        auto interface_name = *(to_cp_info(class_f.constant_pool[interface_name_index - 1])->_utf8);
        outfile << "- Interface: `" << interface << "` ";
        outfile << "`<" << get_utf8_content(interface_name) << ">`" << endl;
    }
    outfile << "</details><br>" << endl << endl;
}

/**
 * @brief Function responsible for printing to the outfile the .class file interfaces
 * @param class_f a reference to the class_file instance
 */
void print_fields(class_file &class_f)
{
    unsigned int field_counter = 0;
    outfile << "## **Fields**" << endl << endl;
    outfile << "<details> <summary>Show more</summary> <hr>" << endl << endl;

    for (auto field : class_f.fields) 
    {
        auto field_name = *(to_cp_info(class_f.constant_pool[field.name_idx - 1])->_utf8);
        auto field_descriptor = *(to_cp_info(class_f.constant_pool[field.descriptor_idx - 1])->_utf8);

        outfile << "### [" << field_counter++ << "] `" << get_utf8_content(field_name) << "`" << endl;

        ios_base::fmtflags f(outfile.flags());
        outfile << "- Fields Access Flags `0x" << hex << setw(4) << setfill('0') << field.access_flags << "`" << endl;
        outfile << "[`" << get_access_flags(field.access_flags, FIELD) << "`]" << endl;
        outfile.flags(f);

        outfile << "- Name Index `" << field.name_idx << "` ";
        outfile << "`<" << get_utf8_content(field_name) << ">`" << endl;
        outfile << "- Descriptor Index `" << field.descriptor_idx << "` ";
        outfile << "`<" << get_utf8_content(field_descriptor) << ">`" << endl;
        outfile << "- Attribute Count `" << field.attr_count << "`" << endl;
        
        outfile << "<details><summary>Show attributes</summary>" << endl << endl;
        print_attributes_vector(field.attr, class_f.constant_pool);
        outfile << "</details><br>" << endl << endl;
    }
    outfile << "</details><br>" << endl << endl;
}

/**
 * @brief Function responsible for printing to the outfile the .class file methods
 * @param class_f a reference to the class_file instance
 */
void print_methods(class_file &class_f)
{
    unsigned int method_counter = 0;
    outfile << "## **Methods**" << endl;
    outfile << "<details> <summary>Show more</summary> <hr>" << endl << endl;

    for (auto method : class_f.methods) 
    {
        auto method_name = *(to_cp_info(class_f.constant_pool[method.name_idx - 1])->_utf8);
        auto method_descriptor = *(to_cp_info(class_f.constant_pool[method.descriptor_idx - 1])->_utf8);

        outfile << "### [" << method_counter++ << "] `" << get_utf8_content(method_name) << "` " << endl;

        ios_base::fmtflags f(outfile.flags());
        outfile << "- Methods Access Flags " << "`0x" << uppercase << hex << method.access_flags << "` ";
        outfile.flags(f);

        outfile << "[`" << get_access_flags(method.access_flags, METHOD) << "`]" << endl;
        outfile << "- Name Index `" << method.name_idx << "` ";
        outfile << "`<" << get_utf8_content(method_name) << ">`" << endl;
        outfile << "- Descriptor Index `" << method.descriptor_idx << "` ";
        outfile << "`<" << get_utf8_content(method_descriptor) << ">`" << endl;
        outfile << "- Attribute Count `" << method.attr_count << "`" << endl;
        
        outfile << "<details><summary>Show attributes</summary>" << endl << endl;
        print_attributes_vector(method.attr, class_f.constant_pool);
        outfile << "</details><br>" << endl << endl;
    }
    outfile << "</details><br>" << endl << endl;
}

/**
 * @brief Function responsible for printing to the outfile the .class file attributes
 * @param class_f a reference to the class_file instance
 */
void print_class_attributes(class_file &class_f)
{
    outfile << "## **Attributes**" << endl;
    outfile << "<details> <summary>Show more</summary> <hr>" << endl << endl;
    print_attributes_vector(class_f.attributes, class_f.constant_pool);
    outfile << "</details><br>" << endl << endl;
}

/**
 * @brief Function responsible for printing to the outfile the .class file method and field attributes
 * @param class_f a reference to the class_file instance
 */
void print_attributes_vector(attr_info_vector &attr_vector, cp_info_vector &constant_pool)
{
    unsigned int attr_counter = 0;
    for (auto attr : attr_vector)
    {
        auto attr_info = to_attr_info(attr);
        attr_info->dump_info_to_file(constant_pool, attr_counter);
    }
    outfile << endl;
}
