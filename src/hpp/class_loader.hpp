#ifndef _CLASS_LOADER_HPP
#define _CLASS_LOADER_HPP

#include "class_file.hpp"

class ClassLoader {
private:
    ifstream file;
    void get_metadata(class_file*);
    void get_constant_pool(class_file*);
    void get_class_data(class_file*);
    void get_interfaces(class_file*);
    void get_fields(class_file*);
    void get_methods(class_file*);
    void get_attributes(class_file*);

public:
    class_file* carregar(string&);
};

#endif // _CLASS_LOADER_HPP