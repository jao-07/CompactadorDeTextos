#include <math.h>
#include <fstream>
#include <sstream>

#include "../include/Huffman.hpp"

//Construtor da classe Huffman
Huffman::Huffman()
{
    lista = NULL;
    vetor = new No* [128];
}

//Função que recebe o nome do arquivo a ser comprimido e comprime o arquivo utilizando funções auxiliares
void Huffman::Comprime(std::string arq_entrada, std::string arq_saida) {
    std::string conteudo = this->Ler_Arquivo(arq_entrada);
    CriaVetor(conteudo);
    CriaLista();
    No* arvore = CriaArvore();
    std::string texto_codificado = this->Codifica(conteudo, arvore);
    std::string arv_str = this->StringArvore(arvore);
    PreencheArquivoComprimido(arv_str, conteudo.length(), texto_codificado, arq_saida);
}

//Função que recebe o nome do arquivo de entrada como parâmetro e retorna o conteudo desse arquivo em formato de string
std::string Huffman::Ler_Arquivo(std::string nome_arq) {
    std::ifstream arquivo;
    arquivo.open(nome_arq);

    if (!arquivo) {
        std::cout << "Arquivo não encontrado!" << std::endl;
        exit(-1);
    }

    if (!arquivo.is_open()) {
        std::cout << "Não foi possível abrir o arquivo " << nome_arq << " !" << std::endl;
        exit(-1);
    }

    std::string conteudo, linha;
    while(getline(arquivo, linha)){
        conteudo += linha;
        conteudo += "\n";
    }
    conteudo = conteudo.substr(0, conteudo.length() - 1);

    arquivo.close();

    return conteudo;
}

//Função que recebe o texto a ser compactado e preenche o vetor com os simbolos e frequencias dos simbolos presentes no texto
void Huffman::CriaVetor(std::string conteudo){
    for(long unsigned int i=0; i<conteudo.length(); i++){
        int c = (int)conteudo[i];
        if(vetor[c] == NULL){
            No* n = new No(c, 1);
            vetor[c] = n;
        }
        else{
            int aux = vetor[c]->GetFreq();
            vetor[c]->SetFreq(aux+1);
        }
    }
}

//Função que gera uma lista com os nós do vetor criado na função CriaVetor. Essa lista é ordenada pela frequencia de cada nó. 
void Huffman::CriaLista() {
    Lista* l = new Lista();
    for (long unsigned int i = 0; i < 128; ++i){
        if(vetor[i] != NULL)
            l->Insere(vetor[i]);
    }
    lista = l;
}

//Função que cria uma arvore de Huffman utilizando os nós da lista atributo da classe Huffman
No* Huffman::CriaArvore() {
    No* a = new No();
    if (lista == NULL || lista->GetTamanho() == 0)
        return a;

    while (lista->GetTamanho() > 1)
    {
        No* pri = lista->Remove();
        No* seg = lista->Remove();

        int f = pri->GetFreq() + seg->GetFreq();

        No* noPai = new No(f, pri, seg);

        lista->Insere(noPai);
    }

    return lista->GetPrimeiro()->GetProx();
}

//Função que recebe a raiz da arvore de huffman do texto a ser compactado e o próprio texto em formato de string e transforma esse texto em 0s e 1s, substituindo cada simbolo por seu respectivo codigo
std::string Huffman::Codifica(std::string conteudo, No* arvore) {
    std::string texto_codificado = "";
    std::string* tabela = CriaTabela(arvore);

    for (long unsigned int i = 0; i < conteudo.length(); ++i) {
        texto_codificado = texto_codificado + tabela[(int)conteudo[i]];
    }

    return texto_codificado;
}

//Função que utiliza uma função auxiliar para criar uma tabela com os códigos de cada simbolo e retorna essa tabela
std::string* Huffman::CriaTabela(No *raiz) {
    std::string* tabela = new std::string[128];
    this->CriaTabelaRecursivo(tabela, raiz, "");
    return tabela;
}

//Função auxiliar que passa pelos nós da árvore e vai gerando o código de cada simbolo
void Huffman::CriaTabelaRecursivo(std::string* tabela, No* no, std::string codigo) {

    if (no->Folha())
    {
        tabela[(int)no->GetSimbolo()] = codigo;     
        return;
    }

    this->CriaTabelaRecursivo(tabela, no->GetEsq(), codigo + '0');
    this->CriaTabelaRecursivo(tabela, no->GetDir(), codigo + '1');
}

//Função que recebe a raiz da árvore de Huffman e chama uma função auxiliar para gerar essa arvore em formato de string, para que seja possível ler essa string e gerar essa arvore quando for descompactar o arquivo
std::string Huffman::StringArvore(No* arvore) {
    return this->StringArvoreRecursivo(arvore, "");
}

//Função recursiva que passa por cada nó da arvore e retorna a parte da string gerada por cada nó
std::string Huffman::StringArvoreRecursivo(No* no, std::string str) {
    if (no->Folha())
        return str + '1' + no->GetSimbolo();

    str += '0';
    str = StringArvoreRecursivo(no->GetEsq(), str);
    str = StringArvoreRecursivo(no->GetDir(), str);
    return str;
}

