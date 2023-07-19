#ifndef _LEITOR_EXIBIDOR_HPP
#define _LEITOR_EXIBIDOR_HPP

#include "class_file.hpp"
#include "constant_pool_info.hpp"

#define CLASS 0
#define FIELD 1
#define METHOD 2

void exibir_informacoes_gerais(class_file &class_f);
string exibir_utf8(CONSTANT_utf8_info&);
string get_versao(u2 major, u2 minor);
string ler_flags_acesso(u2 access_flags, int type);
void exibir_constant_pool(cp_info_vector&);
void exibir_vetor_atributos(attr_info_vector&, cp_info_vector&);
void exibir_interfaces(class_file &class_f);
void exibir_campos(class_file &class_f);
void exibir_metodos(class_file &class_f);
void exibir_atributos_de_classe(class_file &class_f);
inline void criar_arquivo_saida(string nome_arquivo);
inline void ler_exibir_arquivo(class_file &class_f, string caminho_arquivo);

#endif // _LEITOR_EXIBIDOR