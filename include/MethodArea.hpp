/**
 * @file MethodArea.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira - 150143401
 * @brief Biblioteca de definição da estrutura da MethodArea 
 * @details A biblioteca MethodArea.hpp contém a descrição do pair classes que contém umma string e uma estrutura do tipo ClassFile
 * além de duas funções.
 * @see MethodArea.cpp
 */

#ifndef METHOD_AREA_H_INCLUDED
#define METHOD_AREA_H_INCLUDED

#include <vector>
#include <map>
#include "ClassFile.hpp"

using namespace std;

/** @class MethodArea
*   @brief Classe que contém toda a estrutura do MethodArea
*/

class MethodArea {
private:
    map<string, ClassFile> classes;
    map<string, bool> clinitWasExecuted;
public:
    void insertClass(ClassFile);
    ClassFile* getClassFile(string name);
    bool isClassInitialized(string name);
    void setClassAsInitialized(string name);
};

#endif