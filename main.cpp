
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class PontoDeInteresse
{
public:
    int codigo;
    int valorTuristico;
    bool disponivel;
    PontoDeInteresse(int codigo, int valorTuristico)
    {
        this->codigo = codigo;
        this->valorTuristico = valorTuristico;
        this->disponivel = true;
    }
};

class Trecho
{
public:
    int trechoUm;
    int trechoUmAtratividade;
    int trechoDois;
    int trechoDoisAtratividade;
    int custo;
    bool disponivel;
    Trecho(int trechoUm, int trechoDois, int custo)
    {
        this->trechoUm = trechoUm;
        this->trechoDois = trechoDois;
        this->custo = custo;
        this->disponivel = true;
    }
};
class Configuracoes
{
public:
    vector<Trecho*> obterTrechosParaPonto(vector<Trecho> &vetorTrechos, PontoDeInteresse ponto)
    {
        vector<Trecho*> trechosComCaminhoParaPontoAtual;
        for (int i = 0; i < vetorTrechos.size(); i++)
        {
            Trecho *trechoAtual = &vetorTrechos.at(i);
            if (trechoAtual->trechoDois == ponto.codigo || trechoAtual->trechoUm == ponto.codigo)
            {
                trechosComCaminhoParaPontoAtual.push_back(trechoAtual);
            }
        }

        return trechosComCaminhoParaPontoAtual;
    }

    Trecho* obterTrechoComMenorCustoEMaiorAtratividade(vector<Trecho*> vetorTrechos)
    {
        Trecho *melhorTrecho = vetorTrechos.at(0);
        for (int i = 1; i < vetorTrechos.size(); i++)
        {
            Trecho *trechoAtual = vetorTrechos.at(i);
            if ((melhorTrecho->disponivel == false && trechoAtual->disponivel == true) || (trechoAtual->disponivel == true && trechoAtual->custo < melhorTrecho->custo))
            {
                melhorTrecho = trechoAtual;
            }
            else if (trechoAtual->custo == melhorTrecho->custo &&
                     ((trechoAtual->trechoUmAtratividade + trechoAtual->trechoDoisAtratividade) >
                      (melhorTrecho->trechoUmAtratividade + melhorTrecho->trechoDoisAtratividade)))
            {
                melhorTrecho = trechoAtual;
            }
        }

        return melhorTrecho;
    }

    PontoDeInteresse* acharPontoDeInteresseComMenorAtratividade(vector<PontoDeInteresse> &vetorPontosDeInteresse)
    {
        PontoDeInteresse *pontoAtual = &vetorPontosDeInteresse.at(0);
        for (int i = 1; i < vetorPontosDeInteresse.size(); i++)
        {
            if ((pontoAtual->valorTuristico > vetorPontosDeInteresse.at(i).valorTuristico && vetorPontosDeInteresse.at(i).disponivel == true) || (pontoAtual->disponivel == false  && vetorPontosDeInteresse.at(i).disponivel == true))
            {
                pontoAtual = &vetorPontosDeInteresse.at(i);
            }
        }

        return pontoAtual;
    }

    void calculaRota(vector<Trecho> vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse)
    {
        vector<Trecho> resultado;
        int i = vetorPontosDeInteresse.size() - 1;
        while (i > 0)
        {
            PontoDeInteresse *pontoDeMenorInteresse = acharPontoDeInteresseComMenorAtratividade(vetorPontosDeInteresse);
            vector<Trecho*> trechosComCaminhoParaPontoAtual = obterTrechosParaPonto(vetorTrechos, *pontoDeMenorInteresse);
            Trecho *melhorTrecho = obterTrechoComMenorCustoEMaiorAtratividade(trechosComCaminhoParaPontoAtual);
            melhorTrecho->disponivel = false;        
            pontoDeMenorInteresse->disponivel = false;
            resultado.push_back(*melhorTrecho);
            i--;
        }

        cout << "\n \n O resultado . size é: " << resultado.size();
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

void preencherAtratividade(vector<Trecho> &vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse)
{
    for (int i = 0; i < vetorTrechos.size(); i++)
    {
        Trecho *trechoAtual = &vetorTrechos.at(i);
        trechoAtual->trechoUmAtratividade = vetorPontosDeInteresse.at(trechoAtual->trechoUm).valorTuristico;
        trechoAtual->trechoDoisAtratividade = vetorPontosDeInteresse.at(trechoAtual->trechoDois).valorTuristico;
    }
}

int main()
{
    int quantidadePontosDeInteresse, quantidadeTrechosPossiveis;
    vector<PontoDeInteresse> vetorPontosDeInteresse;
    vector<Trecho> vetorTrechos;
    leEntradaPrincipal(quantidadePontosDeInteresse, quantidadeTrechosPossiveis);
    vetorPontosDeInteresse = leEntradaPontosDeInteresse(quantidadePontosDeInteresse);
    vetorTrechos = leEntradaTrechos(quantidadeTrechosPossiveis);
    preencherAtratividade(vetorTrechos, vetorPontosDeInteresse);
    Configuracoes configuracoes = Configuracoes();
    configuracoes.calculaRota(vetorTrechos, vetorPontosDeInteresse);
    return 0;
}