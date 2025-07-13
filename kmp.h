#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Kmp
{
public:
    vector<vector<int>> f;
    string p;
    int sigma;

    Kmp(const string &pattern, int sigma = 256)
    {
        p = pattern;
        this->sigma = sigma;

        int pi = p.size();

        // Inicializa matriz de transição
        f.assign(sigma, vector<int>(pi+1, 0));

        for (int c = 0; c < sigma; c++)
        {
            f[c][0] = 0;
        }
        f[static_cast<unsigned char>(p[0])][0] = 1;

        int x = 0;
        for (int i = 1; i < pi+1; i++)
        {
            for (int c = 0; c < sigma; c++)
            {
                f[c][i] = f[c][x];
            }
            f[static_cast<unsigned char>(p[i])][i] = i + 1;
            x = f[static_cast<unsigned char>(p[i])][x];
        }
    }

    vector<int> buscarOcorrencias(const string &t)
    {
        vector<int> ocorrencias;
        int j = 0;
        int pi = p.size();
        int tau = t.size();

        for (int i = 0; i < tau; i++)
        {
            j = f[static_cast<unsigned char>(t[i])][j];
            if (j == pi)
            {
                ocorrencias.push_back(i - j + 1);
            }
        }
        return ocorrencias;
    }

    void printF() const
    {
        cout << "Matriz de transição f:" << endl;

        for (int c = 0; c < sigma; c++)
        {
            bool linhaVazia = true;

            // Verifica se a linha tem algum valor não-zero, pra não imprimir tudo
            for (size_t j = 0; j < p.size(); j++)
            {
                if (f[c][j] != 0)
                {
                    linhaVazia = false;
                    break;
                }
            }

            if (linhaVazia)
                continue; // pula linhas vazias

            cout << "Caractere: " << c << " ('" << static_cast<char>(c) << "') => ";

            for (size_t j = 0; j < p.size(); j++)
            {
                cout << f[c][j] << " ";
            }
            cout << endl;
        }
    }
};
