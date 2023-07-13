/**
 * @file ClassLoader.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Biblioteca de definição das funções do ClassLoader
 * @details A biblioteca ClassLoader.hpp contém o arquivo com a descrição das funções
 * utilizadas para a implementação dos componentes do Class Loader
 * @see ClassLoader.cpp
 * @see ClassFile.hpp
 * @see MethodArea.hpp
 */

#ifndef __CLASSLOADER_H_INCLUDED__
#define __CLASSLOADER_H_INCLUDED__

#include "ClassFile.hpp"
#include "MethodArea.hpp"
/** @class ClassLoader
*   @brief Classe que armazena o caminho para o arquivo .class e separa o MethodArea; 
*   
*/
class ClassLoader {
private:
    MethodArea * methodArea;
    string projectPath;
public:
    ClassLoader(string);
    ClassFile loadClassFile(string);
    void loadSuperClasses(ClassFile*);
    void setMethodArea(MethodArea* methodArea) {
        this->methodArea = methodArea;
    }
    ClassFile * getClassFromMethodArea(string className) {
        return this->methodArea->getClassFile(className);
    }
    MethodArea * getMethodArea() {
        return this->methodArea;
    }
};

#endif