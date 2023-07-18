#include "../cpp/leitor_exibidor.cpp"
#include "../hpp/Instruction.hpp"
#include <iostream>
#include <string.h>

/** @class Instruction::setClassLoader
 *  @brief Seta o classLoader da classe como o classLoader lido e passado por parâmetro
 *  @param classLoader do tipo ponteiro para ClassLoader
 */
void Instruction::setClassLoader(ClassLoader* classLoader) {
    Instruction::classLoader = classLoader;
}

/** @fn Instruction::Instruction
 *  @brief Construtor da classe Instruction 
 */
Instruction::Instruction() {
    //Para declarar sem argumentos
}

/** @fn Instruction::Instruction
 *  @brief Sobrecarga do método construtor
 *  @param String de mnemonicos, o contador de bytes e um ponteiro para Frame
 */
Instruction::Instruction(string mnemonic, uint32_t bytesCount, uint32_t (*func)(Frame*)) {
    this->mnemonic = mnemonic;
    this->bytesCount = bytesCount;
    this->func = func;
}

/** @class Instruction::setMnemonic
 *  @brief Seta o mnemonico recebido no parametro para o mnemonico da instancia
 *  @param String com o mnemonic
 */
void Instruction::setMnemonic(string mnemonic) {
    this->mnemonic = mnemonic;
}


/** @class Instruction::getMnemonic
 *  @brief Obtem o mnemonico da instancia
 *  @return String com o mnemonic
 */

string Instruction::getMnemonic() {
    return this->mnemonic;
}

/** @class Instruction::setBytesCount
 *  @brief Seta o bytesCount recebido no parametro para o bytesCount da instancia
 *  @param inteiro sem sinal de 4 bytes com o bytesCount
 */
void Instruction::setBytesCount(uint32_t bytesCount) {
    this->bytesCount = bytesCount;
}

/** @class Instruction::getBytesCount
 *  @brief Seta o bytesCount recebido no parametro para o bytesCount da instancia 
 *  @return inteiro sem sinal de 4 bytes com o bytesCount
 */
uint32_t Instruction::getBytesCount() {
    return this->bytesCount;
}

/** @class Instruction::resolveField
 *  @brief Resolve as entradas do vetores de Fields, Interfaces para as Classes e Superclasses
 *  @param currentClass do tipo ClassFile*, fieldName do tipo string e fieldDescriptor do tipo string
 *  @return retorna um FieldInfo*
 */

// typedef struct field_info em class_file.hpp
//FieldInfo* Instruction::resolveField(class_file* currentClass, string fieldName, string fieldDescriptor) {
field_info* Instruction::resolveField(class_file* currentClass, string fieldName, string fieldDescriptor) {
    //vector<CPInfo*> constantPool = currentClass->getConstantPool();
    cp_info_vector constantPool = currentClass->getConstantPool();
    MethodArea * methodArea = classLoader->getMethodArea();
    // FieldInfo* returnField;
    // FieldInfo* noSuchField;
    // noSuchField->nameIdex = 0;
    field_info* returnField;
    field_info* noSuchField;
    noSuchField->name_idx = 0;

    //vector<FieldInfo*> fields = currentClass->getFields();
    vector<field_info> fields = currentClass->getFields();
    for (uint16_t i = 0; i < currentClass->getFieldsCount(); i++) {
        //CPInfo * nameInfo = constantPool[fields[i]->getNameIndex()-1];
        shared_ptr<CP_Info> nameInfo = to_cp_info(constantPool[fields[i].name_idx - 1]);
        //string name = nameInfo->getInfo(constantPool).first;
        string name = nameInfo->get_conteudo(constantPool);
        //CPInfo * descriptorInfo = constantPool[fields[i]->getDescriptorIndex()-1];
        shared_ptr<CP_Info> descriptorInfo = to_cp_info(constantPool[fields[i].descriptor_idx - 1]);
        //string descriptor = descriptorInfo->getInfo(constantPool).first;
        string descriptor = descriptorInfo->get_conteudo(constantPool);

        if (name.compare(fieldName) == 0 && descriptor.compare(fieldDescriptor) == 0) {
            return &(fields[i]);
        }
    }

    //vector<InterfaceInfo*> interfaces = currentClass->getInterfaces();
    vector<u2> interfaces = currentClass->getInterfaces();
    for (uint16_t i = 0; i < currentClass->getInterfacesCount(); i++) {
        //CPInfo * classInfo = constantPool[interfaces[i]->getInterfaceIndex()-1];
        // acho que a interface ja e o proprio index
        shared_ptr<CP_Info> classInfo = to_cp_info(constantPool[interfaces[i] - 1]);
        auto interfaceIdx = classInfo->_class->name_idx;
        
        string interfaceName = exibir_utf8(*(to_cp_info(constantPool[interfaceIdx-1])->_utf8));
        class_file * interfaceClass = methodArea->getClassFile(interfaceName);

        returnField = resolveField(interfaceClass, fieldName, fieldDescriptor);
        if (returnField->name_idx != 0) {
            return returnField;
        }
    }

    //CPInfo* superClassInfo = constantPool[currentClass->getSuperClass()-1];
    auto superClassIdx = to_cp_info(constantPool[currentClass->getSuperClass() - 1])->_class->name_idx;
    string superClassName = exibir_utf8(*(to_cp_info(constantPool[superClassIdx])->_utf8));


    class_file * superClass = methodArea->getClassFile(superClassName);
    returnField = resolveField(superClass, fieldName, fieldDescriptor);
    if (returnField->name_idx != 0) {
        return returnField;
    }

    return noSuchField;
}

/** @class Instruction::nopFunction
 *  @brief Nao faz nada, apenas incrementa o pc atual
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::nopFunction(Frame* frame) {
    return ++frame->localPC;
}

/** @class Instruction::aconst_nullFunction
 *  @brief coloca uma referencia de objeto nulo na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aconst_nullFunction(Frame* frame) {
    JavaType null;
    null.tag = CAT_NULL;
    null.type_reference = JAVA_NULL;
    frame->operandStack.push(null);
    return ++frame->localPC;
}

/** @class Instruction::iconst_m1Function
 *  @brief coloca um constante -1 do tipo inteiro na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iconst_m1Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT1;
    constant.type_int = (int32_t)(-1);
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::iconst_0Function
 *  @brief coloca um constante 0 do tipo inteiro na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iconst_0Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT1;
    constant.type_int = (int32_t)0;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::iconst_1Function
 *  @brief coloca um constante 1 do tipo inteiro na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iconst_1Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT1;
    constant.type_int = (int32_t)1;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::iconst_2Function
 *  @brief coloca um constante 2 do tipo inteiro na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iconst_2Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT1;
    constant.type_int = (int32_t)2;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::iconst_3Function
 *  @brief coloca um constante 3 do tipo inteiro na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado3811
 */
uint32_t Instruction::iconst_3Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT1;
    constant.type_int = (int32_t)3;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::iconst_4Function
 *  @brief coloca um constante 4 do tipo inteiro na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iconst_4Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT1;
    constant.type_int = (int32_t)4;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::iconst_5Function
 *  @brief coloca um constante 5 do tipo inteiro na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iconst_5Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT1;
    constant.type_int = (int32_t)5;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::lconst_0Function
 *  @brief coloca um constante 0 do tipo long na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lconst_0Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT2;
    constant.type_long = (int64_t)0;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::lconst_1Function
 *  @brief coloca um constante 1 do tipo long na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lconst_1Function(Frame* frame) {
    JavaType constant;
    constant.tag = CAT2;
    constant.type_long = (int64_t)1;
    frame->operandStack.push(constant);
    return ++frame->localPC;
}

