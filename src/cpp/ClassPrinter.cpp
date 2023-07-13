/**
 * @file ClassPrinter.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Atributos a serem usados na execuçao da JVM 
 * @details A biblioteca ClassPrinter.hpp contém o arquivo com a descrição das funções
 * utilizadas para exibir os atributos de um arquivo.class
 * @see ClassPrinter.hpp
 */
 
#include "../hpp/ClassPrinter.hpp"

/** @class ClassPrinter::interpretClassFlags
 *  @brief Método para identificar a descrição da flag passada
 *  @param accessFlag code da flag
 *  @return Descritor da flag
 */
string ClassPrinter::interpretClassFlags(uint16_t accessFlags) {
    vector<string> identifiedFlags;
    ostringstream outputFlagsStream;

    if (accessFlags & ClassFile::ACC_PUBLIC) {
       identifiedFlags.push_back("public");
    }
    if (accessFlags & ClassFile::ACC_FINAL) {
       identifiedFlags.push_back("final");
    }
    // For ClassFile structures, 0x0020 is ACC_SUPER, which has historical significance only
    // if (accessFlags & ClassFile::ACC_SUPER) {
    //    identifiedFlags.push_back("super");
    // }
    if (accessFlags & ClassFile::ACC_INTERFACE) {
       identifiedFlags.push_back("interface");
    }
    if (accessFlags & ClassFile::ACC_ABSTRACT) {
       identifiedFlags.push_back("abstract");
    }
    if (accessFlags & ClassFile::ACC_SYNTHETIC) {
       identifiedFlags.push_back("synthetic");
    }
    if (accessFlags & ClassFile::ACC_ANNOTATION) {
       identifiedFlags.push_back("annotation");
    }
    if (accessFlags & ClassFile::ACC_ENUM) {
       identifiedFlags.push_back("enum");
    }

    outputFlagsStream << "[";
    if (!identifiedFlags.empty()) {
        copy(identifiedFlags.begin(), identifiedFlags.end()-1, ostream_iterator<string>(outputFlagsStream, " "));
        outputFlagsStream << identifiedFlags.back();
    }
    outputFlagsStream << "]";

    return outputFlagsStream.str();
}


/** @class ClassPrinter::interpretMethodFlags
 *  @brief Método para identificar a descrição da flag passada
 *  @param accessFlag code da flag
 *  @return Descritor da flag
 */
string ClassPrinter::interpretMethodFlags(uint16_t accessFlags) {
    vector<string> identifiedFlags;
    ostringstream outputFlagsStream;

    if (accessFlags & MethodInfo::ACC_PUBLIC) {
       identifiedFlags.push_back("public");
    }
    if (accessFlags & MethodInfo::ACC_PRIVATE) {
       identifiedFlags.push_back("private");
    }
    if (accessFlags & MethodInfo::ACC_PROTECTED) {
       identifiedFlags.push_back("protected");
    }
    if (accessFlags & MethodInfo::ACC_STATIC) {
       identifiedFlags.push_back("static");
    }
    if (accessFlags & MethodInfo::ACC_FINAL) {
       identifiedFlags.push_back("final");
    }
    if (accessFlags & MethodInfo::ACC_SYNCHRONIZED) {
       identifiedFlags.push_back("synchronized");
    }
    if (accessFlags & MethodInfo::ACC_BRIDGE) {
       identifiedFlags.push_back("bridge");
    }
    if (accessFlags & MethodInfo::ACC_VARARGS) {
       identifiedFlags.push_back("varargs");
    }
    if (accessFlags & MethodInfo::ACC_NATIVE) {
       identifiedFlags.push_back("native");
    }
    if (accessFlags & MethodInfo::ACC_ABSTRACT) {
       identifiedFlags.push_back("abstract");
    }
    if (accessFlags & MethodInfo::ACC_STRICT) {
       identifiedFlags.push_back("strict");
    }
    if (accessFlags & MethodInfo::ACC_SYNTHETIC) {
       identifiedFlags.push_back("synthetic");
    }

    outputFlagsStream << "[";
    if (!identifiedFlags.empty()) {
        copy(identifiedFlags.begin(), identifiedFlags.end()-1, ostream_iterator<string>(outputFlagsStream, " "));
        outputFlagsStream << identifiedFlags.back();
    }
    outputFlagsStream << "]";

    return outputFlagsStream.str();
}

/** @class ClassPrinter::interpretFieldFlags
 *  @brief Método para identificar a descrição da flag passada
 *  @param accessFlag code da flag
 *  @return Descritor da flag
 */
