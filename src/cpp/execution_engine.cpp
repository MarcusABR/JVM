/**
 * @file execution_engine.cpp
 * @author André Larrosa Chimpliganond - 190010321
 * @author Marcus Vinicius Oliveira de Abrantes - 190034084
 * @author  Matheus Barbosa e Silva - 190113987
 * @author Moises Felipe Jaco Andrade de Lima - 190018364 
 * @author Thiago Elias dos Reis - 190126892
 * @brief Definicoes da classe ExecutionEngine
 * @details Define busca de metodo principal e funcao execute do motor.
**/

#include "../hpp/execution_engine.hpp"
#include "../hpp/leitor_exibidor.hpp"

ExecutionEngine::ExecutionEngine(class_file* classFile, InstructionSet* instructionSet) {
    this->instructionSet = instructionSet;
    
    this->classFile = classFile;

    findMainMethod();
}

void ExecutionEngine::findMainMethod() {
    cp_info_vector constantPool = classFile->getConstantPool();
    
    vector<method_info> methods = classFile->getMethods();
    int i;
    bool foundMain = false;

    for (i = 0; i < classFile->getMethodsCount() && !foundMain; i++) {
        method_info* method = &(methods[i]);
        auto name_idx = to_cp_info(constantPool[method->name_idx - 1])->_name_and_type->name_idx;
        auto method_name = *(to_cp_info(constantPool[name_idx - 1])->_utf8);
        string name = exibir_utf8(method_name);
        
        auto descriptor_idx = to_cp_info(constantPool[method->descriptor_idx - 1])->_name_and_type->descriptor_idx;
        auto method_descriptor = *(to_cp_info(constantPool[descriptor_idx - 1])->_utf8);
        string descriptor = exibir_utf8(method_descriptor);


        if (name.compare("main") == 0 && descriptor.compare("([Ljava/lang/String;)V") == 0) {
            foundMain = true;
            this->mainMethod = method;
        }
    }

    if (!foundMain) {
        printf("A main nao foi encontrada no arquivo especificado!\n");
        exit(0);
    }
}

void ExecutionEngine::execute() {
    cp_info_vector constantPool = classFile->getConstantPool();
    
    JavaVirtualMachineThread jvmThread;
    Frame mainFrame(constantPool, this->mainMethod, jvmThread.getJVMStack());
    Instruction* instructions = instructionSet->getInstructionSet();

    jvmThread.pushToJVMStack(mainFrame);

    do {
        Frame* currentFrame = jvmThread.getCurrentFrame();
        uint8_t* bytecode = currentFrame->getCode();
        uint32_t bytecodeLength = currentFrame->getCodeLength();
        uint8_t opcode = bytecode[jvmThread.pc];
        Instruction instruction = instructions[opcode];

        jvmThread.pc = instruction.func(currentFrame);

        if (instruction.getMnemonic().compare("return") == 0) {
            jvmThread.popFromJVMStack();
            if (!jvmThread.isJVMStackEmpty()) {
                jvmThread.pc = jvmThread.getCurrentFrame()->localPC;
            }
        }
    } while (!jvmThread.isJVMStackEmpty());
}