/** @class Instruction::fconst_0Function
 *  @brief coloca um constante 0.0 do tipo float na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fconst_0Function(Frame* frame) {
    JavaType value;
    float fconst = 0.0f;

    memcpy(&value.type_float, &fconst, sizeof(uint32_t));
    value.tag = CAT1;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::fconst_1Function
 *  @brief coloca um constante 1.0 do tipo float na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fconst_1Function(Frame* frame) {
    JavaType value;
    float fconst = 1.0f;

    memcpy(&value.type_float, &fconst, sizeof(uint32_t));
    value.tag = CAT1;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::fconst_2Function
 *  @brief coloca um constante 2.0 do tipo float na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fconst_2Function(Frame* frame) {
    JavaType value;
    float fconst = 2.0f;

    memcpy(&value.type_float, &fconst, sizeof(uint32_t));
    value.tag = CAT1;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::dconst_0Function
 *  @brief coloca um constante 0.0 do tipo double na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dconst_0Function(Frame* frame) {
    JavaType value;
    double dconst = 0.0;

    memcpy(&value.type_double, &dconst, sizeof(uint64_t));
    value.tag = CAT2;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::dconst_1Function
 *  @brief coloca um constante 1.0 do tipo double na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dconst_1Function(Frame* frame) {
    JavaType value;
    double dconst = 1.0;

    memcpy(&value.type_double, &dconst, sizeof(uint64_t));
    value.tag = CAT2;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::bipushFunction
 *  @brief O byte imediato tem o sinal extendido para um int na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::bipushFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte = bytecode[++frame->localPC];
    JavaType value;

    value.type_int = (int32_t)((int8_t)byte);
    value.tag = CAT1;
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::sipushFunction
 *  @brief Os bytes byte1 e byte2 sem sinal sao concatenados com extensao de sinal e adicionados na pilha de operandos como um inteiro
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::sipushFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    JavaType value;

    value.type_short = (int32_t)((((int16_t)(int8_t)byte1 << 8)) | byte2);
    value.tag = CAT1;
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::ldcFunction
 *  @brief adiciona um item do constantPool na pilha de operandos e o index do ldc deve ser um index valido no constantPool atual
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ldcFunction(Frame* frame) {
    uint8_t * bytecode = frame->getCode();
    uint8_t byte = bytecode[++frame->localPC];
    uint8_t index = byte;
    JavaType value;
    //i

    //CPInfo * cpInfo = frame->constantPool[index-1];
    CP_Info * cpInfo = (frame->constantPool)[index-1];
    //switch(cpInfo->getTag()) {

    switch(cpInfo->tag) {
    // case CPInfo::CONSTANT_Class:
    //     break;
    // case CPInfo::CONSTANT_Methodref:
    //     break;
    // case CPInfo::CONSTANT_MethodHandle:
    //     break;
    //case CPInfo::CONSTANT_String:
    case CONSTANT_String:
        //value.type_reference = (uint64_t)new string(cpInfo->getInfo(frame->constantPool).second);
        value.type_reference = (uint64_t)new string(cpInfo->get_conteudo(frame->constantPool));
        value.tag = CAT1;
        frame->operandStack.push(value);
        break;
    //case CPInfo::CONSTANT_Integer:
    case CONSTANT_Integer:
        value.type_int = cpInfo->get_conteudo().bytes;
        value.tag = CAT1;
        frame->operandStack.push(value);
        break;
    //case CPInfo::CONSTANT_Float:
    case CONSTANT_Float:
        value.type_float = cpInfo->getFloatInfo().bytes;
        value.tag = CAT1;
        frame->operandStack.push(value);
        break;
    default:
        printf("A funcao ldc encontrou um tipo indefinido: %d\n", cpInfo->getTag());
        std::exit(0);
        break;
    }


    return ++frame->localPC;
}


/** @class Instruction::ldc_wFunction
 *  @brief adiciona um item do constantPool na pilha de operandos, porem o index vem com wide
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ldc_wFunction(Frame* frame) {
    printf("Instrucao ldc_wFunction nao implementada ainda!\n");
    exit(0);
    return -1;
}

/** @class Instruction::ldc2_wFunction
 *  @brief adiciona um item do constantPool na pilha de operandos e o index do ldc deve ser um index valido do tipo long ou double no constantPool atual
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ldc2_wFunction(Frame* frame) {
    uint8_t * bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    JavaType value;

    CPInfo * cpInfo = frame->constantPool[index-1];
    switch(cpInfo->getTag()) {
    case CONSTANT_Long:
        value.type_long = ((uint64_t)cpInfo->getLongInfo().high_bytes << 32) | cpInfo->getLongInfo().low_bytes;
        value.tag = CAT2;
        frame->operandStack.push(value);
        break;
    case CONSTANT_Double:
        value.type_double = ((uint64_t)cpInfo->getDoubleInfo().high_bytes << 32) | cpInfo->getDoubleInfo().low_bytes;
        value.tag = CAT2;
        frame->operandStack.push(value);
        break;
    default:
        printf("A funcao ldc2_w encontrou um tipo indefinido: %d\n", cpInfo->getTag());
        std::exit(0);
        break;
    }
    return ++frame->localPC;
}

/** @class Instruction::iloadFunction
 *  @brief Carrega um inteiro do vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iloadFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::lloadFunction
 *  @brief Carrega um long do vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lloadFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::floadFunction
 *  @brief Carrega um float do vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::floadFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::dloadFunction
 *  @brief Carrega um double do vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dloadFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::aloadFunction
 *  @brief Carrega um array do vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aloadFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::iload_0Function
 *  @brief Carrega um inteiro do vetor de variaveis locais no index 0
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iload_0Function(Frame* frame) {
    JavaType value;
    value.type_int = frame->localVariables[0].type_int;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::iload_1Function
 *  @brief Carrega um inteiro do vetor de variaveis locais no index 1
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iload_1Function(Frame* frame) {
    JavaType value;
    value.type_int = frame->localVariables[1].type_int;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::iload_2Function
 *  @brief Carrega um inteiro do vetor de variaveis locais no index 2
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iload_2Function(Frame* frame) {
    JavaType value;
    value.type_int = frame->localVariables[2].type_int;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::iload_3Function
 *  @brief Carrega um inteiro do vetor de variaveis locais no index 3
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iload_3Function(Frame* frame) {
    JavaType value;
    value.type_int = frame->localVariables[3].type_int;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::lload_0Function
 *  @brief Carrega um long do vetor de variaveis locais no index 0
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lload_0Function(Frame* frame) {
    JavaType value;
    value.type_long = frame->localVariables[0].type_long;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::lload_1Function
 *  @brief Carrega um long do vetor de variaveis locais no index 1
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lload_1Function(Frame* frame) {
    JavaType value;
    value.type_long = frame->localVariables[1].type_long;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::lload_2Function
 *  @brief Carrega um long do vetor de variaveis locais no index 2
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lload_2Function(Frame* frame) {
    JavaType value;
    value.type_long = frame->localVariables[2].type_long;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::lload_3Function
 *  @brief Carrega um long do vetor de variaveis locais no index 3
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lload_3Function(Frame* frame) {
    JavaType value;
    value.type_long = frame->localVariables[3].type_long;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::fload_0Function
 *  @brief Carrega um float do vetor de variaveis locais no index 0
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fload_0Function(Frame* frame) {
    JavaType value;
    value.type_float = frame->localVariables[0].type_float;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::fload_1Function
 *  @brief Carrega um float do vetor de variaveis locais no index 1
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fload_1Function(Frame* frame) {
    JavaType value;
    value.type_float = frame->localVariables[1].type_float;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::fload_2Function
 *  @brief Carrega um float do vetor de variaveis locais no index 2
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fload_2Function(Frame* frame) {
    JavaType value;
    value.type_float = frame->localVariables[2].type_float;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::fload_3Function
 *  @brief Carrega um float do vetor de variaveis locais no index 3
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fload_3Function(Frame* frame) {
    JavaType value;
    value.type_float = frame->localVariables[3].type_float;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::dload_0Function
 *  @brief Carrega um double do vetor de variaveis locais no index 0
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dload_0Function(Frame* frame) {
    JavaType value;
    value.type_double = frame->localVariables[0].type_double;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::dload_1Function
 *  @brief Carrega um double do vetor de variaveis locais no index 1
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dload_1Function(Frame* frame) {
    JavaType value;
    value.type_double = frame->localVariables[1].type_double;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::dload_2Function
 *  @brief Carrega um double do vetor de variaveis locais no index 2
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dload_2Function(Frame* frame) {
    JavaType value;
    value.type_double = frame->localVariables[2].type_double;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::dload_3Function
 *  @brief Carrega um double do vetor de variaveis locais no index 3
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dload_3Function(Frame* frame) {
    JavaType value;
    value.type_double = frame->localVariables[3].type_double;
    frame->operandStack.push(value);
    return ++frame->localPC;
}

/** @class Instruction::aload_0Function
 *  @brief Carrega uma referencia (ponteiro/vetor) do vetor de variaveis locais no index 0
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aload_0Function(Frame* frame) {
    JavaType objectref;

    objectref.type_reference = frame->localVariables[0].type_reference;
    frame->operandStack.push(objectref);

    return ++frame->localPC;
}

/** @class Instruction::aload_1Function
 *  @brief Carrega uma referencia (ponteiro/vetor) do vetor de variaveis locais no index 1
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aload_1Function(Frame* frame) {
    JavaType objectref;

    objectref.type_reference = frame->localVariables[1].type_reference;
    frame->operandStack.push(objectref);

    return ++frame->localPC;
}

/** @class Instruction::aload_2Function
 *  @brief Carrega uma referencia (ponteiro/vetor) do vetor de variaveis locais no index 2
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aload_2Function(Frame* frame) {
    JavaType objectref;

    objectref.type_reference = frame->localVariables[2].type_reference;
    frame->operandStack.push(objectref);

    return ++frame->localPC;
}

/** @class Instruction::aload_3Function
 *  @brief Carrega uma referencia (ponteiro/vetor) do vetor de variaveis locais no index 3
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aload_3Function(Frame* frame) {
    JavaType objectref;

    objectref.type_reference = frame->localVariables[3].type_reference;
    frame->operandStack.push(objectref);

    return ++frame->localPC;
}

/** @class Instruction::ialoadFunction
 *  @brief Carrega uma inteiro de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ialoadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::laloadFunction
 *  @brief Carrega uma long de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::laloadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::faloadFunction
 *  @brief Carrega um float de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::faloadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::daloadFunction
 *  @brief Carrega um double de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::daloadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::aaloadFunction
 *  @brief Carrega uma referencia de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aaloadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::baloadFunction
 *  @brief Carrega um byte de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::baloadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::caloadFunction
 *  @brief Carrega um char de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::caloadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::saloadFunction
 *  @brief Carrega um short de um array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::saloadFunction(Frame* frame) {
    JavaType index;
    JavaType arrayref;

    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    JavaType value = array->at((int32_t)index.type_int);

    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::istoreFunction
 *  @brief Guarda um inteiro no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::istoreFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value.tag = CAT1;
    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    frame->localVariables[index] = value;

    return ++frame->localPC;
}

/** @class Instruction::lstoreFunction
 *  @brief Guarda um long no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lstoreFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value.tag = CAT2;
    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    frame->localVariables[index] = value;

    return ++frame->localPC;
}

/** @class Instruction::fstoreFunction
 *  @brief Guarda um float no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fstoreFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value.tag = CAT1;
    value.type_float = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    frame->localVariables[index] = value;

    return ++frame->localPC;
}

/** @class Instruction::dstoreFunction
 *  @brief Guarda um double no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dstoreFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value.tag = CAT2;
    value.type_double = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    frame->localVariables[index] = value;

    return ++frame->localPC;
}

/** @class Instruction::astoreFunction
 *  @brief Guarda uma referencia no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::astoreFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t index = bytecode[++frame->localPC];
    JavaType value;

    value.tag = CAT1;
    value.type_reference = frame->operandStack.top().type_reference;
    frame->operandStack.pop();
    frame->localVariables[index] = value;

    return ++frame->localPC;
}

/** @class Instruction::istore_0Function
 *  @brief Guarda um inteiro no indice 0 no vetor de variaveis locais 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::istore_0Function(Frame* frame) {
    frame->localVariables[0] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::istore_1Function
 *  @brief Guarda um inteiro no indice 1 no vetor de variaveis locais 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::istore_1Function(Frame* frame) {
    frame->localVariables[1] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::istore_2Function
 *  @brief Guarda um inteiro no indice 2 no vetor de variaveis locais 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::istore_2Function(Frame* frame) {
    frame->localVariables[2] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::istore_3Function
 *  @brief Guarda um inteiro no indice 3 no vetor de variaveis locais 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::istore_3Function(Frame* frame) {
    frame->localVariables[3] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::lstore_0Function
 *  @brief Guarda um long no indice 0 no vetor de variaveis locais 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lstore_0Function(Frame* frame) {
    frame->localVariables[0] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::lstore_1Function
 *  @brief Guarda um long no indice 1 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lstore_1Function(Frame* frame) {
    frame->localVariables[1] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::lstore_2Function
 *  @brief Guarda um long no indice 2 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lstore_2Function(Frame* frame) {
    frame->localVariables[2] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::lstore_3Function
 *  @brief Guarda um long no indice 3 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lstore_3Function(Frame* frame) {
    frame->localVariables[3] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::fstore_0Function
 *  @brief Guarda um float no indice 0 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fstore_0Function(Frame* frame) {
    frame->localVariables[0] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::fstore_1Function
 *  @brief Guarda um float no indice 1 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fstore_1Function(Frame* frame) {
    frame->localVariables[1] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::fstore_2Function
 *  @brief Guarda um float no indice 2 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fstore_2Function(Frame* frame) {
    frame->localVariables[2] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::fstore_3Function
 *  @brief Guarda um float no indice 3 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fstore_3Function(Frame* frame) {
    frame->localVariables[3] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::dstore_0Function
 *  @brief Guarda um double no indice 0 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dstore_0Function(Frame* frame) {
    frame->localVariables[0] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::dstore_1Function
 *  @brief Guarda um double no indice 1 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dstore_1Function(Frame* frame) {
    frame->localVariables[1] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::dstore_2Function
 *  @brief 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dstore_2Function(Frame* frame) {
    frame->localVariables[2] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::dstore_3Function
 *  @brief Guarda um double no indice 3 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dstore_3Function(Frame* frame) {
    frame->localVariables[3] = frame->operandStack.top();
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::astore_0Function
 *  @brief Guarda uma referencia no indice 0 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::astore_0Function(Frame* frame) {
    JavaType objectref;

    objectref.tag = CAT1;
    objectref.type_reference = frame->operandStack.top().type_reference;
    frame->operandStack.pop();
    frame->localVariables[0] = objectref;

    return ++frame->localPC;
}

/** @class Instruction::astore_1Function
 *  @brief Guarda uma referencia no indice 1 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::astore_1Function(Frame* frame) {
    JavaType objectref;

    objectref.tag = CAT1;
    objectref.type_reference = frame->operandStack.top().type_reference;
    frame->operandStack.pop();
    frame->localVariables[1] = objectref;

    return ++frame->localPC;
}

/** @class Instruction::astore_2Function
 *  @brief Guarda uma referencia no indice 2 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::astore_2Function(Frame* frame) {
    JavaType objectref;

    objectref.tag = CAT1;
    objectref.type_reference = frame->operandStack.top().type_reference;
    frame->operandStack.pop();
    frame->localVariables[2] = objectref;

    return ++frame->localPC;
}

/** @class Instruction::astore_3Function
 *  @brief Guarda uma referencia no indice 3 no vetor de variaveis locais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::astore_3Function(Frame* frame) {
    JavaType objectref;

    objectref.tag = CAT1;
    objectref.type_reference = frame->operandStack.top().type_reference;
    frame->operandStack.pop();
    frame->localVariables[3] = objectref;

    return ++frame->localPC;
}

/** @class Instruction::iastoreFunction
 *  @brief Guarda um inteiro em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iastoreFunction(Frame* frame) {
    JavaType value;
    JavaType index;
    JavaType arrayref;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = value;

    return ++frame->localPC;
}

/** @class Instruction::lastoreFunction
 *  @brief Guarda um long em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lastoreFunction(Frame* frame) {
    JavaType value;
    JavaType index;
    JavaType arrayref;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = value;

    return ++frame->localPC;
}

/** @class Instruction::fastoreFunction
 *  @brief Guarda um float em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fastoreFunction(Frame* frame) {
    JavaType value;
    JavaType index;
    JavaType arrayref;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = value;

    return ++frame->localPC;
}

/** @class Instruction::dastoreFunction
 *  @brief Guarda um double em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dastoreFunction(Frame* frame) {
    JavaType value;
    JavaType index;
    JavaType arrayref;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = value;

    return ++frame->localPC;
}

/** @class Instruction::aastoreFunction
 *  @brief Guarda uma refenrencia em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::aastoreFunction(Frame* frame) {
    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType index = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = value;

    return ++frame->localPC;
}

/** @class Instruction::bastoreFunction
 *  @brief Guarda um byte em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::bastoreFunction(Frame* frame) {
    JavaType value;
    JavaType byteValue;
    JavaType index;
    JavaType arrayref;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    byteValue.tag = CAT1;
    byteValue.type_byte = (int8_t)value.type_int;

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = byteValue;

    return ++frame->localPC;
}

/** @class Instruction::castoreFunction
 *  @brief Guarda um char em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::castoreFunction(Frame* frame) {
    JavaType value;
    JavaType charValue;
    JavaType index;
    JavaType arrayref;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    charValue.tag = CAT1;
    charValue.type_byte = (int8_t)value.type_int;

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = charValue;

    return ++frame->localPC;
}

/** @class Instruction::sastoreFunction
 *  @brief Guarda um short em um vetor
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::sastoreFunction(Frame* frame) {
    JavaType value;
    JavaType shortValue;
    JavaType index;
    JavaType arrayref;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    index = frame->operandStack.top();
    frame->operandStack.pop();
    arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    shortValue.tag = CAT1;
    shortValue.type_byte = (int16_t)value.type_int;

    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
    array->at((int32_t)index.type_int) = shortValue;

    return ++frame->localPC;
}

/** @class Instruction::popFunction
 *  @brief Desempilha o valor do topo da pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::popFunction(Frame* frame) {
    frame->operandStack.pop();
    return ++frame->localPC;
}

/** @class Instruction::pop2Function
 *  @brief Desempilha um ou dois operandos do topo da pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::pop2Function(Frame* frame) {
    printf("Instrucao pop2Function nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::dupFunction
 *  @brief Desempilha um elemento do topo da pilha de operandos e o guarda duas vezes na mesma
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dupFunction(Frame* frame) {
    JavaType duplicated = frame->operandStack.top();
    frame->operandStack.pop();
    frame->operandStack.push(duplicated);
    frame->operandStack.push(duplicated);

    return ++frame->localPC;
}

/** @class Instruction::dup_x1Function
 *  @brief Desempilha o topo da pilha, o duplica, o coloca abaixo do novo topo e o empilha novamente
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dup_x1Function(Frame* frame) {
    printf("Instrucao dup_x1Function nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::dup_x2Function
 *  @brief Desempilha o topo da pilha, o duplica, o coloca 2 elementos abaixo do novo topo e o empilha novamente
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dup_x2Function(Frame* frame) {
    printf("Instrucao dup_x2Function nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::dup2Function
 *  @brief Desempilha os dois elementos do topo da pilha, os duplica e os coloca novamente na pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dup2Function(Frame* frame) {
    if (frame->operandStack.top().tag == CAT1) {
        JavaType value1 = frame->operandStack.top();
        frame->operandStack.pop();
        JavaType value2 = frame->operandStack.top();
        frame->operandStack.pop();

        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
    }
    else if(frame->operandStack.top().tag == CAT2) {
        JavaType value = frame->operandStack.top();
        frame->operandStack.pop();
        frame->operandStack.push(value);
        frame->operandStack.push(value);
    }
    else {
        cout << "Erro no dup2: categoria indefinida!: " << frame->operandStack.top().tag << endl;
    }
    return ++frame->localPC;
}

/** @class Instruction::dup2_x1Function
 *  @brief Desempilha dois topos da pilha, os duplica, os coloca abaixo do novo topo e os empilha novamente
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dup2_x1Function(Frame* frame) {
    printf("Instrucao dup2_x1Function nao implementada ainda!\n");
    exit(0);
    return -1;
}

/** @class Instruction::dup2_x2Function
 *  @brief Desempilha dois topos da pilha, os duplica, os colocam 2 elementos abaixo do novo topo e os empilham novamente
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dup2_x2Function(Frame* frame) {
    printf("Instrucao dup2_x2Function nao implementada ainda!\n");
    exit(0);
    return -1;
}

/** @class Instruction::swapFunction
 *  @brief Troca de lugar os dois elementos mais ao topo da pilha de operandos
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::swapFunction(Frame* frame) {
    printf("Instrucao swapFunction nao implementada ainda!\n");
    exit(0);
    return -1;
}

/** @class Instruction::iaddFunction
 *  @brief Soma dois inteiros
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iaddFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_int = (int32_t)value1.type_int + (int32_t)value2.type_int;

    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::laddFunction
 *  @brief Soma dois longs
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::laddFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_long = (int64_t)value1.type_long + (int64_t)value2.type_long;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::faddFunction
 *  @brief Soma dois floats
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::faddFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    float fvalue1;
    float fvalue2;
    float fresult;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue1, &value1.type_int, sizeof(float));
    memcpy(&fvalue2, &value2.type_int, sizeof(float));

    fresult = fvalue1 + fvalue2;

    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::daddFunction
 *  @brief Soma dois doubles
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::daddFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    double dvalue1;
    double dvalue2;
    double dresult;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue1, &value1.type_long, sizeof(double));
    memcpy(&dvalue2, &value2.type_long, sizeof(double));

    dresult = dvalue1 + dvalue2;

    memcpy(&(result.type_double), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::isubFunction
 *  @brief Subtrai dois inteiros
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::isubFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (int32_t)((int32_t)value1.type_int - (int32_t)value2.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lsubFunction
 *  @brief Subtrai dois longs
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lsubFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_long = (int64_t)value1.type_long - (int64_t)value2.type_long;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::fsubFunction
 *  @brief Subtrai dois floats
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fsubFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    float fvalue1;
    float fvalue2;
    float fresult;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue1, &value1.type_int, sizeof(float));
    memcpy(&fvalue2, &value2.type_int, sizeof(float));

    fresult = fvalue1 - fvalue2;

    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::dsubFunction
 *  @brief Subtrai dois doubles
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dsubFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    double dvalue1;
    double dvalue2;
    double dresult;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue1, &value1.type_long, sizeof(double));
    memcpy(&dvalue2, &value2.type_long, sizeof(double));

    dresult = dvalue1 - dvalue2;

    memcpy(&(result.type_double), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::imulFunction
 *  @brief Multiplica dois inteiros
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::imulFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (int32_t)((int32_t)value1.type_int * (int32_t)value2.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lmulFunction
 *  @brief Multiplica dois longs
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lmulFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_long = (int64_t)value1.type_long * (int64_t)value2.type_long;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::fmulFunction
 *  @brief Multiplica dois floats
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fmulFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    float fvalue1;
    float fvalue2;
    float fresult;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue1, &value1.type_int, sizeof(float));
    memcpy(&fvalue2, &value2.type_int, sizeof(float));

    fresult = fvalue1 * fvalue2;

    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::dmulFunction
 *  @brief Multiplica dois doubles
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dmulFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    double dvalue1;
    double dvalue2;
    double dresult;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue1, &value1.type_long, sizeof(double));
    memcpy(&dvalue2, &value2.type_long, sizeof(double));

    dresult = dvalue1 * dvalue2;

    memcpy(&(result.type_double), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::idivFunction
 *  @brief Divide dois inteiros
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::idivFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (int32_t)((int32_t)value1.type_int / (int32_t)value2.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::ldivOpFunction
 *  @brief Divide dois longs
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ldivOpFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_long = (int64_t)value1.type_long / (int64_t)value2.type_long;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::fdivFunction
 *  @brief Divide dois floats
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fdivFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    float fvalue1;
    float fvalue2;
    float fresult;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue1, &value1.type_int, sizeof(float));
    memcpy(&fvalue2, &value2.type_int, sizeof(float));

    fresult = fvalue1 / fvalue2;

    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::ddivFunction
 *  @brief Divide dois doubles
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ddivFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    double dvalue1;
    double dvalue2;
    double dresult;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue1, &value1.type_long, sizeof(double));
    memcpy(&dvalue2, &value2.type_long, sizeof(double));

    dresult = dvalue1 / dvalue2;

    memcpy(&(result.type_double), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::iremFunction
 *  @brief Retorna o resto de dois numeors inteiros
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iremFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (int32_t)((int32_t)value1.type_int - (int32_t)((int32_t)value1.type_int / (int32_t)value2.type_int) * (int32_t)value2.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lremFunction
 *  @brief 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lremFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    result.type_long = (int64_t)((int64_t)value1.type_long - (int64_t)((int64_t)value1.type_long / (int64_t)value2.type_long) * (int64_t)value2.type_long);
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::fremFunction
 *  @brief 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fremFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    float fvalue1;
    float fvalue2;
    float fresult;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue1, &value1.type_int, sizeof(float));
    memcpy(&fvalue2, &value2.type_int, sizeof(float));

    fresult = fmod(fvalue1, fvalue2);

    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::dremFunction
 *  @brief 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dremFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    double dvalue1;
    double dvalue2;
    double dresult;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue1, &value1.type_long, sizeof(double));
    memcpy(&dvalue2, &value2.type_long, sizeof(double));

    dresult = fmod(dvalue1, dvalue2);

    memcpy(&(result.type_double), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::inegFunction
 *  @brief Inverte o sinal do topo da pilha de operando do tipo inteiro
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::inegFunction(Frame* frame) {
    JavaType value;
    JavaType result;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (int32_t)(-(int32_t)value.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lnegFunction
 *  @brief Inverte o sinal do topo da pilha de operando do tipo long
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lnegFunction(Frame* frame) {
    JavaType value;
    JavaType result;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    result.type_long = (int64_t)(-(int64_t)value.type_long);
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::fnegFunction
 *  @brief Inverte o sinal do topo da pilha de operando do tipo float
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fnegFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    float fvalue;
    float fresult;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    memcpy(&fvalue, &value.type_int, sizeof(float));

    fresult = -fvalue;

    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::dnegFunction
 *  @brief Inverte o sinal do topo da pilha de operando do tipo double
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dnegFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    double dvalue;
    double dresult;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    memcpy(&dvalue, &value.type_long, sizeof(double));

    dresult = -dvalue;

    memcpy(&(result.type_double), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::ishlFunction
 *  @brief Puxa para a esquerda o topo (desde que seja do tipo inteiro)
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ishlFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (int32_t)((int32_t)value1.type_int << ((int32_t)value2.type_int & 0x0000001F));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lshlFunction
 *  @brief Puxa para a esquerda o topo (desde que seja do tipo long)
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lshlFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    result.type_long = (int64_t)((int64_t)value1.type_long << ((int32_t)value2.type_int & 0x0000003F));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::ishrFunction
 *  @brief Puxa para a direita o topo (desde que seja do tipo inteiro)
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ishrFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (int32_t)((int32_t)value1.type_int >> ((int32_t)value2.type_int & 0x0000001F));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lshrFunction
 *  @brief Puxa para a direita o topo (desde que seja do tipo long)
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lshrFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    result.type_long = (int64_t)((int64_t)value1.type_long >> ((int32_t)value2.type_int & 0x0000003F));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::iushrFunction
 *  @brief Puxa para a direita o topo (desde que seja do tipo inteiro sem sinal)
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iushrFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    result.type_int = (uint32_t)((uint32_t)value1.type_int >> ((int32_t)value2.type_int & 0x0000001F));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lushrFunction
 *  @brief Puxa para a direita o topo (desde que seja do tipo long sem sinal)
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lushrFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    result.type_long = (uint64_t)((uint64_t)value1.type_long >> ((int32_t)value2.type_int & 0x0000003F));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::iandFunction
 *  @brief Executa uma operacao logica 'e' nos dois elementos inteiros do topo da pilha de operandos e empilha o resultado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iandFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_int = (int32_t)value1.type_int & (int32_t)value2.type_int;
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::landFunction
 *  @brief Executa uma operacao logica 'e' nos dois elementos do tipo long do topo da pilha de operandos e empilha o resultado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::landFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_long = (int64_t)value1.type_long & (int64_t)value2.type_long;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::iorFunction
 *  @brief Executa uma operacao logica 'ou' nos dois elementos inteiros do topo da pilha de operandos e empilha o resultado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iorFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_int = (int32_t)value1.type_int | (int32_t)value2.type_int;
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lorFunction
 *  @brief Executa uma operacao logica 'ou' nos dois elementos do tipo long do topo da pilha de operandos e empilha o resultado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lorFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_long = (int64_t)value1.type_long | (int64_t)value2.type_long;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::ixorFunction
 *  @brief Executa uma operacao logica 'ou exclusivo' nos dois elementos inteiros do topo da pilha de operandos e empilha o resultado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ixorFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_int = (int32_t)value1.type_int ^ (int32_t)value2.type_int;
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::lxorFunction
 *  @brief Executa uma operacao logica 'ou exclusivos' nos dois elementos long do topo da pilha de operandos e empilha o resultado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lxorFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_long = (int64_t)value1.type_long ^ (int64_t)value2.type_long;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::iincFunction
 *  @brief Incrementa o inteiro no topo da pilha
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::iincFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];

    uint16_t index = byte1;
    int32_t constValue = (int32_t)((int8_t)byte2);
    frame->localVariables[index].type_int = (int32_t)frame->localVariables[index].type_int + constValue;

    return ++frame->localPC;
}

/** @class Instruction::i2lFunction
 *  @brief Converte um inteiro para um tipo long
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::i2lFunction(Frame* frame) {
    JavaType value;
    JavaType result;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_long = (int64_t)((int32_t)value.type_int);
    result.tag = CAT2;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::i2fFunction
 *  @brief Converte um inteiro para um tipo float
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::i2fFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    float fresult;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    fresult = (float)((int32_t)value.type_int);
    memcpy(&(result.type_float), &fresult, sizeof(float));

    result.tag = CAT1;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::i2dFunction
 *  @brief Converte um inteiro para um tipo double
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::i2dFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    double dresult;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    dresult = (double)((int32_t)value.type_int);
    memcpy(&(result.type_float), &dresult, sizeof(double));

    result.tag = CAT2;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::l2iFunction
 *  @brief Converte um long para um tipo inteiro
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::l2iFunction(Frame* frame) {
    JavaType value;
    JavaType result;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    result.type_int = int32_t((int64_t)value.type_long);
    result.tag = CAT1;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::l2fFunction
 *  @brief Converte um long para um tipo float
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::l2fFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    float fresult;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    fresult = (float)((int64_t)value.type_long);
    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::l2dFunction
 *  @brief Converte um long para um tipo double
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::l2dFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    double dresult;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    dresult = (double)((int64_t)value.type_long);
    memcpy(&(result.type_float), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::f2iFunction
 *  @brief Converte um float para um tipo inteiro
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::f2iFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    float fvalue;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue, &(value.type_int), sizeof(float));
    result.type_int = (int32_t)fvalue;
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::f2lFunction
 *  @brief Converte um float para um tipo long
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::f2lFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    float fvalue;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue, &(value.type_int), sizeof(float));
    result.type_long = (int64_t)fvalue;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::f2dFunction
 *  @brief Converte um float para um tipo double
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::f2dFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    float fvalue;
    double dresult;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue, &(value.type_int), sizeof(float));
    dresult = (double)fvalue;
    memcpy(&(result.type_double), &dresult, sizeof(double));
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::d2iFunction
 *  @brief Converte um double para um tipo inteiro
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::d2iFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    double dvalue;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue, &(value.type_long), sizeof(double));
    result.type_int = (int32_t)dvalue;
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::d2lFunction
 *  @brief Converte um double para um tipo long
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::d2lFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    double dvalue;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue, &(value.type_long), sizeof(double));
    result.type_long = (int64_t)dvalue;
    result.tag = CAT2;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::d2fFunction
 *  @brief Converte um double para um tipo float
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::d2fFunction(Frame* frame) {
    JavaType value;
    JavaType result;
    double dvalue;
    float fresult;

    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue, &(value.type_long), sizeof(double));
    fresult = (float)dvalue;
    memcpy(&(result.type_float), &fresult, sizeof(float));
    result.tag = CAT1;
    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::i2bFunction
 *  @brief Converte um inteiro para um tipo byte
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::i2bFunction(Frame* frame) {
    JavaType value;
    JavaType result;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_byte = (int8_t)((int32_t)value.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::i2cFunction
 *  @brief Converte um inteiro para um char
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::i2cFunction(Frame* frame) {
    JavaType value;
    JavaType result;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_char = (uint8_t)((int32_t)value.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::i2sFunction
 *  @brief Converte um inteiro para um tipo short
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::i2sFunction(Frame* frame) {
    JavaType value;
    JavaType result;

    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    result.type_short = (int16_t)((int32_t)value.type_int);
    result.tag = CAT1;
    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::lcmpFunction
 *  @brief Compara dois elementos do topo da pilha de operandos do tipo long
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lcmpFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    if (value1.type_long > value2.type_long) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
    }
    else if (value1.type_long == value2.type_long) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
    }
    else if (value1.type_long < value2.type_long) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
    }

    frame->operandStack.push(result);

    return ++frame->localPC;
}

/** @class Instruction::fcmplFunction
 *  @brief Compara dois elementos do topo da pilha de operandos do tipo float e empilha -1 no topo caso algum seja NaN
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fcmplFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    float fvalue1;
    float fvalue2;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue1, &value1.type_int, sizeof(float));
    memcpy(&fvalue2, &value2.type_int, sizeof(float));

    if (fvalue1 > fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
    }
    else if (fvalue1 == fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
    }
    else if (fvalue1 < fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
    }
    else {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
    }

    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::fcmpgFunction
 *  @brief Compara dois elementos do topo da pilha de operandos do tipo float e empilha 1 caso algum seja NaN
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::fcmpgFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    float fvalue1;
    float fvalue2;

    value2.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    value1.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    memcpy(&fvalue1, &value1.type_int, sizeof(float));
    memcpy(&fvalue2, &value2.type_int, sizeof(float));

    if (fvalue1 > fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
    }
    else if (fvalue1 == fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
    }
    else if (fvalue1 < fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
    }
    else {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
    }

    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::dcmplFunction
 *  @brief Compara dois elementos do topo da pilha de operandos do tipo double e empilha -1 no topo caso algum seja NaN
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dcmplFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    double dvalue1;
    double dvalue2;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue1, &value1.type_long, sizeof(double));
    memcpy(&dvalue2, &value2.type_long, sizeof(double));

    if (dvalue1 > dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
    }
    else if (dvalue1 == dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
    }
    else if (dvalue1 < dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
    }
    else {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
    }

    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::dcmpgFunction
 *  @brief Compara dois elementos do topo da pilha de operandos do tipo double e empilha 1 caso algum seja NaN
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dcmpgFunction(Frame* frame) {
    JavaType value1;
    JavaType value2;
    JavaType result;
    double dvalue1;
    double dvalue2;

    value2.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    value1.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    memcpy(&dvalue1, &value1.type_long, sizeof(double));
    memcpy(&dvalue2, &value2.type_long, sizeof(double));

    if (dvalue1 > dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
    }
    else if (dvalue1 == dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
    }
    else if (dvalue1 < dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
    }
    else {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
    }

    frame->operandStack.push(result);
    return ++frame->localPC;
}

/** @class Instruction::ifeqFunction
 *  @brief Compara se dois inteiros sao iguais e se forem pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifeqFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value.type_int == 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::ifneFunction
 *  @brief Compara se dois inteiros nao sao iguais e se forem pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifneFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value.type_int != 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::ifltFunction
 *  @brief Compara dois inteiros onde o primeiro deve ser menor do que que o segundo, se verdadeiro, pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifltFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value.type_int < 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::ifgeFunction
 *  @brief Compara dois inteiros onde o primeiro deve ser maior ou igual que o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifgeFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value.type_int >= 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::ifgtFunction
 *  @brief Compara dois inteiros onde o primeiro deve ser maior que o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifgtFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value.type_int > 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::ifleFunction
 *  @brief Compara dois inteiros onde o primeiro deve ser menor que o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifleFunction(Frame* frame) {
uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value.type_int <= 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::if_icmpeqFunction
 *  @brief Compara dois inteiros onde o primeiro deve ser igual o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_icmpeqFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value2 = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType value1 = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value1.type_int == (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::if_icmpneFunction
 *  @brief Compara dois inteiros onde o primeiro nao deve ser igual o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_icmpneFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value2 = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType value1 = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value1.type_int != (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::if_icmpltFunction
 *  @brief Compara dois inteiros onde o primeiro valor deve ser menor que o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_icmpltFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value2 = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType value1 = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value1.type_int < (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::if_icmpgeFunction
 *  @brief Compara dois inteiros onde o primeiro valor deve ser menor ou igual que o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_icmpgeFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value2 = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType value1 = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value1.type_int >= (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::if_icmpgtFunction
 *  @brief Compara dois inteiros onde o primeiro valor deve ser maior que o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_icmpgtFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value2 = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType value1 = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value1.type_int > (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::if_icmpleFunction
 *  @brief Compara dois inteiros onde o primeiro valor deve ser maior ou igual que o segundo, se verdadeiro,pula para o endereco calculado entre os dois bytes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_icmpleFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value2 = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType value1 = frame->operandStack.top();
    frame->operandStack.pop();

    if ((int32_t)value1.type_int <= (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::if_acmpeqFunction
 *  @brief Compara duas referencias, onde a primeira deve ser igual a segunda, se verdadeiro pula para o endereco calculado entre os dois bytes.
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_acmpeqFunction(Frame* frame) {
    printf("Instrucao if_acmpeqFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::if_acmpneFunction
 *  @brief Compara duas referencias, onde a primeira deve ser não igual a segunda, se verdadeiro pula para o endereco calculado entre os dois bytes.
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::if_acmpneFunction(Frame* frame) {
    printf("Instrucao if_acmpneFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::gotoOpFunction
 *  @brief Concatena os bits e pula para o endereco encontrado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::gotoOpFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    frame->localPC = baseAddress + branchOffset;
    return frame->localPC;
}

/** @class Instruction::jsrFunction
 *  @brief Pula para uma subrotina 
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::jsrFunction(Frame* frame) {
    printf("Instrucao jsrFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::retFunction
 *  @brief Retorna o valor de uma subrotina
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::retFunction(Frame* frame) {
    printf("Instrucao retFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::tableswitchFunction
 *  @brief Executa High - Low e define o range dos cases do switch, se nenhum caso passar o pulo é feito para o default
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::tableswitchFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    JavaType key = frame->operandStack.top();
    frame->operandStack.pop();

    frame->localPC++;
    while ((frame->localPC)%4 != 0) {
        frame->localPC++;
    }

    uint8_t defaultByte1 = bytecode[frame->localPC++];
    uint8_t defaultByte2 = bytecode[frame->localPC++];
    uint8_t defaultByte3 = bytecode[frame->localPC++];
    uint8_t defaultByte4 = bytecode[frame->localPC++];
    int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) | (defaultByte3 << 8) | defaultByte4;

    uint8_t lowByte1 = bytecode[frame->localPC++];
    uint8_t lowByte2 = bytecode[frame->localPC++];
    uint8_t lowByte3 = bytecode[frame->localPC++];
    uint8_t lowByte4 = bytecode[frame->localPC++];
    int32_t low = (lowByte1 << 24) | (lowByte2 << 16) | (lowByte3 << 8) | lowByte4;

    uint8_t highByte1 = bytecode[frame->localPC++];
    uint8_t highByte2 = bytecode[frame->localPC++];
    uint8_t highByte3 = bytecode[frame->localPC++];
    uint8_t highByte4 = bytecode[frame->localPC++];
    int32_t high = (highByte1 << 24) | (highByte2 << 16) | (highByte3 << 8) | highByte4;

    for (int match = low; match <= high; match++) {
        uint8_t offsetByte1 = bytecode[frame->localPC++];
        uint8_t offsetByte2 = bytecode[frame->localPC++];
        uint8_t offsetByte3 = bytecode[frame->localPC++];
        uint8_t offsetByte4 = bytecode[frame->localPC++];
        int32_t offset = (offsetByte1 << 24) | (offsetByte2 << 16) | (offsetByte3 << 8) | offsetByte4;

        if ((int32_t)key.type_int == match) {
            frame->localPC = baseAddress + offset;
            return frame->localPC;
        }
    }
    frame->localPC = baseAddress + defaultValue;
    return frame->localPC;
}

/** @class Instruction::lookupswitchFunction
 *  @brief Calcula atraves do npairs os indexs de cada case e executa os pulos partindo de um offset somado ao endereco base
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lookupswitchFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    JavaType key = frame->operandStack.top();
    frame->operandStack.pop();

    frame->localPC++;
    while ((frame->localPC)%4 != 0) {
        frame->localPC++;
    }

    uint8_t defaultByte1 = bytecode[frame->localPC++];
    uint8_t defaultByte2 = bytecode[frame->localPC++];
    uint8_t defaultByte3 = bytecode[frame->localPC++];
    uint8_t defaultByte4 = bytecode[frame->localPC++];
    int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) | (defaultByte3 << 8) | defaultByte4;

    uint8_t npairs1 = bytecode[frame->localPC++];
    uint8_t npairs2 = bytecode[frame->localPC++];
    uint8_t npairs3 = bytecode[frame->localPC++];
    uint8_t npairs4 = bytecode[frame->localPC++];
    int32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;

    for (int i = 0; i < npairs; i++) {
        uint8_t matchByte1 = bytecode[frame->localPC++];
        uint8_t matchByte2 = bytecode[frame->localPC++];
        uint8_t matchByte3 = bytecode[frame->localPC++];
        uint8_t matchByte4 = bytecode[frame->localPC++];
        int32_t match = (matchByte1 << 24) | (matchByte2 << 16) | (matchByte3 << 8) | matchByte4;

        uint8_t offsetByte1 = bytecode[frame->localPC++];
        uint8_t offsetByte2 = bytecode[frame->localPC++];
        uint8_t offsetByte3 = bytecode[frame->localPC++];
        uint8_t offsetByte4 = bytecode[frame->localPC++];
        int32_t offset = (offsetByte1 << 24) | (offsetByte2 << 16) | (offsetByte3 << 8) | offsetByte4;

        if ((int32_t)key.type_int == match) {
            frame->localPC = baseAddress + offset;
            return frame->localPC;
        }
    }
    frame->localPC = baseAddress + defaultValue;
    return frame->localPC;
}

/** @class Instruction::ireturnFunction
 *  @brief Retorna um inteiro do metodo
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ireturnFunction(Frame* frame) {
    JavaType value;

    value.tag = CAT1;
    value.type_int = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* invoker = &(frame->jvmStack->top());
    invoker->operandStack.push(value);
    return invoker->localPC;
}

/** @class Instruction::lreturnFunction
 *  @brief Retorna um long do metodo
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::lreturnFunction(Frame* frame) {
    JavaType value;

    value.tag = CAT2;
    value.type_long = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* invoker = &(frame->jvmStack->top());
    invoker->operandStack.push(value);
    return invoker->localPC;
}

/** @class Instruction::freturnFunction
 *  @brief Retorna um float do metodo
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::freturnFunction(Frame* frame) {
    JavaType value;

    value.tag = CAT1;
    value.type_float = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* invoker = &(frame->jvmStack->top());
    invoker->operandStack.push(value);
    return invoker->localPC;
}

/** @class Instruction::dreturnFunction
 *  @brief Retorna um double do metodo
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::dreturnFunction(Frame* frame) {
   JavaType value;

    value.tag = CAT2;
    value.type_double = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* invoker = &(frame->jvmStack->top());
    invoker->operandStack.push(value);
    return invoker->localPC;
}

/** @class Instruction::areturnFunction
 *  @brief Retorna uma referencia do metodo
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::areturnFunction(Frame* frame) {
    JavaType value;

    value.tag = CAT1;
    value.type_reference = frame->operandStack.top().type_reference;
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* invoker = &(frame->jvmStack->top());
    invoker->operandStack.push(value);
    return invoker->localPC;
}

/** @class Instruction::returnOpFunction
 *  @brief Sinaliza o final do metodo com um retorno void
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::returnOpFunction(Frame* frame) {
    if (!frame->operandStack.empty()) {
        printf("A pilha de operandos nao esta vazia! Pode haver erros!\n");
    }
    return frame->localPC;
}

/** @class Instruction::getstaticFunction
 *  @brief Recupera o campo estatico
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::getstaticFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    MethodArea * methodArea = classLoader->getMethodArea();
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    string nameAndType = frame->constantPool[index-1]->getInfo(frame->constantPool).second;
    int j = 0;

    while (j < nameAndType.size() && nameAndType[j+1] != ':') {
        j++;
    }
    string fieldName = nameAndType.substr(0,j);
    string fieldDescriptor = nameAndType.substr(j+3,nameAndType.size());

    if (className.compare("java/lang/System") == 0) {
        return ++frame->localPC;
    }
    else {
        if (!methodArea->isClassInitialized(className)) {
            methodArea->setClassAsInitialized(className);

            class_file aux = classLoader->loadClassFile(className + ".class");
            classLoader->loadSuperClasses(&aux);
            class_file * classFile = classLoader->getClassFromMethodArea(className);
            //vector<CPInfo*> constantPool = classFile->getConstantPool();
            cp_info_vector constantPool = classFile->getConstantPool();
            //vector<MethodInfo*> methods = classFile->getMethods();
            vector<method_info> methods = classFile->getMethods();
            //MethodInfo* method;
            method_info* method;

            bool foundClinit = false;
            for (int i = 0; i < classFile->getMethodsCount() && !foundClinit; i++) {
                //method = methods[i];
                method = &(methods[i]);
                //uint16_t nameIndex = method->getNameIndex();
                uint16_t nameIndex = method->name_idx;
                //uint16_t descriptorIndex = method->getDescriptorIndex();
                uint16_t descriptorIndex = method->descriptor_idx;
                string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
                string classDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
                if (name.compare("<clinit>") == 0 && classDescriptor.compare("()V") == 0) {
                    foundClinit = true;
                }
            }

            if (foundClinit) {
                // Frame recebe (class_file*, stack<Frame>*)
                Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
                frame->jvmStack->push(clinitMethodFrame);
                frame->localPC-=2;
                return clinitMethodFrame.localPC;
            }
        }

        class_file * classFile = methodArea->getClassFile(className);
        //vector<CPInfo*> constantPool = classFile->getConstantPool();
        cp_info_vector constantPool = classFile->getConstantPool();
        //vector<FieldInfo*> fields = classFile->getFields();
        vector<field_info> fields = classFile->getFields();
        //FieldInfo* field;
        field_info* field;
        bool foundField = false;

        for (int i = 0; i < classFile->getFieldsCount() && !foundField; i++) {
            field = &(fields[i]);
            //uint16_t nameIndex = field->getNameIndex();
            uint16_t nameIndex = field->name_idx;
            //uint16_t descriptorIndex = field->getDescriptorIndex();
            uint16_t descriptorIndex = field->descriptor_idx;
            string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
            string descriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
            if (name.compare(fieldName) == 0 && descriptor.compare(fieldDescriptor) == 0) {
                foundField = true;
            }
        }

        if (!foundField) {
            printf("getstatic: o field especificado nao pode ser resolvido! Deve estar em uma superclasse ou superinterface! Falta implementar!\n");
            exit(0);
        }

        if (fieldDescriptor.compare("C") == 0) {
            frame->operandStack.push(field->staticValue);
        }
        else if (fieldDescriptor.compare("I") == 0) {
            frame->operandStack.push(field->staticValue);
        }
        else if (fieldDescriptor.compare("F") == 0) {
            frame->operandStack.push(field->staticValue);
        }
        else if (fieldDescriptor.compare("D") == 0) {
            frame->operandStack.push(field->staticValue);
        }
        else if (fieldDescriptor.compare("J") == 0) {
            frame->operandStack.push(field->staticValue);
        }
        else if (fieldDescriptor.compare("Z") == 0) {
            frame->operandStack.push(field->staticValue);
        }
        else if (fieldDescriptor[0] == '[') {
            frame->operandStack.push(field->staticValue);
        }
        else {
            printf("getstatic: tipo do descritor nao reconhecido: %s\n", fieldDescriptor.c_str());
            std::exit(0);
        }
    }

    return ++frame->localPC;
}

/** @class Instruction::putstaticFunction
 *  @brief Seta o campo estatico
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::putstaticFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    MethodArea * methodArea = classLoader->getMethodArea();

    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    string nameAndType = frame->constantPool[index-1]->getInfo(frame->constantPool).second;
    int j = 0;

    while (j < nameAndType.size() && nameAndType[j+1] != ':') {
        j++;
    }
    string fieldName = nameAndType.substr(0,j);
    string fieldDescriptor = nameAndType.substr(j+3,nameAndType.size());

    if (!methodArea->isClassInitialized(className)) {
        methodArea->setClassAsInitialized(className);

        class_file aux = classLoader->loadClassFile(className + ".class");
        classLoader->loadSuperClasses(&aux);
        class_file * classFile = classLoader->getClassFromMethodArea(className);
        //vector<CPInfo*> constantPool = classFile->getConstantPool();
        cp_info_vector constantPool = classFile->getConstantPool();
        //vector<MethodInfo*> methods = classFile->getMethods();
        vector<method_info> methods = classFile->getMethods();
        MethodInfo* method;

        bool foundClinit = false;
        for (int i = 0; i < classFile->getMethodsCount() && !foundClinit; i++) {
            //method = methods[i];
            method = &(methods[i]);
            uint16_t nameIndex = method->getNameIndex();
            uint16_t descriptorIndex = method->getDescriptorIndex();
            string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
            string classDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
            if (name.compare("<clinit>") == 0 && classDescriptor.compare("()V") == 0) {
                foundClinit = true;
            }
        }

        if (foundClinit) {
            // Frame recebe class_file, jvm_stack
            Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
            frame->jvmStack->push(clinitMethodFrame);
            frame->localPC-=2;
            return clinitMethodFrame.localPC;
        }
    }

    class_file * classFile = methodArea->getClassFile(className);
    //vector<CPInfo*> constantPool = classFile->getConstantPool();
    cp_info_vector constantPool = classFile->getConstantPool();
    //vector<FieldInfo*> fields = classFile->getFields();
    vector<field_info> fields = classFile->getFields();
    //FieldInfo* field;
    field_info* field;
    bool foundField = false;

    for (int i = 0; i < classFile->getFieldsCount() && !foundField; i++) {
        //field = fields[i];
        field = &(fields[i]);
        //uint16_t nameIndex = field->getNameIndex();
        uint16_t nameIndex = field->name_idx;
        //uint16_t descriptorIndex = field->getDescriptorIndex();
        uint16_t descriptorIndex = field->descriptor_idx;
        string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
        string descriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
        if (name.compare(fieldName) == 0 && descriptor.compare(fieldDescriptor) == 0) {
            foundField = true;
        }
    }

    if (!foundField) {
        printf("putstatic: o field especificado nao pode ser resolvido! Deve estar em uma superclasse ou superinterface! Falta implementar!\n");
        exit(0);
    }

    if (fieldDescriptor.compare("C") == 0) {
        field->staticValue.tag = CAT1;
        field->staticValue.type_char = frame->operandStack.top().type_char;
        frame->operandStack.pop();
    }
    else if (fieldDescriptor.compare("I") == 0) {
        field->staticValue.tag = CAT1;
        field->staticValue.type_int = frame->operandStack.top().type_int;
        frame->operandStack.pop();
    }
    else if (fieldDescriptor.compare("F") == 0) {
        field->staticValue.tag = CAT1;
        field->staticValue.type_float = frame->operandStack.top().type_float;
        frame->operandStack.pop();
    }
    else if (fieldDescriptor.compare("D") == 0) {
        field->staticValue.tag = CAT2;
        field->staticValue.type_double = frame->operandStack.top().type_double;
        frame->operandStack.pop();
    }
    else if (fieldDescriptor.compare("J") == 0) {
        field->staticValue.tag = CAT2;
        field->staticValue.type_long = frame->operandStack.top().type_long;
        frame->operandStack.pop();
    }
    else if (fieldDescriptor.compare("Z") == 0) {
        field->staticValue.tag = CAT1;
        field->staticValue.type_boolean = frame->operandStack.top().type_boolean;
        frame->operandStack.pop();
    }
    else if (fieldDescriptor[0] == '[') {
        field->staticValue.tag = CAT1;
        field->staticValue.type_reference = frame->operandStack.top().type_reference;
        frame->operandStack.pop();
    }
    else {
        printf("putstatic: tipo do descritor nao reconhecido: %s\n", fieldDescriptor.c_str());
        exit(0);
    }

    return ++frame->localPC;
}

/** @class Instruction::getfieldFunction
 *  @brief Recupera o campo estatico da classe
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::getfieldFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    MethodArea * methodArea = classLoader->getMethodArea();

    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    string nameAndType = frame->constantPool[index-1]->getInfo(frame->constantPool).second;
    int j = 0;

    while (j < nameAndType.size() && nameAndType[j+1] != ':') {
        j++;
    }
    string fieldName = nameAndType.substr(0,j);
    string fieldDescriptor = nameAndType.substr(j+3,nameAndType.size());

    JavaType objectref = frame->operandStack.top();
    frame->operandStack.pop();

    map<string, JavaType>* object = (map<string, JavaType>*)objectref.type_reference;
    JavaType value = object->at(fieldName);
    frame->operandStack.push(value);

    return ++frame->localPC;
}

/** @class Instruction::putfieldFunction
 *  @brief Seta o campo no objeto
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::putfieldFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    MethodArea * methodArea = classLoader->getMethodArea();

    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    string nameAndType = frame->constantPool[index-1]->getInfo(frame->constantPool).second;
    int j = 0;

    while (j < nameAndType.size() && nameAndType[j+1] != ':') {
        j++;
    }
    string fieldName = nameAndType.substr(0,j);
    string fieldDescriptor = nameAndType.substr(j+3,nameAndType.size());

    //Falta resolver o field!

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();
    JavaType objectref = frame->operandStack.top();
    frame->operandStack.pop();

    map<string, JavaType>* object = (map<string, JavaType>*)objectref.type_reference;
    object->at(fieldName) = value;

    return ++frame->localPC;
}

/** @class Instruction::invokevirtualFunction
 *  @brief Invoca um metodo baseado na classe objeto
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::invokevirtualFunction(Frame* frame) {
    // Frame utiliza class_file para recuperar a method_area
    MethodArea * methodArea = classLoader->getMethodArea();
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    string nameAndType = frame->constantPool[index-1]->getInfo(frame->constantPool).second;
    int j = 0;

    while (j < nameAndType.size() && nameAndType[j+1] != ':') {
        j++;
    }
    string methodName = nameAndType.substr(0,j);
    string descriptor = nameAndType.substr(j+3,nameAndType.size());

    // Para debug
    // cout << className << " " << methodName << " " << descriptor << endl;

    if (className.compare("java/io/PrintStream") == 0) {
        if (methodName.compare("println") == 0) {
            if (descriptor.compare("(Ljava/lang/String;)V") == 0) {
                string* stringReference = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();
                cout << *stringReference << endl;
            }
            else if (descriptor.compare("(C)V") == 0) {
                uint8_t character = frame->operandStack.top().type_char;
                frame->operandStack.pop();
                cout << character << endl;
            }
            else if (descriptor.compare("(I)V") == 0) {
                int32_t integer = (int32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                cout << integer << endl;
            }
            else if (descriptor.compare("(F)V") == 0) {
                float floatNumber;
                memcpy(&floatNumber, &(frame->operandStack.top().type_float), sizeof(float));
                frame->operandStack.pop();
                cout << floatNumber << endl;
            }
            else if (descriptor.compare("(D)V") == 0) {
                double doubleNumber;
                memcpy(&doubleNumber, &(frame->operandStack.top().type_double), sizeof(double));
                frame->operandStack.pop();
                cout << doubleNumber << endl;
            }
            else if (descriptor.compare("(J)V") == 0) {
                int64_t longNumber = (int64_t)frame->operandStack.top().type_long;
                frame->operandStack.pop();
                cout << longNumber << endl;
            }
            else if (descriptor.compare("(Z)V") == 0) {
                uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();

                if (integer == 1) {
                    cout << "true" << endl;
                }
                else if (integer == 0) {
                    cout << "false" << endl;
                }
                else {
                    cout << "Erro no tipo booleano!\\n" << endl;
                    std::exit(0);
                }
            }
            else if (descriptor.compare("()V") == 0) {
                cout << endl;
            }
            else {
                printf("invokevirtualFunction: tipo do descritor nao reconhecido: %s\n", descriptor.c_str());
                std::exit(0);
            }
        }
        else if (methodName.compare("print") == 0) {
            if (descriptor.compare("(Ljava/lang/String;)V") == 0) {
                string* stringReference = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();
                cout << *stringReference;
            }
            else if (descriptor.compare("(I)V") == 0) {
                int32_t integer = (int32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                cout << integer;
            }
            else if (descriptor.compare("(F)V") == 0) {
                float floatNumber;
                memcpy(&floatNumber, &(frame->operandStack.top().type_float), sizeof(float));
                frame->operandStack.pop();
                cout << floatNumber;
            }
            else if (descriptor.compare("(D)V") == 0) {
                double doubleNumber;
                memcpy(&doubleNumber, &(frame->operandStack.top().type_double), sizeof(double));
                frame->operandStack.pop();
                cout << doubleNumber;
            }
            else if (descriptor.compare("(J)V") == 0) {
                int64_t longNumber = (int64_t)frame->operandStack.top().type_long;
                frame->operandStack.pop();
                cout << longNumber;
            }
            else if (descriptor.compare("(Z)V") == 0) {
                uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();

                if (integer == 1) {
                    cout << "true";
                }
                else if (integer == 0) {
                    cout << "false";
                }
                else {
                    cout << "Erro no tipo booleano!";
                    std::exit(0);
                }
            }
            else if (descriptor.compare("()V") == 0) {
                //Nao faz nada
            }
            else {
                printf("invokevirtualFunction: tipo do descritor nao reconhecido: %s\n", descriptor.c_str());
                std::exit(0);
            }
        }
        else {
            printf("invokevirtualFunction: falta implementar\n");
            std::exit(0);
        }
    }
    else if (className.compare("java/lang/StringBuilder") == 0) {
        if (methodName.compare("append") == 0) {
            if (descriptor.compare("(Ljava/lang/String;)Ljava/lang/StringBuilder;") == 0) {
                string* str1 = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();
                string* str2 = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                JavaType objectref;
                objectref.type_reference = (uint64_t)new string(*str2 + *str1);
                objectref.tag = CAT1;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(I)Ljava/lang/StringBuilder;") == 0) {
                int32_t integer = (int32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                JavaType objectref;
                objectref.type_reference = (uint64_t)new string(*str + to_string(integer));
                objectref.tag = CAT1;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(J)Ljava/lang/StringBuilder;") == 0) {
                int64_t longNumber = (int64_t)(frame->operandStack.top().type_long);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                JavaType objectref;
                objectref.type_reference = (uint64_t)new string(*str + to_string(longNumber));
                objectref.tag = CAT1;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(F)Ljava/lang/StringBuilder;") == 0) {
                uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                float floatNumber;
                memcpy(&floatNumber, &integer, sizeof(float));

                JavaType objectref;
                objectref.type_reference = (uint64_t)new string(*str + to_string(floatNumber));
                objectref.tag = CAT1;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(D)Ljava/lang/StringBuilder;") == 0) {
                uint64_t longNumber = (uint64_t)(frame->operandStack.top().type_double);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                double doubleNumber;
                memcpy(&doubleNumber, &longNumber, sizeof(double));

                JavaType objectref;
                objectref.type_reference = (uint64_t)new string(*str + to_string(doubleNumber));
                objectref.tag = CAT1;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(Z)Ljava/lang/StringBuilder;") == 0) {
                uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                JavaType objectref;
                if (integer == 1) {
                    objectref.type_reference = (uint64_t)new string(*str + "true");
                }
                else if (integer == 0) {
                    objectref.type_reference = (uint64_t)new string(*str + "false");
                }
                else {
                    cout << "Erro no tipo booleano durante a concatenacao!";
                    std::exit(0);
                }
                frame->operandStack.push(objectref);
                objectref.tag = CAT1;
            }
            else {
                printf("invokevirtual: StringBuilder: descritor nao reconhecido: %s\n", descriptor.c_str());
                std::exit(0);
            }
        }
        else if (methodName.compare("toString") == 0) {
            //Fingindo que estou convertendo em string
        }
        else {
            printf("invokevirtualFunction: Metodo do StringBuilder nao reconhecido: %s\n", methodName.c_str());
            std::exit(0);
        }
    }
    else {
        stack<JavaType> auxstack;
        for (int i = 1; descriptor[i] != ')'; i++) {
            if (descriptor[i] == 'I' || descriptor[i] == 'F') {
            }
            else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
            }
            else if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
            else if (descriptor[i] == '[') {
                while (descriptor[i] == '[') {
                    i++;
                }
                if (descriptor[i] == 'L') {
                    while (descriptor[i] != ';') {
                        i++;
                    }
                }
            }
            else {
                cout << "Tipo de descritor nao reconhecido na contagem: " << descriptor[i] << endl;
                std::exit(0);
            }
            auxstack.push(frame->operandStack.top());
            frame->operandStack.pop();
        }

        bool foundMethod = false;
        //vector<CPInfo*> constantPool;
        cp_info_vector constantPool;
        MethodInfo* method;

        JavaType objectref = frame->operandStack.top();
        frame->operandStack.pop();
        map<string, JavaType>* object = (map<string, JavaType>*)objectref.type_reference;
        string * objectClassName = (string*)object->at("<this_class>").type_reference;
        class_file * objectClassFile = methodArea->getClassFile(*objectClassName);

        constantPool = objectClassFile->getConstantPool();
        vector<MethodInfo*> methods = objectClassFile->getMethods();

        for (int i = 0; i < objectClassFile->getMethodsCount() && !foundMethod; i++) {
            method = methods[i];
            uint16_t nameIndex = method->getNameIndex();
            uint16_t descriptorIndex = method->getDescriptorIndex();
            string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
            string methodDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
            if (name.compare(methodName) == 0 && methodDescriptor.compare(descriptor) == 0) {
                foundMethod = true;
            }
        }

        //Caso nao encontre checa as superclasses
        if (!foundMethod) {
            do {
                class_file * classFile = methodArea->getClassFile(className);
                constantPool = classFile->getConstantPool();
                vector<MethodInfo*> methods = classFile->getMethods();

                for (int i = 0; i < classFile->getMethodsCount() && !foundMethod; i++) {
                    method = methods[i];
                    uint16_t nameIndex = method->getNameIndex();
                    uint16_t descriptorIndex = method->getDescriptorIndex();
                    string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
                    string methodDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
                    if (name.compare(methodName) == 0 && methodDescriptor.compare(descriptor) == 0) {
                        foundMethod = true;
                    }
                }

                if (!foundMethod) {
                    if (classFile->getSuperClass() == 0) {
                        printf("invokevirutal:  metodo nao foi encontrado em nenhuma superclasse! Talvez esteja em uma interface, falta Implementar!\n");
                        std::exit(0);
                    }
                    className = constantPool[classFile->getSuperClass()-1]->getInfo(constantPool).first;
                }
            } while(!foundMethod);
        }

        // Frame recebe class_file e jvm_stack
        Frame staticMethodFrame(constantPool, method, frame->jvmStack);

        int argCnt = 1;
        for (int i = 1; descriptor[i] != ')'; i++) {
            if (descriptor[i] == 'I' || descriptor[i] == 'F') {
                JavaType arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt++;
            }
            else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
                JavaType arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt+=2;
            }
            else if (descriptor[i] == 'L') {
                int j = i;
                while (descriptor[i] != ';') {
                    i++;
                }
                JavaType arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt++;
            }
            else if (descriptor[i] == '[') {
                while (descriptor[i] == '[') {
                    i++;
                }
                if (descriptor[i] == 'L') {
                    while (descriptor[i] != ';') {
                        i++;
                    }
                }
                JavaType arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt++;
            }
            else {
                cout << "Tipo de descritor nao reconhecido: " << descriptor[i] << endl;
                std::exit(0);
            }
        }
        staticMethodFrame.localVariables[0] = objectref;

        frame->jvmStack->push(staticMethodFrame);
        frame->localPC++;
        return staticMethodFrame.localPC;
    }
    return ++frame->localPC;
}

/** @class Instruction::invokespecialFunction
 *  @brief Invoca metodo de inicializacao da instancia como privado, invoca metodos da superclasse e da classe atual.
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::invokespecialFunction(Frame* frame) {
    MethodArea * methodArea = classLoader->getMethodArea();
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    string nameAndType = frame->constantPool[index-1]->getInfo(frame->constantPool).second;
    int j = 0;

    while (j < nameAndType.size() && nameAndType[j+1] != ':') {
        j++;
    }
    string methodName = nameAndType.substr(0,j);
    string descriptor = nameAndType.substr(j+3,nameAndType.size());

    if (className.compare("java/lang/String") == 0) {
        if (methodName.compare("<init>") == 0) {
            string* stringReference = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();
            string* initStringReference = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();
            *initStringReference = *stringReference;
        }
        else {
            printf("invokespecial: metodo da classe string desconhecido: %s\n", methodName.c_str());
            std::exit(0);
        }
        return ++frame->localPC;
    }
    if (className.compare("java/lang/StringBuilder") == 0) {
        if (methodName.compare("<init>") == 0) {
            frame->operandStack.pop();
        }
        return ++frame->localPC;
    }

    bool foundMethod = false;
    //vector<CPInfo*> constantPool;
    cp_info_vector constantPool;
    //MethodInfo* method;
    method_info* method;
    do {
        class_file * classFile = methodArea->getClassFile(className);
        constantPool = classFile->getConstantPool();
        //vector<MethodInfo*> methods = classFile->getMethods();
        vector<method_info> methods = classFile->getMethods();

        for (int i = 0; i < classFile->getMethodsCount() && !foundMethod; i++) {
            //method = methods[i];
            method = &(methods[i]);
            //uint16_t nameIndex = method->getNameIndex();
            uint16_t nameIndex = method->name_idx;
            //uint16_t descriptorIndex = method->getDescriptorIndex();
            uint16_t descriptorIndex = method->descriptor_idx;
            string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
            string methodDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
            if (name.compare(methodName) == 0 && methodDescriptor.compare(descriptor) == 0) {
                foundMethod = true;
            }
        }

        if (!foundMethod) {
            if (classFile->getSuperClass() == 0) {
                printf("invokespecial:  metodo nao foi encontrado em nenhuma superclasse! Talvez esteja em uma interface, falta Implementar!\n");
            }
            string className = constantPool[classFile->getSuperClass()-1]->getInfo(constantPool).first;
        }
    } while(!foundMethod);

    // Frame recebe class_file e jvm_stack
    Frame staticMethodFrame(constantPool, method, frame->jvmStack);

    stack<JavaType> auxstack;

    for (int i = 1; descriptor[i] != ')'; i++) {
        if (descriptor[i] == 'I' || descriptor[i] == 'F') {
        }
        else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
        }
        else if (descriptor[i] == 'L') {
            while (descriptor[i] != ';') {
                i++;
            }
        }
        else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
                i++;
            }
            if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
        }
        else {
            cout << "Tipo de descritor nao reconhecido na contagem: " << descriptor[i] << endl;
            std::exit(0);
        }
        auxstack.push(frame->operandStack.top());
        frame->operandStack.pop();
    }
    int argCnt = 1;
    for (int i = 1; descriptor[i] != ')'; i++) {
        if (descriptor[i] == 'I' || descriptor[i] == 'F') {
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt += 2;
        }
        else if (descriptor[i] == 'L') {
            int j = i;
            while (descriptor[i] != ';') {
                i++;
            }
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
                i++;
            }
            if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else {
            cout << "Tipo de descritor nao reconhecido: " << descriptor[i] << endl;
            std::exit(0);
        }
    }
    JavaType objectref = frame->operandStack.top();
    frame->operandStack.pop();
    staticMethodFrame.localVariables[0] = objectref;

    frame->jvmStack->push(staticMethodFrame);
    frame->localPC++;
    return staticMethodFrame.localPC;
}

/** @class Instruction::invokestaticFunction
 *  @brief Invoca um metodo de uma classe estatica
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::invokestaticFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    MethodArea * methodArea = classLoader->getMethodArea();

    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    string nameAndType = frame->constantPool[index-1]->getInfo(frame->constantPool).second;
    int j = 0;

    while (j < nameAndType.size() && nameAndType[j+1] != ':') {
        j++;
    }
    string methodName = nameAndType.substr(0,j);
    string descriptor = nameAndType.substr(j+3,nameAndType.size());

    if (!methodArea->isClassInitialized(className)) {
        methodArea->setClassAsInitialized(className);

        class_file aux = classLoader->loadClassFile(className + ".class");
        classLoader->loadSuperClasses(&aux);
        class_file * classFile = classLoader->getClassFromMethodArea(className);
        //vector<CPInfo*> constantPool = classFile->getConstantPool();
        cp_info_vector constantPool = classFile->getConstantPool();
        //vector<MethodInfo*> methods = classFile->getMethods();
        vector<method_info> methods = classFile->getMethods();
        MethodInfo* method;

        bool foundClinit = false;
        for (int i = 0; i < classFile->getMethodsCount() && !foundClinit; i++) {
            method = methods[i];
            uint16_t nameIndex = method->getNameIndex();
            uint16_t descriptorIndex = method->getDescriptorIndex();
            string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
            string classDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
            if (name.compare("<clinit>") == 0 && classDescriptor.compare("()V") == 0) {
                foundClinit = true;
            }
        }

        if (foundClinit) {
            // Frame recebe class_file e jvm_stack
            Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
            frame->jvmStack->push(clinitMethodFrame);
            frame->localPC-=2;
            return clinitMethodFrame.localPC;
        }
    }

    class_file * classFile = methodArea->getClassFile(className);
    //vector<CPInfo*> constantPool = classFile->getConstantPool();
    cp_info_vector constantPool = classFile->getConstantPool();
    //vector<MethodInfo*> methods = classFile->getMethods();
    vector<method_info> methods = classFile->getMethods();
    //MethodInfo* method;
    method_info* method;
    bool foundMethod = false;

    for (int i = 0; i < classFile->getMethodsCount() && !foundMethod; i++) {
        //method = methods[i];
        method = &(methods[i]);
        //uint16_t nameIndex = method->getNameIndex();
        uint16_t nameIndex = method->name_idx;
        //uint16_t descriptorIndex = method->getDescriptorIndex();
        uint16_t descriptorIndex = method->descriptor_idx
        string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
        string classDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
        if (name.compare(methodName) == 0 && classDescriptor.compare(descriptor) == 0) {
            foundMethod = true;
        }
    }

    if (!foundMethod) {
        printf("Invokestatic: o método especificado nao foi encontrado!\n");
        std::exit(0);
    }

    // Frame recebe class_file e jvm_stack
    Frame staticMethodFrame(constantPool, method, frame->jvmStack);

    stack<JavaType> auxstack;

    for (int i = 1; descriptor[i] != ')'; i++) {
        if (descriptor[i] == 'I' || descriptor[i] == 'F') {
        }
        else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
        }
        else if (descriptor[i] == 'L') {
            while (descriptor[i] != ';') {
                i++;
            }
        }
        else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
                i++;
            }
            if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
        }
        else {
            cout << "Tipo de descritor nao reconhecido na contagem: " << descriptor[i] << endl;
            std::exit(0);
        }
        auxstack.push(frame->operandStack.top());
        frame->operandStack.pop();
    }
    int argCnt = 0;
    for (int i = 1; descriptor[i] != ')'; i++) {
        if (descriptor[i] == 'I' || descriptor[i] == 'F') {
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt += 2;
        }
        else if (descriptor[i] == 'L') {
            int j = i;
            while (descriptor[i] != ';') {
                i++;
            }
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
                i++;
            }
            if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else {
            cout << "Tipo de descritor nao reconhecido: " << descriptor[i] << endl;
            std::exit(0);
        }
    }

    frame->jvmStack->push(staticMethodFrame);
    frame->localPC++;
    return staticMethodFrame.localPC;
}

/** @class Instruction::invokeinterfaceFunction
 *  @brief Invoca um metodo da interface.
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::invokeinterfaceFunction(Frame* frame) {
    printf("Instrucao invokeinterfaceFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::invokedynamicFunction
 *  @brief Invoca um metodo dinamico
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::invokedynamicFunction(Frame* frame) {
    printf("Instrucao invokedynamicFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::newOpFunction
 *  @brief Cria um novo objeto
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::newOpFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    MethodArea * methodArea = classLoader->getMethodArea();

    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;

    if (className.compare("java/lang/String") == 0) {
        JavaType objectref;
        objectref.type_reference = (uint64_t)new string("");
        objectref.tag = CAT1;
        frame->operandStack.push(objectref);
    }
    else if (className.compare("java/lang/StringBuilder") == 0) {
        JavaType objectref;
        objectref.type_reference = (uint64_t)new string("");
        objectref.tag = CAT1;
        frame->operandStack.push(objectref);
    }
    else {
        if (!methodArea->isClassInitialized(className)) {
            methodArea->setClassAsInitialized(className);

            class_file aux = classLoader->loadClassFile(className + ".class");
            classLoader->loadSuperClasses(&aux);
            class_file * classFile = classLoader->getClassFromMethodArea(className);
            //vector<CPInfo*> constantPool = classFile->getConstantPool();
            cp_info_vector constantPool = classFile->getConstantPool();
            //vector<MethodInfo*> methods = classFile->getMethods();
            vector<method_info> methods = classFile->getMethods();
            //MethodInfo* method;
            method_info* method;

            bool foundClinit = false;
            for (int i = 0; i < classFile->getMethodsCount() && !foundClinit; i++) {
                //method = methods[i];
                method = &(methods[i]);
                //uint16_t nameIndex = method->getNameIndex();
                uint16_t nameIndex = method->name_idx;
                //uint16_t descriptorIndex = method->getDescriptorIndex();
                uint16_t descriptorIndex = method->descriptor_idx;
                string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
                string classDescriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
                if (name.compare("<clinit>") == 0 && classDescriptor.compare("()V") == 0) {
                    foundClinit = true;
                }
            }

            if (foundClinit) {
                Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
                frame->jvmStack->push(clinitMethodFrame);
                frame->localPC-=2;
                return clinitMethodFrame.localPC;
            }
        }

        class_file * classFile = methodArea->getClassFile(className);
        JavaType objectref;
        objectref.tag = CAT1;
        objectref.type_reference = (uint64_t)initializeFields(classFile);
        frame->operandStack.push(objectref);
    }
    return ++frame->localPC;
}

map<string, JavaType>* Instruction::initializeFields(class_file* classFile) {
    MethodArea * methodArea = classLoader->getMethodArea();
    map<string, JavaType>* object = new map<string, JavaType>;
    class_file * objectClass = classFile;

    do {
        //vector<CPInfo*> constantPool = classFile->getConstantPool();
        cp_info_vector constantPool = classFile->getConstantPool();
        //vector<FieldInfo*> fields = classFile->getFields();
        vector<field_info> fields = classFile->getFields();
        for (uint16_t i = 0; i < classFile->getFieldsCount(); i++) {
            //CPInfo* fieldInfo = constantPool[fields[i]->getNameIndex()-1];
            shared_ptr<CP_Info> fieldInfo = to_cp_info(constantPool[fields[i].name_idx-1]);
            string fieldName = fieldInfo->getInfo(constantPool).first;

            //CPInfo* descriptorInfo = constantPool[fields[i]->getDescriptorIndex()-1];
            shared_ptr<CP_Info> descriptorInfo = to_cp_info(constantPool[fields[i].descriptor_idx-1]);
            string fieldDescriptor = descriptorInfo->getInfo(constantPool).first;
            JavaType fieldContent;

            if (fieldDescriptor.compare("C") == 0) {
                fieldContent.tag = CAT1;
                fieldContent.type_char = 0;
            }
            else if (fieldDescriptor.compare("I") == 0) {
                fieldContent.tag = CAT1;
                fieldContent.type_int = 0;
            }
            else if (fieldDescriptor.compare("F") == 0) {
                fieldContent.tag = CAT1;
                fieldContent.type_float = 0;
            }
            else if (fieldDescriptor.compare("D") == 0) {
                fieldContent.tag = CAT2;
                fieldContent.type_double = 0;
            }
            else if (fieldDescriptor.compare("J") == 0) {
                fieldContent.tag = CAT2;
                fieldContent.type_long = 0;
            }
            else if (fieldDescriptor.compare("Z") == 0) {
                fieldContent.tag = CAT1;
                fieldContent.type_boolean = 0;
            }
            else if (fieldDescriptor[0] == 'L') {
                fieldContent.tag = CAT1;
                fieldContent.type_reference = JAVA_NULL;
            }
            else if (fieldDescriptor[0] == '[') {
                fieldContent.tag = CAT1;
                fieldContent.type_reference = JAVA_NULL;
            }
            else {
                printf("Criacao de fields: tipo do descritor nao reconhecido: %s\n", fieldDescriptor.c_str());
                std::exit(0);
            }

            object->insert(make_pair(fieldName, fieldContent));
        }

        string superClassName = constantPool[classFile->getSuperClass()-1]->getInfo(constantPool).first;
        classFile = methodArea->getClassFile(superClassName);
    } while (classFile->getSuperClass() != 0);

    //Warning!
    // cout << "Warning: os atributos de interfaces ainda nao estao sendo buscados!" << endl;

    JavaType thisClass;
    uint16_t thisClassIndex = objectClass->getThisClass();
    //CPInfo* thisClassInfo = objectClass->getConstantPool()[thisClassIndex-1];
    shared_ptr<CP_Info> thisClassInfo = to_cp_info(objectClass->getConstantPool()[thisClassIndex-1]);
    string thisClassName = thisClassInfo->getInfo(objectClass->getConstantPool()).first;
    thisClass.type_reference = (uint64_t)new string(thisClassName);
    object->insert(make_pair("<this_class>", thisClass));
    return object;
}



/** @class Instruction::newarrayFunction
 *  @brief Cria um novo array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::newarrayFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t atype = bytecode[++frame->localPC];

    JavaType count;
    count.type_int = (int32_t)frame->operandStack.top().type_int;
    frame->operandStack.pop();

    vector<JavaType>* array = new vector<JavaType>(count.type_int);

    if (atype == T_BOOLEAN) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT1;
            array->at(i).type_boolean = (int8_t)0;
        }
    }
    else if (atype == T_CHAR) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT1;
            array->at(i).type_char = (int16_t)0;
        }
    }
    else if (atype == T_FLOAT) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT1;
            array->at(i).type_float = (uint32_t)0;
        }
    }
    else if (atype == T_DOUBLE) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT2;
            array->at(i).type_double = (uint64_t)0;
        }
    }
    else if (atype == T_BYTE) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT1;
            array->at(i).type_byte = (int8_t)0;
        }
    }
    else if (atype == T_SHORT) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT1;
            array->at(i).type_short = (int16_t)0;
        }
    }
    else if (atype == T_INT) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT1;
            array->at(i).type_int = (int32_t)0;
        }
    }
    else if (atype == T_LONG) {
        for (int32_t i = 0; i < count.type_int; i++) {
            array->at(i).tag = CAT2;
            array->at(i).type_long = (int64_t)0;
        }
    }
    else {
        printf("newarray: tipo de array indefinido: %u\n", atype);
    }


    JavaType arrayref;
    arrayref.tag = CAT1;
    arrayref.type_reference = (uint64_t)array;
    frame->operandStack.push(arrayref);

    return ++frame->localPC;
}

/** @class Instruction::anewarrayFunction
 *  @brief Cria um novo de array de referencias.
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::anewarrayFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];

    int32_t count = (int32_t)frame->operandStack.top().type_int;
    frame->operandStack.pop();

    vector<JavaType>* array = new vector<JavaType>(count);

    for (int i = 0; i < count; i++) {
        array->at(i).tag = CAT1;
        array->at(i).type_reference = JAVA_NULL;
    }

    JavaType arrayref;
    arrayref.tag = CAT1;
    arrayref.type_reference = (uint64_t)array;
    frame->operandStack.push(arrayref);

    return ++frame->localPC;
}

/** @class Instruction::arraylengthFunction
 *  @brief Pega o tamanho do array
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::arraylengthFunction(Frame* frame) {
    JavaType arrayref = frame->operandStack.top();
    frame->operandStack.pop();
    vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;

    JavaType length;
    length.tag = CAT1;
    length.type_int = (uint32_t)array->size();
    frame->operandStack.push(length);

    return ++frame->localPC;
}

/** @class Instruction::athrowFunction
 *  @brief Lanca erros de excecoes
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::athrowFunction(Frame* frame) {
    printf("Instrucao athrowFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::checkcastFunction
 *  @brief Checa se o objeto e do tipo dado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::checkcastFunction(Frame* frame) {
    printf("Instrucao checkcastFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::instanceofFunction
 *  @brief Determina se o objeto e do tipo dado
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::instanceofFunction(Frame* frame) {
    printf("Instrucao instanceofFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::monitorenterFunction
 *  @brief Entra no moitor para o objeto
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::monitorenterFunction(Frame* frame) {
    printf("Instrucao monitorenterFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::monitorexitFunction
 *  @brief Sai do monitor para o o objeto
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::monitorexitFunction(Frame* frame) {
    printf("Instrucao monitorexitFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::wideFunction
 *  @brief Extende o index da variavel local atraves de bytes adicionais
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::wideFunction(Frame* frame) {
    printf("Instrucao wideFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

vector<JavaType>* Instruction::buildMultiAnewArray(vector<int> dimensions, int index, char type) {
    vector<JavaType>* array = new vector<JavaType>(dimensions[index]);

    if (index == 0) {
        for (int i = 0; i < dimensions[index]; i++) {
            if (type == 'B' || type == 'C' || type == 'F' || type == 'I' || type == 'S' || type == 'Z' || type == ';') {
                array->at(i).tag = CAT1;
                array->at(i).type_int = 0;
            }
            else if (type == 'D' || type == 'J') {
                array->at(i).tag = CAT1;
                array->at(i).type_int = 0;
            }
            else {
                cout << "Tipo de multianewaray desconhecido: " << type << endl;
                std::exit(0);
            }
        }
        return array;
    }

    for (int i = 0; i < dimensions[index]; i++) {
        array->at(i).tag = CAT1;
        array->at(i).type_reference = (uint64_t)buildMultiAnewArray(dimensions, index-1, type);
    }

    return array;
}


/** @class Instruction::multianewarrayFunction
 *  @brief Cria um array multidimensional
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::multianewarrayFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    uint8_t byte3 = bytecode[++frame->localPC];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    uint32_t dimensions = byte3;
    vector<int> dimensionsArray;

    for (int i = 0; i < dimensions; i++) {
        uint32_t dimension = frame->operandStack.top().type_int;
        frame->operandStack.pop();
        if (dimension == 0) {
            break;
        }
        dimensionsArray.push_back(dimension);
    }

    string className = frame->constantPool[index-1]->getInfo(frame->constantPool).first;
    vector<JavaType>* array = buildMultiAnewArray(dimensionsArray, dimensions-1, className[className.size()-1]);

    JavaType arrayref;
    arrayref.tag = CAT1;
    arrayref.type_reference = (uint64_t)array;
    frame->operandStack.push(arrayref);
    return ++frame->localPC;
}

/** @class Instruction::ifnullFunction
 *  @brief Salta para branch se a referencia e nula.
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifnullFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if (value.type_reference == JAVA_NULL) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::ifnonnullFunction
 *  @brief Salta para branch se a referencia e nao nula
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::ifnonnullFunction(Frame* frame) {
    uint8_t* bytecode = frame->getCode();
    uint32_t baseAddress = frame->localPC;
    uint8_t byte1 = bytecode[++frame->localPC];
    uint8_t byte2 = bytecode[++frame->localPC];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value = frame->operandStack.top();
    frame->operandStack.pop();

    if (value.type_reference != JAVA_NULL) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
    }

    return ++frame->localPC;
}

/** @class Instruction::goto_wFunction
 *  @brief Salta pra branch sempre
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::goto_wFunction(Frame* frame) {
    printf("Instrucao goto_wFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}

/** @class Instruction::jsr_wFunction
 *  @brief Salta para branch sempre (wide index)
 *  @param Frame atual para utilizacao da pilha de operandos e pc atual
 *  @return inteiro sem sinal de 4 bytes com o pc atualizado
 */
uint32_t Instruction::jsr_wFunction(Frame* frame) {
    printf("Instrucao jsr_wFunction nao implementada ainda!\n");
    std::exit(0);
    return -1;
}