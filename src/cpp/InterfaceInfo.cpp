/**
 * @file InterfaceInfo.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Implementa a classe Interface
 * @see InterfaceInfo.hpp
 */
#include "../hpp/InterfaceInfo.hpp"

/** @class InterfaceInfo::read
 *  @brief Método que armazena o valor das informações das interfaces
 *  @param fp ponteiro para o arquivo .class
 */
void InterfaceInfo::read(FILE *fp) {
    ByteReader<uint16_t> twoByteReader;
    interfaceIndex = twoByteReader.byteCatch(fp);
}