#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "arvore_huffman.h"

using namespace std;
#define TAMANHO_TABELA_FREQUENCIA 256

vector<unsigned char> lerTexto(string nome_arquivo);

void populaTabelaFrequencia(unsigned int *tabela, const vector<unsigned char>& texto);

void inicializaTabela(unsigned int tabela[TAMANHO_TABELA_FREQUENCIA]);

void imprimeTabelaFrequencia(unsigned int tabela[TAMANHO_TABELA_FREQUENCIA]);

void imprimiTexto(vector<unsigned char> texto, string nome = "");

void preencheDicionario(No* raiz, string codigo, char** dicionario, int colunas);

char** geraDicionario(int colunas, No* arvore);

void imprimirDicionario(char** dicionario);

vector<unsigned char> codificaTexto(char** dicionario, vector<unsigned char> texto);

vector<unsigned char> decodificaTexto(No* raiz, vector<unsigned char> texto_codificado);

void compactador(const vector<unsigned char>& texto_codificado, string nome_arquivo, No* raiz);

void descompactador(string nome_arquivo_compactado, string nome_arquivo_descompactado);

#endif