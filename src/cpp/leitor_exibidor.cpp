#include "../hpp/leitor_exibidor.hpp"
#include "../hpp/windows.hpp"
#include "../hpp/utils.hpp"
#include <iomanip>
#include <regex>
#include <iostream>

using namespace std;

inline unsigned int pos_counter = 0;

inline ofstream arquivo_saida;

inline void criar_arquivo_saida(string nome_arquivo)
{

    printf("criar_arquivo_saida\n");
    create_dir();
    arquivo_saida = ofstream("./out/" + nome_arquivo + ".txt");
}


inline void ler_exibir_arquivo(class_file &class_f, string caminho_arquivo)
{
    printf("ler_exibir_arquivo\n");

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

inline void exibir_informacoes_gerais(class_file &class_f)
{

    printf("exibir_informacoes_gerais\n");
    arquivo_saida << "----------Informações Gerais----------" << endl;
    ios_base::fmtflags f(arquivo_saida.flags());
    arquivo_saida << "Magic " << "'0x" << uppercase << hex << class_f.getMagic() << "'  " << endl;
    arquivo_saida.flags(f);
    
    arquivo_saida << "Minor version '" << class_f.getMinorVersion() << "'  " << endl;
    arquivo_saida << "Major version '" << class_f.getMajorVersion() << "'";
    arquivo_saida << "['" << get_versao(class_f.getMajorVersion(), class_f.getMinorVersion()) << "']  " << endl;
    
    arquivo_saida << "Constant Pool Count '" << class_f.getConstantPoolCount() << "'  " << endl;
    
    ios_base::fmtflags g(arquivo_saida.flags());
    arquivo_saida << "Access Flags '0x" << setw(4) << setfill('0') << hex << class_f.getAccessFlags() << "'";
    arquivo_saida << " ['" << ler_flags_acesso(class_f.getAccessFlags(), CLASS) << "']  " << endl;
    arquivo_saida.flags(g);
    
    auto this_class = to_cp_info(class_f.getConstantPool()[class_f.getThisClass() - 1])->_class->name_idx;
    auto this_class_name = *(to_cp_info(class_f.getConstantPool()[this_class - 1])->_utf8);
    arquivo_saida << "This Class '" << class_f.getThisClass() << "' ";
    arquivo_saida << "'<" << exibir_utf8(this_class_name)  << ">'  " << endl;
    
    auto super_class = to_cp_info(class_f.getConstantPool()[class_f.getSuperClass() - 1])->_class->name_idx;
    auto super_class_name = *(to_cp_info(class_f.getConstantPool()[super_class - 1])->_utf8);
    arquivo_saida << "Super Class '" << class_f.getSuperClass() << "' ";
    arquivo_saida << "'<" << exibir_utf8(super_class_name) << ">'  " << endl;

    arquivo_saida << "Interfaces Count '" << class_f.getInterfacesCount() << "'  " << endl;
    arquivo_saida << "Fields Count '" << class_f.getFieldsCount() << "'  " << endl;
    arquivo_saida << "Methods Count '" << class_f.getMethodsCount() << "'  " << endl;
    arquivo_saida << "Attributes Count '" << class_f.getAttributesCount() << "'" << endl;
    arquivo_saida << endl;
}

inline string get_versao(u2 major, u2 minor)
{
    printf("get_versao\n");

    if (major >= 45 && major <= 48)
        return "1." + to_string(major - 45 + 1);
    return to_string(major - 49 + 5);
}

inline void exibir_constant_pool(cp_info_vector &constant_pool)
{
    printf("exibir_constant_pool\n");

    unsigned int cp_counter = 1;
    arquivo_saida << "----------Constant Pool----------" << endl << endl << endl;

    for (auto cp_item : constant_pool) 
    {
        auto cp_info = to_cp_info(cp_item);
        cp_info->exibir_info(constant_pool, cp_counter);
    }
    arquivo_saida << "________________________________________________________________" << endl << endl;
}


inline string exibir_utf8(CONSTANT_utf8_info &utf8)
{
    printf("exibir_utf8\n");

    string out = "";
    // loop infinito
    for (auto j : utf8.bytes){
        printf("%hhx\n", j);
        out += j;
    }
    
    printf("vai sair exibir_utf8\n");
    return out;
}


inline void exibir_interfaces(class_file &class_f)
{
    printf("exibir_interfaces\n");

    arquivo_saida << "----------Interfaces----------" << endl << endl;
    arquivo_saida << "________________________________________________________________" <<endl << endl;

    for (auto interface : class_f.getInterfaces() )
    {
        auto interface_name_index = to_cp_info(class_f.getConstantPool()[interface - 1])->_class->name_idx;
        auto interface_name = *(to_cp_info(class_f.getConstantPool()[interface_name_index - 1])->_utf8);
        arquivo_saida << "- Interface: '" << interface << "' ";
        arquivo_saida << "'<" << exibir_utf8(interface_name) << ">'" << endl;
    }
}


inline void exibir_campos(class_file &class_f)
{
    printf("exibir_campos\n");

    unsigned int field_counter = 0;
    arquivo_saida << "----------Fields----------" << endl << endl;
    arquivo_saida << endl << endl;

    for (auto field : class_f.getFields() ) 
    {
        auto field_name = *(to_cp_info(class_f.getConstantPool()[field.name_idx - 1])->_utf8);
        auto field_descriptor = *(to_cp_info(class_f.getConstantPool()[field.descriptor_idx - 1])->_utf8);

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


inline void exibir_metodos(class_file &class_f)
{
    printf("exibir_metodos\n");

    unsigned int method_counter = 0;
    arquivo_saida << "----------Methods----------" << endl;
    arquivo_saida << endl << endl;

    for (auto method : class_f.getMethods()) 
    {
        auto method_name = *(to_cp_info(class_f.getConstantPool()[method.name_idx - 1])->_utf8);
        auto method_descriptor = *(to_cp_info(class_f.getConstantPool()[method.descriptor_idx - 1])->_utf8);

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


inline void exibir_atributos_de_classe(class_file &class_fp)
{
    printf("exibir_atributos_de_classe\n");

    class_file &class_f = class_fp;
    arquivo_saida << "----------Attributes----------" << endl;
    arquivo_saida << "________________________________________________________________" << endl << endl;
    exibir_vetor_atributos(class_f.attributes, class_f.constant_pool);
    arquivo_saida << "________________________________________________________________"<< endl << endl;
}


inline void exibir_vetor_atributos(attr_info_vector &attr_vector, cp_info_vector &constant_pool)
{
    printf("exibir_vetor_atributos\n");

    unsigned int attr_counter = 0;
    for (auto attr : attr_vector)
    {
        auto attr_info = to_attr_info(attr);
        attr_info->exibir_info(constant_pool, attr_counter);
    }
    arquivo_saida <<  endl;
}
