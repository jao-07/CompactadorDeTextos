#include <fstream>
#include <string.h>
#include "../include/Huffman.hpp"

int main(int argc, char* argv[]) {

    Huffman* huff = new Huffman();

    if(argc == 4){
        //Se tiver -c seguidos do arquivo de entrada e do arquivo de saida, o arquivo de entrada é comprimido e armazenado no arquivo de saida
        if(strcmp(argv[1], "-c") == 0) {
            std::string arq_entrada = (std::string)argv[2];
            std::string arq_saida = (std::string)argv[3];
            huff->Comprime(arq_entrada, arq_saida);
        }
        //Se tiver -d seguidos do arquivo de entrada e do arquivo de saida, o arquivo de entrada é descomprimido e armazenado no arquivo de saida
        else if(strcmp(argv[1], "-d") == 0) {
            std::string arq_entrada = (std::string)argv[2];
            std::string arq_saida = (std::string)argv[3];
            huff->Descomprime(arq_entrada, arq_saida);
        }
        else
            std::cout << "Entrada Inválida!" << std::endl;
    }
    else
        std::cout << "Entrada Inválida!" << std::endl;
}