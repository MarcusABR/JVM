
#include <iostream>
#include <fstream>
#include "../hpp/class_file.hpp"
#include "../hpp/class_loader.hpp"
#include "../hpp/libraries.hpp"
#include "../cpp/leitor_exibidor.cpp"
#include "../hpp/execution_engine.hpp"

using namespace std;

string getProjectPath(string commandLinePath) {
    int i = commandLinePath.size()-1;

    #if defined(_WIN32)
    while (i >= 0 && commandLinePath[i] != '\\') {
        i--;
    }
    #else
    while (i >= 0 && commandLinePath[i] != '/') {
        i--;
    }
    #endif

    return commandLinePath.substr(0, i+1);
}

string getClassName(string commandLinePath) {
    int i = commandLinePath.size()-1;

    #if defined(_WIN32)
    while (i >= 0 && commandLinePath[i] != '\\') {
        i--;
    }
    #else
    while (i >= 0 && commandLinePath[i] != '/') {
        i--;
    }
    #endif

    return commandLinePath.substr(i+1, commandLinePath.size());
}

int main(int argc, char *argv[]) {
    if (argc != 3)  {
        cout << "Numero incorreto de argumentos especificado" << endl;
    }
    else {
        // ClassFile classFile;
        // string projectPath = getProjectPath(argv[2]);
        // string className = getClassName(argv[2]);
        // ClassLoader classLoader(getProjectPath(argv[2]));
        // MethodArea methodArea;

        // classLoader.setMethodArea(&methodArea);
        // classFile = classLoader.loadClassFile(className);

        string option = argv[1];

        if (option.compare("-e") == 0) {
            printf("e\n");

            // ClassPrinter classPrinter(classFile, &instructionSet); //Trocar pelo antigo
            auto nome_arquivo = static_cast<string>(argv[argc - 1]);

            printf("nome_arquivo\n");
    
            ClassLoader loader;

            printf("loader\n");

            class_file *arquivo_de_entrada = loader.carregar(nome_arquivo);

            printf("class_file\n");

            ler_exibir_arquivo(*arquivo_de_entrada, nome_arquivo);

            delete arquivo_de_entrada;
        }
        else if (option.compare("-i") == 0) {
            printf("i\n");
            //string projectPath = getProjectPath(argv[2]);

            //classLoader.loadSuperClasses(&classFile);
            
            auto nome_arquivo = static_cast<string>(argv[argc - 1]);
            ClassLoader loader;
            class_file *arquivo_de_entrada = loader.carregar(nome_arquivo);

            InstructionSet instructionSet(&loader); 

            //Inicio da execucao do programa
            //ExecutionEngine executionEngine(&classFile, &methodArea, &instructionSet);
            ExecutionEngine executionEngine(arquivo_de_entrada, &instructionSet);
            executionEngine.execute();
        }
        else {
            cout << "O segundo argumento deve ser -e para exibidor ou -i para interpredaor" << endl;
        }
    }

    printf("fim\n");
    return 0;
}