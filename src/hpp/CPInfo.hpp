// /**
//  * @file CPIInfo.hpp
//  * @author Ayssa Giovanna de Oliveira Marques - 170100065
//  * @author Fernanda Macedo de Sousa - 170010058
//  * @author Gabriel dos Santos Martins - 150126298
//  * @author Lucas Raphael Ferreira de Miranda - 180046799 
//  * @author Otávio Souza de Oliveira 150143401
//  * @brief Atributos a serem usados na execuçao da JVM 
//  * @details A biblioteca CPInfo.hpp contém as informações as que servem de referência as instruções.
//  * 
//  * @see AttributeInfo.cpp
//  */

// #ifndef CPINFO_H_INCLUDED
// #define CPINFO_H_INCLUDED

// #include <cstdint>
// #include <cstring>
// #include <fstream>
// #include <iostream>
// #include <vector>
// #include <utility>
// #include <sstream>

// using namespace std;

// typedef struct {
//     uint16_t name_index;
// } ConstantClassInfo;

// typedef struct {
//     uint16_t class_index;
//     uint16_t name_and_type_index;
// } ConstantFieldrefInfo;

// typedef struct {
//     uint16_t class_index;
//     uint16_t name_and_type_index;
// } ConstantMethodrefInfo;

// typedef struct {
//     uint16_t class_index;
//     uint16_t name_and_type_index;
// } ConstantInterfaceMethodrefInfo;

// typedef struct {
//     uint16_t string_index;
// } ConstantStringInfo;

// typedef struct {
//     uint32_t bytes;
// } ConstantIntegerInfo;

// typedef struct {
//     uint32_t bytes;
// } ConstantFloatInfo;

// typedef struct {
//     uint32_t high_bytes;
//     uint32_t low_bytes;
// } ConstantLongInfo;

// typedef struct {
//     uint32_t high_bytes;
//     uint32_t low_bytes;
// } ConstantDoubleInfo;

// typedef struct {
//     uint16_t name_index;
//     uint16_t descriptor_index;
// } ConstantNameAndTypeInfo;

// typedef struct {
//     uint16_t length;
//     uint8_t *bytes;
// } ConstantUTF8Info;

// typedef struct {
//     uint8_t reference_kind;
//     uint16_t reference_index;
// } ConstantMethodHandleInfo;

// typedef struct {
//     uint16_t descriptor_index;
// } ConstantMethodTypeInfo;

// typedef struct {
//     uint16_t bootstrap_method_attr_index;
//     uint16_t name_and_type_index;
// } ConstantInvokeDynamicInfo;
// /**
// *   @class CpInfo
// *   @brief Classe contém tag(uint8) e union que será um tipo diferente dependendo de qual tag que será passada;
// */

// class CPInfo {
// private:
//     uint8_t tag;
//     union {
//         ConstantClassInfo CONSTANT_Class_info;
//         ConstantFieldrefInfo CONSTANT_Fieldref_info;
//         ConstantMethodrefInfo CONSTANT_Methodref_info;
//         ConstantInterfaceMethodrefInfo CONSTANT_InterfaceMethodref_info;
//         ConstantStringInfo CONSTANT_String_info;
//         ConstantIntegerInfo CONSTANT_Integer_info;
//         ConstantFloatInfo CONSTANT_Float_info;
//         ConstantLongInfo CONSTANT_Long_info;
//         ConstantDoubleInfo CONSTANT_Double_info;
//         ConstantNameAndTypeInfo CONSTANT_NameAndType_info;
//         ConstantUTF8Info CONSTANT_Utf8_info;
//         ConstantMethodHandleInfo CONSTANT_MethodHandle_info;
//         ConstantMethodTypeInfo CONSTANT_MethodType_info;
//         ConstantInvokeDynamicInfo CONSTANT_InvokeDynamic_info;
//     };
//     string escapeString(string input);
//     string getUTF8(vector<CPInfo*> constantPool);
//     string getClassUTF8(vector<CPInfo*> constantPool);
//     string getStringUTF8(vector<CPInfo*> constantPool);
//     pair<string,string> getFieldrefUTF8(vector<CPInfo*> constantPool);
//     pair<string,string> getMethodrefUTF8(vector<CPInfo*> constantPool);
//     pair<string,string> getInterfaceMethodrefUTF8(vector<CPInfo*> constantPool);
//     pair<string,string> getNameAndTypeUTF8(vector<CPInfo*> constantPool);
//     pair<string,string> getDoubleUTF8(vector<CPInfo*> constantPool);
// public:
//     static const uint8_t CONSTANT_Class = 7;
//     static const uint8_t CONSTANT_Fieldref = 9;
//     static const uint8_t CONSTANT_Methodref = 10;
//     static const uint8_t CONSTANT_InterfaceMethodref = 11;
//     static const uint8_t CONSTANT_String = 8;
//     static const uint8_t CONSTANT_Integer = 3;
//     static const uint8_t CONSTANT_Float = 4;
//     static const uint8_t CONSTANT_Long = 5;
//     static const uint8_t CONSTANT_Double = 6;
//     static const uint8_t CONSTANT_NameAndType = 12;
//     static const uint8_t CONSTANT_Utf8 = 1;
//     static const uint8_t CONSTANT_MethodHandle = 15;
//     static const uint8_t CONSTANT_MethodType = 16;
//     static const uint8_t CONSTANT_InvokeDynamic = 18;
//     static const uint8_t CONSTANT_Empty = 0;

//     CPInfo();
//     ~CPInfo();
//     void read(FILE *fp);
//     void setTag(uint8_t tag);
//     pair<string,string> getInfo(vector<CPInfo*> constantPool);
//     float getFloatNumber();
//     int64_t getLongNumber();
//     double getDoubleNumber();

//     uint8_t getTag() {
//         return this->tag;
//     }

//     ConstantClassInfo getClassInfo() {
//         return this->CONSTANT_Class_info;
//     }

//     ConstantFieldrefInfo getFieldrefInfo() {
//         return this->CONSTANT_Fieldref_info;
//     }

//     ConstantMethodrefInfo getMethodrefInfo() {
//         return this->CONSTANT_Methodref_info;
//     }

//     ConstantInterfaceMethodrefInfo getInterfaceMethodrefInfo() {
//         return this->CONSTANT_InterfaceMethodref_info;
//     }

//     ConstantStringInfo getStringInfo() {
//         return this->CONSTANT_String_info;
//     }

//     ConstantIntegerInfo getIntegerInfo() {
//         return this->CONSTANT_Integer_info;
//     }

//     ConstantFloatInfo getFloatInfo() {
//         return this->CONSTANT_Float_info;
//     }

//     ConstantLongInfo getLongInfo() {
//         return this->CONSTANT_Long_info;
//     }

//     ConstantDoubleInfo getDoubleInfo() {
//         return this->CONSTANT_Double_info;
//     }

//     ConstantNameAndTypeInfo getNameAndTypeInfo() {
//         return this->CONSTANT_NameAndType_info;
//     }

//     ConstantUTF8Info getUTF8Info() {
//         return this->CONSTANT_Utf8_info;
//     }

//     ConstantMethodHandleInfo getMethodHandleInfo() {
//         return this->CONSTANT_MethodHandle_info;
//     }

//     ConstantMethodTypeInfo getMethodTypeInfo() {
//         return this->CONSTANT_MethodType_info;
//     }

//     ConstantInvokeDynamicInfo getInvokeDynamicInfo() {
//         return this->CONSTANT_InvokeDynamic_info;
//     }
// };

// #endif