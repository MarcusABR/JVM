/**
 * @file ExecutionEngine.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Biblioteca de definição com metodos e atributos para execução da jvm 
 * @details A biblioteca ExecutionEngine.hpp contém as variaveis privadas de uso da execution engine, bem como seus metodos
 * para execução da jvm
 * @see ExecutionEngine.cpp
 */

#ifndef EXECUTION_ENGINE_H_INCLUDED
#define EXECUTION_ENGINE_H_INCLUDED

#include <string>
#include "ClassFile.hpp"
#include "ClassLoader.hpp"
#include "MethodArea.hpp"
#include "InstructionSet.hpp"
#include "JavaVirtualMachineThread.hpp"
/** @class ExecutionEngine
*   @brief Classe que contém a estrutura para o interpretador funcionar; 
*/
class ExecutionEngine {
private:
    string mainClassFileName;
    InstructionSet * instructionSet;
    MethodInfo* mainMethod;
    MethodArea* methodArea;
    void findMainMethod();
    void executeInstruction(uint8_t*, uint32_t, Frame*);
public:
    ExecutionEngine(ClassFile*, MethodArea*, InstructionSet*);
    void execute();
};

#endif