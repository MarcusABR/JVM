/**
 * @file Instruction.hpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Descreve a estrutura de uma instrução
 * @details Tem como atributos uma string com o mnemônico da instrução e o número de bytes armazenado em um inteiro de 32 bits
 * @see Instruction.cpp
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <cmath>
#include <vector>
#include "Frame.hpp"
#include "ClassLoader.hpp"

using namespace std;
/** @class Instruction
*   @brief Classe que contém a estrutura de uma instrução a ser executada pelo interpretador; 
*/
class Instruction {
private:
    string mnemonic;
    uint32_t bytesCount;
public:
    static ClassLoader * classLoader;
    static void setClassLoader(ClassLoader*);
    uint32_t (*func)(Frame*);
    Instruction();
    Instruction(string, uint32_t, uint32_t (*)(Frame*));
    void setMnemonic(string);
    void setBytesCount(uint32_t);
    string getMnemonic();
    uint32_t getBytesCount();

    static map<string, JavaType>* initializeFields(ClassFile*);
    static vector<JavaType>* buildMultiAnewArray(vector<int>, int, char);
    static ClassFile* resolveClass(string);
    static FieldInfo* resolveField(ClassFile*, string, string);



    static uint32_t nopFunction(Frame*);
    static uint32_t aconst_nullFunction(Frame*);
    static uint32_t iconst_m1Function(Frame*);
    static uint32_t iconst_0Function(Frame*);
    static uint32_t iconst_1Function(Frame*);
    static uint32_t iconst_2Function(Frame*);
    static uint32_t iconst_3Function(Frame*);
    static uint32_t iconst_4Function(Frame*);
    static uint32_t iconst_5Function(Frame*);
    static uint32_t lconst_0Function(Frame*);
    static uint32_t lconst_1Function(Frame*);
    static uint32_t fconst_0Function(Frame*);
    static uint32_t fconst_1Function(Frame*);
    static uint32_t fconst_2Function(Frame*);
    static uint32_t dconst_0Function(Frame*);
    static uint32_t dconst_1Function(Frame*);
    static uint32_t bipushFunction(Frame*);
    static uint32_t sipushFunction(Frame*);
    static uint32_t ldcFunction(Frame*);
    static uint32_t ldc_wFunction(Frame*);
    static uint32_t ldc2_wFunction(Frame*);

    //Loads
    static uint32_t iloadFunction(Frame*);
    static uint32_t lloadFunction(Frame*);
    static uint32_t floadFunction(Frame*);
    static uint32_t dloadFunction(Frame*);
    static uint32_t aloadFunction(Frame*);
    static uint32_t iload_0Function(Frame*);
    static uint32_t iload_1Function(Frame*);
    static uint32_t iload_2Function(Frame*);
    static uint32_t iload_3Function(Frame*);
    static uint32_t lload_0Function(Frame*);
    static uint32_t lload_1Function(Frame*);
    static uint32_t lload_2Function(Frame*);
    static uint32_t lload_3Function(Frame*);
    static uint32_t fload_0Function(Frame*);
    static uint32_t fload_1Function(Frame*);
    static uint32_t fload_2Function(Frame*);
    static uint32_t fload_3Function(Frame*);
    static uint32_t dload_0Function(Frame*);
    static uint32_t dload_1Function(Frame*);
    static uint32_t dload_2Function(Frame*);
    static uint32_t dload_3Function(Frame*);
    static uint32_t aload_0Function(Frame*);
    static uint32_t aload_1Function(Frame*);
    static uint32_t aload_2Function(Frame*);
    static uint32_t aload_3Function(Frame*);
    static uint32_t ialoadFunction(Frame*);
    static uint32_t laloadFunction(Frame*);
    static uint32_t faloadFunction(Frame*);
    static uint32_t daloadFunction(Frame*);
    static uint32_t aaloadFunction(Frame*);
    static uint32_t baloadFunction(Frame*);
    static uint32_t caloadFunction(Frame*);
    static uint32_t saloadFunction(Frame*);

