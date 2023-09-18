#include <iostream>
#include "../include/Lista.hpp"

//Construtor da classe Lista
Lista::Lista() {
    primeiro = new No();
    ultimo = primeiro;
    tamanho = 0;
}

//Destrutor da classe Lista
Lista::~Lista(){
    Limpa();
    delete primeiro;
}

//Função que insere um nó na lista, ordenadamente, de acordo com a frequencia desse nó
void Lista::Insere(No* no){
    No *p;

    if(tamanho == 0) {
        primeiro->prox = no;
        ultimo = no;
        tamanho++;
    }
    else {
        p = primeiro;
        while(p->prox != NULL){
            if(no->freq > p->prox->freq){
                p = p->prox;
            }
            else
                break;
        }
        if(p == ultimo)
            ultimo = no;

        no->prox = p->prox;
        p->prox = no;
        tamanho++;
    }
}

//Função que remove o primeiro nó da lista
No* Lista::Remove() {
    No *p;
    if (tamanho == 0)
        throw "ERRO: Lista vazia!";

    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;
    if(primeiro->prox == NULL)
        ultimo = primeiro;

    return p;
}

//Função que deleta todos os elementos da lista
void Lista::Limpa(){
    No *p;

    p = primeiro->prox;
    while (p!=NULL) {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
}

//Função que verifica se a lista está vazia ou não
bool Lista::Vazia() {
    return this->primeiro == NULL && this->ultimo == NULL;
}

//Função que retorna o nó primeiro, atributo da lista
No* Lista::GetPrimeiro() {
    return this->primeiro;
}

//Função que retorna o tamanho da lista
int Lista::GetTamanho() {
    return this->tamanho;
}