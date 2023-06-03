#include "../include/libraries.hpp"

using namespace std;

/**
 * @brief Entry point of the JVM
 * @param argc number of args
 * @param argv vector of args (the .class file)
 * @return the status of the execution 
 */
int main(int argc, char** argv) 
{
    CmdArgs opts;
    opts.init(argc, argv);

    ClassLoader loader;
    class_file *entry_file = loader.load(opts.filename);

    if (opts.read_bytecode)
        print_all(*entry_file, opts.filename);
    else
    {
        JVMInterpreter interpreter;
        interpreter.run(entry_file);
    }

    delete entry_file;

    return 0;
}