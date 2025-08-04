#include "functions.h"
#include "arvore_huffman.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

vector<unsigned char> lerTexto(string nome_arquivo) {
    ifstream arquivo(nome_arquivo, ios::binary);
    vector<unsigned char> conteudo;

    if (arquivo.is_open()) {
        arquivo.seekg(0, ios::end);
        streamsize tamanho = arquivo.tellg();
        arquivo.seekg(0, ios::beg);
        conteudo.resize(tamanho);
        if (!arquivo.read(reinterpret_cast<char*>(conteudo.data()), tamanho)) {
            cout << "Erro na leitura do arquivo." << endl;
        }

        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }

    return conteudo;
}

void populaTabelaFrequencia(unsigned int tabela[TAMANHO_TABELA_FREQUENCIA], const vector<unsigned char>& texto) {
    inicializaTabela(tabela);
    for (unsigned char c : texto) {
        tabela[c]++; 
    }
}

void inicializaTabela(unsigned int tabela[TAMANHO_TABELA_FREQUENCIA]) {
    for (int i = 0; i < TAMANHO_TABELA_FREQUENCIA; i++) {
        tabela[i] = 0;
    }
}

void imprimeTabelaFrequencia(unsigned int tabela[TAMANHO_TABELA_FREQUENCIA]){
    cout<<"\n\tTabela Frequencia:\n";
    for (int i = 0; i < TAMANHO_TABELA_FREQUENCIA; i++) {
        if (tabela[i] > 0) {
            cout << "Caractere '" << char(i) << "' aparece " << tabela[i] << " vezes.\n";
        }
    }
}

void imprimiTexto(vector<unsigned char> texto, string nome){
    cout<<"\n\tTexto " << nome << ": \n";
    for (unsigned char c : texto) {
        cout << c;
    }
    cout<<"\n\n";
}

void preencheDicionario(No* raiz, string codigo, char** dicionario, int colunas) {
    if (!raiz) return;
    if (!raiz->esq && !raiz->dir) {
        strcpy(dicionario[raiz->caracter], codigo.c_str());
        return;
    }
    preencheDicionario(raiz->esq, codigo + "0", dicionario, colunas);
    preencheDicionario(raiz->dir, codigo + "1", dicionario, colunas);
}

char** geraDicionario(int colunas, No* arvore) {
    if (!arvore) return nullptr;
    char** dicionario = new char*[256];
    for (int i = 0; i < 256; i++) {
        dicionario[i] = new char[colunas];
        memset(dicionario[i], 0, colunas);
    }
    preencheDicionario(arvore, "", dicionario, colunas);

    return dicionario;
}

void imprimirDicionario(char** dicionario) {
    if (!dicionario) {
        cout << "Dicionario vazio ou não inicializado.\n";
        return;
    }
    cout << "\n\tDicionario de Huffman:\n";
    for (int i = 0; i < 256; i++) {
        if (dicionario[i][0] != '\0') {
            cout << static_cast<char>(i) << " : " << dicionario[i] << endl;
        }
    }
}

vector<unsigned char> codificaTexto(char** dicionario, vector<unsigned char> texto) {
    vector<unsigned char> texto_codificado;
    for(unsigned char c : texto) {
        for (int i = 0; dicionario[c][i] != '\0'; i++) {
            texto_codificado.push_back(dicionario[c][i]);
        }
    }
    return texto_codificado;
}

vector<unsigned char> decodificaTexto(No* raiz, vector<unsigned char> texto_codificado){
    vector<unsigned char> texto;
    No* aux = raiz;
    for (unsigned char c : texto_codificado)
    {
        if(c == '0'){
            aux = aux->esq;
        }
        else{
            aux = aux->dir;
        }
        if(!aux->esq && !aux->dir){
            texto.push_back(aux->caracter);
            aux = raiz;
        }
        
    }
    return texto;
}

void compactador(const vector<unsigned char>& texto_codificado, string nome_arquivo, No* raiz) {
    ofstream arquivo(nome_arquivo, ios::binary);
    if (!arquivo.is_open()) {
        cout << "Erro ao criar arquivo compactado!!";
        exit(1);
    }
    int bits_extras = 8 - texto_codificado.size() % 8;
    arquivo.put(bits_extras);   
    serializarArvoreBinario(raiz, arquivo);
    unsigned char byte = 0;
    int percorre_byte = 7;
    for (unsigned char c : texto_codificado) {
        if (c == '1') {
            byte |= (1 << percorre_byte);
        }
        percorre_byte--;

        if (percorre_byte < 0) {
            arquivo.put(byte);
            byte = 0;           
            percorre_byte = 7;
        }
    }
    if (percorre_byte != 7) {
        arquivo.put(byte);
    }
    arquivo.close();
}

void descompactador(string nome_arquivo_compactado, string nome_arquivo_descompactado) {
    ifstream arquivo_compactado(nome_arquivo_compactado, ios::binary);
    if (!arquivo_compactado.is_open()) {
        cerr << "Erro ao abrir arquivo compactado!!" << endl;
        exit(1);
    }
    ofstream arquivo_descompactado(nome_arquivo_descompactado, ios::binary);
    if (!arquivo_descompactado.is_open()) {
        cerr << "Erro ao criar arquivo descompactado!!" << endl;
        exit(1);
    }
    arquivo_compactado.seekg(0, ios::end);
    streampos tamanho_arquivo = arquivo_compactado.tellg();
    arquivo_compactado.seekg(0, ios::beg);

    unsigned char byte;
    arquivo_compactado.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    int bits_extras = byte;
    No* raiz = deserializarArvoreBinario(arquivo_compactado);
    No* aux = raiz;
    while (arquivo_compactado.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        streampos pos_atual = arquivo_compactado.tellg();
        if (pos_atual == tamanho_arquivo) {
            break;
        }
        for (int percorre_byte = 7; percorre_byte >= 0; percorre_byte--) {
            bool bit = (byte >> percorre_byte) & 1;
            if (bit)
                aux = aux->dir;
            else
                aux = aux->esq;
            if (!aux->esq && !aux->dir) {
                arquivo_descompactado.put(aux->caracter);
                aux = raiz;
            }
        }
    }
    arquivo_compactado.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    for (int percorre_byte = 7; percorre_byte >= bits_extras; percorre_byte--) {
        bool bit = (byte >> percorre_byte) & 1;
        if (bit)
            aux = aux->dir;
        else
            aux = aux->esq;
        if (!aux->esq && !aux->dir) {
            arquivo_descompactado.put(aux->caracter);
            aux = raiz;
        }
    }
    arquivo_compactado.close();
    arquivo_descompactado.close();
}