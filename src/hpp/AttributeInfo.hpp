/**
 * @file AttributeInfo.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Atributos a serem usados na execuçao da JVM 
 * @details A biblioteca AttributeInfo.hpp contém o arquivo com a descrição das funções
 * utilizadas para a implementação dos gets e sets dos componentes do Attribute Info
 * @see AttributeInfo.cpp
 */

#ifndef ATTRIBUTE_INFO_H_INCLUDED
#define ATTRIBUTE_INFO_H_INCLUDED

#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>
#include "ByteReader.hpp"
#include "CPInfo.hpp"

using namespace std;

class AttributeInfo;
class ConstantValueAttribute;
class CodeAttribute;
/** @class ConstantValueAttribute
*   @brief Classe que consiste em armazenar as informações dos index referentes aos atributos
*/

class ConstantValueAttribute {
private:
    uint16_t constantValueIndex;
public:
    void read(FILE*);
    uint16_t getConstantValueIndex() {
        return constantValueIndex;
    }
};

/** @class ExceptionHandler
*   @brief Classe que consiste em armazenar as informações das exceções 
*/

class ExceptionHandler {
private:
    uint16_t startPC;
    uint16_t endPC;
    uint16_t handlerPC;
    uint16_t catchType;
public:
    void read(FILE * fp);
    uint16_t getStartPC() {
        return startPC;
    };
    uint16_t getEndPC() {
        return endPC;
    };
    uint16_t getHandlerPC() {
        return handlerPC;
    };
    uint16_t getCatchType() {
        return catchType;
    };
};

/** @class CodeAttribute
 *  @brief Classe que consiste em armazenar as  informações dos atributos
*/

class CodeAttribute {
private:
    uint16_t maxStack;
    uint16_t maxLocals;
    uint32_t codeLength;
    uint8_t *code;
    uint16_t exceptionTableLength;
    ExceptionHandler* exceptionTable;
    uint16_t attributesCount;
    AttributeInfo *attributes;
public:
    void read(FILE*, vector<CPInfo*>);
    uint16_t getMaxStack() {
        return maxStack;
    }
    uint16_t getMaxLocals() {
        return maxLocals;
    }
    uint32_t getCodeLength() {
        return codeLength;
    }
    uint8_t* getCode() {
        return code;
    }
    uint16_t getExceptionTableLength() {
        return exceptionTableLength;
    }
    ExceptionHandler* getExceptionTable() {
        return exceptionTable;
    }
    uint16_t getAttributesCount() {
        return attributesCount;
    }
    AttributeInfo* getAttributes() {
        return attributes;
    }
};

/** @class ExceptionAttribute
*   @brief Classe contém numberOfExceptions e ponteiro para exceptionIndexTable - todos uint16;
*/


class ExceptionsAttribute {
private:
    uint16_t numberOfExceptions;
    uint16_t *execeptionIndexTable;
public:
    void read(FILE *);
    uint16_t getNumberOfExceptions() {
        return numberOfExceptions;
    }
    uint16_t* getExeceptionIndexTable() {
        return execeptionIndexTable;
    }
};

/** @class ClassInfo
*   @brief Classe que contém as informações gerais das classes
*/

class ClassInfo {
private:
    uint16_t innerClassInfoIndex;
    uint16_t outerClassInfoIndex;
    uint16_t innerNameIndex;
    uint16_t innerClassAccessFlags;
public:
    void read(FILE * fp);
    uint16_t getInnerClassInfoIndex() {
        return innerClassInfoIndex;
    };
    uint16_t getOuterClassInfoIndex() {
        return outerClassInfoIndex;
    };
    uint16_t getInnerNameIndex() {
        return innerNameIndex;
    };
    uint16_t getInnerClassAccessFlags() {
        return innerClassAccessFlags;
    };
};


/** @class InnerClassesAttribute
*   @brief Classe que contém as informações dos atributos das classes
*/
class InnerClassesAttribute {
private:
    uint16_t numberOfClasses;
    ClassInfo *classes;
public:
    void read(FILE*);
    uint16_t getNumberOfClasses() {
        return numberOfClasses;
    }
    ClassInfo* getClasses() {
        return classes;
    }
};


/** @class SourceFileAttribute
*   @brief Classe que contém as informações do index do SourceFile
*/

class SourceFileAttribute {
private:
    uint16_t sourcefileIndex;
public:
    void read(FILE*);
    uint16_t getSourceFileIndex() {
        return sourcefileIndex;
    }
};

