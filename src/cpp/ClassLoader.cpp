

// #include "../hpp/ClassLoader.hpp"

// /** @fn ClassLoader::ClassLoader
//  *  @brief Construtor ClassLoader
//  *  @param projectPath
//  */
// ClassLoader::ClassLoader(string projectPath) {
//     this->projectPath = projectPath;
// }


// /** @class ClassLoader::loadClassFile
//  *  @brief Método que visa carregar o arquivo .class
//  *  @param className tipo string
//  *  @return tipo ClassFile
//  */
// ClassFile ClassLoader::loadClassFile(string className) {
//     FILE *fp;

//     if (className.compare("java/lang/Object") == 0) {
//         fp = fopen("java/lang/Object.class", "rb");
//     }
//     else {
//         fp = fopen((projectPath + className).c_str(), "rb");
//     }

//     if (fp != NULL) {
//         ClassFile classFile(fp);
//         methodArea->insertClass(classFile);
//         fclose(fp);
//         return classFile;
//     }
//     cout << "Nao foi possivel abrir o arquivo! Programa terminado!" << projectPath << " " << className << endl;
//     exit(0);
// }

// /** @class ClassLoader::loadSuperClasses
//  *  @brief Método que visa carregar as superClasses o arquivo .class
//  *  @param classFile ponteiro do tipo ClassFile
//  */

// void ClassLoader::loadSuperClasses(ClassFile* classFile) {
//     vector<CPInfo*> constantPool = classFile->getConstantPool();

//     if (classFile->getSuperClass() == 0) {
//         return;
//     }

//     string superClassPath = constantPool[classFile->getSuperClass()-1]->getInfo(constantPool).first.c_str();

//     // if (superClassPath.compare("java/lang/string") == 0 ||
//     //     superClassPath.compare("java/lang/System.out") == 0 ||
//     //     superClassPath.compare("java/lang/System.in") == 0) {
//     //     return;
//     // }

//     ClassFile superClassFile;

//     if (superClassPath.compare("java/lang/Object") == 0) {
//         superClassFile = loadClassFile("java/lang/Object");
//     }
//     else {
//         superClassFile = loadClassFile(superClassPath+".class");
//         loadSuperClasses(&superClassFile);
//     }
// }