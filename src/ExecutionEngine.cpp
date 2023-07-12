/**
 * @file ExecutionEngine.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Arquivo de implementação das funções da ExecutionEngine
 * @see ExecutionEngine.hpp
 */

#include "../hpp/ExecutionEngine.hpp"

/** @fn ExecutionEngine::ExecutionEngine
 *  @brief Construtor
 *  @param classFile do tipo ClassFile @param methodArea do tipo MethodArea @param instructionSet InstructionSet
 */
ExecutionEngine::ExecutionEngine(ClassFile* classFile, MethodArea* methodArea, InstructionSet* instructionSet) {
    vector<CPInfo*>constantPool = classFile->getConstantPool();
    string name = constantPool[classFile->getThisClass()-1]->getInfo(constantPool).first;

    this->methodArea = methodArea;
    this->instructionSet = instructionSet;
    this->mainClassFileName = name;
    findMainMethod();
}

/** @class ExecutionEngine::findMainMethod
 *  @brief Método com o objetivo de encontrar a função main, já que é por ela que começa a execução do interpretador
 */
void ExecutionEngine::findMainMethod() {
    ClassFile* mainClassFile = methodArea->getClassFile(mainClassFileName);
    vector<CPInfo*> constantPool = mainClassFile->getConstantPool();
    vector<MethodInfo*> methods = mainClassFile->getMethods();
    int i;
    bool foundMain = false;

    for (i = 0; i < mainClassFile->getMethodsCount() && !foundMain; i++) {
        MethodInfo* method = methods[i];
        uint16_t nameIndex = method->getNameIndex();
        uint16_t descriptorIndex = method->getDescriptorIndex();
        string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
        string descriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
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

/** @class ExecutionEngine::execute
 *  @brief Método com o objetivo de executar cada frame que está guardado na pilha
 */

void ExecutionEngine::execute() {
    ClassFile* mainClassFile = methodArea->getClassFile(mainClassFileName);
    vector<CPInfo*> constantPool = mainClassFile->getConstantPool();
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

        //Para debug
        // cout << "Executando: " << jvmThread.pc << " " << instruction.getMnemonic() << " " << currentFrame << " " << instruction.func << endl;
        jvmThread.pc = instruction.func(currentFrame);

        if (instruction.getMnemonic().compare("return") == 0) {
            jvmThread.popFromJVMStack();
            if (!jvmThread.isJVMStackEmpty()) {
                jvmThread.pc = jvmThread.getCurrentFrame()->localPC;
            }
        }
    } while (!jvmThread.isJVMStackEmpty());
}