string ClassPrinter::interpretFieldFlags(uint16_t accessFlags) {
    vector<string> identifiedFlags;
    ostringstream outputFlagsStream;

    if (accessFlags & FieldInfo::ACC_PUBLIC) {
        identifiedFlags.push_back("public");
    }
    if (accessFlags & FieldInfo::ACC_PRIVATE) {
        identifiedFlags.push_back("private");
    }
    if (accessFlags & FieldInfo::ACC_PROTECTED) {
        identifiedFlags.push_back("protected");
    }
    if (accessFlags & FieldInfo::ACC_STATIC) {
        identifiedFlags.push_back("static");
    }
    if (accessFlags & FieldInfo::ACC_FINAL) {
        identifiedFlags.push_back("final");
    }
    if (accessFlags & FieldInfo::ACC_VOLATILE) {
        identifiedFlags.push_back("volatile");
    }
    if (accessFlags & FieldInfo::ACC_TRANSIENT) {
        identifiedFlags.push_back("transient");
    }
    if (accessFlags & FieldInfo::ACC_SYNTHETIC) {
        identifiedFlags.push_back("synthetic");
    }
    if (accessFlags & FieldInfo::ACC_ENUM) {
        identifiedFlags.push_back("enum");
    }

    outputFlagsStream << "[";
    if (!identifiedFlags.empty()) {
        copy(identifiedFlags.begin(), identifiedFlags.end()-1, ostream_iterator<string>(outputFlagsStream, " "));
        outputFlagsStream << identifiedFlags.back();
    }
    outputFlagsStream << "]";

return outputFlagsStream.str();
}

/** @fn ClassPrinter::ClassPrinter
 *  @brief Armazena os valores do .class e do conjunto de instruções nas variáveis locais
 *  @param classFile arquivo .class @param  instructionSet conjunto de instruções
 *  @return 
 */
ClassPrinter::ClassPrinter(ClassFile classFile, InstructionSet * instructionSet) {
    this->classFile = classFile;
    this->instructionSet = instructionSet;
}

/** @class ClassPrinter::printGeneralInformation
 *  @brief Ientifica e mostra na tela as informações gerais do .class
 *  @param 
 *  @return 
 */
void ClassPrinter::printGeneralInformation() {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    string version = "";

    switch (classFile.getMajorVersion()) {
    case 46:
        version = "1.2";
        break;
    case 47:
        version = "1.3";
        break;
    case 48:
        version = "1.4";
        break;
    case 49:
        version = "1.5";
        break;
    case 50:
        version = "1.6";
        break;
    case 51:
        version = "1.7";
        break;
    case 52:
        version = "1.8";
        break;
    case 53:
        version = "1.9";
        break;
    case 54:
        version = "1.10";
        break;
    case 55:
        version = "1.11";
        break;
    case 56:
        version = "1.12";
        break;
    case 57:
        version = "1.13";
        break;
    }

    printf("********************General Information********************\n");
    printf("Magic Number:        0x%08x\n", classFile.getMagic());
    printf("Minor version:       %d\n", classFile.getMinorVersion());
    printf("Major version:       %d [%s]\n", classFile.getMajorVersion(), version.c_str());
    printf("Constant pool count: %d\n", classFile.getConstantPoolCount());
    printf("Access flags:        0x%04x %s\n", classFile.getAccessFlags(), interpretClassFlags(classFile.getAccessFlags()).c_str());
    printf("This class:          cp_info #%d <%s>\n", classFile.getThisClass(), constantPool[classFile.getThisClass()-1]->getInfo(constantPool).first.c_str());
    if(classFile.getSuperClass() == 0) {
        printf("Super class:         cp_info #%d <%s>\n", classFile.getSuperClass(), "invalid constant pool reference");
    }
    else {
        printf("Super class:         cp_info #%d <%s>\n", classFile.getSuperClass(), constantPool[classFile.getSuperClass()-1]->getInfo(constantPool).first.c_str());
    }
    printf("Interfaces count:    %d\n", classFile.getInterfacesCount());
    printf("Fields count:        %d\n", classFile.getFieldsCount());
    printf("Methods count:       %d\n", classFile.getMethodsCount());
    printf("Atributes count:     %d\n", classFile.getAttributesCount());
}


/** @class ClassPrinter::printConstantPool
 *  @brief Mostra na tela todas as ConstantPools identificadas no .class
 *  @param 
 *  @return 
 */
