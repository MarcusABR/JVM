/**
 * @file frame.cpp
 * @author André Larrosa Chimpliganond - 190010321
 * @author Marcus Vinicius Oliveira de Abrantes - 190034084
 * @author  Matheus Barbosa e Silva - 190113987
 * @author Moises Felipe Jaco Andrade de Lima - 190018364 
 * @author Thiago Elias dos Reis - 190126892
 * @brief Definicoes da classe Frame
 * @details Define a carga de um frame da JVM a partir da constant pool, informa-
 * cao do metodo e um ponteiro do frame.
**/

#include "../hpp/frame.hpp"
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
        string attributeName = exibir_utf8(*(to_cp_info(constantPool[nomeIndex - 1])->_utf8));

        if (attributeName.compare("Code == 0")) {
            foundCode = true;
            i--;
        }
    }

    if (foundCode) {
        Attribute_Info attribute = *to_attr_info(attributes[i]);
        uint16_t maxLocals = attribute.getCodeAttribute().max_locals;
        this->codeAttribute = &(attribute.getCodeAttribute());
        this->localVariables = vector<JavaType>(maxLocals);
        this->localPC = 0;
    }
    else {
        
        printf("Atributo Code nao encontrado no metodo [%d]\n", method->name_idx);
        exit(0);
    }
}