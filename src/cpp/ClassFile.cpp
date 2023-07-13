/**
 * @file ClassFile.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Arquivo de implementação das funções do Class File
 * @see ClassFile.hpp
 */

#include "../hpp/ClassFile.hpp"

/** @fn ClassFile::ClassFile
 *  @brief Método construtor da classe Class File
 * 
 */
ClassFile::ClassFile() {
    
}

/** @class ClassFile::ClassFile
 *  @brief Método para verificar se o inicio do MagicNumber é 0xCAFEBABE, caso contrário mostra erro. Além de setar todos os valores adquiridos das informações retiradas do .class
 *  @param fp ponteiro para o arquivo .class
 */

ClassFile::ClassFile(FILE * fp) {
    this->setMagic(fp);
    if ((this->getMagic()) == 0xCAFEBABE) {
        this->setMinor(fp);
        this->setMajorVersion(fp);
        this->setConstantPoolCount(fp);
        this->setConstantPool(fp);
        this->setAccessFlags(fp);
        this->setThisClass(fp);
        this->setSuperClass(fp);
        this->setInterfacesCount(fp);
        this->setInterfaces(fp);
        this->setFieldsCount(fp);
        this->setFields(fp);
        this->setMethodsCount(fp);
        this->setMethods(fp);
        this->setAttributesCount(fp);
        this->setAttributes(fp);
    }
    else {
        cout << "O magic number nao eh 0xCAFEBABE! Programa terminado!" << endl;
        exit(0);
    }
}

/** @class ClassFile::~ClassFile
 *  @brief Destrutor da classe do Class File (ainda não implementado)
 *  @param fp ponteiro para o arquivo .class
 */
ClassFile::~ClassFile() {
    // for (auto i : interfaces) {
    //     i->~InterfaceInfo();
    // }

    // // for (auto a : attributes) {
    // //     a->~AttributeInfo();
    // // }

    // for(auto f : fields) {
    //     f->~FieldInfo();
    // }

    // //Isso causa segfault nao sei pq
    // // for(auto m : methods) {
    // //     m->~MethodInfo();
    // // }

    // for(auto cp : constantPool) {
    //     cp->~CPInfo();
    // }
}

/** @class ClassFile::setMagic
 *  @brief Método que armazena o valor do Magic
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */
void ClassFile::setMagic(FILE * fp) {
    ByteReader<typeof(magic)> magicReader;
    magic = magicReader.byteCatch(fp);
}

