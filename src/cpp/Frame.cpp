/**
 * @file Frame.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Um frame é usado para armazenar dados e resultados parciais, bem como para realizar links dinâmicos, retornar valores para métodos e despachar exceções.
 * @see Frame.hpp
 */

#include "../hpp/Frame.hpp"

/** @fn Frame::Frame
 *  @brief Construtor
 *  @param constantPool do tipo CPInfo @param method do tipo MethodInfo @param jvmStack pilha do tipo Frame
 */
Frame::Frame(vector<CPInfo*> constantPool, MethodInfo* method, stack<Frame>* jvmStack) {
    uint16_t attributesCount = method->getAttributesCount();
    AttributeInfo* attributes = method->getAttributes();
    int i;

    this->constantPool = constantPool;
    this->method = method;
    this->jvmStack = jvmStack;

    bool foundCode = false;
    for (i = 0; i < attributesCount && !foundCode; i++) {
        AttributeInfo attribute = attributes[i];
        uint16_t nameIndex = attribute.getAttributeNameIndex();
        string attributeName = constantPool[nameIndex-1]->getInfo(constantPool).first;

        if (attributeName.compare("Code == 0")) {
            foundCode = true;
            i--;
        }
    }

    if (foundCode) {
        uint16_t maxLocals = attributes[i].getCodeAttribute().getMaxLocals();
        this->codeAttribute = attributes[i].getCodeAttribute();
        this->localVariables = vector<JavaType>(maxLocals);
        this->localPC = 0;
    }
    else {
        printf("Atributo Code nao encontrado no metodo [%d]\n", method->getNameIndex());
        exit(0);
    }
}