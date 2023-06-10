#include "../include/leitor_exibidor.hpp"
#include "../include/windows.hpp"
#include "../include/utils.hpp"
#include <iomanip>
#include <regex>
#include <iostream>

using namespace std;

unsigned int pos_counter = 0;

ofstream arquivo_saida;

void criar_arquivo_saida(string nome_arquivo)
{
    create_dir();
    arquivo_saida = ofstream("./out/" + nome_arquivo + ".txt");
}


void ler_exibir_arquivo(class_file &class_f, string caminho_arquivo)
{
    smatch matcher;
    regex regexp("[a-zA-Z0-9_]+.class");
    regex_search(caminho_arquivo, matcher, regexp);
    
    string nome_arquivo = matcher[0];
    nome_arquivo = nome_arquivo.substr(0, nome_arquivo.find('.')); 
    criar_arquivo_saida(nome_arquivo);

    arquivo_saida << "CLASSE: " << nome_arquivo << "" << endl << endl;
    exibir_informacoes_gerais(class_f);
    exibir_constant_pool(class_f.constant_pool);
    exibir_interfaces(class_f);
    exibir_campos(class_f);
    exibir_metodos(class_f);
    exibir_atributos_de_classe(class_f);
    arquivo_saida.close();
    pos_counter = 0;

    cout << "Arquivo: \"" << nome_arquivo + ".txt\" criado com sucesso em /out/" << endl;
}

void exibir_informacoes_gerais(class_file &class_f)
{
    arquivo_saida << "----------Informações Gerais----------" << endl;
    ios_base::fmtflags f(arquivo_saida.flags());
    arquivo_saida << "Magic " << "'0x" << uppercase << hex << class_f.magic << "'  " << endl;
    arquivo_saida.flags(f);
    
    arquivo_saida << "Minor version '" << class_f.minor_version << "'  " << endl;
    arquivo_saida << "Major version '" << class_f.major_version << "'";
    arquivo_saida << "['" << get_versao(class_f.major_version, class_f.minor_version) << "']  " << endl;
    
    arquivo_saida << "Constant Pool Count '" << class_f.constant_pool_count << "'  " << endl;
    
    ios_base::fmtflags g(arquivo_saida.flags());
    arquivo_saida << "Access Flags '0x" << setw(4) << setfill('0') << hex << class_f.access_flag << "'";
    arquivo_saida << " ['" << ler_flags_acesso(class_f.access_flag, CLASS) << "']  " << endl;
    arquivo_saida.flags(g);
    
    auto this_class = to_cp_info(class_f.constant_pool[class_f.this_class - 1])->_class->name_idx;
    auto this_class_name = *(to_cp_info(class_f.constant_pool[this_class - 1])->_utf8);
    arquivo_saida << "This Class '" << class_f.this_class << "' ";
    arquivo_saida << "'<" << exibir_utf8(this_class_name)  << ">'  " << endl;
    
    auto super_class = to_cp_info(class_f.constant_pool[class_f.super_class - 1])->_class->name_idx;
    auto super_class_name = *(to_cp_info(class_f.constant_pool[super_class - 1])->_utf8);
    arquivo_saida << "Super Class '" << class_f.super_class << "' ";
    arquivo_saida << "'<" << exibir_utf8(super_class_name) << ">'  " << endl;

    arquivo_saida << "Interfaces Count '" << class_f.interfaces_count << "'  " << endl;
    arquivo_saida << "Fields Count '" << class_f.fields_count << "'  " << endl;
    arquivo_saida << "Methods Count '" << class_f.methods_count << "'  " << endl;
    arquivo_saida << "Attributes Count '" << class_f.attributes_count << "'" << endl;
    arquivo_saida << endl;
}

string get_versao(u2 major, u2 minor)
{
    if (major >= 45 && major <= 48)
        return "1." + to_string(major - 45 + 1);
    return to_string(major - 49 + 5);
}

void exibir_constant_pool(cp_info_vector &constant_pool)
{
    unsigned int cp_counter = 1;
    arquivo_saida << "----------Constant Pool----------" << endl << endl << endl;

    for (auto cp_item : constant_pool) 
    {
        auto cp_info = to_cp_info(cp_item);
        cp_info->exibir_info(constant_pool, cp_counter);
    }
    arquivo_saida << "________________________________________________________________" << endl << endl;
}


string exibir_utf8(CONSTANT_utf8_info &utf8)
{
    string out = "";
    for (auto j : utf8.bytes)
         out += j;
    return out;
}


