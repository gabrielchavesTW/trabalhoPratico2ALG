
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <list> 
#include <limits.h> 
#include <bits/stdc++>
using namespace std;

void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
 
bool isCyclicConntected(vector<int> adj[], int s,
                        int V, vector<bool>& visited)
{
    // Set parent vertex for every vertex as -1.
    vector<int> parent(V, -1);
 
    // Create a queue for BFS
    queue<int> q;
 
    // Mark the current node as 
    // visited and enqueue it
    visited[s] = true;
    q.push(s);
 
    while (!q.empty()) {
 
        // Dequeue a vertex from queue and print it
        int u = q.front();
        q.pop();
 
        // Get all adjacent vertices of the dequeued
        // vertex u. If a adjacent has not been visited,
        // then mark it visited and enqueue it. We also
        // mark parent so that parent is not considered
        // for cycle.
        for (auto v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                parent[v] = u;
            }
            else if (parent[u] != v)
                return true;
        }
    }
    return false;
}
 
bool isCyclicDisconntected(vector<int> adj[], int V)
{
    // Mark all the vertices as not visited
    vector<bool> visited(V, false);
 
    for (int i = 0; i < V; i++)
        if (!visited[i] && isCyclicConntected(adj, i,
                                         V, visited))
            return true;
    return false;
}

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
    int trechoOrigem;
    int trechoDestino;
    int custo;
    bool disponivel;
    Trecho(int trechoOrigem, int trechoDestino, int custo)
    {
        this->trechoOrigem = trechoOrigem;
        this->trechoDestino = trechoDestino;
        this->custo = custo;
        this->disponivel = true;
    }
};

class Configuracoes
{
public:
    vector<Trecho> resultado;
    void imprimirResultado()
    {
        int custoTotal = 0;
        int atratividadeAgregada = 0;
        for (int i = 0; i < resultado.size(); i++)
        {
            custoTotal += resultado.at(i).custo;
        }

        cout << custoTotal << " " << atratividadeAgregada;
    }

    bool novoTrechoNaoOcasionaUmCiclo(int trechoOrigem, int trechoDestino)
    {
        int tamanhoGrafo = resultado.size() + 1;
        Graph g1(tamanhoGrafo);
        for (int i = 0; i < resultado.size(); i++)
        {
            int src = resultado.at(i).trechoOrigem;
            int dest = resultado.at(i).trechoDestino;
            g1.addEdge(1, 0);
        }
        g1.addEdge(4, 2);

        return !(g1.isCyclic());
    }

    void calculaRota(vector<Trecho> vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse)
    {
        int tamanhoResultado = vetorPontosDeInteresse.size() - 1;
        int i = 0;
        do
        {
            Trecho trechoAtual = vetorTrechos.at(i);

            if (resultado.size() == 0)
            {
                resultado.push_back(trechoAtual);
            }
            else if (novoTrechoNaoOcasionaUmCiclo(trechoAtual.trechoOrigem, trechoAtual.trechoDestino))
            {
                resultado.push_back(trechoAtual);
            }
            i++;
            //vetorTrechos.erase(vetorTrechos.begin() + i);
        } while (i <= tamanhoResultado);
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

    //Ordena o grafo pelo peso das arestas assim como o algoritmo de kruskal
    sort(vetorTrechos.begin(), vetorTrechos.end(), comparaCustoDosTrechos);

    Configuracoes configuracoes = Configuracoes();
    configuracoes.calculaRota(vetorTrechos, vetorPontosDeInteresse);
    configuracoes.imprimirResultado();
    return 0;
}