//Função que recebe a arvore de Huffman do texto, o tamanho do texto, o texto codificado e o nome do arquivo de saida e gera o texto comprimido e coloca ele no arquivo de saida 
void Huffman::PreencheArquivoComprimido(std::string arvore, int tamanho, std::string texto_codificado, std::string arq_saida) {
    std::ofstream arq;

    std::string conteudo = arvore + "---" + std::to_string(tamanho) + "---" + CriaBytes(texto_codificado);
    arq.open(arq_saida);
    if (!arq.is_open()) {
        std::cout << "Não foi possível abrir o arquivo " << arq_saida << " !" << std::endl;
        exit(-1);
    }
    arq << conteudo;
    arq.close();
}

//Função que recebe uma string com o texto codificado de acordo com os codigos criados e transforma o texto para binário, armazenando cada byte criado em uma variável char e armazena essa variável na string de saída
std::string Huffman::CriaBytes(std::string texto_codificado) {

    unsigned char byte = 0;
    unsigned int contBit = 0;
    std::string saida = "";

    while (contBit < texto_codificado.length()) {

        for (int i = 0; i < 8; ) {
            if (texto_codificado[contBit] == '1'){
                byte = byte << 1;
                byte = byte | 1;
            }
            else if (texto_codificado[contBit] == '0')
                byte = byte << 1;

            ++contBit;
            ++i;

            if (contBit >= texto_codificado.length()) {
                int resto = 8 - i;

                for (int j = 0; j < resto; ++j)
                    byte = byte << 1;

                break;
            }
        }

        saida += byte;
        byte = 0;
    }

    return saida;
}










//Função que recebe o nome do arquivo de entrada a ser descomprimido e utiliza funções auxiliares para descomprimir o arquivo
void Huffman::Descomprime(std::string arq_entrada, std::string arq_saida) {
    std::string conteudo = Ler_Arquivo(arq_entrada);
    No* arvore = LeArvore(conteudo);
    conteudo = conteudo.substr(conteudo.find("---")+3);
    int tamanho = stoi(conteudo);
    conteudo = conteudo.substr(conteudo.find("---")+3);
    PreencheArquivoDescomprimido(conteudo, tamanho, arvore, arq_saida);
}

//Função que recebe uma string representando uma arvore de Huffman e utiliza uma função auxiliar para gerar essa arvore novamente
No* Huffman::LeArvore(std::string arv_string) {
    int posicao = -1;

    No* node = LeArvoreRecursivo(arv_string, &posicao);
    return node;
}

//Função recursiva que itera sobre as posições da string e gera os nós da arvore
No* Huffman::LeArvoreRecursivo(std::string arv_string, int* posicao){
    (*posicao)++;

    if (arv_string[*posicao] == '1') {
        (*posicao)++;
        char s = arv_string[*posicao];
        return new No(s, 0);
    }

    return new No(0, LeArvoreRecursivo(arv_string, posicao), LeArvoreRecursivo(arv_string, posicao));
}

//Função que recebe o texto comprimido, o tamanho do texto original, a raiz da arvore de huffman desse texto e o nome do arquivo de saida e gera o texto original e coloca ele no arquivo de saida
void Huffman::PreencheArquivoDescomprimido(std::string conteudo, int tamanho, No* arvore, std::string arq_saida){
    std::ofstream arq;

    std::string texto_codificado = CriaBits(conteudo);
    std::string txt_original = Descodifica(texto_codificado, tamanho, arvore);

    arq.open(arq_saida);
    if (!arq.is_open()) {
        std::cout << "Não foi possível abrir o arquivo " << arq_saida << " !" << std::endl;
        exit(-1);
    }

    arq << txt_original;
    arq.close();
}

//Função que recebe o texto compactado e transforma ele para o formato codificado, uma string com os simbolos transformados codigos formados por 0s e 1s
std::string Huffman::CriaBits(std::string bytes) {
    std::string bits = "";

    for (long unsigned int i = 0; i < bytes.length(); ++i){
        for (int j = 0; j < 8; ++j){
            if ((bytes[i] & 128) == 128) // compare "c" with 1000 0000
                bits += '1';
            else
                bits += '0';

            bytes[i] = bytes[i] << 1; // left shift
        }
    }

    return bits;
}

//Função que recebe o texto codificado, o tamanho do texto original e a raiz da árvore e retorna uma string contendo o texto original
std::string Huffman::Descodifica(std::string texto_codificado, int tamanho, No* raiz) {
    int bit = 0;
    std::string texto = "";

    for (int i = 0; i < tamanho; ++i) {
        No* aux = raiz;

        while (!aux->Folha()) {
            if (texto_codificado[bit] == '1')
                aux = aux->GetDir();
            else
                aux = aux->GetEsq();

            ++bit;
        }
        texto += aux->GetSimbolo();
    }
    return texto;
}