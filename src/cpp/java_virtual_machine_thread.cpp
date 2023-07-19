/**
 * @file java_virtual_machine_thread.cpp
 * @author André Larrosa Chimpliganond - 190010321
 * @author Marcus Vinicius Oliveira de Abrantes - 190034084
 * @author  Matheus Barbosa e Silva - 190113987
 * @author Moises Felipe Jaco Andrade de Lima - 190018364 
 * @author Thiago Elias dos Reis - 190126892
 * @brief Definicoes da classe JavaVirtualMachineThread
 * @details Define as operacoes de frames de uma thread da maquina virtual.
**/
#include "../hpp/java_virtual_machine_thread.hpp"

JavaVirtualMachineThread::JavaVirtualMachineThread() {
    this->pc = 0;
}

void JavaVirtualMachineThread::pushToJVMStack(Frame frame) {
    this->javaVirtualMachineStack.push(frame);
}

void JavaVirtualMachineThread::popFromJVMStack() {
    this->javaVirtualMachineStack.pop();
}

void JavaVirtualMachineThread::incrementPcBy(uint32_t increment) {
    this->pc += increment;
}