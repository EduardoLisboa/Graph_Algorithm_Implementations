#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

class Subset
{
public:
    int pai;
    int rank;
};


/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

Grafo* criarGrafo(int V, int E);
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
int comparar(const void* a, const void* b);
void KruskalMST(Grafo* grafo);


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

    KruskalMST(G);

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


int find(Subset subsets[], int i)
{
    if (subsets[i].pai != i)
        subsets[i].pai = find(subsets, subsets[i].pai);

    return subsets[i].pai;
}


void Union(Subset subsets[], int x, int y)
{
    int raizX = find(subsets, x);
    int raizY = find(subsets, y);

    if (subsets[raizX].rank < subsets[raizY].rank)
        subsets[raizX].pai = raizY;
    else if (subsets[raizX].rank > subsets[raizY].rank)
        subsets[raizY].pai = raizX;

    else
    {
        subsets[raizY].pai = raizX;
        subsets[raizX].rank++;
    }
}


int comparar(const void* a, const void* b)
{
    Aresta* a1 = (Aresta*)a;
    Aresta* b1 = (Aresta*)b;
    return a1->peso > b1->peso;
}


void KruskalMST(Grafo* grafo)
{
    int V = grafo->V;
    Aresta result[V];
    int e = 0;
    int i = 0;

    qsort(grafo->aresta, grafo->E, sizeof(grafo->aresta[0]), comparar);

    Subset* subsets = new Subset[(V * sizeof(Subset))];

    for (int v = 0; v < V; ++v)
    {
        subsets[v].pai = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < grafo->E)
    {
        Aresta proximaAresta = grafo->aresta[i++];

        int x = find(subsets, proximaAresta.orig);
        int y = find(subsets, proximaAresta.dest);

        if (x != y)
        {
            result[e++] = proximaAresta;
            Union(subsets, x, y);
        }
    }

    cout << "As arestas da MST construida:" << endl;
    int custoMinimo = 0;
    for (i = 0; i < e; ++i)
    {
        cout << result[i].orig << " -- " << result[i].dest << " = " << result[i].peso << endl;
        custoMinimo = custoMinimo + result[i].peso;
    }

    cout << "Custo Minimo de Arvore Geradora: " << custoMinimo << endl;
}