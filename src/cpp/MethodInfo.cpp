/**
 * @file MethodInfo.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Biblioteca MethodInfo para declaração das constantes requeridas para funcionamento dos métodos da JVM.
 * @see MethodInfo.hpp
 */

#include "../hpp/MethodInfo.hpp"

/** @fn ClassFile::ClassFile
 *  @brief Destrutor
 */
MethodInfo::~MethodInfo() {
    // for (auto a : attributes) {
    //     //TODO
    // }
}

/** @class MethodInfo::read
 *  @brief Método que visa fazer leitura da estrutura do MethodInfo
 *  @param fp ponteiro para o arquivo .class @param constantPool do tipo vetor de CPInfo
 */
void MethodInfo::read(FILE *fp, vector<CPInfo*> constantPool) {
    ByteReader<uint16_t> reader;

    accessFlags = reader.byteCatch(fp);
    nameIndex = reader.byteCatch(fp);
    descriptorIndex = reader.byteCatch(fp);
    attributesCount = reader.byteCatch(fp);

    attributes = (AttributeInfo*)calloc(attributesCount, sizeof(AttributeInfo));
    for(int i = 0; i < attributesCount; i++){
        AttributeInfo *attributeInfo = (AttributeInfo *)calloc(1, sizeof(AttributeInfo));
        attributeInfo->read(fp, constantPool);
        attributes[i] = *attributeInfo;
    }
}