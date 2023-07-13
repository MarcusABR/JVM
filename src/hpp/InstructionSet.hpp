/**
 * @file InstructionSet.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Descreve a classe InstructionSet
 * @details A classe InstructionSet contém como atributos todas as instruções JVM, implementadas ou não. Possui o atributo instructionsCount para  a quantidade real de instruções implementadas.
 * @see InstructionSet.cpp
 */
 
#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <vector>
#include "Instruction.hpp"
#include "ClassLoader.hpp"

using namespace std;

class InstructionSet {
private:
    Instruction instructionSet[256];
    uint32_t instructionsCount;
public:
    InstructionSet(ClassLoader*);
    Instruction * getInstructionSet() {
        return instructionSet;
    }
    uint32_t getInstructionsCount() {
        return instructionsCount;
    }
};

#endif