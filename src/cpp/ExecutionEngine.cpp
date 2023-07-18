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
#include "../include/dump_class_file.hpp"

/** @fn ExecutionEngine::ExecutionEngine
 *  @brief Construtor
 *  @param classFile do tipo ClassFile @param methodArea do tipo MethodArea @param instructionSet InstructionSet
 */
//ExecutionEngine::ExecutionEngine(class_file* classFile, MethodArea* methodArea, InstructionSet* instructionSet) {
ExecutionEngine::ExecutionEngine(class_file* classFile, InstructionSet* instructionSet) {
    // vector<CPInfo*>constantPool = classFile->getConstantPool();
    // string name = constantPool[classFile->getThisClass()-1]->getInfo(constantPool).first;

    //this->methodArea = methodArea;
    this->instructionSet = instructionSet;
    
    //this->mainClassFileName = name;
    // nome_arquivo passado como argumento
    // int start_position_to_erase = nome_arquivo.find(".class");
    // nome_arquivo.erase(start_position_to_erase, 6);
    // this->mainClassFileName = nome_arquivo ;
    
    // atributo class_file
    this->classFile = classFile;

    findMainMethod();
}

/** @class ExecutionEngine::findMainMethod
 *  @brief Método com o objetivo de encontrar a função main, já que é por ela que começa a execução do interpretador
 */
void ExecutionEngine::findMainMethod() {
    //class_file* mainClassFile = methodArea->getClassFile(mainClassFileName);
    
    //vector<CPInfo*> constantPool = mainClassFile->getConstantPool();
    // typedef vector<shared_ptr<CP_Item>> cp_info_vector;
    cp_info_vector constantPool = classFile->getConstantPool();
    
    //vector<MethodInfo*> methods = mainClassFile->getMethods();
    vector<method_info> methods = classFile->getMethods();
    int i;
    bool foundMain = false;

    //for (i = 0; i < mainClassFile->getMethodsCount() && !foundMain; i++) {
    for (i = 0; i < classFile->getMethodsCount() && !foundMain; i++) {
        //MethodInfo* method = methods[i];
        method_info* method = &(methods[i]);
        
        //uint16_t nameIndex = method->getNameIndex();
        //uint16_t nameIndex = method->name_idx;
        
        //uint16_t descriptorIndex = method->getDescriptorIndex();
        //uint16_t descriptorIndex = method->descriptor_idx;
        
        //string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
        auto name_idx = to_cp_info(constantPool[method->name_idx - 1])->_name_and_type->name_idx;
        auto method_name = *(to_cp_info(constantPool[name_idx - 1])->_utf8);
        string name = get_utf8_content(method_name);
        
        //string descriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
        auto descriptor_idx = to_cp_info(constantPool[method->descriptor_idx - 1])->_name_and_type->descriptor_idx;
        auto method_descriptor = *(to_cp_info(constantPool[descriptor_idx - 1])->_utf8);
        string descriptor = get_utf8_content(method_descriptor);


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
    // class_file* mainClassFile = methodArea->getClassFile(mainClassFileName);
    // vector<CPInfo*> constantPool = mainClassFile->getConstantPool();
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