void ClassPrinter::printConstantPool() {
    vector<CPInfo*> constantPool = classFile.getConstantPool();

    cout << "********************Constant Pool********************" << endl << endl;
    for (int i = 0; i < classFile.getConstantPoolCount()-1; i++) {
        CPInfo *cpInfo = constantPool[i];
        cout << "[" << i+1 << "]";
        pair<string,string> info;

        switch (cpInfo->getTag()) {
        case CPInfo::CONSTANT_Class:
            info = cpInfo->getInfo(constantPool);
            cout << "CONSTANT_Class_info" << endl;
            cout << "Class name: cp_info #" << cpInfo->getClassInfo().name_index << " <" << info.first  << ">";
            break;
        case CPInfo::CONSTANT_Fieldref:
            info = cpInfo->getInfo(constantPool);
            cout << "CONSTANT_Fieldref_info" << endl;
            cout << "Class name:    cp_info #" << cpInfo->getFieldrefInfo().class_index << " <" << info.first << ">" << endl;
            cout << "Name and type: cp_info #" << cpInfo->getFieldrefInfo().name_and_type_index << " <" << info.second << ">";
            break;
        case CPInfo::CONSTANT_Methodref:
            info = cpInfo->getInfo(constantPool);
            cout << "CONSTANT_Methodref_info" << endl;
            cout << "Class name:    cp_info #" << cpInfo->getMethodrefInfo().class_index << " <" << info.first << ">" << endl;
            cout << "Name and type: cp_info #" << cpInfo->getMethodrefInfo().name_and_type_index << " <" << info.second << ">";
            break;
        case CPInfo::CONSTANT_InterfaceMethodref:
            info = cpInfo->getInfo(constantPool);
            cout << "CONSTANT_InterfaceMethodref_info" << endl;
            cout << "Class name:    cp_info #" << cpInfo->getInterfaceMethodrefInfo().class_index << " <" << info.first << ">" << endl;
            cout << "Name and type: cp_info #" << cpInfo->getInterfaceMethodrefInfo().name_and_type_index << " <" << info.second << ">";
            break;
        case CPInfo::CONSTANT_String:
            info = cpInfo->getInfo(constantPool);
            cout << "CONSTANT_String_info" << endl;
            cout << "String: cp_info #" << cpInfo->getStringInfo().string_index << " <" << info.first << ">";
            break;
        case CPInfo::CONSTANT_Integer:
            cout << "CONSTANT_Integer" << endl;
            cout << "Bytes: " << cpInfo->getInfo(constantPool).first;
            break;
        case CPInfo::CONSTANT_Float:
            cout << "CONSTANT_Float_info" << endl;
            cout << "Bytes: " << cpInfo->getInfo(constantPool).first;
            break;
        case CPInfo::CONSTANT_Long:
            cout << "CONSTANT_Long_info" << endl;
            printf("High Bytes: 0x%08X\n", cpInfo->getLongInfo().high_bytes);
            printf("High Bytes: 0x%08X\n", cpInfo->getLongInfo().low_bytes);
            cout << "Long:       " << cpInfo->getInfo(constantPool).first;
            break;
        case CPInfo::CONSTANT_Double:
            cout << "CONSTANT_Double_info" << endl;
            printf("High Bytes: 0x%08X\n", cpInfo->getDoubleInfo().high_bytes);
            printf("High Bytes: 0x%08X\n", cpInfo->getDoubleInfo().low_bytes);
            cout << "Double:     " << cpInfo->getInfo(constantPool).first;
            break;
        case CPInfo::CONSTANT_NameAndType:
            info = cpInfo->getInfo(constantPool);
            cout << "CONSTANT_NameAndType_info" << endl;
            cout << "Name      :" << "cp_info #" << cpInfo->getNameAndTypeInfo().name_index << " <" << info.first << ">" << endl;
            cout << "Descriptor:" << "cp_info #" << cpInfo->getNameAndTypeInfo().descriptor_index << " <" << info.second << ">";
            break;
        case CPInfo::CONSTANT_Utf8:
            cout << "Constant_Utf8_info" << endl;
            cout << "Length of byte array: " << cpInfo->getUTF8Info().length << endl;
            cout << "Length of string:     " << cpInfo->getUTF8Info().length << endl;
            cout << "String:               " << cpInfo->getInfo(constantPool).first;
            break;
        // case CPInfo::CONSTANT_MethodHandle:
        //     break;
        // case CPInfo::CONSTANT_MethodType:
        //     break;
        // case CPInfo::CONSTANT_InvokeDynamic:
        //     break;
        case CPInfo::CONSTANT_Empty:
            cout << "(large numeric continued)";
            break;
        default:
            break;
        }
        cout << endl << endl;
    }
}

/** @class ClassPrinter::printerInterfaces
 *  @brief Método para identificar e mostrar na tela as interfaces contidas no arquivo .class
 *  @param 
 *  @return 
 */
void ClassPrinter::printInterfaces() {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    vector<InterfaceInfo*> interfaces = classFile.getInterfaces();

    cout << "******************************Interfaces******************************" << endl << endl;
    for (int i = 0; i < classFile.getInterfacesCount(); i++) {
        uint16_t index = interfaces[i]->getInterfaceIndex();
        string name = constantPool[index-1]->getInfo(constantPool).first;

        cout << "Interface " << i << endl;
        cout << "Interface: cp_info #" << index << " <" << name << ">" << endl;
    }
    cout << endl;
}

/** @class ClassPrinter::printerFields
 *  @brief Método para identificar e mostrar na tela os fields contidos no arquivo .class
 *  @param 
 *  @return 
 */
