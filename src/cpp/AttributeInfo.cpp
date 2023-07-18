// /**
//  * @file AttributeInfo.cpp
//  * @author Ayssa Giovanna de Oliveira Marques - 170100065
//  * @author Fernanda Macedo de Sousa - 170010058
//  * @author Gabriel dos Santos Martins - 150126298
//  * @author Lucas Raphael Ferreira de Miranda - 180046799 
//  * @author Otávio Souza de Oliveira 150143401
//  * @brief Arquivo de implementação das funções do Attribute Info
//  * @see AttributeInfo.hpp
//  */

// /** @file AttributeInfo.cpp
//  *  @brief Métodos com o objetivo de adquirir as informações dos atributos do arquivo .class 
//  *  @bug No known bugs.
//  */
// #include "../hpp/AttributeInfo.hpp"


// /** @class ConstantValueAttribute::read
//  *  @brief Método ler os valores das constantes dos atributos
//  *  @param fp ponteiro para o arquivo .class
//  */
// void ConstantValueAttribute::read(FILE *fp) {
//     ByteReader<uint16_t> twoByteReader;
//     constantValueIndex = twoByteReader.byteCatch(fp);
// }

// /** @class LineNumber::read
//  *  @brief Método visando ler os valores do LineNumber
//  *  @param fp ponteiro para o arquivo .class
//  */

// void LineNumber::read(FILE * fp) {
//     ByteReader<uint16_t> twoByteReader;
//     startPC = twoByteReader.byteCatch(fp);
//     lineNumber = twoByteReader.byteCatch(fp);
// }
// /** @class LineNumber::read
//  *  @brief Método visando ler os valores da tabela de atributos do LineNumber
//  *  @param fp ponteiro para o arquivo .class
//  */

// void LineNumberTableAttribute::read(FILE *fp) {
//     ByteReader<uint16_t> twoByteReader;
//     lineNumberTableLength = twoByteReader.byteCatch(fp);
//     lineNumberTable = (LineNumber*)calloc(lineNumberTableLength, sizeof(LineNumber));

//     for (int i = 0; i < lineNumberTableLength; i++) {
//         lineNumberTable[i].read(fp);
//     }
// }
// /** @class ExceptionHandler::read
//  *  @brief Método que visa armazenar os valores das exceções
//  *  @param fp ponteiro para o arquivo .class
//  */

// void ExceptionHandler::read(FILE *fp) {
//     ByteReader<uint16_t> twoByteReader;

//     startPC = twoByteReader.byteCatch(fp);
//     endPC = twoByteReader.byteCatch(fp);
//     handlerPC = twoByteReader.byteCatch(fp);
//     catchType = twoByteReader.byteCatch(fp);
// }
// /** @class CodeAttribute::read
//  *  @brief Método que visa armazenar os valores dos code dos atributos
//  *  @param fp ponteiro para o arquivo .class
//  */

// void CodeAttribute::read(FILE *fp, vector<CPInfo*> constantPool) {
//     ByteReader<uint8_t> oneByteReader;
//     ByteReader<uint16_t> twoByteReader;
//     ByteReader<uint32_t> fourByteReader;

//     maxStack = twoByteReader.byteCatch(fp);
//     maxLocals = twoByteReader.byteCatch(fp);
//     codeLength = fourByteReader.byteCatch(fp);

//     code = (uint8_t *)calloc(codeLength, sizeof(uint8_t));
//     for (int i = 0; i < codeLength; i++){
//         code[i] = oneByteReader.byteCatch(fp);
//     }

//     exceptionTableLength = twoByteReader.byteCatch(fp);

//     exceptionTable = (ExceptionHandler*)calloc(exceptionTableLength, sizeof(ExceptionHandler));
//     for (int i = 0; i < exceptionTableLength; i++){
//         exceptionTable[i].read(fp);
//     }

//     attributesCount = twoByteReader.byteCatch(fp);
//     attributes = (AttributeInfo *)calloc(attributesCount, sizeof(AttributeInfo));
//     for (int i = 0; i < attributesCount; i++){
//         attributes[i].read(fp, constantPool);
//     }
// }
// /** @class ClassInfo::read
//  *  @brief Método que visa armazenar os valores das informações das classes
//  *  @param fp ponteiro para o arquivo .class
//  */

// void ClassInfo::read(FILE * fp) {
//     ByteReader<uint16_t> twoByteReader;
//     innerClassInfoIndex = twoByteReader.byteCatch(fp);
//     outerClassInfoIndex = twoByteReader.byteCatch(fp);
//     innerNameIndex = twoByteReader.byteCatch(fp);
//     innerClassAccessFlags = twoByteReader.byteCatch(fp);
// }
// /** @class InnerClassesAttribute::read
//  *  @brief Método que visa armazenar os valores do InnerClassesAttribute
//  *  @param fp ponteiro para o arquivo .class
//  */

