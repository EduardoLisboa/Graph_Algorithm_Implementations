#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

/* -------------------------------------------------- */
/* --------------------- CLASSES -------------------- */
/* -------------------------------------------------- */

class Aresta
{
public:
    int orig, dest, peso;
};

class Grafo
{
public:
    int V, E;
    Aresta* aresta;
};


/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

Grafo* criarGrafo(int V, int E);
void bellmanFord(struct Grafo* grafo, int orig);


/* --------------------------------------------------- */
/* ----------------------- MAIN ---------------------- */
/* --------------------------------------------------- */

int main(int argc, char **argv)
{
    string linha;
    string sub;
    stringstream strParaIntAux;
    int iter = 0, i = 0;
    int V, E, indiceGrafo = 0;
    int orig = 0, dest = 0, peso = 0;
    Grafo* G;

    fstream file;
    file.open(argv[1], ios::in);
    if(file.is_open())
    {
        while(getline(file, linha))
        {
            if (iter == 0)
            {
                for(int indiceLinha = 0; indiceLinha < linha.length(); indiceLinha++)
                {
                    if (linha[indiceLinha] != ' ')
                    {
                        sub += linha[indiceLinha];
                    }
                    else
                    {
                        strParaIntAux << sub;
                        strParaIntAux >> V;
                        sub.clear();
                        strParaIntAux.clear();
                    }
                }
                strParaIntAux << sub;
                strParaIntAux >> E;
                sub.clear();
                G = criarGrafo(V, E);
            }
            else
            {
                i = 0;
                sub.clear();
                for(int indiceLinha = 0; indiceLinha < linha.length(); indiceLinha++)
                {
                    if (linha[indiceLinha] != ' ')
                    {
                        sub += linha[indiceLinha];
                    }
                    else
                    {
                        if(i == 0)
                        {
                            strParaIntAux << sub;
                            strParaIntAux >> orig;
                            sub.clear();
                            strParaIntAux.clear();
                        }
                        else
                        {
                            strParaIntAux << sub;
                            strParaIntAux >> dest;
                            sub.clear();
                            strParaIntAux.clear();
                        }
                        i++;
                    }
                }
                strParaIntAux << sub;
                strParaIntAux >> peso;
                sub.clear();
                strParaIntAux.clear();

                G->aresta[indiceGrafo].orig = orig;
                G->aresta[indiceGrafo].dest = dest;
                G->aresta[indiceGrafo].peso = peso;
                indiceGrafo++;
            }
            iter++;
        }
        file.close();
    }

    bellmanFord(G, 0);

    return 0;
}


/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

Grafo* criarGrafo(int V, int E)
{
    Grafo* grafo = new Grafo;
    grafo->V = V;
    grafo->E = E;
    grafo->aresta = new Aresta[E];
    return grafo;
}


void bellmanFord(struct Grafo* grafo, int orig)
{
    int V = grafo->V;
    int E = grafo->E;
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[orig] = 0;

    for (int i = 1; i < V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = grafo->aresta[j].orig;
            int v = grafo->aresta[j].dest;
            int peso = grafo->aresta[j].peso;
            if (dist[u] != INT_MAX && dist[u] + peso < dist[v])
                dist[v] = dist[u] + peso;
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = grafo->aresta[i].orig;
        int v = grafo->aresta[i].dest;
        int peso = grafo->aresta[i].peso;
        if (dist[u] != INT_MAX && dist[u] + peso < dist[v])
        {
            cout << "Grafo contem ciclo de peso negativo" << endl;
            return;
        }
    }

    cout << "Vertice   Distancia da Origem" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;

    return;
}
