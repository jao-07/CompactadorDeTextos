#pragma once

#include "No.hpp"

class Lista {
    
    public:
        Lista();
        ~Lista();
        void Insere(No* no);
        No* Remove();
        bool Vazia();
        void Limpa();
        No* GetPrimeiro();
        int GetTamanho();

    private:
        No* primeiro;
        No* ultimo;
        int tamanho;
};