    //Stores
    static uint32_t istoreFunction(Frame*);
    static uint32_t lstoreFunction(Frame*);
    static uint32_t fstoreFunction(Frame*);
    static uint32_t dstoreFunction(Frame*);
    static uint32_t astoreFunction(Frame*);
    static uint32_t istore_0Function(Frame*);
    static uint32_t istore_1Function(Frame*);
    static uint32_t istore_2Function(Frame*);
    static uint32_t istore_3Function(Frame*);
    static uint32_t lstore_0Function(Frame*);
    static uint32_t lstore_1Function(Frame*);
    static uint32_t lstore_2Function(Frame*);
    static uint32_t lstore_3Function(Frame*);
    static uint32_t fstore_0Function(Frame*);
    static uint32_t fstore_1Function(Frame*);
    static uint32_t fstore_2Function(Frame*);
    static uint32_t fstore_3Function(Frame*);
    static uint32_t dstore_0Function(Frame*);
    static uint32_t dstore_1Function(Frame*);
    static uint32_t dstore_2Function(Frame*);
    static uint32_t dstore_3Function(Frame*);
    static uint32_t astore_0Function(Frame*);
    static uint32_t astore_1Function(Frame*);
    static uint32_t astore_2Function(Frame*);
    static uint32_t astore_3Function(Frame*);
    static uint32_t iastoreFunction(Frame*);
    static uint32_t lastoreFunction(Frame*);
    static uint32_t fastoreFunction(Frame*);
    static uint32_t dastoreFunction(Frame*);
    static uint32_t aastoreFunction(Frame*);
    static uint32_t bastoreFunction(Frame*);
    static uint32_t castoreFunction(Frame*);
    static uint32_t sastoreFunction(Frame*);

    //Stack
    static uint32_t popFunction(Frame*);
    static uint32_t pop2Function(Frame*);
    static uint32_t dupFunction(Frame*);
    static uint32_t dup_x1Function(Frame*);
    static uint32_t dup_x2Function(Frame*);
    static uint32_t dup2Function(Frame*);
    static uint32_t dup2_x1Function(Frame*);
    static uint32_t dup2_x2Function(Frame*);
    static uint32_t swapFunction(Frame*);

    //Math
    static uint32_t iaddFunction(Frame*);
    static uint32_t laddFunction(Frame*);
    static uint32_t faddFunction(Frame*);
    static uint32_t daddFunction(Frame*);
    static uint32_t isubFunction(Frame*);
    static uint32_t lsubFunction(Frame*);
    static uint32_t fsubFunction(Frame*);
    static uint32_t dsubFunction(Frame*);
    static uint32_t imulFunction(Frame*);
    static uint32_t lmulFunction(Frame*);
    static uint32_t fmulFunction(Frame*);
    static uint32_t dmulFunction(Frame*);
    static uint32_t idivFunction(Frame*);
    static uint32_t ldivOpFunction(Frame*);
    static uint32_t fdivFunction(Frame*);
    static uint32_t ddivFunction(Frame*);
    static uint32_t iremFunction(Frame*);
    static uint32_t lremFunction(Frame*);
    static uint32_t fremFunction(Frame*);
    static uint32_t dremFunction(Frame*);
    static uint32_t inegFunction(Frame*);
    static uint32_t lnegFunction(Frame*);
    static uint32_t fnegFunction(Frame*);
    static uint32_t dnegFunction(Frame*);
    static uint32_t ishlFunction(Frame*);
    static uint32_t lshlFunction(Frame*);
    static uint32_t ishrFunction(Frame*);
    static uint32_t lshrFunction(Frame*);
    static uint32_t iushrFunction(Frame*);
    static uint32_t lushrFunction(Frame*);
    static uint32_t iandFunction(Frame*);
    static uint32_t landFunction(Frame*);
    static uint32_t iorFunction(Frame*);
    static uint32_t lorFunction(Frame*);
    static uint32_t ixorFunction(Frame*);
    static uint32_t lxorFunction(Frame*);
    static uint32_t iincFunction(Frame*);

    //Conversions
    static uint32_t i2lFunction(Frame*);
    static uint32_t i2fFunction(Frame*);
    static uint32_t i2dFunction(Frame*);
    static uint32_t l2iFunction(Frame*);
    static uint32_t l2fFunction(Frame*);
    static uint32_t l2dFunction(Frame*);
    static uint32_t f2iFunction(Frame*);
    static uint32_t f2lFunction(Frame*);
    static uint32_t f2dFunction(Frame*);
    static uint32_t d2iFunction(Frame*);
    static uint32_t d2lFunction(Frame*);
    static uint32_t d2fFunction(Frame*);
    static uint32_t i2bFunction(Frame*);
    static uint32_t i2cFunction(Frame*);
    static uint32_t i2sFunction(Frame*);

