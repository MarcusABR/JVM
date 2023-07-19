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
    methodArea->insertClass(*class_f);

    return class_f;
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

