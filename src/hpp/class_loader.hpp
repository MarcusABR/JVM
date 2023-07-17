#ifndef _CLASS_LOADER_HPP
#define _CLASS_LOADER_HPP

#include "class_file.hpp"
#include "MethodArea.hpp"

class ClassLoader {
private:
    ifstream file;
    MethodArea * methodArea;
    string projectPath;
    void get_metadata(class_file*);
    void get_constant_pool(class_file*);
    void get_class_data(class_file*);
    void get_interfaces(class_file*);
    void get_fields(class_file*);
    void get_methods(class_file*);
    void get_attributes(class_file*);

public:
    class_file* carregar(string&);
    class_file loadClassFile(string);
    void loadSuperClasses(class_file*);
    void setMethodArea(MethodArea* methodArea) {
        this->methodArea = methodArea;
    }
    class_file * getClassFromMethodArea(string className) {
        return this->methodArea->getClassFile(className);
    }
    MethodArea * getMethodArea() {
        return this->methodArea;
    }
};

#endif // _CLASS_LOADER_HPP