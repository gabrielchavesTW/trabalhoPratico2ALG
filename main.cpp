
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
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

class Resultado
{
public:
    int custoTotal;
    int atratividadeAgregada;
    vector<Trecho> trechosResultado;
    Resultado()
    {
        this->custoTotal = 0;
        this->atratividadeAgregada = 0;
    }
    void adicionarCusto(int custo)
    {
        this->custoTotal += custo;
    }
    void adicionarAtratividade(int atratividadeTrecho)
    {
        this->atratividadeAgregada += atratividadeTrecho;
    }
    void adicionarTrecho(Trecho trecho)
    {
        this->trechosResultado.push_back(trecho);
    }
};

class Configuracoes
{
public:
    void imprimirResultado(Resultado resultado, vector<int> qtdTrechosPorPonto)
    {
        cout << resultado.custoTotal << " " << resultado.atratividadeAgregada << "\n";
        for (int i = 0; i < qtdTrechosPorPonto.size(); i++)
        {
            cout << qtdTrechosPorPonto.at(i) << " ";
        }
        cout << "\n";
        for (int i = 0; i < resultado.trechosResultado.size(); i++)
        {
            Trecho trechoAtual = resultado.trechosResultado.at(i);
            cout << trechoAtual.trechoOrigem << " " << trechoAtual.trechoDestino << " " << trechoAtual.custo << "\n";
        }
    }

    void calculaRota(vector<Trecho> vetorTrechos, vector<PontoDeInteresse> vetorPontosDeInteresse)
    {
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

bool comparaCustoDosTrechos(Trecho t1, Trecho t2){
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
    return 0;
}