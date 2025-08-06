#include "arvore_huffman.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void imprimirNo(No* no){
    cout << "No :( F: "<< no->frequencia << ", C: "<< no->caracter<<")\n";
}

bool compararPorFrequencia(const No& a, const No& b) {
    return a.frequencia < b.frequencia;
}

void    inserirCaracter(list<No>& lista, unsigned int tabela[]) {
    for (int i = 0; i < TAMANHO_TABELA_FREQUENCIA; i++) {
        if (tabela[i] > 0) {
            lista.push_back(No(i, tabela[i]));
        }
    }
}

void ordenarLista(std::list<No>& lista) {
    std::list<No> ordenada;

    while (!lista.empty()) {
        No atual = lista.front();
        lista.pop_front();

        auto it = ordenada.begin();
        while (it != ordenada.end() && compararPorFrequencia(*it, atual)) {
            ++it;
        }

        ordenada.insert(it, atual);
    }

    lista = std::move(ordenada);
}



void imprimirLista(list<No> lista){
    cout<<"\n\tLista Ordenada:\n";
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        cout << "Caractere: " << it->caracter << ", Frequencia: " << it->frequencia << endl;
    }
}

No* construirArvoreHuffman(list<No>& lista) {
    while (lista.size() > 1) {
        ordenarLista(lista);
        No* esq = new No(lista.front().caracter, lista.front().frequencia);
        esq->esq = lista.front().esq;
        esq->dir = lista.front().dir;
        lista.pop_front();
        No* dir = new No(lista.front().caracter, lista.front().frequencia);
        dir->esq = lista.front().esq;
        dir->dir = lista.front().dir;
        lista.pop_front();
        No* novoNo = new No('\0', esq->frequencia + dir->frequencia);
        novoNo->esq = esq;
        novoNo->dir = dir;
        lista.push_back(*novoNo);
    }

    return new No(lista.front());
}

void imprimirCodigos(No* raiz){
    cout<<"\n\tTabela de Codigos:\n";
    imprimirCodigosRec(raiz);
}

void imprimirCodigosRec(No* raiz, string codigo) {
    if (!raiz) return;
    if (!raiz->esq && !raiz->dir) {
        cout << raiz->caracter << ": " << codigo << endl;
    }
    imprimirCodigosRec(raiz->esq, codigo + "0");
    imprimirCodigosRec(raiz->dir, codigo + "1");
}

int altura_da_arvore(No* raiz){
    int esq, dir;
    if(!raiz)
        return -1;
    else{
        esq = altura_da_arvore(raiz->esq)+1;
        dir = altura_da_arvore(raiz->dir)+1;

        if(esq>dir)
            return esq;
        else
            return dir;
    }
}

void serializarArvoreBinario(No* raiz, ofstream& out) {
    if (raiz == nullptr) return;
    if (raiz->esq == nullptr && raiz->dir == nullptr) {  
        out.put(0x00);
        out.put(raiz->caracter);
        out.write(reinterpret_cast<const char*>(&raiz->frequencia), sizeof(int));
    } else {  
        out.put(0x01);
        out.write(reinterpret_cast<const char*>(&raiz->frequencia), sizeof(int));
    }
    serializarArvoreBinario(raiz->esq, out);
    serializarArvoreBinario(raiz->dir, out);
}


No* deserializarArvoreBinario(ifstream& in) {
    char tipo_no;
    if (!in.get(tipo_no)) return nullptr;
    if (tipo_no == 0x00) {
        char caracter;
        int frequencia;
        in.get(caracter);
        in.read(reinterpret_cast<char*>(&frequencia), sizeof(int));
        return new No(caracter, frequencia);
    } else if (tipo_no == 0x01) {
        int frequencia;
        in.read(reinterpret_cast<char*>(&frequencia), sizeof(int));
        No* esq = deserializarArvoreBinario(in);
        No* dir = deserializarArvoreBinario(in);
        return new No(frequencia, esq, dir);
    }

    return nullptr;
}