void ClassPrinter::printFields() {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    vector<FieldInfo*> fields = classFile.getFields();

    cout << "******************************Fields******************************" << endl << endl;
    cout << "Displayed members---------------------------------------------" << endl << endl;
    cout << "Member count: " << classFile.getFieldsCount() << endl << endl;

    for (int i = 0; i < classFile.getFieldsCount(); i++) {
        uint16_t accessFlags = fields[i]->getAccessFlags();
        uint16_t nameIndex = fields[i]->getNameIndex();
        uint16_t descriptorIndex = fields[i]->getDescriptorIndex();
        string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
        string descriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;

        cout << "[" << i << "]" << name << endl;
        cout <<"Name:         cp_info #" << nameIndex << " <" << name << ">" << endl;
        cout <<"Descriptor:   cp_info #" << descriptorIndex << " <" << descriptor << ">" << endl;
        printf("Access flags: 0x%04X %s\n", accessFlags, interpretFieldFlags(accessFlags).c_str());
    }
}

/** @class ClassPrinter::printerMethods
 *  @brief Método para identificar e mostrar na tela os methods contidos no arquivo .class
 *  @param 
 *  @return 
 */
void ClassPrinter::printMethods() {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    vector<MethodInfo*> methods = classFile.getMethods();

    cout << "******************************Methods******************************" << endl << endl;
    cout << "Displayed members---------------------------------------------" << endl << endl;
    cout << "Member count: " << classFile.getMethodsCount() << endl << endl;

    for (int i = 0; i < classFile.getMethodsCount(); i++) {
        MethodInfo* method = methods[i];
        uint16_t nameIndex = method->getNameIndex();
        uint16_t descriptorIndex = method->getDescriptorIndex();
        string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
        string descriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;
        uint16_t accessFlags = method->getAccessFlags();

        cout << "[" << i << "]" << name << endl;
        cout << "Name      :   " << "cp_info #" << nameIndex << " <" << name << ">" << endl;
        cout << "Descriptor:   " << "cp_info #" << descriptorIndex << " <" << descriptor << ">" << endl;
        printf("Access flags: 0x%04X %s\n", accessFlags, interpretMethodFlags(accessFlags).c_str());
        cout << endl;

        printAttributes(method->getAttributes(), method->getAttributesCount());
    }


}

/** @class ClassPrinter::printSourceFieldInfo
 *  @brief Método que visa mostrar na tela o index referente ao attribute localizado na tabela de constantpool
 *  @param attribute tipo SourceFileAttribute
 *  @return 
 */
void ClassPrinter::printSourceFileInfo(SourceFileAttribute* attribute) {
    uint16_t sourceFileIndex = attribute->getSourceFileIndex();
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    CPInfo* info = constantPool[sourceFileIndex-1];

    cout << "Source file name index: cp_info #" << sourceFileIndex << " <" << info->getInfo(constantPool).first << ">" << endl;
}
/** @class ClassPrinter::printConstantValueInfo
 *  @brief Método que visa mostrar na tela o index referente ao attribute localizado na tabela de constantpool
 *  @param attribute tipo ConstantValueAttribute
 *  @return 
 */
void ClassPrinter::printConstantValueInfo(ConstantValueAttribute* attribute) {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    uint16_t index = attribute->getConstantValueIndex();
    CPInfo* constantValueInfo = constantPool[index-1];

    cout << "Constante value Index: cp info #" << index << constantValueInfo->getInfo(constantPool).first << endl;
}
/** @class ClassPrinter::printCodeExceptionTableInfo
 *  @brief Método que visa mostrar na tela as informações da Tabela de exceções
 *  @param exceptionTable tipo ExceptionHandler @param exceptionTableLength tamanho da tabela exceptionTable
 *  @return 
 */
void ClassPrinter::printCodeExceptionTableInfo(ExceptionHandler* exceptionTable, uint16_t exceptionTableLength) {
    vector<CPInfo*> constantPool = classFile.getConstantPool();

    cout << "ExceptionTable-----------" << endl;
    printf("Nr.\tStart PC\tEnd PC\tHandlerPC\tCatch Type\n");

    for (int i = 0; i < exceptionTableLength; i++) {
        uint16_t startPC = exceptionTable[i].getStartPC();
        uint16_t endPC = exceptionTable[i].getEndPC();
        uint16_t handlerPC = exceptionTable[i].getHandlerPC();
        uint16_t catchTypeIndex = exceptionTable[i].getCatchType();
        string catchType = constantPool[catchTypeIndex-1]->getInfo(constantPool).first;

        printf("%d\t%d\t\t%d\t%d\t\tcp_info#%d\n", i, startPC, endPC, handlerPC, catchTypeIndex);
        printf("\t\t\t\t\t\t%s\n", catchType.c_str());
    }
}

/** @class ClassPrinter::printCodeInfo
 *  @brief Método que visa mostrar na tela as informações do bytecode 
 *  @param attribute tipo CodeAttribute
 *  @return 
 */
