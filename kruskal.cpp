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

class Graph
{
public:
    int V, E;
    Aresta* aresta;
};

class subset
{
public:
    int pai;
    int rank;
};


/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

Graph* createGraph(int V, int E);
int find(subset subsets[], int i);
void Union(subset subsets[], int x, int y);
int comparar(const void* a, const void* b);
void KruskalMST(Graph* graph);


/* --------------------------------------------------- */
/* ----------------------- MAIN ---------------------- */
/* --------------------------------------------------- */

int main(int argc, char **argv)
{
    string line;
    string sub;
    stringstream aux;
    int iter = 0, i = 0;
    int V, E, gIndex = 0;
    int orig = 0, dest = 0, peso = 0;
    Graph* G;

    fstream file;
    file.open(argv[1], ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            if (iter == 0)
            {
                for(int lineIndex = 0; lineIndex < line.length(); lineIndex++)
                {
                    if (line[lineIndex] != ' ')
                    {
                        sub += line[lineIndex];
                    }
                    else
                    {
                        aux << sub;
                        aux >> V;
                        sub.clear();
                        aux.clear();
                    }
                }
                aux << sub;
                aux >> E;
                sub.clear();
                G = createGraph(V, E);
            }
            else
            {
                i = 0;
                sub.clear();
                for(int lineIndex = 0; lineIndex < line.length(); lineIndex++)
                {
                    if (line[lineIndex] != ' ')
                    {
                        sub += line[lineIndex];
                    }
                    else
                    {
                        if(i == 0)
                        {
                            aux << sub;
                            aux >> orig;
                            sub.clear();
                            aux.clear();
                        }
                        else
                        {
                            aux << sub;
                            aux >> dest;
                            sub.clear();
                            aux.clear();
                        }
                        i++;
                    }
                }
                aux << sub;
                aux >> peso;
                sub.clear();
                aux.clear();

                G->aresta[gIndex].orig = orig;
                G->aresta[gIndex].dest = dest;
                G->aresta[gIndex].peso = peso;
                gIndex++;
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

Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;

    graph->aresta = new Aresta[E];

    return graph;
}


int find(subset subsets[], int i)
{
    if (subsets[i].pai != i)
        subsets[i].pai = find(subsets, subsets[i].pai);

    return subsets[i].pai;
}


void Union(subset subsets[], int x, int y)
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


void KruskalMST(Graph* graph)
{
    int V = graph->V;
    Aresta result[V];
    int e = 0;
    int i = 0;

    qsort(graph->aresta, graph->E, sizeof(graph->aresta[0]), comparar);

    subset* subsets = new subset[(V * sizeof(subset))];

    for (int v = 0; v < V; ++v)
    {
        subsets[v].pai = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E)
    {
        Aresta proximaAresta = graph->aresta[i++];

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