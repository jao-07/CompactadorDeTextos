#pragma once

class No {
    
    public:
        No();
        No(char simbolo, int freq);
        No(int freq, No* esq, No* dir);

        void SetSimbolo(char simbolo);
        char GetSimbolo();
        void SetFreq(int freq);
        int GetFreq();
        void SetProx(No* prox);
        No* GetProx();
        void SetEsq(No* esq);
        No* GetEsq();
        void SetDir(No* dir);
        No* GetDir();

        bool Folha();

    private:
        char simbolo;
        int freq;
        No* prox;
        No* esq;
        No* dir;
        friend class Lista;
};