    //Comparisons
    static uint32_t lcmpFunction(Frame*);
    static uint32_t fcmplFunction(Frame*);
    static uint32_t fcmpgFunction(Frame*);
    static uint32_t dcmplFunction(Frame*);
    static uint32_t dcmpgFunction(Frame*);
    static uint32_t ifeqFunction(Frame*);
    static uint32_t ifneFunction(Frame*);
    static uint32_t ifltFunction(Frame*);
    static uint32_t ifgeFunction(Frame*);
    static uint32_t ifgtFunction(Frame*);
    static uint32_t ifleFunction(Frame*);
    static uint32_t if_icmpeqFunction(Frame*);
    static uint32_t if_icmpneFunction(Frame*);
    static uint32_t if_icmpltFunction(Frame*);
    static uint32_t if_icmpgeFunction(Frame*);
    static uint32_t if_icmpgtFunction(Frame*);
    static uint32_t if_icmpleFunction(Frame*);
    static uint32_t if_acmpeqFunction(Frame*);
    static uint32_t if_acmpneFunction(Frame*);

    //Control
    static uint32_t gotoOpFunction(Frame*);
    static uint32_t jsrFunction(Frame*);
    static uint32_t retFunction(Frame*);
    static uint32_t tableswitchFunction(Frame*);
    static uint32_t lookupswitchFunction(Frame*);
    static uint32_t ireturnFunction(Frame*);
    static uint32_t lreturnFunction(Frame*);
    static uint32_t freturnFunction(Frame*);
    static uint32_t dreturnFunction(Frame*);
    static uint32_t areturnFunction(Frame*);;
    static uint32_t returnOpFunction(Frame*);

    //References
    static uint32_t getstaticFunction(Frame*);
    static uint32_t putstaticFunction(Frame*);
    static uint32_t getfieldFunction(Frame*);
    static uint32_t putfieldFunction(Frame*);
    static uint32_t invokevirtualFunction(Frame*);
    static uint32_t invokespecialFunction(Frame*);
    static uint32_t invokestaticFunction(Frame*);
    static uint32_t invokeinterfaceFunction(Frame*);
    static uint32_t invokedynamicFunction(Frame*);
    static uint32_t newOpFunction(Frame*);
    static uint32_t newarrayFunction(Frame*);
    static uint32_t anewarrayFunction(Frame*);
    static uint32_t arraylengthFunction(Frame*);
    static uint32_t athrowFunction(Frame*);
    // As quatro instrucoes seguintes nao precisam ser implementadas
    static uint32_t checkcastFunction(Frame*);
    static uint32_t instanceofFunction(Frame*);
    static uint32_t monitorenterFunction(Frame*);
    static uint32_t monitorexitFunction(Frame*);

    //Extended
    static uint32_t wideFunction(Frame*);
    static uint32_t multianewarrayFunction(Frame*);
    static uint32_t ifnullFunction(Frame*);
    static uint32_t ifnonnullFunction(Frame*);
    static uint32_t goto_wFunction(Frame*);
    static uint32_t jsr_wFunction(Frame*);

    //Constants
    static const uint8_t nop = 0x00;
    static const uint8_t aconst_null = 0x01;
    static const uint8_t iconst_m1 = 0x02;
    static const uint8_t iconst_0 = 0x03;
    static const uint8_t iconst_1 = 0x04;
    static const uint8_t iconst_2 = 0x05;
    static const uint8_t iconst_3 = 0x06;
    static const uint8_t iconst_4 = 0x07;
    static const uint8_t iconst_5 = 0x08;
    static const uint8_t lconst_0 = 0x09;
    static const uint8_t lconst_1 = 0x0a;
    static const uint8_t fconst_0 = 0x0b;
    static const uint8_t fconst_1 = 0x0c;
    static const uint8_t fconst_2 = 0x0d;
    static const uint8_t dconst_0 = 0x0e;
    static const uint8_t dconst_1 = 0x0f;
    static const uint8_t bipush = 0x10;
    static const uint8_t sipush = 0x11;
    static const uint8_t ldc = 0x12;
    static const uint8_t ldc_w = 0x13;
    static const uint8_t ldc2_w = 0x14;

