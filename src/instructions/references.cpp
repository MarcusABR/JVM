#include "../../include/instructions/references.hpp"
#include "../../include/utils.hpp"
#include <iostream>
#include <string.h>

void getstatic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();
    u1 indexbyte1 = code[++top_frame.pc];
    u1 indexbyte2 = code[++top_frame.pc];
    u2 index = ((u2)indexbyte1 << 8) | indexbyte2;

    auto reference = to_cp_info(constant_pool[index-1]);

    if (!reference)
    {
        cout << "Doesn't exist data in index: " << endl;
        return;
    }

    if (reference->tag != 9) // TAG_REF_CMP
    {
        cout << "It's not possible access a static field with wrong reference" << endl;
        return;
    }

    string class_name = reference->get_content(constant_pool);

    cout << "[GETSTATIC] Class name: " << class_name << endl;

    if(class_name.substr(0, 16) != "java/lang/System")
    {
        cout << "As 'java/lang/System', doesn't need" << endl;
        top_frame.pc++;
        stack_f->pop();
        stack_f->push(top_frame);
        return;
    }
    top_frame.pc++;
    stack_f->pop();
    stack_f->push(top_frame);
}

void putstatic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void getfield(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void putfield(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void invokevirtual(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    auto top_frame = stack_f->top();

    auto indexbyte1 = code[++top_frame.pc];
    auto indexbyte2 = code[++top_frame.pc];
    auto index = (indexbyte1 << 8) | indexbyte2;

    auto methodref = to_cp_info(constant_pool[index - 1]);

    top_frame.pc++;

    if (!methodref)
    {
        cout << "Doesn't exist data in index: " << endl;
        return;
    }

    if (methodref->tag != 10)
    {
        cout << "It's not possible access a static field with wrong reference" << endl;
        return;
    }

    string class_name = methodref->_methodref->get_class_name(constant_pool);
    string method_name = methodref->_methodref->get_method_name(constant_pool);
    string descriptor = methodref->_methodref->get_method_descriptor(constant_pool);

    if (strstr(class_name.c_str(), "java/"))
    {
        if (class_name == "java/io/PrintStream" && (method_name == "println" || method_name == "print"))
        {
            if (descriptor != "()V")
            {
                if(method_name == "println")
                    cout << endl;
                cout << endl;
            }
        }
    }

    stack_f->pop();
    stack_f->push(top_frame);

    cout << "[INVOKE_VIRTUAL] index: " << (u4) index << endl;
}

void invokespecial(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void invokestatic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void invokeinterface(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void invokedynamic(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void _new(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void newarray(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void anewarray(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void arraylength(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void athrow(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void checkcast(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void instanceof(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void monitorenter(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}

void monitorexit(cp_info_vector &constant_pool, bytestream &code, stack<frame_t> *stack_f)
{
    exit(1);
}