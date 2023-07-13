/**
 * @file CPIInfo.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Atributos a serem usados na execuçao da JVM 
 * @details A biblioteca CPInfo.hpp contém as informações as que servem de referência as instruções.
 * 
 * @see CPInfo.hpp
 */

#include "../hpp/CPInfo.hpp"
/** @fn CPInfo::~CPInfo
 *  @brief Destrutor
 *  @param classFile arquivo .class @param  instructionSet conjunto de instruções
 */
CPInfo::~CPInfo() {
    //TODO
}

/** @class CPInfo::setTag
 *  @brief Método que visa armazenar o valor da tag
 *  @param tag tipo uint8_t
 */

void CPInfo::setTag(uint8_t tag) {
    this->tag = tag;
}
/** @class CPInfo::read
 *  @brief Método que visa fazer a leitura da constantpool de acordo com o valor da tag
 *  @param fp ponteiro para o arquivo .class
 */

void CPInfo::read(FILE * fp) {
    ByteReader<uint8_t> oneByteReader;
    ByteReader<uint16_t> twoByteReader;
    ByteReader<uint32_t> fourByteReader;

    this->tag = oneByteReader.byteCatch(fp);

    switch(this->tag) {
    case CONSTANT_Utf8:
        this->CONSTANT_Utf8_info.length = twoByteReader.byteCatch(fp);
        this->CONSTANT_Utf8_info.bytes = (uint8_t *) calloc(this->CONSTANT_Utf8_info.length+1,sizeof(uint8_t));
        for (int j = 0; j < this->CONSTANT_Utf8_info.length; j++) {
            uint8_t byte = oneByteReader.byteCatch(fp);
            this->CONSTANT_Utf8_info.bytes[j] = byte;
        }
        this->CONSTANT_Utf8_info.bytes[this->CONSTANT_Utf8_info.length] = '\0';
        if ((char*)CONSTANT_Utf8_info.bytes == 0) {
            printf("\n\nO valor de bytes nao pode ser zero!\n\n");
        }
        break;
    case CONSTANT_Integer:
        this->CONSTANT_Integer_info.bytes = fourByteReader.byteCatch(fp);
        break;
    case CONSTANT_Float:
        this->CONSTANT_Float_info.bytes = fourByteReader.byteCatch(fp);
        break;
    case CONSTANT_Long:
        this->CONSTANT_Long_info.high_bytes = fourByteReader.byteCatch(fp);
        this->CONSTANT_Long_info.low_bytes  = fourByteReader.byteCatch(fp);
        break;
    case CONSTANT_Double:
        this->CONSTANT_Double_info.high_bytes = fourByteReader.byteCatch(fp);
        this->CONSTANT_Double_info.low_bytes  = fourByteReader.byteCatch(fp);
        break;
    case CONSTANT_Class:
        this->CONSTANT_Class_info.name_index = twoByteReader.byteCatch(fp);
        break;
    case CONSTANT_String:
        this->CONSTANT_String_info.string_index = twoByteReader.byteCatch(fp);
        break;
    case CONSTANT_Fieldref:
        this->CONSTANT_Fieldref_info.class_index = twoByteReader.byteCatch(fp);
        this->CONSTANT_Fieldref_info.name_and_type_index = twoByteReader.byteCatch(fp);
        break;
    case CONSTANT_Methodref:
        this->CONSTANT_Methodref_info.class_index = twoByteReader.byteCatch(fp);
        this->CONSTANT_Methodref_info.name_and_type_index = twoByteReader.byteCatch(fp);
        break;
    case CONSTANT_InterfaceMethodref:
        this->CONSTANT_InterfaceMethodref_info.class_index = twoByteReader.byteCatch(fp);
        this->CONSTANT_InterfaceMethodref_info.name_and_type_index = twoByteReader.byteCatch(fp);
        break;
    case CONSTANT_NameAndType:
        this->CONSTANT_NameAndType_info.name_index = twoByteReader.byteCatch(fp);
        this->CONSTANT_NameAndType_info.descriptor_index = twoByteReader.byteCatch(fp);
        break;
    default:
        cout << "Uma tag invalida foi detectada" << endl;
        exit(0);
    }
}

