#ifndef METHOD_AREA_H_INCLUDED
#define METHOD_AREA_H_INCLUDED

#include <vector>
#include <map>
#include "class_file.hpp"

using namespace std;

class MethodArea {
private:
    map<string, class_file> classes;
    map<string, bool> clinitWasExecuted;
public:
    void insertClass(class_file);
    class_file* getClassFile(string name);
    bool isClassInitialized(string name);
    void setClassAsInitialized(string name);
};

#endif