void exibir_interfaces(class_file &class_f)
{
    arquivo_saida << "----------Interfaces----------" << endl << endl;
    arquivo_saida << "________________________________________________________________" <<endl << endl;

    for (auto interface : class_f.interfaces)
    {
        auto interface_name_index = to_cp_info(class_f.constant_pool[interface - 1])->_class->name_idx;
        auto interface_name = *(to_cp_info(class_f.constant_pool[interface_name_index - 1])->_utf8);
        arquivo_saida << "- Interface: '" << interface << "' ";
        arquivo_saida << "'<" << exibir_utf8(interface_name) << ">'" << endl;
    }
}


void exibir_campos(class_file &class_f)
{
    unsigned int field_counter = 0;
    arquivo_saida << "----------Fields----------" << endl << endl;
    arquivo_saida << endl << endl;

    for (auto field : class_f.fields) 
    {
        auto field_name = *(to_cp_info(class_f.constant_pool[field.name_idx - 1])->_utf8);
        auto field_descriptor = *(to_cp_info(class_f.constant_pool[field.descriptor_idx - 1])->_utf8);

        arquivo_saida << "--> [" << field_counter++ << "] '" << exibir_utf8(field_name) << "'" << endl;

        ios_base::fmtflags f(arquivo_saida.flags());
        arquivo_saida << "- Fields Access Flags '0x" << hex << setw(4) << setfill('0') << field.access_flags << "'" << endl;
        arquivo_saida << "['" << ler_flags_acesso(field.access_flags, FIELD) << "']" << endl;
        arquivo_saida.flags(f);

        arquivo_saida << "- Name Index '" << field.name_idx << "' ";
        arquivo_saida << "'<" << exibir_utf8(field_name) << ">'" << endl;
        arquivo_saida << "- Descriptor Index '" << field.descriptor_idx << "' ";
        arquivo_saida << "'<" << exibir_utf8(field_descriptor) << ">'" << endl;
        arquivo_saida << "- Attribute Count '" << field.attr_count << "'" << endl;
        
        arquivo_saida << "<details><summary>Show attributes</summary>" << endl << endl;
        exibir_vetor_atributos(field.attr, class_f.constant_pool);
        arquivo_saida << "________________________________________________________________" << endl << endl;
    }
    arquivo_saida <<  "________________________________________________________________"<<endl << endl;
}


void exibir_metodos(class_file &class_f)
{
    unsigned int method_counter = 0;
    arquivo_saida << "----------Methods----------" << endl;
    arquivo_saida << endl << endl;

    for (auto method : class_f.methods) 
    {
        auto method_name = *(to_cp_info(class_f.constant_pool[method.name_idx - 1])->_utf8);
        auto method_descriptor = *(to_cp_info(class_f.constant_pool[method.descriptor_idx - 1])->_utf8);

        arquivo_saida << "--> [" << method_counter++ << "] '" << exibir_utf8(method_name) << "' " << endl;

        ios_base::fmtflags f(arquivo_saida.flags());
        arquivo_saida << "- Methods Access Flags " << "'0x" << uppercase << hex << method.access_flags << "' ";
        arquivo_saida.flags(f);

        arquivo_saida << "['" << ler_flags_acesso(method.access_flags, METHOD) << "']" << endl;
        arquivo_saida << "- Name Index '" << method.name_idx << "' ";
        arquivo_saida << "'<" << exibir_utf8(method_name) << ">'" << endl;
        arquivo_saida << "- Descriptor Index '" << method.descriptor_idx << "' ";
        arquivo_saida << "'<" << exibir_utf8(method_descriptor) << ">'" << endl;
        arquivo_saida << "- Attribute Count '" << method.attr_count << "'" << endl;
        
        arquivo_saida << endl << endl;
        exibir_vetor_atributos(method.attr, class_f.constant_pool);
    }
    arquivo_saida << "________________________________________________________________" << endl << endl;
}


void exibir_atributos_de_classe(class_file &class_f)
{
    arquivo_saida << "----------Attributes----------" << endl;
    arquivo_saida << "________________________________________________________________" << endl << endl;
    exibir_vetor_atributos(class_f.attributes, class_f.constant_pool);
    arquivo_saida << "________________________________________________________________"<< endl << endl;
}


void exibir_vetor_atributos(attr_info_vector &attr_vector, cp_info_vector &constant_pool)
{
    unsigned int attr_counter = 0;
    for (auto attr : attr_vector)
    {
        auto attr_info = to_attr_info(attr);
        attr_info->exibir_info(constant_pool, attr_counter);
    }
    arquivo_saida <<  endl;
}