void ClassPrinter::printCodeInfo(CodeAttribute* attribute) {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    uint8_t* bytecode = attribute->getCode();

    uint32_t instructionsCount = instructionSet->getInstructionsCount();
    Instruction* instructions = instructionSet->getInstructionSet();
    cout << "Bytecode-----------" << endl;
    for (int i = 0; i < attribute->getCodeLength(); i++) {
        uint8_t opcode = bytecode[i];
        Instruction instruction = instructions[opcode];

        cout << i << ": " << instruction.getMnemonic() << " ";

        if (opcode == Instruction::wide) {
            uint8_t modifiedOpcode = bytecode[++i];
            cout << instructions[modifiedOpcode].getMnemonic() << " ";

            if ((modifiedOpcode >= Instruction::iload && modifiedOpcode <= Instruction::aload) ||
                (modifiedOpcode >= Instruction::istore && modifiedOpcode <= Instruction::astore) ||
                (modifiedOpcode == Instruction::ret)) {
                uint8_t indexbyte1 = bytecode[++i];
                uint8_t indexbyte2 = bytecode[++i];
                uint16_t index = (indexbyte1 << 8) | indexbyte2;

                cout << index << endl;
            }
            else if (modifiedOpcode == Instruction::iinc) {
                uint8_t indexbyte1 = bytecode[++i];
                uint8_t indexbyte2 = bytecode[++i];
                uint16_t index = (indexbyte1 << 8) | indexbyte2;

                uint8_t constbyte1 = bytecode[++i];
                uint8_t constbyte2 = bytecode[++i];
                int16_t constImmediate = (constbyte1 << 8) | constbyte2;
                cout << index << " by " << constImmediate << endl;
            }
        }
        else if (opcode == Instruction::tableswitch) {
            int baseAddress = i;
            i++;
            while (i%4 != 0) {
                i++;
            }

            uint8_t defaultByte1 = bytecode[i++];
            uint8_t defaultByte2 = bytecode[i++];
            uint8_t defaultByte3 = bytecode[i++];
            uint8_t defaultByte4 = bytecode[i++];
            int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) | (defaultByte3 << 8) | defaultByte4;

            uint8_t lowByte1 = bytecode[i++];
            uint8_t lowByte2 = bytecode[i++];
            uint8_t lowByte3 = bytecode[i++];
            uint8_t lowByte4 = bytecode[i++];
            int32_t low = (lowByte1 << 24) | (lowByte2 << 16) | (lowByte3 << 8) | lowByte4;

            uint8_t highByte1 = bytecode[i++];
            uint8_t highByte2 = bytecode[i++];
            uint8_t highByte3 = bytecode[i++];
            uint8_t highByte4 = bytecode[i++];
            int32_t high = (highByte1 << 24) | (highByte2 << 16) | (highByte3 << 8) | highByte4;

            cout << low << " to " << high << endl;

            for (int j = low; j <= high; j++) {
                uint8_t jumpByte1 = bytecode[i++];
                uint8_t jumpByte2 = bytecode[i++];
                uint8_t jumpByte3 = bytecode[i++];
                uint8_t jumpByte4 = bytecode[i++];
                int32_t jump = (jumpByte1 << 24) | (jumpByte2 << 16) | (jumpByte3 << 8) | jumpByte4;

                string sign = jump > 0 ? "+" : "";
                printf("\t%d:    %d (%s%d)\n", j, baseAddress+jump, sign.c_str(), jump);
            }
            string sign = defaultValue > 0 ? "+" : "";
            printf("\tdefault:    %d (%s%d)\n", baseAddress+defaultValue, sign.c_str(), defaultValue);
            i--;
        }
        else if (opcode == Instruction::lookupswitch) {
            int baseAddress = i;
            i++;
            while (i%4 != 0) {
                i++;
            }

            uint8_t defaultByte1 = bytecode[i++];
            uint8_t defaultByte2 = bytecode[i++];
            uint8_t defaultByte3 = bytecode[i++];
            uint8_t defaultByte4 = bytecode[i++];
            int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) | (defaultByte3 << 8) | defaultByte4;

            uint8_t npairs1 = bytecode[i++];
            uint8_t npairs2 = bytecode[i++];
            uint8_t npairs3 = bytecode[i++];
            uint8_t npairs4 = bytecode[i++];
            int32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;
            cout << npairs << endl;

            for (int j = 0; j < npairs; j++) {
                uint8_t matchByte1 = bytecode[i++];
                uint8_t matchByte2 = bytecode[i++];
                uint8_t matchByte3 = bytecode[i++];
                uint8_t matchByte4 = bytecode[i++];
                int32_t match = (matchByte1 << 24) | (matchByte2 << 16) | (matchByte3 << 8) | matchByte4;
                uint8_t offsetByte1 = bytecode[i++];
                uint8_t offsetByte2 = bytecode[i++];
                uint8_t offsetByte3 = bytecode[i++];
                uint8_t offsetByte4 = bytecode[i++];
                int32_t offset = (offsetByte1 << 24) | (offsetByte2 << 16) | (offsetByte3 << 8) | offsetByte4;
                string sign = offset > 0 ? "+" : "";
                printf("\t%d:    %d (%s%d)\n", match, baseAddress+offset, sign.c_str(), offset);
            }
            string sign = defaultValue > 0 ? "+" : "";
            printf("\tdefault:    %d (%s%d)\n", baseAddress+defaultValue, sign.c_str(), defaultValue);
            i--;
        }
        //Operacoes que nao tem bytes adicionais
        else if (instruction.getBytesCount() == 0) {
            cout << endl;
        }
        else if (instruction.getBytesCount() == 1) {
            uint8_t byte = bytecode[++i];

            //Operacoes que exigem referencia a constant pool
            if (opcode == Instruction::ldc) {
                uint8_t index = byte;
                cout << "#" << +index << " <" << constantPool[index-1]->getInfo(constantPool).first << ">" << endl;
            }
            else if ((opcode == Instruction::bipush)) {
                int32_t value = (int8_t)byte;
                cout << value << endl;
            }
            else if((opcode >= Instruction::iload && opcode <= Instruction::aload) ||
                    (opcode >= Instruction::istore && opcode <= Instruction::astore) ||
                    (opcode == Instruction::ret) ) {
                uint8_t index = byte;
                cout << +index << endl;
            }
            else if (opcode == Instruction::newarray) {
                int atype = byte;
                cout << atype << " ";
                switch(atype) {
                case Instruction::T_BOOLEAN: cout << "(bool)";   break;
                case Instruction::T_CHAR:    cout << "(char)";   break;
                case Instruction::T_FLOAT:   cout << "(float)";  break;
                case Instruction::T_DOUBLE:  cout << "(double)"; break;
                case Instruction::T_BYTE:    cout << "(byte)";   break;
                case Instruction::T_SHORT:   cout << "(short)";  break;
                case Instruction::T_INT:     cout << "(int)";    break;
                case Instruction::T_LONG:    cout << "(long)";   break;
                }
                cout << endl;
            }
        }
        else if (instruction.getBytesCount() == 2) {
            uint8_t byte1 = bytecode[++i];
            uint8_t byte2 = bytecode[++i];
            if (opcode == Instruction::sipush) {
                int16_t immediate = ((int16_t)byte1 << 8) | byte2;
                cout << immediate << endl;
            }
            else if (opcode == Instruction::iinc) {
                uint8_t index = byte1;
                int8_t constImmediate = byte2;
                cout << +index << " by " << +constImmediate << endl;
            }
            else if ((opcode >= Instruction::ifeq && opcode <= Instruction::jsr) ||
                     (opcode == Instruction::ifnull) ||
                     (opcode == Instruction::ifnonnull)) {
                int16_t offset = ((int16_t)byte1 << 8) | byte2;
                int index = i-2 + offset;
                string sign = offset > 0 ? "+" : "";

                cout << index << " (" << sign << offset << ")" << endl;
            }
            else if ((opcode >= Instruction::getstatic && opcode <= Instruction::invokestatic)) {
                uint16_t index = ((uint16_t)byte1 << 8) | byte2;
                string methodName = constantPool[index-1]->getInfo(constantPool).first;
                string nameAndType = constantPool[index-1]->getInfo(constantPool).second;
                int j = 0;

                while (j < nameAndType.size() && nameAndType[j+1] != ':') {
                    j++;
                }
                string name = nameAndType.substr(0,j);
                cout << "#" << index << " <" << methodName << "." << name << ">" << endl;
            }
            else if ((opcode == Instruction::ldc_w) ||
                     (opcode == Instruction::ldc2_w) ||
                     (opcode == Instruction::newOp) ||
                     (opcode == Instruction::anewarray) ||
                     (opcode == Instruction::checkcast) ||
                     (opcode == Instruction::instanceof)) {
                uint16_t index = ((uint16_t)byte1 << 8) | byte2;
                string className = constantPool[index-1]->getInfo(constantPool).first;
                cout << "#" << index << " <" << className << ">" << endl;
            }
        }
        else if (instruction.getBytesCount() == 3) {
            uint8_t byte1 = bytecode[++i];
            uint8_t byte2 = bytecode[++i];
            uint8_t byte3 = bytecode[++i];
            if (opcode == Instruction::multianewarray) {
                uint16_t index = ((uint16_t)byte1 << 8) | byte2;
                uint8_t dimensions = byte3;
                CPInfo* info = constantPool[index-1];

                cout << "#" << index << " <" << info->getInfo(constantPool).first << "> " << "dim " << +dimensions << endl;
            }
        }
        else if (instruction.getBytesCount() == 4) {
            uint8_t byte1 = bytecode[++i];
            uint8_t byte2 = bytecode[++i];
            uint8_t byte3 = bytecode[++i];
            uint8_t byte4 = bytecode[++i];

            if (opcode == Instruction::goto_w || opcode == Instruction:: jsr_w) {
                int32_t offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
                int index = i-2 + offset;
                string sign = offset > 0 ? "+" : "";

                cout << index << " (" << sign << offset << ")" << endl;
            }
            else if ((opcode == Instruction::invokeinterface || opcode == Instruction::invokedynamic)) {
                int16_t index = ((int16_t)byte1 << 8) | byte2;
                string methodName = constantPool[index-1]->getInfo(constantPool).first;
                string nameAndType = constantPool[index-1]->getInfo(constantPool).second;
                int j = 0;

                while (j < nameAndType.size() && nameAndType[j+1] != ':') {
                    j++;
                }
                string name = nameAndType.substr(0,j);
                cout << "#" << index << " <" << methodName << "." << name << ">" << endl;
            }
        }
    }

    //Printa a aba Exception Table
    printCodeExceptionTableInfo(attribute->getExceptionTable(), attribute->getExceptionTableLength());

    cout << "Misc----------------" << endl << endl;
    cout << "Max Stack:               " << attribute->getMaxStack() << endl;
    cout << "Maximum local variables: " << attribute->getMaxLocals() << endl;
    cout << "Code Length:             " << attribute->getCodeLength() << endl;

    //Printa os atributos do Code Attribute
    printAttributes(attribute->getAttributes(), attribute->getAttributesCount());


}

