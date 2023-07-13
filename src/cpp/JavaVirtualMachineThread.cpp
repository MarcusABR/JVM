/**
 * @file JavaVirtualMachineThread.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Contém métodos para manipulação da pilha de frames  
 * @see JavaVirtualMachineThread.hpp
 */

#include "../hpp/JavaVirtualMachineThread.hpp"

/** @fn JavaVirtualMachineThread::JavaVirtualMachineThread
 *  @brief Construtor do JavaVirtualMachineThread
 */
JavaVirtualMachineThread::JavaVirtualMachineThread() {
    this->pc = 0;
}

/** @class JavaVirtualMachineThread::pushToJVMStack
 *  @brief Método que armazena o frame na pilha
 *  @param frame do tipo Frame
 */
void JavaVirtualMachineThread::pushToJVMStack(Frame frame) {
    this->javaVirtualMachineStack.push(frame);
}

/** @class JavaVirtualMachineThread::popFromJVMStack
 *  @brief Método que retira o frame do topo da pilha
 */

void JavaVirtualMachineThread::popFromJVMStack() {
    this->javaVirtualMachineStack.pop();
}

/** @class JavaVirtualMachineThread::incrementPcBy
 *  @brief Método que incrementa o PC
 *  @param increment do tipo uint32_t
 */
void JavaVirtualMachineThread::incrementPcBy(uint32_t increment) {
    this->pc += increment;
}