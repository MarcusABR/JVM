#ifndef EXECUTION_ENGINE_H_INCLUDED
#define EXECUTION_ENGINE_H_INCLUDED

#include <string>
#include "class_file.hpp"
#include "class_loader.hpp"
#include "method_area.hpp"
#include "instruction_set.hpp"
#include "java_virtual_machine_thread.hpp"

class ExecutionEngine {
private:
    string mainClassFileName;
    InstructionSet * instructionSet;
    //MethodInfo* mainMethod;
    method_info* mainMethod;
    MethodArea* methodArea;
    // ponteiro para aquivo de classe
    class_file* classFile;
    void findMainMethod();
    void executeInstruction(uint8_t*, uint32_t, Frame*);
public:
    //ExecutionEngine(ClassFile*, MethodArea*, InstructionSet*);
    ExecutionEngine(class_file*, InstructionSet*);
    void execute();
};

#endif