#include "../include/libraries.hpp"

using namespace std;


int main(int argc, char** argv) 
{
    if (argc <= 1) {
        cerr << "Faltam argumentos" << endl;
        exit(EXIT_FAILURE);
    }

    auto nome_arquivo = static_cast<string>(argv[argc - 1]);
    
    ClassLoader loader;
    class_file *arquivo_de_entrada = loader.carregar(nome_arquivo);

    ler_exibir_arquivo(*arquivo_de_entrada, nome_arquivo);

    delete arquivo_de_entrada;

    return 0;
}
//kkkkk