/** @class ClassPrinter::printLineNumberTableInfo
 *  @brief Método que visa mostrar na tela o index, o startPC e o lineNumber;
 *  @param attribute tipo LineNumberTableAttribute
 *  @return 
 */
void ClassPrinter::printLineNumberTableInfo(LineNumberTableAttribute* attribute) {
    uint16_t lineNumberTableLength = attribute->getLineNumberTableLength();
    LineNumber* lineNumberTable = attribute->getLineNumberTable();

    printf("Nr.\tStart PC\tLineNumber\n");
    for (int i = 0; i < lineNumberTableLength; i++) {
        printf("%d\t%d\t\t%d\n", i, lineNumberTable[i].getStartPC(), lineNumberTable[i].getLineNumber());
    }
}

/** @class ClassPrinter::printLocalVariableTableInfo
 *  @brief Método que visa mostrar na tela as características das varíaveis locais da tabela de informações;
 *  @param attribute tipo LocalVariableTableAttribute
 *  @return 
 */
void ClassPrinter::printLocalVariableTableInfo(LocalVariableTableAttribute* attribute) {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    uint16_t localVariableTableLength = attribute->getLocalVariableTableLength();
    LocalVariable* localVariableTable = attribute->getLocalVariableTable();

    printf("Nr.\tStart PC\tLength\tIndex\tName\t\t\tDescriptor\n");
    for (int i = 0; i < localVariableTableLength; i++) {
        uint16_t startPC = localVariableTable[i].getStartPC();
        uint16_t length = localVariableTable[i].getLength();
        uint16_t index = localVariableTable[i].getIndex();
        uint16_t nameIndex = localVariableTable[i].getNameIndex();
        uint16_t descriptorIndex = localVariableTable[i].getDescriptorIndex();
        string name = constantPool[nameIndex-1]->getInfo(constantPool).first;
        string descriptor = constantPool[descriptorIndex-1]->getInfo(constantPool).first;

        printf("%d\t%d\t\t%d\t%d\tcp_info #%d\t\tcp_info #%d\n", i, startPC, length, index, nameIndex, descriptorIndex);
        printf("\t\t\t\t\t\t\t\t%s\r\t\t\t\t\t%s\n", descriptor.c_str(), name.c_str());
    }
}

