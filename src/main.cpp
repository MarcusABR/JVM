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

   print_all(*entry_file, opts.filename);

    delete entry_file;

    return 0;
}