/** @class LineNumber
*   @brief Classe que contém as informações LineNumber contendo startPC e o lineNumber
*/

class LineNumber {
private:
    uint16_t startPC;
    uint16_t lineNumber;
public:
    void read(FILE *fp);
    uint16_t getStartPC() {
        return startPC;
    }
    uint16_t getLineNumber() {
        return lineNumber;
    }
};

/** @class LineNumberTableAttribute
*   @brief Classe que contém as informações LineNumberTableAttribute contendo o tamanho da LineNumberTable e um ponteiro do tipo LineNumber
*/

class LineNumberTableAttribute {
private:
    uint16_t lineNumberTableLength;
    LineNumber* lineNumberTable;
public:
    void read(FILE*);
    uint16_t getLineNumberTableLength() {
        return lineNumberTableLength;
    }
    LineNumber* getLineNumberTable() {
        return lineNumberTable;
    }
};


/** @class LocalVariable
*   @brief Classe que contém as características das variáveis locais;
*/
class LocalVariable {
private:
    uint16_t startPC;
    uint16_t length;
    uint16_t nameIndex;
    uint16_t descriptorIndex;
    uint16_t index;
public:
    void read(FILE*);
    uint16_t getStartPC() {
        return startPC;
    };
    uint16_t getLength() {
        return length;
    };
    uint16_t getNameIndex() {
        return nameIndex;
    };
    uint16_t getDescriptorIndex() {
        return descriptorIndex;
    };
    uint16_t getIndex() {
        return index;
    };
};

/** @class LocalVariableTableAttribute
*   @brief Classe que contém as variáves locais na tabela de atributos
*/

class LocalVariableTableAttribute {
private:
    uint16_t localVariableTableLength;
    LocalVariable *localVariableTable;
public:
    void read(FILE*);
    uint16_t getLocalVariableTableLength() {
        return localVariableTableLength;
    };
    LocalVariable* getLocalVariableTable() {
        return localVariableTable;
    };
};

/** @class AttributeInfo
*   @brief Classe que contém as informações dos atributos.
*/
class AttributeInfo {
private:
    uint16_t attributeNameIndex;
    uint32_t attributeLength;
    union {
        ConstantValueAttribute constantValue;
        CodeAttribute code;
        // StackMapTable stackMapTable;
        ExceptionsAttribute exceptions;
        InnerClassesAttribute innerClasses;
        // EnclosingMethod enclosingMethod;
        // Synthetic synthetic;
        // Signature signature;
        SourceFileAttribute sourceFile;
        // SourceDebugExtension sourceDebugExtension;
        LineNumberTableAttribute lineNumberTable;
        LocalVariableTableAttribute localVariableTable;
        // LocalVariableTypeTable localVariableTypeTable;
        // Deprecated deprecated;
        // RuntimeVisibleAnnotations runtimeVisibleAnnotations;
        // RuntimeInvisibleAnnotations runtimeInvisibleAnnotations;
        // RuntimeVisibleParameterAnnotations runtimeVisibleParameterAnnotations;
        // RuntimeInvisibleParameterAnnotations runtimeInvisibleParameterAnnotations;
        // RuntimeVisibleTypeAnnotations runtimeVisibleTypeAnnotations;
        // RuntimeInvisibleTypeAnnotations runtimeInvisibleTypeAnnotations;
        // AnnotationDefault annotationDefault;
        // BootstrapMethods bootstrapMethods;
        // MethodParameters methodParameters;
        uint8_t *info;
    };
public:
    AttributeInfo();
    // ~AttributeInfo();
    void read(FILE*, vector<CPInfo*>);
    void print(vector<CPInfo*>);

    uint16_t getAttributeNameIndex() {
        return attributeNameIndex;
    }

    uint16_t getAttributeLength() {
        return attributeLength;
    }

    ConstantValueAttribute getConstantValueAttribute() {
        return constantValue;
    }

    CodeAttribute getCodeAttribute() {
        return code;
    }

    InnerClassesAttribute getInnerClassesAttribute() {
        return innerClasses;
    }

    SourceFileAttribute getSourceFileAttribute() {
        return sourceFile;
    }

    LineNumberTableAttribute getLineNumberTableAttribute() {
        return lineNumberTable;
    }
    LocalVariableTableAttribute getLocalVariableTableAttribute() {
        return localVariableTable;
    }
    ExceptionsAttribute getExceptionsAttribute() {
        return exceptions;
    }
};

#endif