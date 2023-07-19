
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