// void InnerClassesAttribute::read(FILE *fp) {
//     ByteReader<uint16_t> twoByteReader;
//     numberOfClasses = twoByteReader.byteCatch(fp);
//     classes = (ClassInfo*)calloc(numberOfClasses, sizeof(ClassInfo));

//     for (int i = 0; i < numberOfClasses; i++) {
//         classes[i].read(fp);
//     }   
// }
// /** @class ExceptionsAttribute::read
//  *  @brief Método que visa armazenar os valores das exceções dos atributos
//  *  @param fp ponteiro para o arquivo .class
//  */

// void ExceptionsAttribute::read(FILE *fp) {
//     ByteReader<uint16_t> twoByteReader;
//     numberOfExceptions = twoByteReader.byteCatch(fp);
//     execeptionIndexTable = (uint16_t *)calloc(numberOfExceptions, sizeof(uint16_t));
//     for (int i = 0; i < numberOfExceptions; i++) {
//         execeptionIndexTable[i] = twoByteReader.byteCatch(fp);
//     }
// }

// /** @class ExceptionsAttribute::read
//  *  @brief Método que visa armazenar os valores do SourceFileAttribute
//  *  @param fp ponteiro para o arquivo .class
//  */
// void SourceFileAttribute::read(FILE * fp) {
//     ByteReader<uint16_t> twoByteReader;
//     sourcefileIndex = twoByteReader.byteCatch(fp);
// }

// /** @class LocalVariable::read
//  *  @brief Método que visa armazenar os valores das variáveis locais
//  *  @param fp ponteiro para o arquivo .class
//  */
// void LocalVariable::read(FILE * fp) {
//     ByteReader<uint16_t> twoByteReader;

//     startPC = twoByteReader.byteCatch(fp);
//     length = twoByteReader.byteCatch(fp);
//     nameIndex = twoByteReader.byteCatch(fp);
//     descriptorIndex = twoByteReader.byteCatch(fp);
//     index = twoByteReader.byteCatch(fp);
// }

// /** @class LocalVariableTableAttribute::read
//  *  @brief Método que visa armazenar os valores das variáveis locais da tabela de atributos
//  *  @param fp ponteiro para o arquivo .class
//  */
// void LocalVariableTableAttribute::read(FILE *fp) {
//     ByteReader<uint16_t> twoByteReader;
//     localVariableTableLength = twoByteReader.byteCatch(fp);

//     localVariableTable = (LocalVariable*)calloc(localVariableTableLength, sizeof(LocalVariable));

//     for (int i = 0; i < localVariableTableLength; i++) {
//         localVariableTable[i].read(fp);
//     }
// }

// /** @class AttributeInfo::read
//  *  @brief Método que visa armazenar os valores das informações dos atributos
//  *  @param fp ponteiro para o arquivo .class @param constantPool vetor do tipo CPInfo
//  */
// void AttributeInfo::read(FILE * fp, std::vector<CPInfo *> constantPool){
//     CPInfo* cpInfo;
//     ByteReader<uint8_t> oneByteReader;
//     ByteReader<uint16_t> twoByteReader;
//     ByteReader<uint32_t> fourByteReader;

//     attributeNameIndex = twoByteReader.byteCatch(fp);
//     attributeLength = fourByteReader.byteCatch(fp);
//     cpInfo = constantPool[attributeNameIndex-1];
//     string attributeName = cpInfo->getInfo(constantPool).first;

//     if(attributeName == "Code"){
//         code.read(fp, constantPool);
//     }
//     else if(attributeName == "ConstantValue") {
//         constantValue.read(fp);
//     }
//     else if(attributeName == "Exceptions") {
//         exceptions.read(fp);
//     }
//     else if(attributeName == "InnerClasses") {
//         innerClasses.read(fp);
//     }
//     else if(attributeName == "SourceFile") {
//         sourceFile.read(fp);
//     }
//     else if(attributeName == "LineNumberTable") {
//         lineNumberTable.read(fp);
//     }
//     else if (attributeName == "LocalVariableTable") {
//         localVariableTable.read(fp);
//     }
//     else {
//         info = (uint8_t*)calloc(attributeLength, sizeof(uint8_t));
//         for(int i = 0; i < attributeLength; i++) {
//             info[i] = oneByteReader.byteCatch(fp);
//         }
//     }
// }