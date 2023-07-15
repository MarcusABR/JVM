/**
 * @file InterfaceInfo.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Descreve uma estrutura de Interface 
 * @see InterfaceInfo.cpp
 */

#ifndef __INTERFACEINFO_H__
#define __INTERFACEINFO_H__

#include <fstream>
#include <cstdint>
#include "ByteReader.hpp"

/** @class InterfaceInfo
*   @brief Classe que contém toda a estrutura das interfaces do .class
*/

class InterfaceInfo {
private:
    uint16_t interfaceIndex;
    ~InterfaceInfo();
public:
    void read(FILE *fp);
    uint16_t getInterfaceIndex() {
        return interfaceIndex;
    }
};

#endif