#include "../hpp/method_area.hpp"
#include "../cpp/leitor_exibidor.cpp"

void MethodArea::insertClass(class_file classFile) {
    printf("entrou MethodArea::insertClass\n");
    cp_info_vector constantPool = classFile.getConstantPool();
    printf("1\n");
    // exibir_utf8 entra em loop infinito
    string name = exibir_utf8(*(to_cp_info(constantPool[classFile.getThisClass()-1])->_utf8));
    printf("2\n");
    this->classes.insert(make_pair(name, classFile));
    printf("saiu MethodArea::insertClass\n");
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