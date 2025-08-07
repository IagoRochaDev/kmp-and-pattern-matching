#pragma once
#include "kmp.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;
//contexto buscador  de numeros de telefone,datas e email
class DataMining {
private:
    string texto;

    string lerArquivo(const string& nomeArquivo) {
        ifstream arq(nomeArquivo);
        if (!arq.is_open()) {
            cerr << "Erro ao abrir o arquivo." << endl;
            return "";
        }

        stringstream buffer;
        buffer << arq.rdbuf(); 
        return buffer.str();   
    }

    void extrairComRegex(const string& trecho, const regex& padrao) {
        sregex_iterator it(trecho.begin(), trecho.end(), padrao);
        sregex_iterator end;

        while (it != end) {
            cout << " - " << it->str() << endl;
            ++it;
        }
    }

public:
    DataMining(const string& nomeArquivo) {
        texto = lerArquivo(nomeArquivo);
    }

    void analisarEmails() {
        cout << "\n[E-mails encontrados]\n";
        Kmp kmpArroba("@");
        auto posicoes = kmpArroba.buscarOcorrencias(texto);

        regex padraoEmail(R"([\w.%+-]+@[\w.-]+\.[a-zA-Z]{2,})");

        for (int pos : posicoes) {
            int ini = max(0, pos - 30);
            int fim = min((int)texto.size(), pos + 50);
            string trecho = texto.substr(ini, fim - ini);
            extrairComRegex(trecho, padraoEmail);
        }
    }

    void analisarDatas() {
        cout << "\n[Datas encontradas]\n";
        Kmp kmpBarra("/");
        auto posicoes = kmpBarra.buscarOcorrencias(texto);

        regex padraoData(R"(\b\d{2}/\d{2}/\d{4}\b)");

        for (int pos : posicoes) {
            int ini = max(0, pos - 10);
            int fim = min((int)texto.size(), pos + 10);
            string trecho = texto.substr(ini, fim - ini);
            extrairComRegex(trecho, padraoData);
        }
    }

    void analisarTelefones() {
        cout << "\n[Telefones encontrados]\n";
        Kmp kmpParenteses("("); // detecta possíveis telefones com DDD
        auto posicoes = kmpParenteses.buscarOcorrencias(texto);

        regex padraoTelefone(R"(\(?\d{2}\)?\d{4,5}-?\d{4})");

        for (int pos : posicoes) {
            int ini = max(0, pos - 10);
            int fim = min((int)texto.size(), pos + 20);
            string trecho = texto.substr(ini, fim - ini);
            extrairComRegex(trecho, padraoTelefone);
        }
    }

    void executarBusca() {
        analisarEmails();
        analisarDatas();
        analisarTelefones();
    }
};
