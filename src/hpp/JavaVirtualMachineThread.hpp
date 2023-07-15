/**
 * @file JavaVirtualMachineThread.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Definição de thread da JVM. 
 * @details A biblioteca JavaVirtualMachineThread.hpp possui como propósito executar métodos correntes, nativos e não nativos,
 * manipulando variáveis locais e participando de chamadaa e retornos de métodos. 
 * É a unidade básica de uso do processador, o fluxo de execução. A fornece suporte à criação, escalonamento e gerência de threads.
 * 
 * @see JavaVirtualMachineThread.cpp
 * @see Frame.hpp
 */

#ifndef JAVA_VIRTUAL_MACHINE_THREAD_H_INCLUDED
#define JAVA_VIRTUAL_MACHINE_THREAD_H_INCLUDED

#include <stack>
#include "Frame.hpp"

using namespace std;
/** @class JavaVirtualMachineThread
*   @brief Classe que contém toda a estrutura de manipulação da pilha de frames
*/
class JavaVirtualMachineThread {
private:
    stack<Frame> javaVirtualMachineStack;
public:
    uint32_t pc;
    JavaVirtualMachineThread();
    void pushToJVMStack(Frame);
    void popFromJVMStack();
    void incrementPcBy(uint32_t);

    Frame* getCurrentFrame() {
        return &(this->javaVirtualMachineStack.top());
    }
    bool isJVMStackEmpty() {
        return this->javaVirtualMachineStack.empty();
    }
    stack<Frame>* getJVMStack() {
        return &javaVirtualMachineStack;
    }
    // uint32_t getPc() {
    //     return pc;
    // }
    // stack<Frame> getJavaVirtualMachineStack() {
    //     return javaVirtualMachineStack;
    // }
};

#endif