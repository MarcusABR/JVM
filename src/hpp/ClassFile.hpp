/**
 * @file ClassFile.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira - 150143401
 * @brief Biblioteca de definição da estrutura de ClassFile 
 * @details A biblioteca ClassFile.hpp contém o arquivo com a descrição das funções
 * utilizadas para a implementação dos gets e sets dos componentes do Class File
 * @see ClassFile.cpp
 */

#ifndef __CLASSFILE_H_INCLUDED__
#define __CLASSFILE_H_INCLUDED__

#define typeof __typeof__

#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>
#include "CPInfo.hpp"
#include "FieldInfo.hpp"
#include "MethodInfo.hpp"
#include "AttributeInfo.hpp"
#include "InterfaceInfo.hpp"


using namespace std;
/** @class ClassFile
*   @brief Classe que contém toda a estrutura do .class
*/

class ClassFile {
private:
    uint32_t magic;
    uint16_t minorVersion;
    uint16_t majorVersion;
    uint16_t constantPoolCount;
    vector<CPInfo*> constantPool;
    uint16_t accessFlags;
    uint16_t thisClass;
    uint16_t superClass;
    uint16_t interfacesCount;
    vector<InterfaceInfo*> interfaces;
    uint16_t fieldsCount;
    vector<FieldInfo*> fields;
    uint16_t methodsCount;
    vector<MethodInfo*> methods;
    uint16_t attributesCount;
    AttributeInfo* attributes;

    void setMagic(FILE * fp);
    void setMajorVersion(FILE * fp);
    void setMinor(FILE * fp);
    void setConstantPoolCount(FILE * fp);
    void setConstantPool(FILE * fp);
    void setAccessFlags(FILE * fp);
    void setThisClass(FILE * fp);
    void setSuperClass(FILE * fp);
    void setInterfacesCount(FILE * fp);
    void setInterfaces(FILE * fp);
    void setFieldsCount(FILE * fp);
    void setFields(FILE * fp);
    void setMethodsCount(FILE * fp);
    void setMethods(FILE * fp);
    void setAttributesCount(FILE * fp);
    void setAttributes(FILE * fp);
public:
    static const uint32_t MAGIC_NUMBER = 0xCAFEBABE;
    static const uint16_t ACC_PUBLIC = 0x0001;
    static const uint16_t ACC_FINAL = 0x0010;
    static const uint16_t ACC_SUPER = 0x0020;
    static const uint16_t ACC_INTERFACE = 0x0200;
    static const uint16_t ACC_ABSTRACT = 0x0400;
    static const uint16_t ACC_SYNTHETIC = 0x1000;
    static const uint16_t ACC_ANNOTATION = 0x2000;
    static const uint16_t ACC_ENUM = 0x4000;
    ClassFile();
    ClassFile(FILE * fp);
    ~ClassFile();

    uint32_t getMagic() {
        return magic;
    }
    uint16_t getMajorVersion() {
        return majorVersion;
    }
    uint16_t getMinorVersion() {
        return minorVersion;
    }
    uint16_t getConstantPoolCount() {
        return constantPoolCount;
    }
    vector<CPInfo*> getConstantPool() {
        return constantPool;
    }

    uint16_t getAccessFlags() {
        return accessFlags;
    }
    uint16_t getThisClass() {
        return thisClass;
    }
    uint16_t getSuperClass() {
        return superClass;
    }
    uint16_t getInterfacesCount() {
        return interfacesCount;
    }

    vector<InterfaceInfo*> getInterfaces() {
        return interfaces;
    }

    uint16_t getFieldsCount() {
        return fieldsCount;
    }

    vector<FieldInfo*> getFields() {
        return fields;
    }

    uint16_t getMethodsCount() {
        return methodsCount;
    }

    vector<MethodInfo*> getMethods() {
        return methods;
    }

    uint16_t getAttributesCount() {
        return attributesCount;
    }

    AttributeInfo* getAttributes() {
        return attributes;
    }
};


#endif