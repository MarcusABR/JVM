/**
 * @file method_area.cpp
 * @author André Larrosa Chimpliganond - 190010321
 * @author Marcus Vinicius Oliveira de Abrantes - 190034084
 * @author  Matheus Barbosa e Silva - 190113987
 * @author Moises Felipe Jaco Andrade de Lima - 190018364 
 * @author Thiago Elias dos Reis - 190126892
 * @brief Definicoes da classe MethodArea
 * @details Obtem, verifica inicializacao e insere class files.
**/

#include "../hpp/method_area.hpp"
#include "../cpp/leitor_exibidor.cpp"

void MethodArea::insertClass(class_file classFile) {
    cp_info_vector constantPool = classFile.getConstantPool();
    string name = exibir_utf8(*(to_cp_info(constantPool[classFile.getThisClass()-1])->_utf8));
    this->classes.insert(make_pair(name, classFile));
}

class_file* MethodArea::getClassFile(string name) {
    return &(classes[name]);
}

bool MethodArea::isClassInitialized(string name) {
    if (clinitWasExecuted.count(name)) {
        return true;
    }
    return false;
}

void MethodArea::setClassAsInitialized(string name) {
    this->clinitWasExecuted.insert(make_pair(name, true));
}