/** @class ClassPrinter::printExceptionsInfo
 *  @brief Método que visa mostrar na tela as informações das exceções contidas na tabela de exceções;
 *  @param attribute tipo ExceptionsInfo
 *  @return 
 */
void ClassPrinter::printExceptionsInfo(ExceptionsAttribute* attribute) {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    uint16_t *exceptionTable = attribute->getExeceptionIndexTable();

    printf("Nr.\tException\tVerbose\n");

    for (int i = 0; i < attribute->getNumberOfExceptions(); i++) {
        uint16_t exceptionIndex = exceptionTable[i];
        string verbose = constantPool[exceptionIndex-1]->getInfo(constantPool).first;

        printf("%d\tcp_info #%d\t%s\n", i, exceptionIndex, verbose.c_str());
    }
}

/** @class ClassPrinter::printInnerClassesInfo
 *  @brief Método que visa mostrar as informações da InnerClasses
 *  @param attribute tipo InnerClassesAttribute
 *  @return 
 */
void ClassPrinter::printInnerClassesInfo(InnerClassesAttribute* attribute) {
    vector<CPInfo*> constantPool = classFile.getConstantPool();
    ClassInfo* classes = attribute->getClasses();

    printf("Nr.\tInner Class\t\tOuter Class\tInner Name\tAccess Flags\n");

    for (int i = 0; i < attribute->getNumberOfClasses(); i++) {
        uint16_t innerClassInfoIndex = classes[i].getInnerClassInfoIndex();
        uint16_t outerClassInfoIndex = classes[i].getOuterClassInfoIndex();
        uint16_t innerNameIndex = classes[i].getInnerNameIndex();
        uint16_t innerClassAccessFlags = classes[i].getInnerClassAccessFlags();
        string innerClassName = constantPool[innerClassInfoIndex-1]->getInfo(constantPool).first;
        string outerClassName = constantPool[outerClassInfoIndex-1]->getInfo(constantPool).first;
        string innerName = constantPool[innerNameIndex-1]->getInfo(constantPool).first;

        printf("%d\tcp_info #%d\t\tcp_info #%d\tcp_info#%d\t0x%04x %s\n",
               i, innerClassInfoIndex, outerClassInfoIndex, innerNameIndex, innerClassAccessFlags,
               interpretClassFlags(innerClassAccessFlags).c_str());
        printf("\t%s\t%s\t%s\n", innerClassName.c_str(), outerClassName.c_str(), innerName.c_str());
    }
}

