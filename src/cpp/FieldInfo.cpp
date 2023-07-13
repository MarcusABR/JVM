/**
 * @file FieldInfo.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Arquivo de implementação das funções do FieldInfo
 * @see FieldInfo.hpp
 */
#include "../hpp/FieldInfo.hpp"

/** @class FieldInfo::read
 *  @brief Método com o objetivo de fazer a leitura das fields do .class
 */
void FieldInfo::read(FILE *fp, vector<CPInfo*> constantPool){
    ByteReader<uint16_t> twoByteReader;

    accessFlags = twoByteReader.byteCatch(fp);
    nameIndex = twoByteReader.byteCatch(fp);
    descriptorIndex = twoByteReader.byteCatch(fp);
    attributesCount = twoByteReader.byteCatch(fp);
    
    for(int i = 0; i < attributesCount; i++) {
        AttributeInfo * attribute = (AttributeInfo *)calloc(1, sizeof(AttributeInfo));
        //TALVEZ ESTEJA ERRADA ESSA PARTE NAO ESQUECE
        attribute->read(fp,constantPool);
        attributes.push_back(attribute);
    }
}