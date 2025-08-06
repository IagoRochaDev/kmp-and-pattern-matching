#ifndef ARVORE_HUFFMAN_H
#define ARVORE_HUFFMAN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
#define TAMANHO_TABELA_FREQUENCIA 256

struct No {
    unsigned char caracter;
    int frequencia;         
    No* esq;               
    No* dir;                

    No(unsigned char c, int f) : caracter(c), frequencia(f), esq(NULL), dir(NULL) {}

    No(int f, No* e, No* d) : frequencia(f), esq(e), dir(d) {}
};

void imprimirNo(No* no);

bool compararPorFrequencia(const No& a, const No& b);

void inserirCaracter(list<No>& lista, unsigned int tabela[]);

void imprimirLista(list<No> lista);

void ordenarLista(list<No>& lista);

No* construirArvoreHuffman(list<No>& lista);

int altura_da_arvore(No* raiz);

void imprimirCodigosRec(No* raiz, string codigo = "");

void imprimirCodigos(No* raiz);

void serializarArvoreBinario(No* raiz, ofstream& out);

No* deserializarArvoreBinario(ifstream& in);

#endif