/** @class ClassPrinter::printAttributes
 *  @brief Método que visa mostrar na tela os atributos contidos no .class
 *  @param attributes tipo AttributeInfo @param attributesCount tamanho da quantidade de attributes passados
 *  @return 
 */
void ClassPrinter::printAttributes(AttributeInfo* attributes, uint16_t attributesCount) {
    vector<CPInfo*> constantPool = classFile.getConstantPool();

    for (int i = 0; i < attributesCount; i++) {
        AttributeInfo attribute = attributes[i];
        uint16_t nameIndex = attribute.getAttributeNameIndex();
        string attributeName = constantPool[nameIndex-1]->getInfo(constantPool).first;
        uint16_t attributeLength = attribute.getAttributeLength();

        cout << "[" << i << "]" << attributeName << endl;
        cout << "Generic info ---------------------------------------------" << endl << endl;
        cout << "Attribute name index: cp_info #" << nameIndex << " <" << attributeName << ">" << endl;
        cout << "Attribute length:     " << attributeLength << endl << endl;
        cout << "Specific info --------------------------------------------" << endl << endl;
        if (attributeName.compare("ConstantValue") == 0) {
            ConstantValueAttribute constantValueAttribute = attribute.getConstantValueAttribute();
            printConstantValueInfo(&constantValueAttribute);
        }
        else if (attributeName.compare("Code") == 0) {
            CodeAttribute codeAttribute = attribute.getCodeAttribute();
            printCodeInfo(&codeAttribute);
        }
        else if (attributeName.compare("InnerClasses") == 0) {
            InnerClassesAttribute innerClassesAttribute = attribute.getInnerClassesAttribute();
            printInnerClassesInfo(&innerClassesAttribute);
        }
        else if (attributeName.compare("SourceFile") == 0) {
            SourceFileAttribute sourceFileAttribute = attribute.getSourceFileAttribute();
            printSourceFileInfo(&sourceFileAttribute);
        }
        else if (attributeName.compare("LineNumberTable") == 0) {
            LineNumberTableAttribute lineNumberTableAttribute = attribute.getLineNumberTableAttribute();
            printLineNumberTableInfo(&lineNumberTableAttribute);
        }
        else if (attributeName.compare("LocalVariableTable") == 0) {
            LocalVariableTableAttribute localVariableTable = attribute.getLocalVariableTableAttribute();
            printLocalVariableTableInfo(&localVariableTable);
        }
        else if (attributeName.compare("Exceptions") == 0) {
            ExceptionsAttribute exceptions = attribute.getExceptionsAttribute();
            printExceptionsInfo(&exceptions);
        }
        cout << endl << "----------------------------------------------------------" << endl << endl;
    }
}

/** @class ClassPrinter::printClassFileAttributes
 *  @brief Método que visa chamar os metodos de pegar os atributos e o tamanho final da quantidade destes no .class
 *  @param 
 *  @return 
 */
void ClassPrinter::printClassFileAttributes() {
    cout << "******************************Attributes******************************" << endl << endl;
    printAttributes(classFile.getAttributes(), classFile.getAttributesCount());
}

/** @class ClassPrinter::printAttributes
 *  @brief Método que tem objetivo de chamar os outros métodos para que seja mostrado na tela a mesma ordem feita pelo jclasslib
 *  @param 
 *  @return 
 */
void ClassPrinter::print(){
    printGeneralInformation();
    printConstantPool();
    printInterfaces();
    printFields();
    printMethods();
    printClassFileAttributes();
}