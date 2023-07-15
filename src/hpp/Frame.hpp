/**
 * @file Frame.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Execução de um método. 
 * @details A biblioteca Frame.hpp possui os componentes necessários para execução de um método.
 * Define o uso para evitar a inclusão múltipla de arquivos.
 * Um novo frame é criado cada vez que um método é invocado. Um frame é destruído quando sua invocação de método é concluída.
 * Os quadros são alocados na pilha da JVM do thread que cria o frame. Cada frame tem seu próprio array de variáveis ​​locais, sua própria pilha de operandos e uma referência ao pool de constantes.
 * @see Frame.cpp
 * @see CPInfo.hpp
 * @see MethodInfo.hpp
 */

#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include <cstdint>
#include <vector>
#include <stack>
#include "CPInfo.hpp"
#include "MethodInfo.hpp"

const uint64_t JAVA_NULL = 0;
const uint8_t CAT_NULL = 0;
const uint8_t CAT1 = 1;
const uint8_t CAT2 = 2;
struct JavaType {
    uint8_t tag;
    union {
        uint32_t type_empty;
        uint32_t type_boolean;
        uint32_t type_byte;
        uint32_t type_char;
        uint32_t type_short;
        uint32_t type_int;
        uint32_t type_float;
        uint64_t type_reference;
        uint32_t type_returnAddress;
        uint64_t type_long;
        uint64_t type_double;
    };
};

/** @class Frame
 *  @brief Classe que contém todos os atributos para a criação de um frame
 */
class Frame {
private:
    MethodInfo* method;
    CodeAttribute codeAttribute;
public:
    vector<CPInfo*> constantPool;
    stack<JavaType> operandStack;
    vector<JavaType> localVariables;
    stack<Frame>* jvmStack;
    uint32_t localPC;
    // Frame(vector<JavaType>, stack<JavaType>, vector<CPInfo*>);
    Frame(vector<CPInfo*>, MethodInfo*, stack<Frame>*);
    uint8_t* getCode() {
        return this->codeAttribute.getCode();
    }
    uint32_t getCodeLength() {
        return this->codeAttribute.getCodeLength();
    }
};

#endif