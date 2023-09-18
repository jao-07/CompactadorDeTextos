#include <iostream>
#include <string>
#include <sstream>
#include "../include/No.hpp"

//Construtores da classe No

No::No() {
    this->simbolo = '\0';
    this->freq = 0;
    this->esq = NULL;
    this->dir = NULL;
    this->prox = NULL;
}

No::No(char simbolo, int freq) {
    this->simbolo = simbolo;
    this->freq = freq;
    this->prox = NULL;
    this->esq = NULL;
    this->dir = NULL;
}

No::No(int freq, No* esq, No* dir) {
    this->simbolo = '\0';
    this->freq = freq;
    this->prox = NULL;
    this->esq = esq;
    this->dir = dir;
}

//Função que verifica se o nó é folha ou não
bool No::Folha() {
    return this->esq == NULL && this->dir == NULL;
}

//Funções de Get e Set dos atributos da classe No:

void No::SetSimbolo(char simbolo) {
    this->simbolo = simbolo;
}

char No::GetSimbolo() {
    return this->simbolo;
}

void No::SetFreq(int freq) {
    this->freq = freq;
}

int No::GetFreq() {
    return this->freq;
}

void No::SetEsq(No* esq) {
    this->esq = esq;
}

No* No::GetEsq() {
    return this->esq;
}

void No::SetDir(No* dir) {
    this->dir = dir;
}

No* No::GetDir() {
    return this->dir;
}

void No::SetProx(No* prox) {
    this->prox = prox;
}

No* No::GetProx() {
    return this->prox;
}