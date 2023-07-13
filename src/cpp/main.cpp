/**
 * @file main.cpp
 * @author Ayssa Giovanna de Oliveira Marques - 170100065
 * @author Fernanda Macedo de Sousa - 170010058
 * @author Gabriel dos Santos Martins - 150126298
 * @author Lucas Raphael Ferreira de Miranda - 180046799 
 * @author Otávio Souza de Oliveira 150143401
 * @brief Arquivo principal, o qual contém a execução da JVM
 * @details O arquivo a seguir contém a implementação da seleção de execução pelo usuário entre leitor/exibidor ou interpretador
 * @see ClassFile.hpp
 * @see ClassLoader.hpp
 * @see ClassPrinter.hpp
 * @see ExecutionEngine.hpp
 */

#include <iostream>
#include <fstream>
#include "../hpp/ClassFile.hpp"
#include "../hpp/ClassLoader.hpp"
#include "../hpp/ClassPrinter.hpp"
#include "../hpp/ExecutionEngine.hpp"

using namespace std;

/**
 * @brief Função utilizada para retornar o caminho do arquivo .class
 * 
 * @param commandLinePath 
 * @return string com o caminho para o arquivo
 */
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

/**
 * @brief Separa o nome do arquivo .class dado o caminho para o arquivo
 * 
 * @param commandLinePath 
 * @return string com o nome do .class
 */
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

/**
 * @brief Função main da JVM
 * @details Permite a seleção de execução pelo usuário entre leitor/exibidor ou interpretador
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
    if (argc != 3)  {
        cout << "Numero incorreto de argumentos especificado" << endl;
    }
    else {
        ClassFile classFile;
        string projectPath = getProjectPath(argv[2]);
        string className = getClassName(argv[2]);
        ClassLoader classLoader(getProjectPath(argv[2]));
        MethodArea methodArea;

        classLoader.setMethodArea(&methodArea);
        classFile = classLoader.loadClassFile(className);

        string option = argv[1];
        InstructionSet instructionSet(&classLoader);

        if (option.compare("-e") == 0) {
            ClassPrinter classPrinter(classFile, &instructionSet);
            classPrinter.print();
        }
        else if (option.compare("-i") == 0) {
            string projectPath = getProjectPath(argv[2]);

            classLoader.loadSuperClasses(&classFile);

            //Inicio da execucao do programa
            ExecutionEngine executionEngine(&classFile, &methodArea, &instructionSet);
            executionEngine.execute();
        }
        else {
            cout << "O segundo argumento deve ser -e para exibidor ou -i para interpredaor" << endl;
        }
    }
    return 0;
}