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
#include "../hpp/leitor_exibidor.hpp"
#include "../hpp/utils.hpp"

Frame::Frame(cp_info_vector constantPool, method_info* method, stack<Frame>* jvmStack) {
    uint16_t attributesCount = method->attr_count;
    vector<shared_ptr<Attribute>> attributes = method->attr;
    int i;

    this->constantPool = constantPool;
    this->method = method;
    this->jvmStack = jvmStack;

    bool foundCode = false;
    for (i = 0; i < attributesCount && !foundCode; i++) {
        Attribute attribute = *attributes[i];
        uint16_t nomeIndex = attribute.attribute_nome_index;
        // string attributeName = constantPool[nomeIndex-1]->getInfo(constantPool).first;
        string attributeName = exibir_utf8(*(to_cp_info(constantPool[nomeIndex - 1])->_utf8));

        if (attributeName.compare("Code == 0")) {
            foundCode = true;
            i--;
        }
    }

    if (foundCode) {
        Attribute_Info attribute = *attributes[i];
        uint16_t maxLocals = attribute.getCodeAttribute().max_locals;
        this->codeAttribute = attribute.getCodeAttribute();
        this->localVariables = vector<JavaType>(maxLocals);
        this->localPC = 0;
    }
    else {
        printf("Atributo Code nao encontrado no metodo [%d]\n", method->);
        exit(0);
    }
}