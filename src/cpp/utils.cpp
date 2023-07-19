/**
 * @file Nom
 * @author André Larrosa Chimpliganond - 190010321
 * @author Marcus Vinicius Oliveira de Abrantes - 190034084
 * @author  Matheus Barbosa e Silva - 190113987
 * @author Moises Felipe Jaco Andrade de Lima - 190018364 
 * @author Thiago Elias dos Reis - 190126892
 * @brief Definicoes de funcoes auxiliares
 * @details Define diversas funcoes relacionadas a interpretacao de dados de 
 * ponto flutuante, abertura de arquivos ou flags.
**/

#include "../hpp/utils.hpp"
#include "../hpp/class_file.hpp"
#include "../hpp/leitor_exibidor.hpp"
#include <cmath>
#include <limits>
#include <sys/stat.h>

double ler_double(u4 high, u4 low)
{
    u8 bits = ler_long(high, low);
    if (bits == 0x7ff0000000000000L)
        return numeric_limits<double>::infinity();
    else if (bits == 0xfff0000000000000L)
        return -numeric_limits<double>::infinity();
    else if (bits >= 0x7ff0000000000001L && bits <= 0x7fffffffffffffffL)
        return numeric_limits<double>::quiet_NaN();
    else if (bits >= 0xfff0000000000001L && bits <= 0xffffffffffffffffL)
        return numeric_limits<double>::quiet_NaN();
    else
    {
        int s = ((bits >> 63) == 0) ? 1 : -1;
        int e = (bits >> 52) & 0x7ffL;
        u8 m = (e == 0) ? ((bits & 0xfffffffffffffL) << 1) : ((bits & 0xfffffffffffffL) | 0x10000000000000L);
        return s * m * pow(2, e - 1075);
    }
}


float ler_float(u4 bytes)
{
    if (bytes == 0x7f800000)
        return numeric_limits<float>::infinity();
    else if (bytes == 0xff800000)
        return -numeric_limits<float>::infinity();
    else if (bytes >= 0x7f800001 && bytes <= 0x7fffffff)
        return numeric_limits<float>::signaling_NaN();
    else if (bytes >= 0xff800001 && bytes <= 0xffffffff)
        return numeric_limits<float>::signaling_NaN();
    else
    {
        int s = ((bytes >> 31) == 0) ? 1 : -1;
        int e = ((bytes >> 23) & 0xff);
        int m = (e == 0) ? 
            (bytes & 0x7fffff) << 1 :
            (bytes & 0x7fffff) | 0x800000;

        return s * m * pow(2, e - 150);
    }
}

long long ler_long(u4 high, u4 low)
{
    auto l = ((u8) high << 32) | low;
    return (long long) l;
}


ifstream abrir_arquivo(string &nome_arquivo)
{
    ifstream arquivo(nome_arquivo, ios::binary);
    return arquivo;
}


string ler_nome(cp_info_vector &constant_pool, u2 idx)
{
    return to_cp_info(constant_pool[idx - 1])->_class->get_conteudo(constant_pool);
}


bool existe(string &nome)
{
    struct stat buffer;   
    return (stat (nome.c_str(), &buffer) == 0); 
}

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

string ler_flags_acesso(u2 flags_acesso, int type)
{
    string classe_acessos = " ";
    
    Nibble n;
    n.h16 = flags_acesso;

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
                classe_acessos += "ACC_PUBLIC ";
                break;
            case ACC_FINAL:
                classe_acessos += "ACC_FINAL ";
                break;
            case ACC_SYNTHETIC:
                classe_acessos += "ACC_SYNTHETIC ";
                break;
        }
        if (type == CLASS)
        {
            switch (flag)
            {
                case ACC_SUPER:
                    classe_acessos += "ACC_SUPER ";
                    break;
                case ACC_INTERFACE:
                    classe_acessos += "ACC_INTERFACE ";
                    break;
                case ACC_ABSTRACT:
                    classe_acessos += "ACC_ABSTRACT ";
                    break;
                case ACC_ANNOTATION:
                    classe_acessos += "ACC_ANNOTATION ";
                    break;
                case ACC_ENUM:
                    classe_acessos += "ACC_ENUM ";
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
                    classe_acessos += "ACC_ENUM ";
                    break;
                case ACC_PRIVATE:
                    classe_acessos += "ACC_PRIVATE ";
                    break;
                case ACC_PROTECTED:
                    classe_acessos += "ACC_PROTECTED ";
                    break;
                case ACC_STATIC:
                    classe_acessos += "ACC_STATIC ";
                    break;
                case ACC_VOLATILE:
                    classe_acessos += "ACC_VOLATILE ";
                    break;
                case ACC_TRANSIENT:
                    classe_acessos += "ACC_TRANSIENT ";
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
                    classe_acessos += "ACC_ABSTRACT ";
                    break;
                case ACC_PRIVATE:
                    classe_acessos += "ACC_PRIVATE ";
                    break;
                case ACC_PROTECTED:
                    classe_acessos += "ACC_PROTECTED ";
                    break;
                case ACC_STATIC:
                    classe_acessos += "ACC_STATIC ";
                    break;
                case ACC_SYNCHRONIZED:
                    classe_acessos += "ACC_SYNCHRONIZED ";
                    break;
                case ACC_BRIDGE:
                    classe_acessos += "ACC_BRIDGE ";
                    break;
                case ACC_VARARGS:
                    classe_acessos += "ACC_VARARGS ";
                    break;
                case ACC_NATIVE:
                    classe_acessos += "ACC_NATIVE ";
                    break;
                case ACC_STRICT:
                    classe_acessos += "ACC_STRICT ";
                    break;
                default:
                    break;
            }
        }
        else
            classe_acessos = "###########ERRO########## - Flag de acesso inválida";
    }
    return classe_acessos;
}