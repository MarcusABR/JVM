#ifndef _CONSTANT_POOL_INFO_HPP
#define _CONSTANT_POOL_INFO_HPP

#include <memory>
#include "types.hpp"

using namespace std; 

typedef enum {
    CONSTANT_Utf8               =  1,
    CONSTANT_Integer            =  3,
    CONSTANT_Float              =  4,
    CONSTANT_Long               =  5,
    CONSTANT_Double             =  6,
    CONSTANT_Class              =  7,
    CONSTANT_String             =  8,
    CONSTANT_Fieldref           =  9,
    CONSTANT_Methodref          = 10,
    CONSTANT_InterfaceMethodref = 11,
    CONSTANT_NameAndType        = 12,
    CONSTANT_MethodHandle       = 15,
    CONSTANT_MethodType         = 16,
    CONSTANT_InvokeDynamic      = 18,
    CONSTANT_Continuation       = 19
} CONSTANT_Types;


class CP_Item {
public:
    CP_Item(u1);
    virtual ~CP_Item() {}
    CONSTANT_Types tag;
};


typedef vector<shared_ptr<CP_Item>> cp_info_vector;

struct CONSTANT_utf8_info {
    CONSTANT_utf8_info(ifstream &file);
    u2 length;
    vector<u1> bytes;
    void exibir();
    string get_conteudo();
};

struct CONSTANT_integer_info {
    CONSTANT_integer_info(ifstream &file);
    u4 bytes;
    void exibir();
    string get_conteudo();
};

struct CONSTANT_float_info {
    CONSTANT_float_info(ifstream &file);
    u4 bytes;
    void exibir();
    string get_conteudo();
};

struct CONSTANT_long_info {
    CONSTANT_long_info(ifstream &file);
    u4 high_bytes;
    u4 low_bytes;
    void exibir();
    string get_conteudo();
};

struct CONSTANT_double_info {
    CONSTANT_double_info(ifstream &file);
    u4 high_bytes;
    u4 low_bytes;
    void exibir();
    string get_conteudo();
};

struct CONSTANT_class_info {
    CONSTANT_class_info(ifstream &file);
    u2 name_idx;
    void exibir(cp_info_vector&);
    string get_conteudo(cp_info_vector&);
};

struct CONSTANT_string_info {
    CONSTANT_string_info(ifstream &file);
    u2 str_idx;
    void exibir(cp_info_vector&);
    string get_conteudo(cp_info_vector&);
};

struct CONSTANT_fieldref_info {
    CONSTANT_fieldref_info(ifstream &file);
    u2 class_idx;
    u2 name_and_type_idx;
    void exibir(cp_info_vector&);
    string get_conteudo(cp_info_vector&);
};

struct CONSTANT_methodref_info {
    CONSTANT_methodref_info(ifstream &file);
    u2 class_idx;
    u2 name_and_type_idx;
    void exibir();
    string get_class_name(cp_info_vector&);
    string get_conteudo(cp_info_vector&);
    string get_method_name(cp_info_vector&);
    string get_method_descriptor(cp_info_vector&);
};

struct CONSTANT_interface_methodref_info {
    CONSTANT_interface_methodref_info(ifstream &file);
    u2 class_idx;
    u2 name_and_type_idx;
    void exibir();
    string get_content();
};

struct CONSTANT_name_and_type_info {
    CONSTANT_name_and_type_info(ifstream &file);
    u2 name_idx;
    u2 descriptor_idx;
    void exibir();
    string get_content();
    string get_name(cp_info_vector&);
    string get_descriptor(cp_info_vector&);
};

struct CONSTANT_method_handle_info {
    CONSTANT_method_handle_info(ifstream &file);
    u1 reference_kind;
    u2 reference_index;
    void exibir();
    string get_content();
};

struct CONSTANT_method_type_info {
    CONSTANT_method_type_info(ifstream &file);
    u2 descriptor_index;
    void exibir();
    string get_content();
};

struct CONSTANT_invoke_dynamic_info {
    CONSTANT_invoke_dynamic_info(ifstream &file);
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
    void exibir();
    string get_content();
};

class CP_Info : public CP_Item {
public:
    CP_Info(u1 tag, ifstream &file);
    ~CP_Info();

    union {
        CONSTANT_utf8_info* _utf8;
        CONSTANT_integer_info* _integer;
        CONSTANT_float_info* _float;
        CONSTANT_long_info* _long;
        CONSTANT_double_info* _double;
        CONSTANT_class_info* _class;
        CONSTANT_string_info* _string;
        CONSTANT_fieldref_info* _fieldref;
        CONSTANT_methodref_info* _methodref;
        CONSTANT_interface_methodref_info* _interface_methodref;
        CONSTANT_name_and_type_info* _name_and_type;
        CONSTANT_method_handle_info* _method_handle;
        CONSTANT_method_type_info* _method_type;
        CONSTANT_invoke_dynamic_info* _invoke_dynamic;
    };

    void exibir_info(cp_info_vector&, unsigned int&);
    string get_conteudo(cp_info_vector&);

};

#endif // _CONSTANT_POOL_INFO_HPP