/**
 * @file MethodArea.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Implementa a classe Method Area
 * @see MethodArea.hpp
 */
 
#include "../hpp/MethodArea.hpp"

/** @class MethodArea::insertClass
 *  @brief Método que insere uma classe no MethodArea
 *  @param classFile do tipo classFile
 */
void MethodArea::insertClass(ClassFile classFile) {
    vector<CPInfo*>constantPool = classFile.getConstantPool();
    string name = constantPool[classFile.getThisClass()-1]->getInfo(constantPool).first;
    this->classes.insert(make_pair(name, classFile));
}

/** @class MethodArea::getClassFile
 *  @brief Método que busca uma classe no MethodArea
 *  @param name do tipo string
 *  @return ClassFile type
 */

ClassFile* MethodArea::getClassFile(string name) {
    return &(classes[name]);
}

/** @class MethodArea::isClassInitialized
 *  @brief Método que inicializa uma classe
 *  @param name do tipo string
 *  @return TrueOrFalse boolean
 */
bool MethodArea::isClassInitialized(string name) {
    if (clinitWasExecuted.count(name)) {
        return true;
    }
    return false;
}

/** @class MethodArea::setClassAsInitialized
 *  @brief Método que insere a classe inicializada
 *  @param name do tipo string
 */

void MethodArea::setClassAsInitialized(string name) {
    this->clinitWasExecuted.insert(make_pair(name, true));
}