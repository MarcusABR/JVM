/**
 * @file ClassPrinter.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Atributos a serem usados na execuçao da JVM 
 * @details A biblioteca ClassPrinter.hpp contém o arquivo com a descrição das funções
 * utilizadas para exibir os atributos de um arquivo.class
 * @see ClassPrinter.cpp
 */

#ifndef ___CLASSPRINTER_H___
#define ___CLASSPRINTER_H___

/*definicoes para limpar a tela e promover ilusao de movimento*/
#if defined(_WIN32)					
	#define CLEAR system("cls");
#else
	#define CLEAR system("clear");
#endif

#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <utility>
#include "ClassFile.hpp"
#include "InstructionSet.hpp"

using namespace std;
/** @class ClassPrinter
*   @brief Classe que contém a chamada de todos os métodos que visam mostrar na tela os campos do classFile; 
*   
*/
class ClassPrinter {
private:
    class_file classFile;
    InstructionSet * instructionSet;
    string interpretClassFlags(uint16_t);
    string interpretMethodFlags(uint16_t);
    string interpretFieldFlags(uint16_t);
    void printGeneralInformation();
    void printConstantPool();
    void printInterfaces();
    void printFields();
    void printMethods();
    void printAttributes(AttributeInfo*, uint16_t);
    void printClassFileAttributes();

    void printSourceFileInfo(SourceFileAttribute*);
    void printConstantValueInfo(ConstantValueAttribute*);
    void printCodeInfo(CodeAttribute*);
    void printCodeExceptionTableInfo(ExceptionHandler*, uint16_t);
    void printLineNumberTableInfo(LineNumberTableAttribute*);
    void printLocalVariableTableInfo(LocalVariableTableAttribute*);
    void printExceptionsInfo(ExceptionsAttribute*);
    void printInnerClassesInfo(InnerClassesAttribute*);

public:
    ClassPrinter(class_file classFile, InstructionSet * instructionSet);
    void print();
    //nao mudei o nome da funcao de baixo, dps nois ve como fica
    string Flag_names(int flag_byte, int parametro);
};

#endif