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