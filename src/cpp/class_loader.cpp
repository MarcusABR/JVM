/**
 * @file class_loader.cpp
 * @author André Larrosa Chimpliganond - 190010321
 * @author Marcus Vinicius Oliveira de Abrantes - 190034084
 * @author  Matheus Barbosa e Silva - 190113987
 * @author Moises Felipe Jaco Andrade de Lima - 190018364 
 * @author Thiago Elias dos Reis - 190126892
 * @brief Definicoes do ClassLoader
 * @details Definicoes de função de carga do ClassLoader como arquivos
 * e superclasses.
**/

#include "../hpp/class_loader.hpp"
#include "../hpp/class_file.hpp"
#include "../hpp/utils.hpp"
#include "../cpp/leitor_exibidor.cpp"
#include <iostream>

class_file* ClassLoader::carregar(string &filename)
{
    class_file *class_f = new class_file;
    file = abrir_arquivo(filename);

    get_metadata(class_f);
    get_constant_pool(class_f);
    get_class_data(class_f);
    get_interfaces(class_f);
    get_fields(class_f);
    get_methods(class_f);
    get_attributes(class_f);
    //methodArea->insertClass(*class_f);

    return class_f;
}

void ClassLoader::get_metadata(class_file *class_f)
{
    //class_f->magic         = ler_bytes_big_endian<u4>(file); // signature (0xCAFEBABE) 
    class_f->setMagic(ler_bytes_big_endian<u4>(file)); // signature (0xCAFEBABE) 
    //class_f->minor_version = ler_bytes_big_endian<u2>(file);
    class_f->setMinor(ler_bytes_big_endian<u2>(file));
    //class_f->major_version = ler_bytes_big_endian<u2>(file);
    class_f->setMajorVersion(ler_bytes_big_endian<u2>(file));
}

void ClassLoader::get_constant_pool(class_file *class_f)
{
    //class_f->constant_pool_count = ler_bytes_big_endian<u2>(file); 
    class_f->setConstantPoolCount(ler_bytes_big_endian<u2>(file));
    //int iteration_counter = class_f->constant_pool_count - 1;
    int iteration_counter = class_f->getConstantPoolCount() - 1;
    while (iteration_counter--)
    {
        u1 tag = ler_bytes_big_endian<u1>(file);
        shared_ptr<CP_Info> new_el(new CP_Info(tag, file));
        class_f->constant_pool.push_back(new_el);
        if ((CONSTANT_Types)tag == CONSTANT_Double || (CONSTANT_Types)tag == CONSTANT_Long)
        {
            iteration_counter--;
            shared_ptr<CP_Info> continuation_el(new CP_Info(CONSTANT_Continuation, file));
            class_f->constant_pool.push_back(continuation_el);
        }
    }
}

void ClassLoader::get_class_data(class_file *class_f)
{
    //class_f->access_flag = ler_bytes_big_endian<u2>(file);
    class_f->setAccessFlags(ler_bytes_big_endian<u2>(file));
    //class_f->this_class  = ler_bytes_big_endian<u2>(file);
    class_f->setThisClass(ler_bytes_big_endian<u2>(file));
    //class_f->super_class = ler_bytes_big_endian<u2>(file);
    class_f->setSuperClass(ler_bytes_big_endian<u2>(file));
}

void ClassLoader::get_interfaces(class_file *class_f)
{
    //class_f->interfaces_count = ler_bytes_big_endian<u2>(file);
    class_f->setAttributesCount(ler_bytes_big_endian<u2>(file));
    
    //for (int i = 0; i < class_f->interfaces_count; i++)
    for (int i = 0; i < class_f->getInterfacesCount(); i++)
        //class_f->interfaces.push_back(ler_bytes_big_endian<u2>(file));
        class_f->getInterfaces().push_back(ler_bytes_big_endian<u2>(file));
}

void ClassLoader::get_fields(class_file *class_f)
{
    //class_f->fields_count = ler_bytes_big_endian<u2>(file);
    class_f->setFieldsCount(ler_bytes_big_endian<u2>(file));

    //for(int i = 0; i < class_f->fields_count; i++)
    for(int i = 0; i < class_f->getFieldsCount(); i++)
        //class_f->fields.push_back(field_info(file, class_f->constant_pool));
        class_f->getFields().push_back(field_info(file, class_f->constant_pool));
}

void ClassLoader::get_methods(class_file *class_f)
{
    //class_f->methods_count = ler_bytes_big_endian<u2>(file);
    class_f->setMethodsCount(ler_bytes_big_endian<u2>(file));

    //for(int i = 0; i < class_f->methods_count; i++)
    for(int i = 0; i < class_f->getMethodsCount(); i++)
        //class_f->methods.push_back(method_info(file, class_f->constant_pool));
        class_f->getMethods().push_back(method_info(file, class_f->constant_pool));
}

void ClassLoader::get_attributes(class_file *class_f)
{
    //class_f->attributes_count = ler_bytes_big_endian<u2>(file);
    class_f->setAttributesCount(ler_bytes_big_endian<u2>(file));

    //for (int i = 0; i < class_f->attributes_count; i++)
    for (int i = 0; i < class_f->getAttributesCount(); i++)
    {
        shared_ptr<Attribute> new_attr(new Attribute_Info(file, class_f->constant_pool));
        class_f->getAttributes().push_back(new_attr);
    }
}

void ClassLoader::loadSuperClasses(class_file* classFile) {
    cp_info_vector constantPool = classFile->getConstantPool();

    if (classFile->getSuperClass() == 0) {
        return;
    }
     

    string superClassPath = exibir_utf8(*(to_cp_info(constantPool[classFile->getSuperClass()-1])->_utf8));;

    if (superClassPath.compare("java/lang/string") == 0 ||
        superClassPath.compare("java/lang/System.out") == 0 ||
        superClassPath.compare("java/lang/System.in") == 0) {
        return;
    }

    class_file superClassFile;

    if (superClassPath.compare("java/lang/Object") == 0) {
        superClassFile = loadClassFile("java/lang/Object");
        
    }
    else {
        superClassFile = loadClassFile(superClassPath+".class");
        loadSuperClasses(&superClassFile);
    }
}

class_file ClassLoader::loadClassFile(string className) {
    FILE *fp;

    if (className.compare("java/lang/Object") == 0) {
        fp = fopen("java/lang/Object.class", "rb");
    }
    else {
        fp = fopen((projectPath + className).c_str(), "rb"); //TODO verificar onde é setado o projectPath
    }

    if (fp != NULL) {
        class_file *  classFile;
        get_metadata(classFile);
        get_constant_pool(classFile);
        get_class_data(classFile);
        get_interfaces(classFile);
        get_fields(classFile);
        get_methods(classFile);
        get_attributes(classFile);
        methodArea->insertClass(*classFile);
        fclose(fp);
        return *classFile;
    }
    cout << "Nao foi possivel abrir o arquivo! Programa terminado!" << projectPath << " " << className << endl;
    exit(0);
}

