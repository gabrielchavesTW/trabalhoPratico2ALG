
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "grafo.h"
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
    int trechoOrigem;
    int trechoDestino;
    int custo;
    int atratividadeAgregada;
    Trecho(int trechoOrigem, int trechoDestino, int custo)
    {
        this->trechoOrigem = trechoOrigem;
        this->trechoDestino = trechoDestino;
        this->custo = custo;
        this->atratividadeAgregada = 0;
    }
};

class Configuracoes
{
public:
    vector<Trecho> resultado;
    int custoTotal = 0;
    int atratividadeAgregada = 0;
    int quantidadePontosDeInteresse;
    void imprimirResultado()
    {
        cout << custoTotal << " " << atratividadeAgregada << "\n";

        for(int i = 0; i < resultado.size(); i++){
            cout << resultado.at(i).trechoOrigem << " " << resultado.at(i).trechoDestino << "\n";
        }
    }

    bool novoTrechoOcasionaUmCiclo(int trechoOrigem, int trechoDestino)
    {
        Graph grafo(quantidadePontosDeInteresse);
        grafo.addEdge(trechoOrigem, trechoDestino);
        for (int i = 0; i < resultado.size(); i++)
        {
            int src = resultado.at(i).trechoOrigem;
            int dest = resultado.at(i).trechoDestino;
            grafo.addEdge(src,dest);
        }

        return grafo.isCyclic();
    }

    vector<Trecho> removerTrecho(Trecho trecho, vector<Trecho> vetorTrechos){
        for(int i = 0; i<vetorTrechos.size(); i++){
            if(vetorTrechos.at(i).trechoDestino == trecho.trechoDestino && vetorTrechos.at(i).trechoOrigem == trecho.trechoOrigem){
                vetorTrechos.erase(vetorTrechos.begin() + i);
            }
        }

        return vetorTrechos;
    }

    void calculaRota(vector<Trecho> vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse)
    {
        do
        {
            Trecho trechoAtual = acharMelhorTrechoDisponivel(vetorTrechos, vetorPontosDeInteresse);

            if (resultado.size() == 0)
            {
                resultado.push_back(trechoAtual);
                custoTotal +=trechoAtual.custo;
                atratividadeAgregada +=trechoAtual.atratividadeAgregada;
            }
            else if (!novoTrechoOcasionaUmCiclo(trechoAtual.trechoOrigem, trechoAtual.trechoDestino))
            {
                resultado.push_back(trechoAtual);
                custoTotal +=trechoAtual.custo;
                atratividadeAgregada +=trechoAtual.atratividadeAgregada;
            }

            vetorTrechos = removerTrecho(trechoAtual, vetorTrechos);

        } while (vetorTrechos.size() > 0);
    }

    int acharAtratividadeTrecho(int trechoOrigem, int trechoDestino, vector<PontoDeInteresse> vetorPontosDeInteresse){
        int atratividade = 0;
        for(int i =0; i<vetorPontosDeInteresse.size(); i ++){
            PontoDeInteresse pontoAtual = vetorPontosDeInteresse.at(i);
            if(pontoAtual.codigo == trechoOrigem || pontoAtual.codigo == trechoDestino){
                atratividade += pontoAtual.valorTuristico;
            }
        }

        return atratividade;
    }

    Trecho acharMelhorTrechoDisponivel(vector<Trecho> vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse){
        Trecho melhorTrecho = vetorTrechos.at(0);
        melhorTrecho.atratividadeAgregada = acharAtratividadeTrecho(melhorTrecho.trechoOrigem, melhorTrecho.trechoDestino, vetorPontosDeInteresse);
        for(int i =1; i < vetorTrechos.size(); i ++){
            Trecho trechoAtual = vetorTrechos.at(i);
            trechoAtual.atratividadeAgregada = acharAtratividadeTrecho(trechoAtual.trechoOrigem, trechoAtual.trechoDestino, vetorPontosDeInteresse);

            if(trechoAtual.custo < melhorTrecho.custo){
                melhorTrecho = trechoAtual;
            } else if(trechoAtual.custo == melhorTrecho.custo){
                if(trechoAtual.atratividadeAgregada > melhorTrecho.atratividadeAgregada){
                    melhorTrecho = trechoAtual;
                }
            }
        }
        
        return melhorTrecho;
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

        int trechoOrigem = stoi(temp.at(0));
        int trechoDestino = stoi(temp.at(1));
        int custo = stoi(temp.at(2));

        Trecho trechoAtual = Trecho(trechoOrigem, trechoDestino, custo);
        vetorTrechos.push_back(trechoAtual);
    }

    return vetorTrechos;
}

bool comparaCustoDosTrechos(Trecho t1, Trecho t2)
{
    return (t1.custo < t2.custo);
}

int main()
{
    int quantidadePontosDeInteresse, quantidadeTrechosPossiveis;
    vector<PontoDeInteresse> vetorPontosDeInteresse;
    vector<Trecho> vetorTrechos;
    leEntradaPrincipal(quantidadePontosDeInteresse, quantidadeTrechosPossiveis);
    vetorPontosDeInteresse = leEntradaPontosDeInteresse(quantidadePontosDeInteresse);
    vetorTrechos = leEntradaTrechos(quantidadeTrechosPossiveis);

    sort(vetorTrechos.begin(), vetorTrechos.end(), comparaCustoDosTrechos);

    Configuracoes configuracoes = Configuracoes();
    configuracoes.quantidadePontosDeInteresse = vetorPontosDeInteresse.size();    
    configuracoes.calculaRota(vetorTrechos, vetorPontosDeInteresse);
    configuracoes.imprimirResultado();
    return 0;
}