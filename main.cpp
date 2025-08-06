#include <iostream>
#include "kmp.h"
#include "kmp_2.h"
#include "kmp_3.h"


int main()
{   
    DataMining analisador("documento.txt");
    analisador.executarAnalise();
    
    // string pattern = "aba";
    // string text = "aaababacaababc";

    // Kmp kmp(pattern);
    // kmp.printF();
    // vector<int> posicoes = kmp.buscarOcorrencias(text);

    // for (int pos : posicoes)
    // {
    //     cout << "Encontrado na posição: " << pos << endl;
    // }

    // pattern = "a*a";

    // Kmp_Wild kmpw(pattern);
    // kmpw.printF();
    // posicoes = kmpw.buscarOcorrencias(text);

    // for (int pos : posicoes)
    // {
    //     cout << "Encontrado na posição: " << pos << endl;
    // }

    

    return 0;
}
// g++ main.cpp -o main
//./main.exe