/** @class CPInfo::escapeString
 *  @brief Método que visa trasnformar o valor da string passada
 *  @param input tipo string
 *  @return output tipo string
 */
string CPInfo::escapeString(string input) {
    string output;

    for (auto c : input) {
        if (isprint((unsigned char) c)) {
            output += c;
        }
        else {
            stringstream stream;
            stream << uppercase << hex << (unsigned int)(unsigned char)(c);
            string code = stream.str();
            output += string("\\x") + (code.size() < 2 ? "0" : "") + code;
        }
    }
    return output;
}

/** @class CPInfo::getUTF8
 *  @brief Método que visa pegar a string UTF-8
 *  @param input tipo string
 *  @return output tipo string chamada de método
 */

string CPInfo::getUTF8(vector<CPInfo*> constantPool) {
    string str = (char*)CONSTANT_Utf8_info.bytes;
    return escapeString(str);
}

/** @class CPInfo::getClassUTF8
 *  @brief Método que visa nome da classe de contantPool
 *  @param constantPool vetor de CPInfo
 *  @return nameInfo->UTF8 tipo string
 */

string CPInfo::getClassUTF8(vector<CPInfo*> constantPool) {
    CPInfo *nameInfo = constantPool[CONSTANT_Class_info.name_index-1];
    return nameInfo->getUTF8(constantPool);
}

/** @class CPInfo::getStringUTF8
 *  @brief Método que visa armazenar o valor da string da constantPool
 *  @param constantPool vetor de CPInfo
 *  @return strinfInfo->getUTF8 tipo string
 */

string CPInfo::getStringUTF8(vector<CPInfo*> constantPool) {
    CPInfo *stringInfo = constantPool[CONSTANT_String_info.string_index-1];
    return stringInfo->getUTF8(constantPool);
}

/** @class CPInfo::getFieldrefUTF8
 *  @brief Método que visa armazenar o valor em UTF8 das fields da constantPool
 *  @param constantPool vetor de CPInfo
 *  @return ClassName e nameAndType par do tipo string
 */

pair<string,string> CPInfo::getFieldrefUTF8(vector<CPInfo*> constantPool) {
    CPInfo *classInfo = constantPool[CONSTANT_Fieldref_info.class_index-1];
    CPInfo *nameAndTypeInfo = constantPool[CONSTANT_Fieldref_info.name_and_type_index-1];
    string className = classInfo->getClassUTF8(constantPool);
    string nameAndType = nameAndTypeInfo->getNameAndTypeUTF8(constantPool).first + " : " + nameAndTypeInfo->getNameAndTypeUTF8(constantPool).second;
    return make_pair(className, nameAndType);
}

/** @class CPInfo::getMethodrefUTF8
 *  @brief Método que visa armazenar o valor em UTF8 dos methods da constantPool
 *  @param constantPool vetor de CPInfo
 *  @return ClassName e nameAndType par do tipo string
 */

pair<string,string> CPInfo::getMethodrefUTF8(vector<CPInfo*> constantPool) {
    CPInfo *classInfo = constantPool[CONSTANT_Methodref_info.class_index-1];
    CPInfo *nameAndTypeInfo = constantPool[CONSTANT_Methodref_info.name_and_type_index-1];
    string className = classInfo->getClassUTF8(constantPool);
    string nameAndType = nameAndTypeInfo->getNameAndTypeUTF8(constantPool).first + " : " + nameAndTypeInfo->getNameAndTypeUTF8(constantPool).second;
    return make_pair(className, nameAndType);
}

/** @class CPInfo::getInterfaceMethodrefUTF8
 *  @brief Método que visa armazenar o valor em UTF8 das intefaces dos metodos da constantPool
 *  @param constantPool vetor de CPInfo
 *  @return ClassName e nameAndType par do tipo string
 */

