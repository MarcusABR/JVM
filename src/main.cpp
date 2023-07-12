#include "../include/libraries.hpp"

using namespace std;


int main(int argc, char** argv) 
{
    if (argc <= 2) {
        cerr << "Faltam argumentos" << endl;
        exit(EXIT_FAILURE);
    }

    //auto nome_arquivo = static_cast<string>(argv[argc - 1]);
    auto nome_arquivo = static_cast<string>(argv[2]);
    
    ClassLoader loader;
    class_file *arquivo_de_entrada = loader.carregar(nome_arquivo);

    string option = argv[1];

    if(option.compare("-e") == 0){
            ler_exibir_arquivo(*arquivo_de_entrada, nome_arquivo);
    }
    else if (option.compare("-i") == 0) {
            // acho que pode ser substituido por "arquivo_de_entrada"
            ClassLoader classLoader(getProjectPath(argv[2]));
            
            // area de metodos
            MethodArea methodArea;
            classLoader.setMethodArea(&methodArea);

            // conjunto de instrucoes
            InstructionSet instructionSet(&classLoader);
            
            // acho que pode ser substituído por "nome_arquivo"
            string projectPath = getProjectPath(argv[2]);

            // acho que pode ser substituído por "arquivo_de_entrada"
            classLoader.loadSuperClasses(&classFile);

            //Inicio da execucao do programa
            ExecutionEngine executionEngine(&classFile, &methodArea, &instructionSet);
            executionEngine.execute();
    }
    else {
        cout << "O segundo argumento deve ser -e para exibidor ou -i para interpredaor" << endl;
    }
    delete arquivo_de_entrada;

    return 0;
}
//kkkkk
