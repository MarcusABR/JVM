/**
 * @file instruction_set.cpp
 * @author André Larrosa Chimpliganond - 190010321
 * @author Marcus Vinicius Oliveira de Abrantes - 190034084
 * @author  Matheus Barbosa e Silva - 190113987
 * @author Moises Felipe Jaco Andrade de Lima - 190018364 
 * @author Thiago Elias dos Reis - 190126892
 * @brief Definicoes da classe InstructionSet
 * @details Atribui ao vetor de conjunto de instrucoes as instrucoes individuais
 * com sua string identificadora e funcao propria.
 *  
**/

#include "../hpp/instruction_set.hpp"

ClassLoader* Instruction::classLoader;

InstructionSet::InstructionSet(ClassLoader * classLoader) {
    this->instructionsCount = 256;
    Instruction::setClassLoader(classLoader);

    instructionSet[Instruction::nop] = Instruction("nop", 0, Instruction::nopFunction);
    instructionSet[Instruction::aconst_null] = Instruction("aconst_null", 0, Instruction::aconst_nullFunction);
    instructionSet[Instruction::iconst_m1] = Instruction("iconst_m1", 0, Instruction::iconst_m1Function);
    instructionSet[Instruction::iconst_0] = Instruction("iconst_0", 0, Instruction::iconst_0Function);
    instructionSet[Instruction::iconst_1] = Instruction("iconst_1", 0, Instruction::iconst_1Function);
    instructionSet[Instruction::iconst_2] = Instruction("iconst_2", 0, Instruction::iconst_2Function);
    instructionSet[Instruction::iconst_3] = Instruction("iconst_3", 0, Instruction::iconst_3Function);
    instructionSet[Instruction::iconst_4] = Instruction("iconst_4", 0, Instruction::iconst_4Function);
    instructionSet[Instruction::iconst_5] = Instruction("iconst_5", 0, Instruction::iconst_5Function);
    instructionSet[Instruction::lconst_0] = Instruction("lconst_0", 0, Instruction::lconst_0Function);
    instructionSet[Instruction::lconst_1] = Instruction("lconst_1", 0, Instruction::lconst_1Function);
    instructionSet[Instruction::fconst_0] = Instruction("fconst_0", 0, Instruction::fconst_0Function);
    instructionSet[Instruction::fconst_1] = Instruction("fconst_1", 0, Instruction::fconst_1Function);
    instructionSet[Instruction::fconst_2] = Instruction("fconst_2", 0, Instruction::fconst_2Function);
    instructionSet[Instruction::dconst_0] = Instruction("dconst_0", 0, Instruction::dconst_0Function);
    instructionSet[Instruction::dconst_1] = Instruction("dconst_1", 0, Instruction::dconst_1Function);
    instructionSet[Instruction::bipush] = Instruction("bipush", 1, Instruction::bipushFunction);
    instructionSet[Instruction::sipush] = Instruction("sipush", 2, Instruction::sipushFunction);
    instructionSet[Instruction::ldc] = Instruction("ldc", 1, Instruction::ldcFunction);
    instructionSet[Instruction::ldc_w] = Instruction("ldc_w", 2, Instruction::ldc_wFunction);
    instructionSet[Instruction::ldc2_w] = Instruction("ldc2_w", 2, Instruction::ldc2_wFunction);

    //Loads
    instructionSet[Instruction::iload] = Instruction("iload", 1, Instruction::iloadFunction);
    instructionSet[Instruction::lload] = Instruction("lload", 1, Instruction::lloadFunction);
    instructionSet[Instruction::fload] = Instruction("fload", 1, Instruction::floadFunction);
    instructionSet[Instruction::dload] = Instruction("dload", 1, Instruction::dloadFunction);
    instructionSet[Instruction::aload] = Instruction("aload", 1, Instruction::aloadFunction);
    instructionSet[Instruction::iload_0] = Instruction("iload_0", 0, Instruction::iload_0Function);
    instructionSet[Instruction::iload_1] = Instruction("iload_1", 0, Instruction::iload_1Function);
    instructionSet[Instruction::iload_2] = Instruction("iload_2", 0, Instruction::iload_2Function);
    instructionSet[Instruction::iload_3] = Instruction("iload_3", 0, Instruction::iload_3Function);
    instructionSet[Instruction::lload_0] = Instruction("lload_0", 0, Instruction::lload_0Function);
    instructionSet[Instruction::lload_1] = Instruction("lload_1", 0, Instruction::lload_1Function);
    instructionSet[Instruction::lload_2] = Instruction("lload_2", 0, Instruction::lload_2Function);
    instructionSet[Instruction::lload_3] = Instruction("lload_3", 0, Instruction::lload_3Function);
    instructionSet[Instruction::fload_0] = Instruction("fload_0", 0, Instruction::fload_0Function);
    instructionSet[Instruction::fload_1] = Instruction("fload_1", 0, Instruction::fload_1Function);
    instructionSet[Instruction::fload_2] = Instruction("fload_2", 0, Instruction::fload_2Function);
    instructionSet[Instruction::fload_3] = Instruction("fload_3", 0, Instruction::fload_3Function);
    instructionSet[Instruction::dload_0] = Instruction("dload_0", 0, Instruction::dload_0Function);
    instructionSet[Instruction::dload_1] = Instruction("dload_1", 0, Instruction::dload_1Function);
    instructionSet[Instruction::dload_2] = Instruction("dload_2", 0, Instruction::dload_2Function);
    instructionSet[Instruction::dload_3] = Instruction("dload_3", 0, Instruction::dload_3Function);
    instructionSet[Instruction::aload_0] = Instruction("aload_0", 0, Instruction::aload_0Function);
    instructionSet[Instruction::aload_1] = Instruction("aload_1", 0, Instruction::aload_1Function);
    instructionSet[Instruction::aload_2] = Instruction("aload_2", 0, Instruction::aload_2Function);
    instructionSet[Instruction::aload_3] = Instruction("aload_3", 0, Instruction::aload_3Function);
    instructionSet[Instruction::iaload] = Instruction("iaload", 0, Instruction::ialoadFunction);
    instructionSet[Instruction::laload] = Instruction("laload", 0, Instruction::laloadFunction);
    instructionSet[Instruction::faload] = Instruction("faload", 0, Instruction::faloadFunction);
    instructionSet[Instruction::daload] = Instruction("daload", 0, Instruction::daloadFunction);
    instructionSet[Instruction::aaload] = Instruction("aaload", 0, Instruction::aaloadFunction);
    instructionSet[Instruction::baload] = Instruction("baload", 0, Instruction::baloadFunction);
    instructionSet[Instruction::caload] = Instruction("caload", 0, Instruction::caloadFunction);
    instructionSet[Instruction::saload] = Instruction("saload", 0, Instruction::saloadFunction);

    //Stores
    instructionSet[Instruction::istore] = Instruction("istore", 1, Instruction::istoreFunction);
    instructionSet[Instruction::lstore] = Instruction("lstore", 1, Instruction::lstoreFunction);
    instructionSet[Instruction::fstore] = Instruction("fstore", 1, Instruction::fstoreFunction);
    instructionSet[Instruction::dstore] = Instruction("dstore", 1, Instruction::dstoreFunction);
    instructionSet[Instruction::astore] = Instruction("astore", 1, Instruction::astoreFunction);
    instructionSet[Instruction::istore_0] = Instruction("istore_0", 0, Instruction::istore_0Function);
    instructionSet[Instruction::istore_1] = Instruction("istore_1", 0, Instruction::istore_1Function);
    instructionSet[Instruction::istore_2] = Instruction("istore_2", 0, Instruction::istore_2Function);
    instructionSet[Instruction::istore_3] = Instruction("istore_3", 0, Instruction::istore_3Function);
    instructionSet[Instruction::lstore_0] = Instruction("lstore_0", 0, Instruction::lstore_0Function);
    instructionSet[Instruction::lstore_1] = Instruction("lstore_1", 0, Instruction::lstore_1Function);
    instructionSet[Instruction::lstore_2] = Instruction("lstore_2", 0, Instruction::lstore_2Function);
    instructionSet[Instruction::lstore_3] = Instruction("lstore_3", 0, Instruction::lstore_3Function);
    instructionSet[Instruction::fstore_0] = Instruction("fstore_0", 0, Instruction::fstore_0Function);
    instructionSet[Instruction::fstore_1] = Instruction("fstore_1", 0, Instruction::fstore_1Function);
    instructionSet[Instruction::fstore_2] = Instruction("fstore_2", 0, Instruction::fstore_2Function);
    instructionSet[Instruction::fstore_3] = Instruction("fstore_3", 0, Instruction::fstore_3Function);
    instructionSet[Instruction::dstore_0] = Instruction("dstore_0", 0, Instruction::dstore_0Function);
    instructionSet[Instruction::dstore_1] = Instruction("dstore_1", 0, Instruction::dstore_1Function);
    instructionSet[Instruction::dstore_2] = Instruction("dstore_2", 0, Instruction::dstore_2Function);
    instructionSet[Instruction::dstore_3] = Instruction("dstore_3", 0, Instruction::dstore_3Function);
    instructionSet[Instruction::astore_0] = Instruction("astore_0", 0, Instruction::astore_0Function);
    instructionSet[Instruction::astore_1] = Instruction("astore_1", 0, Instruction::astore_1Function);
    instructionSet[Instruction::astore_2] = Instruction("astore_2", 0, Instruction::astore_2Function);
    instructionSet[Instruction::astore_3] = Instruction("astore_3", 0, Instruction::astore_3Function);
    instructionSet[Instruction::iastore] = Instruction("iastore", 0, Instruction::iastoreFunction);
    instructionSet[Instruction::lastore] = Instruction("lastore", 0, Instruction::lastoreFunction);
    instructionSet[Instruction::fastore] = Instruction("fastore", 0, Instruction::fastoreFunction);
    instructionSet[Instruction::dastore] = Instruction("dastore", 0, Instruction::dastoreFunction);
    instructionSet[Instruction::aastore] = Instruction("aastore", 0, Instruction::aastoreFunction);
    instructionSet[Instruction::bastore] = Instruction("bastore", 0, Instruction::bastoreFunction);
    instructionSet[Instruction::castore] = Instruction("castore", 0, Instruction::castoreFunction);
    instructionSet[Instruction::sastore] = Instruction("sastore", 0, Instruction::sastoreFunction);

    //Stack
    instructionSet[Instruction::pop] = Instruction("pop", 0, Instruction::popFunction);
    instructionSet[Instruction::pop2] = Instruction("pop2", 0, Instruction::pop2Function);
    instructionSet[Instruction::dup] = Instruction("dup", 0, Instruction::dupFunction);
    instructionSet[Instruction::dup_x1] = Instruction("dup_x1", 0, Instruction::dup_x1Function);
    instructionSet[Instruction::dup_x2] = Instruction("dup_x2", 0, Instruction::dup_x2Function);
    instructionSet[Instruction::dup2] = Instruction("dup2", 0, Instruction::dup2Function);
    instructionSet[Instruction::dup2_x1] = Instruction("dup2_x1", 0, Instruction::dup2_x1Function);
    instructionSet[Instruction::dup2_x2] = Instruction("dup2_x2", 0, Instruction::dup2_x2Function);
    instructionSet[Instruction::swap] = Instruction("swap", 0, Instruction::swapFunction);

    //Math
    instructionSet[Instruction::iadd] = Instruction("iadd", 0, Instruction::iaddFunction);
    instructionSet[Instruction::ladd] = Instruction("ladd", 0, Instruction::laddFunction);
    instructionSet[Instruction::fadd] = Instruction("fadd", 0, Instruction::faddFunction);
    instructionSet[Instruction::dadd] = Instruction("dadd", 0, Instruction::daddFunction);
    instructionSet[Instruction::isub] = Instruction("isub", 0, Instruction::isubFunction);
    instructionSet[Instruction::lsub] = Instruction("lsub", 0, Instruction::lsubFunction);
    instructionSet[Instruction::fsub] = Instruction("fsub", 0, Instruction::fsubFunction);
    instructionSet[Instruction::dsub] = Instruction("dsub", 0, Instruction::dsubFunction);
    instructionSet[Instruction::imul] = Instruction("imul", 0, Instruction::imulFunction);
    instructionSet[Instruction::lmul] = Instruction("lmul", 0, Instruction::lmulFunction);
    instructionSet[Instruction::fmul] = Instruction("fmul", 0, Instruction::fmulFunction);
    instructionSet[Instruction::dmul] = Instruction("dmul", 0, Instruction::dmulFunction);
    instructionSet[Instruction::idiv] = Instruction("idiv", 0, Instruction::idivFunction);
    instructionSet[Instruction::ldivOp] = Instruction("ldiv", 0, Instruction::ldivOpFunction);
    instructionSet[Instruction::fdiv] = Instruction("fdiv", 0, Instruction::fdivFunction);
    instructionSet[Instruction::ddiv] = Instruction("ddiv", 0, Instruction::ddivFunction);
    instructionSet[Instruction::irem] = Instruction("irem", 0, Instruction::iremFunction);
    instructionSet[Instruction::lrem] = Instruction("lrem", 0, Instruction::lremFunction);
    instructionSet[Instruction::frem] = Instruction("frem", 0, Instruction::fremFunction);
    instructionSet[Instruction::drem] = Instruction("drem", 0, Instruction::dremFunction);
    instructionSet[Instruction::ineg] = Instruction("ineg", 0, Instruction::inegFunction);
    instructionSet[Instruction::lneg] = Instruction("lneg", 0, Instruction::lnegFunction);
    instructionSet[Instruction::fneg] = Instruction("fneg", 0, Instruction::fnegFunction);
    instructionSet[Instruction::dneg] = Instruction("dneg", 0, Instruction::dnegFunction);
    instructionSet[Instruction::ishl] = Instruction("ishl", 0, Instruction::ishlFunction);
    instructionSet[Instruction::lshl] = Instruction("lshl", 0, Instruction::lshlFunction);
    instructionSet[Instruction::ishr] = Instruction("ishr", 0, Instruction::ishrFunction);
    instructionSet[Instruction::lshr] = Instruction("lshr", 0, Instruction::lshrFunction);
    instructionSet[Instruction::iushr] = Instruction("iushr", 0, Instruction::iushrFunction);
    instructionSet[Instruction::lushr] = Instruction("lushr", 0, Instruction::lushrFunction);
    instructionSet[Instruction::iand] = Instruction("iand", 0, Instruction::iandFunction);
    instructionSet[Instruction::land] = Instruction("land", 0, Instruction::landFunction);
    instructionSet[Instruction::ior] = Instruction("ior", 0, Instruction::iorFunction);
    instructionSet[Instruction::lor] = Instruction("lor", 0, Instruction::lorFunction);
    instructionSet[Instruction::ixor] = Instruction("ixor", 0, Instruction::ixorFunction);
    instructionSet[Instruction::lxor] = Instruction("lxor", 0, Instruction::lxorFunction);
    instructionSet[Instruction::iinc] = Instruction("iinc", 2, Instruction::iincFunction);

    //Conversions
    instructionSet[Instruction::i2l] = Instruction("i2l", 0, Instruction::i2lFunction);
    instructionSet[Instruction::i2f] = Instruction("i2f", 0, Instruction::i2fFunction);
    instructionSet[Instruction::i2d] = Instruction("i2d", 0, Instruction::i2dFunction);
    instructionSet[Instruction::l2i] = Instruction("l2i", 0, Instruction::l2iFunction);
    instructionSet[Instruction::l2f] = Instruction("l2f", 0, Instruction::l2fFunction);
    instructionSet[Instruction::l2d] = Instruction("l2d", 0, Instruction::l2dFunction);
    instructionSet[Instruction::f2i] = Instruction("f2i", 0, Instruction::f2iFunction);
    instructionSet[Instruction::f2l] = Instruction("f2l", 0, Instruction::f2lFunction);
    instructionSet[Instruction::f2d] = Instruction("f2d", 0, Instruction::f2dFunction);
    instructionSet[Instruction::d2i] = Instruction("d2i", 0, Instruction::d2iFunction);
    instructionSet[Instruction::d2l] = Instruction("d2l", 0, Instruction::d2lFunction);
    instructionSet[Instruction::d2f] = Instruction("d2f", 0, Instruction::d2fFunction);
    instructionSet[Instruction::i2b] = Instruction("i2b", 0, Instruction::i2bFunction);
    instructionSet[Instruction::i2c] = Instruction("i2c", 0, Instruction::i2cFunction);
    instructionSet[Instruction::i2s] = Instruction("i2s", 0, Instruction::i2sFunction);

    //Comparisons
    instructionSet[Instruction::lcmp] = Instruction("lcmp", 0, Instruction::lcmpFunction);
    instructionSet[Instruction::fcmpl] = Instruction("fcmpl", 0, Instruction::fcmplFunction);
    instructionSet[Instruction::fcmpg] = Instruction("fcmpg", 0, Instruction::fcmpgFunction);
    instructionSet[Instruction::dcmpl] = Instruction("dcmpl", 0, Instruction::dcmplFunction);
    instructionSet[Instruction::dcmpg] = Instruction("dcmpg", 0, Instruction::dcmpgFunction);
    instructionSet[Instruction::ifeq] = Instruction("ifeq", 2, Instruction::ifeqFunction);
    instructionSet[Instruction::ifne] = Instruction("ifne", 2, Instruction::ifneFunction);
    instructionSet[Instruction::iflt] = Instruction("iflt", 2, Instruction::ifltFunction);
    instructionSet[Instruction::ifge] = Instruction("ifge", 2, Instruction::ifgeFunction);
    instructionSet[Instruction::ifgt] = Instruction("ifgt", 2, Instruction::ifgtFunction);
    instructionSet[Instruction::ifle] = Instruction("ifle", 2, Instruction::ifleFunction);
    instructionSet[Instruction::if_icmpeq] = Instruction("if_icmpeq", 2, Instruction::if_icmpeqFunction);
    instructionSet[Instruction::if_icmpne] = Instruction("if_icmpne", 2, Instruction::if_icmpneFunction);
    instructionSet[Instruction::if_icmplt] = Instruction("if_icmplt", 2, Instruction::if_icmpltFunction);
    instructionSet[Instruction::if_icmpge] = Instruction("if_icmpge", 2, Instruction::if_icmpgeFunction);
    instructionSet[Instruction::if_icmpgt] = Instruction("if_icmpgt", 2, Instruction::if_icmpgtFunction);
    instructionSet[Instruction::if_icmple] = Instruction("if_icmple", 2, Instruction::if_icmpleFunction);
    instructionSet[Instruction::if_acmpeq] = Instruction("if_acmpeq", 2, Instruction::if_acmpeqFunction);
    instructionSet[Instruction::if_acmpne] = Instruction("if_acmpne", 2, Instruction::if_acmpneFunction);

    //Control
    instructionSet[Instruction::gotoOp] = Instruction("goto", 2, Instruction::gotoOpFunction);
    instructionSet[Instruction::jsr] = Instruction("jsr", 2, Instruction::jsrFunction);
    instructionSet[Instruction::ret] = Instruction("ret", 1, Instruction::retFunction);
    instructionSet[Instruction::tableswitch] = Instruction("tableswitch", 16, Instruction::tableswitchFunction); //Ainda nao verifiquei como implementar
    instructionSet[Instruction::lookupswitch] = Instruction("lookupswitch", 8, Instruction::lookupswitchFunction); // Ainda nao verifiquei como implementar
    instructionSet[Instruction::ireturn] = Instruction("ireturn", 0, Instruction::ireturnFunction);
    instructionSet[Instruction::lreturn] = Instruction("lreturn", 0, Instruction::lreturnFunction);
    instructionSet[Instruction::freturn] = Instruction("freturn", 0, Instruction::freturnFunction);
    instructionSet[Instruction::dreturn] = Instruction("dreturn", 0, Instruction::dreturnFunction);
    instructionSet[Instruction::areturn ] = Instruction("areturn", 0, Instruction::areturnFunction);
    instructionSet[Instruction::returnOp] = Instruction("return", 0, Instruction::returnOpFunction);

    //References
    //instructionSet[Instruction::getstatic] = Instruction("getstatic", 2, Instruction::getstaticFunction);
    //instructionSet[Instruction::putstatic] = Instruction("putstatic", 2, Instruction::putstaticFunction);
    //instructionSet[Instruction::getfield] = Instruction("getfield", 2, Instruction::getfieldFunction);
    //instructionSet[Instruction::putfield] = Instruction("putfield", 2, Instruction::putfieldFunction);
    //instructionSet[Instruction::invokevirtual] = Instruction("invokevirtual", 2, Instruction::invokevirtualFunction);
    //instructionSet[Instruction::invokespecial] = Instruction("invokespecial", 2, Instruction::invokespecialFunction);
    //instructionSet[Instruction::invokestatic] = Instruction("invokestatic", 2, Instruction::invokestaticFunction);
    //instructionSet[Instruction::invokeinterface] = Instruction("invokeinterface", 4, Instruction::invokeinterfaceFunction);
    //instructionSet[Instruction::invokedynamic] = Instruction("invokedynamic", 4, Instruction::invokedynamicFunction);
    //instructionSet[Instruction::newOp] = Instruction("new", 2, Instruction::newOpFunction);
    //instructionSet[Instruction::newarray] = Instruction("newarray", 1, Instruction::newarrayFunction);
    instructionSet[Instruction::anewarray] = Instruction("anewarray", 2, Instruction::anewarrayFunction);
    instructionSet[Instruction::arraylength] = Instruction("arraylength", 0, Instruction::arraylengthFunction);
    instructionSet[Instruction::athrow] = Instruction("athrow", 0, Instruction::athrowFunction);
    // As quatro instrucoes seguintes nao precisam ser implementadas
    instructionSet[Instruction::checkcast] = Instruction("checkcast", 2, Instruction::checkcastFunction);
    instructionSet[Instruction::instanceof] = Instruction("instanceof", 2, Instruction::instanceofFunction);
    instructionSet[Instruction::monitorenter] = Instruction("monitorenter", 0, Instruction::monitorenterFunction);
    instructionSet[Instruction::monitorexit] = Instruction("monitorexit", 0, Instruction::monitorexitFunction);

    //Extended
    instructionSet[Instruction::wide] = Instruction("wide", 5, Instruction::wideFunction); //wide eh uma instrucao que tem dois formatos!! tem que ver isso talkey
    instructionSet[Instruction::multianewarray] = Instruction("multianewarray", 3, Instruction::multianewarrayFunction);
    instructionSet[Instruction::ifnull] = Instruction("ifnull", 2, Instruction::ifnullFunction);
    instructionSet[Instruction::ifnonnull] = Instruction("ifnonnull", 2, Instruction::ifnonnullFunction);
    instructionSet[Instruction::goto_w] = Instruction("goto_w", 4, Instruction::goto_wFunction);
    instructionSet[Instruction::jsr_w] = Instruction("jsr_w", 4, Instruction::jsr_wFunction);
}