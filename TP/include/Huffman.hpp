#pragma once

#include <iostream>
#include <string>

#include "Lista.hpp"

class Huffman {
    public:
        Huffman();
        void Comprime(std::string arq_entrada, std::string arq_saida);
        void Descomprime(std::string arq_entrada, std::string arq_saida);    
    
    private:
        Lista* lista;
        No** vetor;

        std::string Ler_Arquivo(std::string nome_arq);
        void CriaVetor(std::string conteudo);
        void CriaLista();
        No* CriaArvore();
        std::string Codifica(std::string conteudo, No* arvore);
        std::string* CriaTabela(No* raiz);
        void CriaTabelaRecursivo(std::string* tabela, No* no, std::string codigo);
        std::string StringArvore(No* arvore);
        std::string StringArvoreRecursivo(No* no, std::string str);
        void PreencheArquivoComprimido(std::string arvore, int tamanho, std::string texto_codificado, std::string arq_saida);
        std::string CriaBytes(std::string texto_codificado);
        
        No* LeArvore(std::string arv_string);
        No* LeArvoreRecursivo(std::string arv_string, int* posicao);
        void PreencheArquivoDescomprimido(std::string conteudo, int tamanho, No* arvore, std::string arq_saida);
        std::string CriaBits(std::string bytes);
        std::string Descodifica(std::string texto_codificado, int tamanho, No* raiz);      
};