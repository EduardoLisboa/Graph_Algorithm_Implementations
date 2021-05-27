#include <iostream>
#include <climits>
#include <queue>
#include <cstring>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

#define Vertices 6

/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

bool bfs(int rGraph[][Vertices], int orig, int dest, int pai[]);
int fordFulkerson(int graph[Vertices][Vertices], int orig, int dest);


/* --------------------------------------------------- */
/* ----------------------- MAIN ---------------------- */
/* --------------------------------------------------- */

int main(int argc, char **argv)
{
    string linha;
    string sub;
    stringstream strParaIntAux;
    list<int> vertices;
    int i = 0;
    int V, E;
    int orig = 0, dest = 0, peso = 0;

    int G[Vertices][Vertices];
    for (int i = 0; i < Vertices; i++)
        for (int j = 0; j < Vertices; j++)
            G[i][j] = 0;

    fstream file;
    file.open(argv[1], ios::in);
    if(file.is_open())
    {
        getline(file, linha);
        for(int indiceLinha = 0; indiceLinha < linha.length(); indiceLinha++)
        {
            if (linha[indiceLinha] != ' ')
                sub += linha[indiceLinha];
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
        while(getline(file, linha))
        {
            i = 0;
            sub.clear();
            for(int indiceLinha = 0; indiceLinha < linha.length(); indiceLinha++)
            {
                if (linha[indiceLinha] != ' ')
                    sub += linha[indiceLinha];
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

            bool verticeExiste = false;
            for(auto item : vertices)
            {
                if (item == orig)
                    verticeExiste = true;
            }
            if(!verticeExiste)
                vertices.push_back(orig);
            verticeExiste = false;
            for(auto item : vertices)
            {
                if (item == dest)
                    verticeExiste = true;
            }
            if(!verticeExiste)
                vertices.push_back(dest);

            G[orig][dest] = peso;

        }
        file.close();

    }

    int verticeOrigem, verticeDestino;
    cout << "Vertices disponiveis:" << endl;
    for(int item : vertices)
        cout << item << " ";
    cout << endl << "Insira o vertice de origem: ";
    cin >> verticeOrigem;
    cout << "Insira o vertice de destino: ";
    cin >> verticeDestino;
    cout << endl << "O maior flow possivel eh " << fordFulkerson(G, verticeOrigem, verticeDestino) << endl;

    return 0;
}


/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

bool bfs(int rGraph[][Vertices], int orig, int dest, int pai[])
{
    bool visitado[Vertices];
    memset(visitado, 0, sizeof(visitado));

    queue<int> q;
    q.push(orig);
    visitado[orig] = true;
    pai[orig] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < Vertices; v++) {
            if (visitado[v] == false && rGraph[u][v] > 0)
            {
                if (v == dest)
                {
                    pai[v] = u;
                    return true;
                }
                q.push(v);
                pai[v] = u;
                visitado[v] = true;
            }
        }
    }

    return false;
}


int fordFulkerson(int graph[Vertices][Vertices], int orig, int dest)
{
    int u, v;

    int rGraph[Vertices][Vertices];

    for (u = 0; u < Vertices; u++)
        for (v = 0; v < Vertices; v++)
            rGraph[u][v] = graph[u][v];

    int pai[Vertices];

    int flowMaximo = 0;

    while (bfs(rGraph, orig, dest, pai))
    {
        int caminhoFluxo = INT_MAX;
        for (v = dest; v != orig; v = pai[v])
        {
            u = pai[v];
            caminhoFluxo = min(caminhoFluxo, rGraph[u][v]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = dest; v != orig; v = pai[v])
        {
            u = pai[v];
            rGraph[u][v] -= caminhoFluxo;
            rGraph[v][u] += caminhoFluxo;
        }

        flowMaximo += caminhoFluxo;
    }

    return flowMaximo;
}
