
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class PontoDeInteresse
{
public:
    int codigo;
    int valorTuristico;
    PontoDeInteresse(int codigo, int valorTuristico)
    {
        this->codigo = codigo;
        this->valorTuristico = valorTuristico;
    }
};

class Trecho
{
public:
    int trechoUm;
    int trechoDois;
    int custo;
    Trecho(int trechoUm, int trechoDois, int custo)
    {
        this->trechoUm = trechoUm;
        this->trechoDois = trechoDois;
        this->custo = custo;
    }
};

class Configuracoes
{
public:
    void CalculaRota(vector<Trecho> vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse)
    {
        vector<Trecho> resultado;
        for (int j = 0; j < vetorPontosDeInteresse.size(); j++)
        {
            int codigoPontoAtual = vetorPontosDeInteresse.at(j).codigo;
            vector<Trecho> trechosComCaminhoParaCodigoAtual;
            for (int i = 0; i < vetorTrechos.size(); i++)
            {
                Trecho trechoAtual = vetorTrechos.at(i);
                if (trechoAtual.trechoDois == codigoPontoAtual || trechoAtual.trechoUm == codigoPontoAtual)
                {
                    trechosComCaminhoParaCodigoAtual.push_back(trechoAtual);
                }
            }

            Trecho trechoComMenorCusto = trechosComCaminhoParaCodigoAtual.at(0);
            for (int i = 0; i < trechosComCaminhoParaCodigoAtual.size(); i++)
            {
                Trecho trechoAtual = trechosComCaminhoParaCodigoAtual.at(i);
                if (trechoAtual.custo < trechoComMenorCusto.custo)
                {
                    trechoComMenorCusto = trechoAtual;
                }
            }

            resultado.push_back(trechoComMenorCusto);

        }

       cout << "\n \n O resultado . size é: "<< resultado.size();
    }
};

void leEntradaPrincipal(int &quantidadePontosDeInteresse, int &quantidadeTrechosPossiveis)
{
    string temp;
    getline(cin, temp);
    vector<string> result;
    istringstream iss(temp);
    for (string s; iss >> s;)
        result.push_back(s);

    quantidadePontosDeInteresse = stoi(result.at(0));
    quantidadeTrechosPossiveis = stoi(result.at(1));
}

vector<PontoDeInteresse> leEntradaPontosDeInteresse(int quantidadePontosDeInteresse)
{
    string line;
    vector<PontoDeInteresse> vetorPontosDeInteresse;
    getline(cin, line);
    istringstream iss(line);
    int codigoAtual = 0;
    for (string s; iss >> s;)
    {
        PontoDeInteresse pontoDeInteresseAtual = PontoDeInteresse(codigoAtual, stoi(s));
        codigoAtual++;
        vetorPontosDeInteresse.push_back(pontoDeInteresseAtual);
    }

    return vetorPontosDeInteresse;
}

vector<Trecho> leEntradaTrechos(int quantidadeDeTrechosPossiveis)
{

    vector<Trecho> vetorTrechos;

    for (int i = 0; i < quantidadeDeTrechosPossiveis; i++)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);
        vector<string> temp;
        for (string s; iss >> s;)
        {
            temp.push_back(s);
        }

        int trechoUm = stoi(temp.at(0));
        int trechoDois = stoi(temp.at(1));
        int custo = stoi(temp.at(2));

        Trecho trechoAtual = Trecho(trechoUm, trechoDois, custo);
        vetorTrechos.push_back(trechoAtual);
    }

    return vetorTrechos;
}

int main()
{
    int quantidadePontosDeInteresse, quantidadeTrechosPossiveis;
    vector<PontoDeInteresse> vetorPontosDeInteresse;
    vector<Trecho> vetorTrechos;
    leEntradaPrincipal(quantidadePontosDeInteresse, quantidadeTrechosPossiveis);
    vetorPontosDeInteresse = leEntradaPontosDeInteresse(quantidadePontosDeInteresse);
    vetorTrechos = leEntradaTrechos(quantidadeTrechosPossiveis);
    Configuracoes configuracoes = Configuracoes();
    configuracoes.CalculaRota(vetorTrechos, vetorPontosDeInteresse);
    return 0;
}