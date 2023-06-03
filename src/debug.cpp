#include "../include/bytecode.hpp"
#include "../include/dump_class_file.hpp"
#include <iostream>

using namespace std;
extern ofstream outfile;

/**
 * @brief Dumps the information about the bipush instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void bipush_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 byte = code[++code_index];
    outfile << " " << (int)byte;
}

/**
 * @brief Dumps the information about the iinc instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void iinc_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 index = code[++code_index];
    u1 _const = code[++code_index];
    outfile << " " << (int)index << " by " << (int)_const;
}

/**
 * @brief Dumps the information about the iinc(wide) instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void iinc_wide_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 indexbyte1 = code[++code_index];
    u1 indexbyte2 = code[++code_index];
    u1 constbyte1 = code[++code_index];
    u1 constbyte2 = code[++code_index];
    u2 index = ((u2)indexbyte1 << 8) | indexbyte2;
    u2 _const = ((u2)constbyte1 << 8) | constbyte2;

    outfile << " #" << (int)index << " <" << (int)_const << ">  ";
}

/**
 * @brief Dumps the information about the index instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void index_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 index = code[++code_index];
    outfile << " " << (int)index;
}

/**
 * @brief Dumps the information about the index(wide) instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void index_wide_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 indexbyte1 = code[++code_index];
    u1 indexbyte2 = code[++code_index];
    u2 index = ((u2)indexbyte1 << 8) | indexbyte2;
    outfile << " #" << (int)index;
}

/**
 * @brief Dumps the information about the invoke instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void invoke_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    reference_debug(code_index, constant_pool, code);
    u1 count = code[++code_index];
    u1 zero = code[++code_index];
}

/**
 * @brief Dumps the information about the jump instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void jump_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    s2 old_index = code_index;
    u1 branchbyte1  = code[++code_index];
    u1 branchbyte2  = code[++code_index];
    s2 branchoffset = ((s2)branchbyte1 << 8) | branchbyte2;
    outfile << " " << old_index + branchoffset << " (" << branchoffset << ")";
}

/**
 * @brief Dumps the information about the jump(wide) instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void jump_wide_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    s4 old_index = code_index;
    u1 branchbyte1  = code[++code_index]; 
    u1 branchbyte2  = code[++code_index];
    u1 branchbyte3  = code[++code_index];
    u1 branchbyte4  = code[++code_index];
    s4 branchoffset = ((s4)branchbyte1 << 24) | ((s4)branchbyte2 << 16) | ((s4)branchbyte3 << 8) | branchbyte4;
    outfile << " " << old_index + branchoffset << " (" << branchoffset << ")";
}

/**
 * @brief Dumps the information about the lookupswitch instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void lookupswitch_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u4 old_index = code_index;
    u1 padding = (++code_index) % 4;
    s4 defaultbyte1 = code[padding + code_index++] << 24;
    s4 defaultbyte2 = code[padding + code_index++] << 16;
    s4 defaultbyte3 = code[padding + code_index++] << 8;
    s4 defaultbyte4 = code[padding + code_index++];
    s4 defaultbytes = defaultbyte1 | defaultbyte2 | defaultbyte3 | defaultbyte4;

    s4 npairs1 = (s4) code[padding + code_index++] << 24;
    s4 npairs2 = (s4) code[padding + code_index++] << 16;
    s4 npairs3 = (s4) code[padding + code_index++] << 8;
    s4 npairs4 = (s4) code[padding + code_index++];
    s4 npairs  = npairs1 | npairs2 | npairs3 | npairs4;

    outfile << " " << npairs << endl;

    for (s4 n = 0; n < npairs; n++)
    {
        s4 matchbyte1 = code[code_index + padding++] << 24;
        s4 matchbyte2 = code[code_index + padding++] << 16;
        s4 matchbyte3 = code[code_index + padding++] << 8;
        s4 matchbyte4 = code[code_index + padding++];
        s4 matchbytes = matchbyte1 | matchbyte2 | matchbyte3 | matchbyte4; 
        
        s4 offset1 = code[code_index + padding++] << 24;
        s4 offset2 = code[code_index + padding++] << 16;
        s4 offset3 = code[code_index + padding++] << 8;
        s4 offset4 = code[code_index + padding++];
        s4 offset = offset1 | offset2 | offset3 | offset4;

        outfile << "    " << matchbytes << ": " << old_index + offset << " (" << offset << ")" << endl;
    }
    outfile << "    default: " << old_index + defaultbytes << " (" << defaultbytes << ")";
    code_index += padding - 1;
}

/**
 * @brief Dumps the information about the multinewarray instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void multianewarray_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 indexbyte1 = code[++code_index];
    u1 indexbyte2 = code[++code_index];
    u1 dimensions = code[++code_index];
    u2 index = (indexbyte1 << 8) | indexbyte2;
    
    outfile << " #" << (int)index;
    auto reference = to_cp_info(constant_pool[index - 1]);
    outfile << " <" << reference->get_content(constant_pool) << "> ";
    outfile << "dim " << (int) dimensions;
}

/**
 * @brief Dumps the information about the newarray instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void newarray_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 atype = code[++code_index];
    map<u1, string> types = {
        {4,  "T_BOOLEAN"},
        {5,  "T_CHAR"},
        {6,  "T_FLOAT"},
        {7,  "T_DOUBLE"},
        {8,  "T_BYTE"},
        {9,  "T_SHORT"},
        {10, "T_INT"}, 
        {11, "T_LONG"}
    };
    outfile << " " << types[atype];
}

/**
 * @brief Dumps the information about the reference instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void reference_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code) 
{
    u1 index = code[++code_index];

    outfile << " #" << (int)index;
    auto reference = to_cp_info(constant_pool[index - 1]);
    outfile << " <" << reference->get_content(constant_pool) << ">  ";
}

/**
 * @brief Dumps the information about the reference(wide) instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void reference_wide_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 indexbyte1 = code[++code_index];
    u1 indexbyte2 = code[++code_index];
    u2 index = ((u2)indexbyte1 << 8) | indexbyte2;

    outfile << " #" << index;
    auto reference = to_cp_info(constant_pool[index - 1]);
    outfile << " <" << reference->get_content(constant_pool) << ">  ";
}

/**
 * @brief Dumps the information about the sipush instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void sipush_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u1 byte1 = code[++code_index];
    u1 byte2 = code[++code_index];
    u2 short_val = ((u1)byte1 << 8) | byte2; 
    outfile << " " << (int)short_val;
}

// no examples to debug tableswitch! :D
/**
 * @brief Dumps the information about the tableswitch instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void tableswitch_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code)
{
    u4 padding = (++code_index) % 4;
    auto defaultbyte1 = code[padding + code_index++] << 24;
    auto defaultbyte2 = code[padding + code_index++] << 16;
    auto defaultbyte3 = code[padding + code_index++] << 8;
    auto defaultbyte4 = code[padding + code_index++];
    auto defaultbytes = defaultbyte1 | defaultbyte2 | defaultbyte3 | defaultbyte4;

    auto lowbytes1 = code[padding + code_index++] << 24;
    auto lowbytes2 = code[padding + code_index++] << 16;
    auto lowbytes3 = code[padding + code_index++] << 8;
    auto lowbytes4 = code[padding + code_index++];
    auto lowbytes  = lowbytes1 | lowbytes2 | lowbytes3 | lowbytes4;

    auto offsets = defaultbytes - lowbytes + 1;

    for (auto n = 0; n < offsets; n++)
    {
        auto highbytes1 = code[padding + code_index++] << 24;
        auto highbytes2 = code[padding + code_index++] << 16;
        auto highbytes3 = code[padding + code_index++] << 8;
        auto highbytes4 = code[padding + code_index++];
        auto highbytes  = highbytes1 | highbytes2 | highbytes3 | highbytes4;
        
        outfile << lowbytes << ": " << code_index + highbytes << " (" << highbytes << ")" << endl;
        lowbytes++;
    }
}

/**
 * @brief Dumps the information about the wide instruction
 * @param code_index the current index of the bytecode
 * @param constant_pool the class constant pool
 * @param code the instruction vector
 */
void wide_debug(int &code_index, cp_info_vector &constant_pool, bytestream &code) 
{
    u1 bytecode   = code[++code_index];
    u1 indexbyte1 = code[++code_index];
    u1 indexbyte2 = code[++code_index];

    if (!mnemonic.count(bytecode))
    {
        cout << "Instrução não encontrada" << endl;
        return;
    }

    if (bytecode == 0x84) // iinc
        iinc_wide_debug(code_index, constant_pool, code);
    else if (bytecode == 0x19) // aload
        reference_wide_debug(code_index, constant_pool, code);
    else
        index_wide_debug(code_index, constant_pool, code);

    outfile << endl;
}