    //Loads
    static const uint8_t iload = 0x15;
    static const uint8_t lload = 0x16;
    static const uint8_t fload = 0x17;
    static const uint8_t dload = 0x18;
    static const uint8_t aload = 0x19;
    static const uint8_t iload_0 = 0x1a;
    static const uint8_t iload_1 = 0x1b;
    static const uint8_t iload_2 = 0x1c;
    static const uint8_t iload_3 = 0x1d;
    static const uint8_t lload_0 = 0x1e;
    static const uint8_t lload_1 = 0x1f;
    static const uint8_t lload_2 = 0x20;
    static const uint8_t lload_3 = 0x21;
    static const uint8_t fload_0 = 0x22;
    static const uint8_t fload_1 = 0x23;
    static const uint8_t fload_2 = 0x24;
    static const uint8_t fload_3 = 0x25;
    static const uint8_t dload_0 = 0x26;
    static const uint8_t dload_1 = 0x27;
    static const uint8_t dload_2 = 0x28;
    static const uint8_t dload_3 = 0x29;
    static const uint8_t aload_0 = 0x2a;
    static const uint8_t aload_1 = 0x2b;
    static const uint8_t aload_2 = 0x2c;
    static const uint8_t aload_3 = 0x2d;
    static const uint8_t iaload = 0x2e;
    static const uint8_t laload = 0x2f;
    static const uint8_t faload = 0x30;
    static const uint8_t daload = 0x31;
    static const uint8_t aaload = 0x32;
    static const uint8_t baload = 0x33;
    static const uint8_t caload = 0x34;
    static const uint8_t saload = 0x35;

    //Stores
    static const uint8_t istore = 0x36;
    static const uint8_t lstore = 0x37;
    static const uint8_t fstore = 0x38;
    static const uint8_t dstore = 0x39;
    static const uint8_t astore = 0x3a;
    static const uint8_t istore_0 = 0x3b;
    static const uint8_t istore_1 = 0x3c;
    static const uint8_t istore_2 = 0x3d;
    static const uint8_t istore_3 = 0x3e;
    static const uint8_t lstore_0 = 0x3f;
    static const uint8_t lstore_1 = 0x40;
    static const uint8_t lstore_2 = 0x41;
    static const uint8_t lstore_3 = 0x42;
    static const uint8_t fstore_0 = 0x43;
    static const uint8_t fstore_1 = 0x44;
    static const uint8_t fstore_2 = 0x45;
    static const uint8_t fstore_3 = 0x46;
    static const uint8_t dstore_0 = 0x47;
    static const uint8_t dstore_1 = 0x48;
    static const uint8_t dstore_2 = 0x49;
    static const uint8_t dstore_3 = 0x4a;
    static const uint8_t astore_0 = 0x4b;
    static const uint8_t astore_1 = 0x4c;
    static const uint8_t astore_2 = 0x4d;
    static const uint8_t astore_3 = 0x4e;
    static const uint8_t iastore = 0x4f;
    static const uint8_t lastore = 0x50;
    static const uint8_t fastore = 0x51;
    static const uint8_t dastore = 0x52;
    static const uint8_t aastore = 0x53;
    static const uint8_t bastore = 0x54;
    static const uint8_t castore = 0x55;
    static const uint8_t sastore = 0x56;

    //Stack
    static const uint8_t pop = 0x57;
    static const uint8_t pop2 = 0x58;
    static const uint8_t dup = 0x59;
    static const uint8_t dup_x1 = 0x5a;
    static const uint8_t dup_x2 = 0x5b;
    static const uint8_t dup2 = 0x5c;
    static const uint8_t dup2_x1 = 0x5d;
    static const uint8_t dup2_x2 = 0x5e;
    static const uint8_t swap = 0x5f;

    //Math
    static const uint8_t iadd = 0x60;
    static const uint8_t ladd = 0x61;
    static const uint8_t fadd = 0x62;
    static const uint8_t dadd = 0x63;
    static const uint8_t isub = 0x64;
    static const uint8_t lsub = 0x65;
    static const uint8_t fsub = 0x66;
    static const uint8_t dsub = 0x67;
    static const uint8_t imul = 0x68;
    static const uint8_t lmul = 0x69;
    static const uint8_t fmul = 0x6a;
    static const uint8_t dmul = 0x6b;
    static const uint8_t idiv = 0x6c;
    static const uint8_t ldivOp = 0x6d;
    static const uint8_t fdiv = 0x6e;
    static const uint8_t ddiv = 0x6f;
    static const uint8_t irem = 0x70;
    static const uint8_t lrem = 0x71;
    static const uint8_t frem = 0x72;
    static const uint8_t drem = 0x73;
    static const uint8_t ineg = 0x74;
    static const uint8_t lneg = 0x75;
    static const uint8_t fneg = 0x76;
    static const uint8_t dneg = 0x77;
    static const uint8_t ishl = 0x78;
    static const uint8_t lshl = 0x79;
    static const uint8_t ishr = 0x7a;
    static const uint8_t lshr = 0x7b;
    static const uint8_t iushr = 0x7c;
    static const uint8_t lushr = 0x7d;
    static const uint8_t iand = 0x7e;
    static const uint8_t land = 0x7f;
    static const uint8_t ior = 0x80;
    static const uint8_t lor = 0x81;
    static const uint8_t ixor = 0x82;
    static const uint8_t lxor = 0x83;
    static const uint8_t iinc = 0x84;

