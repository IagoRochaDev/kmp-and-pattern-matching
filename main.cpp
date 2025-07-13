#include <iostream>
#include "Kmp.h"

int main()
{
    string pattern = "aa";
    string text = "aaababacaababc";

    Kmp kmp(pattern);
    kmp.printF();
    vector<int> posicoes = kmp.buscarOcorrencias(text);

    for (int pos : posicoes)
    {
        cout << "Encontrado na posição: " << pos << endl;
    }

    return 0;
}
// g++ main.cpp Kmp.cpp -o main
//./main.exe