/** @class ClassFile::setMajorVersion
 *  @brief Método que armazena o valor de MajorVersion
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setMajorVersion(FILE * fp) {
    ByteReader<typeof(majorVersion)> majorReader;
    majorVersion = majorReader.byteCatch(fp);
}
/** @class ClassFile::setMinor
 *  @brief Método que armazena o valor do Minor
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setMinor(FILE * fp) {
    ByteReader<typeof(majorVersion)> minorReader;
    minorVersion = minorReader.byteCatch(fp);
}
/** @class ClassFile::setConstantPoolCount
 *  @brief Método que armazena o valor do Quantidade de ConstantPool
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setConstantPoolCount(FILE * fp) {
    ByteReader<typeof(constantPoolCount)> cpCountReader;
    constantPoolCount = cpCountReader.byteCatch(fp);
}
/** @class ClassFile::setConstantPool
 *  @brief Método que armazena o valor das ConstantPool
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setConstantPool(FILE * fp) {
    for (int i = 0; i < this->constantPoolCount-1; i++) {
        CPInfo *cpInfo = (CPInfo*)calloc(1, sizeof(CPInfo));
        cpInfo->read(fp);
        this->constantPool.push_back(cpInfo);

        if((cpInfo->getTag() == CPInfo::CONSTANT_Double) || (cpInfo->getTag() == CPInfo::CONSTANT_Long)) {
            CPInfo *emptyCPInfo = (CPInfo *)calloc(1, sizeof(CPInfo));
            emptyCPInfo->setTag(CPInfo::CONSTANT_Empty);
            this->constantPool.push_back(emptyCPInfo);
            i++;
        }
    } 
}
/** @class ClassFile::setAccessFlags
 *  @brief Método que armazena o valor do accessFlag
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setAccessFlags(FILE * fp) {
    ByteReader<typeof(accessFlags)> accessFlagsReader;
    accessFlags = accessFlagsReader.byteCatch(fp);
}
/** @class ClassFile::setThisClass
 *  @brief Método que armazena o valor do ThisClass
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */
void ClassFile::setThisClass(FILE * fp) {
    ByteReader<typeof(thisClass)> thisClassReader;
    thisClass = thisClassReader.byteCatch(fp);
}
/** @class ClassFile::setSuperClass
 *  @brief Método que armazena o valor de SuperClass
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setSuperClass(FILE * fp) {
    ByteReader<typeof(superClass)> superClassReader;
    superClass = superClassReader.byteCatch(fp);
}
/** @class ClassFile::setInterfacesCount
 *  @brief Método que armazena o valor da quantidade de Interfaces
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setInterfacesCount(FILE * fp) {
    ByteReader<typeof(interfacesCount)> interfacesCountReader;
    interfacesCount = interfacesCountReader.byteCatch(fp);
}
/** @class ClassFile::setInterfaces
 *  @brief Método que armazena o valor das interfaces
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setInterfaces(FILE * fp) {
    for (int i = 0; i < this->interfacesCount; i++) {
        InterfaceInfo *interfaceInfo = (InterfaceInfo*)calloc(1, sizeof(InterfaceInfo));
        interfaceInfo->read(fp);
        this->interfaces.push_back(interfaceInfo);
    }
    
}
/** @class ClassFile::setFieldsCount
 *  @brief Método que armazena o valor da quantidade de fields
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setFieldsCount(FILE * fp) {
    ByteReader<typeof(fieldsCount)> fieldsCountReader;
    fieldsCount = fieldsCountReader.byteCatch(fp);
}
/** @class ClassFile::setFields
 *  @brief Método que armazena o valor das fields
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setFields(FILE * fp) {
    for(int i = 0; i < this->fieldsCount; i++) {
        FieldInfo* field = (FieldInfo *)calloc(1, sizeof(FieldInfo));
        field->read(fp, this->constantPool);
        this->fields.push_back(field);
    }
}
/** @class ClassFile::setMethodsCount
 *  @brief Método que armazena o valor da quantidade de métodos
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setMethodsCount(FILE * fp) {
    ByteReader<typeof(methodsCount)> methodsCountReader;
    methodsCount = methodsCountReader.byteCatch(fp);
}
/** @class ClassFile::setMethods
 *  @brief Método que armazena o valor dos métodos
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setMethods(FILE * fp) {
    for (int i = 0; i < this->methodsCount; i++) {
        MethodInfo *methodInfo = (MethodInfo *)calloc(1, sizeof(MethodInfo));
        methodInfo->read(fp,this->constantPool);
        this->methods.push_back(methodInfo);
    }
}
/** @class ClassFile::setAttributesCount
 *  @brief Método que armazena o valor da quantidade de atributos
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setAttributesCount(FILE * fp) {
    ByteReader<typeof(attributesCount)> attributesCountReader;
    attributesCount = attributesCountReader.byteCatch(fp);
}
/** @class ClassFile::setAttributes
 *  @brief Método que armazena o valor dos atributos
 *  @param fp ponteiro para o arquivo .class
 *  @return
 */

void ClassFile::setAttributes(FILE * fp) {
    this->attributes = (AttributeInfo*)calloc(this->attributesCount, sizeof(AttributeInfo));

    for(int i = 0; i < this->attributesCount; i++) {
        AttributeInfo *attribute = (AttributeInfo *)calloc(1, sizeof(AttributeInfo));
        attribute->read(fp, this->constantPool);
        attributes[i] = *attribute;
    }
}