pair<string,string> CPInfo::getInterfaceMethodrefUTF8(vector<CPInfo*> constantPool) {
    CPInfo *classInfo = constantPool[CONSTANT_InterfaceMethodref_info.class_index-1];
    CPInfo *nameAndTypeInfo = constantPool[CONSTANT_InterfaceMethodref_info.name_and_type_index-1];
    string className = classInfo->getClassUTF8(constantPool);
    string nameAndType = nameAndTypeInfo->getNameAndTypeUTF8(constantPool).first + " : " + nameAndTypeInfo->getNameAndTypeUTF8(constantPool).second;
    return make_pair(className, nameAndType);
}

/** @class CPInfo::getNameAndTypeUTF8
 *  @brief Método que visa armazenar o valor em UTF8 do nome e tipo da constantPool
 *  @param constantPool vetor de CPInfo
 *  @return name e descriptor par do tipo string
 */

pair<string,string> CPInfo::getNameAndTypeUTF8(vector<CPInfo*> constantPool) {
    CPInfo *nameInfo = constantPool[CONSTANT_NameAndType_info.name_index-1];
    CPInfo *descriptorInfo = constantPool[CONSTANT_NameAndType_info.descriptor_index-1];
    string name = nameInfo->getUTF8(constantPool);
    string descriptor = descriptorInfo->getUTF8(constantPool);
    return make_pair(name, descriptor);
}


/** @class CPInfo::getInfo
 *  @brief Método que visa armazenar o valor do par de acordo com a tag passada
 *  @param constantPool vetor de CPInfo
 *  @return info par de strings
 */
pair<string,string> CPInfo::getInfo(vector<CPInfo*> constantPool) {
    pair<string,string> info;
    string str;
    switch(tag) {
    case CONSTANT_Utf8:
        info =  make_pair(getUTF8(constantPool), "");
        break;
    case CONSTANT_Class:
        info = make_pair(getClassUTF8(constantPool), "");
        break;
    case CONSTANT_Fieldref:
        info = getFieldrefUTF8(constantPool);
        break;
    case CONSTANT_Methodref:
        info = getMethodrefUTF8(constantPool);
        break;
    case CONSTANT_NameAndType:
        info = getNameAndTypeUTF8(constantPool);
        break;
    case CONSTANT_InterfaceMethodref:
        info = getInterfaceMethodrefUTF8(constantPool);
        break;
    case CONSTANT_String:
        str = (char*)constantPool[CONSTANT_String_info.string_index-1]->CONSTANT_Utf8_info.bytes;
        info = make_pair(getStringUTF8(constantPool), str);
        break;
    case CONSTANT_Integer:
        info = make_pair(to_string(getIntegerInfo().bytes), "");
        break;
    case CONSTANT_Float:
        info = make_pair(to_string(getFloatNumber()), "");
        break;
    case CONSTANT_Long:
        info = make_pair(to_string(getLongNumber()), "");
        break;
    case CONSTANT_Double:
        info = make_pair(to_string(getDoubleNumber()), "");
        break;
    default:
        cout << "Erro! Tag nao reconhecida:" << tag << endl;
        exit(0);
        break;
    }

    return info;
}


/** @class CPInfo::getFloatNumber
 *  @brief Método que visa armazenar um valor de float
 *  @param constantPool vetor de CPInfo
 *  @return num tipo float
 */
float CPInfo::getFloatNumber() {
    uint32_t bytes = CONSTANT_Float_info.bytes;
    float num;
    memcpy(&num, &bytes, sizeof(float));
    return num;
}

/** @class CPInfo::getLongNumber
 *  @brief Método que visa armazenar o valor de um long
 *  @param constantPool vetor de CPInfo
 *  @return longNumber tipo int64_t
 */

int64_t CPInfo::getLongNumber() {
    return ((uint64_t)this->CONSTANT_Long_info.high_bytes << 32) | this->CONSTANT_Long_info.low_bytes;
}


/** @class CPInfo::getDoubleNumber
 *  @brief Método que visa armazenar o valor de um double
 *  @param constantPool vetor de CPInfo
 *  @return info par de strings
 */
double CPInfo::getDoubleNumber() {
    uint64_t aux = ((uint64_t)this->CONSTANT_Long_info.high_bytes << 32) | this->CONSTANT_Long_info.low_bytes;
    double num;
    memcpy(&num, &aux, sizeof(double));
    return num;
}