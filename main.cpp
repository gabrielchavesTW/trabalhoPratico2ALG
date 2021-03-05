
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <list>
#include <limits.h>
#include <queue>
using namespace std;

class Edge
{
public:
    int src, dest;
    Edge(int src, int dest)
    {
        this->src = src;
        this->dest = dest;
    }
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    vector<vector<int> > adjList;

    // Graph Constructor
    Graph(vector<Edge> edges, int N)
    {
        // resize the vector to hold `N` elements of type `vector<int>`
        adjList.resize(N);

        // add edges to the undirected graph
        for (int i = 0; i < edges.size(); i++)
        {
            Edge edgeAtual = edges.at(i);
            adjList[edgeAtual.src].push_back(edgeAtual.dest);
            adjList[edgeAtual.dest].push_back(edgeAtual.src);
        }
    }
};

// Node to store vertex and its parent info in BFS
class Node
{
public:
    int v, parent;
    Node(int v, int parent)
    {
        this->v = v;
        this->parent = parent;
    }
};

// Perform BFS on the graph starting from vertex `src` and
// return true if a cycle is found in the graph
bool BFS(Graph const &graph, int src, int N)
{
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(N);

    // mark the source vertex as discovered
    discovered[src] = true;

    // create a queue for doing BFS and
    // enqueue source vertex
    queue<Node> q;
    q.push(Node(src, -1));

    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and print it
        Node node = q.front();
        q.pop();

        for (int i = 0; i < graph.adjList[node.v].size(); i++)
        {
            int u = graph.adjList[node.v].at(i);
            if (!discovered[u])
            {
                // mark it as discovered
                discovered[u] = true;

                // construct the queue node containing info
                // about vertex and enqueue it
                q.push(Node(u, node.v));
            }

            // `u` is discovered, and `u` is not a parent
            else if (u != node.parent)
            {
                // we found a cross-edge, i.e., the cycle is found
                return true;
            }
        }
    }

    // no cross-edges were found in the graph
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
        vector<Edge> edges;
        edges.push_back(Edge(trechoOrigem, trechoDestino));
        for (int i = 0; i < resultado.size(); i++)
        {
            int src = resultado.at(i).trechoOrigem;
            int dest = resultado.at(i).trechoDestino;
            edges.push_back(Edge(src, dest));
        }

        // total number of nodes in the graph
        int N = 10;

        // build a graph from the given edges
        Graph grafo = Graph(edges, N);

        bool grafoTemCiclo = (BFS(grafo, 1, N));
        cout << grafoTemCiclo;
        return !(grafoTemCiclo);
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