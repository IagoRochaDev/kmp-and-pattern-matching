// g++ -Wall -Wextra -g3 main.cpp algoritmo_de_huffman/functions.cpp algoritmo_de_huffman/arvore_huffman.cpp -o main.exe
//.\main.exe

#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <locale.h>
#include <bitset>
#include "algoritmo_de_huffman/functions.h"
#include "algoritmo_de_huffman/arvore_huffman.h"
#include "kmp.h"
#include "kmp_2.h"

int main()
{
    int opcao;

    do
    {
        cout << "\n==============================\n";
        cout << "\t   MENU PRINCIPAL\n";
        cout << "==============================\n";
        cout << "1.\tKMP\n";
        cout << "2.\tWildScore\n";
        cout << "3.\tDataMining\n";
        cout << "4.\tCompactar - Algoritmo de Huffman\n";
        cout << "5.\tDescompactar - Algoritmo de Huffman\n";
        cout << "0.\tSair\n";
        cout << "------------------------------\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
            cout << "\n[Executando KMP...]\n";

            string pattern = "aba";
            string text = "aaababacaababc";

            Kmp kmp(pattern);
            kmp.printF();
            vector<int> posicoes = kmp.buscarOcorrencias(text);

            for (int pos : posicoes)
            {
                cout << "Encontrado na posição: " << pos << endl;
            }

            break;
        }
        case 2:
        {
            cout << "\n[Executando WildScore...]\n";
            string pattern = "a*a";
            string text = "aaababacaababc";

            Kmp_Wild kmpw(pattern);
            kmpw.printF();
            vector<int> posicoes = kmpw.buscarOcorrencias(text);

            for (int pos : posicoes)
            {
                cout << "Encontrado na posição: " << pos << endl;
            }
            break;
        }

        case 3:
            cout << "\n[Executando DataMining...]\n";
            // TODO: Adicione aqui o código do processo 3
            break;

        case 4:

        {
            cout << "\n[Executando Compactar - Algoritmo de huffman...]\n";
            string input_file = "arquivo.txt";
            string output_file = "arquivo_compactado.txt";
            auto texto = lerTexto(input_file);
            unsigned int tabela_frequencia[TAMANHO_TABELA_FREQUENCIA];
            list<No> lista;
            populaTabelaFrequencia(tabela_frequencia, texto);
            inserirCaracter(lista, tabela_frequencia);
            ordenarLista(lista);
            No *raiz = construirArvoreHuffman(lista);
            int altura = altura_da_arvore(raiz);
            char **dicionario = geraDicionario(altura, raiz);
            auto texto_codificado = codificaTexto(dicionario, texto);

            // Converte a string para binário
            string texto8bits;
            for (char c : texto)
            {
                texto8bits += bitset<8>(c).to_string();
            }

            cout << "8 bits: " << texto8bits.size() << endl;

            cout << "Comprimido: " << texto_codificado.size() << endl;

            float otimizacao;
            otimizacao = (texto8bits.length() - texto_codificado.size()) / (float)texto8bits.length() * 100.0;
            cout << "A compressão teve " << otimizacao << "%% de melhora." << endl;
            auto texto_decodificado = decodificaTexto(raiz, texto_codificado);
            compactador(texto_codificado, output_file, raiz);
            break;
        }
        case 5:
        {
            cout << "\n[Executando Desompactar - Algoritmo de huffman]\n";
            string input_file = "arquivo_compactado.txt";
            string output_file = "arquivo_descompactado.txt";
            descompactador(input_file, output_file);
            break;
        }

        case 0:
            cout << "Saindo do programa...\n";
            break;

        default:
            cout << "Opcao invalida! Tente novamente.\n";
        }

    } while (opcao != 0);

    return 0;
}
// g++ main.cpp -o main
//./main.exe
