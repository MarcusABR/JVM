/**
 * @file MethodInfo.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Biblioteca com uma única classe MethodInfo para declaração conforme manual da Oracle em: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html.
 * @details Biblioteca MethodInfo para declaração das constantes requeridas para funcionamento dos métodos da JVM.
 * Cada método, incluindo cada método de inicialização de instância e o método de inicialização de classe ou interface, é descrito por uma estrutura method_info.
 * Dois métodos em um arquivo de classe não podem ter o mesmo nome e descritor.
 * O valor do item access_flags é uma máscara de sinalizadores usados ​​para denotar a permissão de acesso e as propriedades deste método estão declaradas.
 * O sinalizador ACC_VARARGS indica que esse método usa um número variável de argumentos no nível do código-fonte. 
 * Um método declarado para receber um número variável de argumentos deve ser compilado com o sinalizador ACC_VARARGS definido como 1 e,
   todos os outros métodos devem ser compilados com o sinalizador ACC_VARARGS definido como 0.
 * O sinalizador ACC_BRIDGE é usado para indicar um método de ponte gerado por um compilador Java.
 * Todos os métodos de interface devem ter seus sinalizadores ACC_ABSTRACT e ACC_PUBLIC definidos.
 * Um método de inicialização de instância específico (§2.9) pode ter no máximo um de seus sinalizadores ACC_PRIVATE, ACC_PROTECTED e ACC_PUBLIC definidos 
   e também pode ter seus sinalizadores ACC_STRICT, ACC_VARARGS e ACC_SYNTHETIC definidos, mas não deve ter nenhum dos outros sinalizadores.
 * Os métodos de inicialização de classes e interfaces são chamados implicitamente pela JVM e o valor de seu item access_flags é ignorado, exceto para a configuração do sinalizador ACC_STRICT.
 * Todos os bits do item access_flags não atribuídos na Tabela 4.5 são reservados para uso futuro,
   eles devem ser definidos como zero nos arquivos de classe gerados e devem ser ignorados pelas implementações do Java Virtual Machine.
 * @see MethodInfo.cpp
 * @see AttributeInfo.hpp
 */

#ifndef METHODINFO_H_INCLUDED
#define METHODINFO_H_INCLUDED

#include <cstdint>
#include <vector>
#include "AttributeInfo.hpp"

using namespace std;
/** @class MethodInfo
*   @brief Classe que contém toda a estrutura de um Method
*/

class MethodInfo {
private:
    uint16_t accessFlags;
    uint16_t nameIndex;
    uint16_t descriptorIndex;
    uint16_t attributesCount;
    AttributeInfo* attributes;
public:
    static const uint16_t ACC_PUBLIC = 0x0001;
    static const uint16_t ACC_PRIVATE = 0x0002;
    static const uint16_t ACC_PROTECTED = 0x0004;
    static const uint16_t ACC_STATIC = 0x0008;
    static const uint16_t ACC_FINAL = 0x0010;
    static const uint16_t ACC_SYNCHRONIZED = 0x0020;
    static const uint16_t ACC_BRIDGE = 0x0040;
    static const uint16_t ACC_VARARGS = 0x0080;
    static const uint16_t ACC_NATIVE = 0x0100;
    static const uint16_t ACC_ABSTRACT = 0x0400;
    static const uint16_t ACC_STRICT = 0x0800;
    static const uint16_t ACC_SYNTHETIC = 0x1000;
    void read(FILE* fp, vector<CPInfo*> constantPool);
    ~MethodInfo();

    uint16_t getAccessFlags() {
        return accessFlags;
    }
    uint16_t getNameIndex() {
        return nameIndex;
    }
    uint16_t getDescriptorIndex() {
        return descriptorIndex;
    }
    uint16_t getAttributesCount() {
        return attributesCount;
    }
    AttributeInfo* getAttributes() {
        return attributes;
    }
};

#endif