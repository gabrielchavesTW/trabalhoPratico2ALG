
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "estruturas.h"
#include "entrada.h"
#include "grafo.h"
using namespace std;



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

        for (int i = 0; i < resultado.size(); i++)
        {
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
            grafo.addEdge(src, dest);
        }

        return grafo.isCyclic();
    }

    vector<Trecho> removerTrecho(Trecho trecho, vector<Trecho> vetorTrechos)
    {
        for (int i = 0; i < vetorTrechos.size(); i++)
        {
            if (vetorTrechos.at(i).trechoDestino == trecho.trechoDestino && vetorTrechos.at(i).trechoOrigem == trecho.trechoOrigem)
            {
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
                custoTotal += trechoAtual.custo;
                atratividadeAgregada += trechoAtual.atratividadeAgregada;
            }
            else if (!novoTrechoOcasionaUmCiclo(trechoAtual.trechoOrigem, trechoAtual.trechoDestino))
            {
                resultado.push_back(trechoAtual);
                custoTotal += trechoAtual.custo;
                atratividadeAgregada += trechoAtual.atratividadeAgregada;
            }

            vetorTrechos = removerTrecho(trechoAtual, vetorTrechos);

        } while (vetorTrechos.size() > 0);
    }

    Trecho acharMelhorTrechoDisponivel(vector<Trecho> vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse)
    {
        Trecho melhorTrecho = vetorTrechos.at(0);
        for (int i = 1; i < vetorTrechos.size(); i++)
        {
            Trecho trechoAtual = vetorTrechos.at(i);

            if (trechoAtual.custo < melhorTrecho.custo)
            {
                melhorTrecho = trechoAtual;
            }
            else if (trechoAtual.custo == melhorTrecho.custo)
            {
                if (trechoAtual.atratividadeAgregada > melhorTrecho.atratividadeAgregada)
                {
                    melhorTrecho = trechoAtual;
                }
            }
        }

        return melhorTrecho;
    }
};

bool comparaCustoDosTrechos(Trecho t1, Trecho t2)
{
    if (t1.custo < t2.custo)
    {
        return true;
    }

    if (t1.custo == t2.custo && t1.atratividadeAgregada > t2.atratividadeAgregada)
    {
        return true;
    }

    return false;
}

int acharAtratividadeTrecho(int trechoOrigem, int trechoDestino, vector<PontoDeInteresse> vetorPontosDeInteresse)
{
    int atratividade = 0;
    for (int i = 0; i < vetorPontosDeInteresse.size(); i++)
    {
        PontoDeInteresse pontoAtual = vetorPontosDeInteresse.at(i);
        if (pontoAtual.codigo == trechoOrigem || pontoAtual.codigo == trechoDestino)
        {
            atratividade += pontoAtual.valorTuristico;
        }
    }

    return atratividade;
}

int main()
{
    int quantidadePontosDeInteresse, quantidadeTrechosPossiveis;
    vector<PontoDeInteresse> vetorPontosDeInteresse;
    vector<Trecho> vetorTrechos;
    leEntradaPrincipal(quantidadePontosDeInteresse, quantidadeTrechosPossiveis);
    vetorPontosDeInteresse = leEntradaPontosDeInteresse(quantidadePontosDeInteresse);
    vetorTrechos = leEntradaTrechos(quantidadeTrechosPossiveis);
    for (int i = 0; i < vetorTrechos.size(); i++)
    {
        vetorTrechos.at(i).atratividadeAgregada = acharAtratividadeTrecho(vetorTrechos.at(i).trechoOrigem, vetorTrechos.at(i).trechoDestino, vetorPontosDeInteresse);
    }

    sort(vetorTrechos.begin(), vetorTrechos.end(), comparaCustoDosTrechos);

    Configuracoes configuracoes = Configuracoes();
    configuracoes.quantidadePontosDeInteresse = vetorPontosDeInteresse.size();
    configuracoes.calculaRota(vetorTrechos, vetorPontosDeInteresse);
    configuracoes.imprimirResultado();
    return 0;
}