/**
 * @file FieldInfo.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Descreve a classe FieldInfo para estruturas do tipo field_info
 * @details A estrutura tipo field_info representa os fields de um arquivo .class
 * @see FieldInfo.cpp
 */

#ifndef FIELDINFO_H_INCLUDED
#define FIELDINFO_H_INCLUDED

#include <cstdint>
#include <vector>
#include "AttributeInfo.hpp"
#include "Frame.hpp"


using namespace std;
/** @class FieldInfo
*   @brief Classe que contém a estrutura de uma field; 
*/
class FieldInfo {
private:
    uint16_t accessFlags;
    uint16_t descriptorIndex;
    uint16_t attributesCount;
    vector<AttributeInfo*> attributes;
public:
    uint16_t nameIndex;
    JavaType staticValue;
    static const uint16_t ACC_PUBLIC = 0x0001;
    static const uint16_t ACC_PRIVATE = 0x0002;
    static const uint16_t ACC_PROTECTED = 0x0004;
    static const uint16_t ACC_STATIC = 0x0008;
    static const uint16_t ACC_FINAL = 0x0010;
    static const uint16_t ACC_VOLATILE = 0x0040;
    static const uint16_t ACC_TRANSIENT = 0x0080;
    static const uint16_t ACC_SYNTHETIC = 0x1000;
    static const uint16_t ACC_ENUM = 0x4000;
    ~FieldInfo();
    void read(FILE *fp, vector<CPInfo*> constantPool);

    uint16_t getAccessFlags(){
        return accessFlags;
    }
    uint16_t getNameIndex(){
        return nameIndex;
    }
    uint16_t getDescriptorIndex(){
        return descriptorIndex;
    }
    uint16_t getAttributesCount(){
        return attributesCount;
    }
};

#endif