    //Conversions
    static const uint8_t i2l = 0x85;
    static const uint8_t i2f = 0x86;
    static const uint8_t i2d = 0x87;
    static const uint8_t l2i = 0x88;
    static const uint8_t l2f = 0x89;
    static const uint8_t l2d = 0x8a;
    static const uint8_t f2i = 0x8b;
    static const uint8_t f2l = 0x8c;
    static const uint8_t f2d = 0x8d;
    static const uint8_t d2i = 0x8e;
    static const uint8_t d2l = 0x8f;
    static const uint8_t d2f = 0x90;
    static const uint8_t i2b = 0x91;
    static const uint8_t i2c = 0x92;
    static const uint8_t i2s = 0x93;

    //Comparisons
    static const uint8_t lcmp = 0x94;
    static const uint8_t fcmpl = 0x95;
    static const uint8_t fcmpg = 0x96;
    static const uint8_t dcmpl = 0x97;
    static const uint8_t dcmpg = 0x98;
    static const uint8_t ifeq = 0x99;
    static const uint8_t ifne = 0x9a;
    static const uint8_t iflt = 0x9b;
    static const uint8_t ifge = 0x9c;
    static const uint8_t ifgt = 0x9d;
    static const uint8_t ifle = 0x9e;
    static const uint8_t if_icmpeq = 0x9f;
    static const uint8_t if_icmpne = 0xa0;
    static const uint8_t if_icmplt = 0xa1;
    static const uint8_t if_icmpge = 0xa2;
    static const uint8_t if_icmpgt = 0xa3;
    static const uint8_t if_icmple = 0xa4;
    static const uint8_t if_acmpeq = 0xa5;
    static const uint8_t if_acmpne = 0xa6;

    //Control
    static const uint8_t gotoOp = 0xa7;
    static const uint8_t jsr = 0xa8;
    static const uint8_t ret = 0xa9;
    static const uint8_t tableswitch = 0xaa;
    static const uint8_t lookupswitch = 0xab;
    static const uint8_t ireturn = 0xac;
    static const uint8_t lreturn = 0xad;
    static const uint8_t freturn = 0xae;
    static const uint8_t dreturn = 0xaf;
    static const uint8_t areturn  = 0xb0;
    static const uint8_t returnOp = 0xb1;

    //References
    static const uint8_t getstatic = 0xb2;
    static const uint8_t putstatic = 0xb3;
    static const uint8_t getfield = 0xb4;
    static const uint8_t putfield = 0xb5;
    static const uint8_t invokevirtual = 0xb6;
    static const uint8_t invokespecial = 0xb7;
    static const uint8_t invokestatic = 0xb8;
    static const uint8_t invokeinterface = 0xb9;
    static const uint8_t invokedynamic = 0xba;
    static const uint8_t newOp = 0xbb;
    static const uint8_t newarray = 0xbc;
    static const uint8_t anewarray = 0xbd;
    static const uint8_t arraylength = 0xbe;
    static const uint8_t athrow = 0xbf;
    // As quatro instrucoes seguintes nao precisam ser implementadas
    static const uint8_t checkcast = 0xc0;
    static const uint8_t instanceof = 0xc1;
    static const uint8_t monitorenter = 0xc2;
    static const uint8_t monitorexit = 0xc3;

    //Extended
    static const uint8_t wide = 0xc4;
    static const uint8_t multianewarray = 0xc5;
    static const uint8_t ifnull = 0xc6;
    static const uint8_t ifnonnull = 0xc7;
    static const uint8_t goto_w = 0xc8;
    static const uint8_t jsr_w = 0xc9;


    //newarray type codes
    static const uint8_t T_BOOLEAN = 4;
    static const uint8_t T_CHAR = 5;
    static const uint8_t T_FLOAT = 6;
    static const uint8_t T_DOUBLE = 7;
    static const uint8_t T_BYTE = 8;
    static const uint8_t T_SHORT = 9;
    static const uint8_t T_INT = 10;
    static const uint8_t T_LONG = 11;
};

#endif