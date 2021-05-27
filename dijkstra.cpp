#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <climits>
using namespace std;


/* -------------------------------------------------- */
/* --------------------- CLASSES -------------------- */
/* -------------------------------------------------- */

class Grafo
{
    int V;
    list<pair<int, int>> *adj;

public:
    Grafo(int V);
    void adicionarAresta(int orig, int dest, int peso);
    void dijkstra(int origem);
};


/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

Grafo::Grafo(int V)
{
    this->V = V;
    adj = new list<pair<int, int>>[V];
}


void Grafo::adicionarAresta(int orig, int dest, int peso)
{
    adj[orig].push_back(make_pair(dest, peso));
    adj[dest].push_back(make_pair(orig, peso));
}


void Grafo::dijkstra(int origem)
{
    set<pair<int, int>> setds;

    vector<int> dist(V, INT_MAX);

    setds.insert(make_pair(0, origem));
    dist[origem] = 0;

    while (!setds.empty())
    {
        pair<int, int> tmp = *(setds.begin());
        setds.erase(setds.begin());

        int u = tmp.second;

        for (auto i = adj[u].begin(); i != adj[u].end(); i++)
        {
            int v = (*i).first;
            int peso = (*i).second;

            if (dist[v] > dist[u] + peso)
            {
                if (dist[v] != INT_MAX)
                    setds.erase(setds.find(make_pair(dist[v], v)));

                dist[v] = dist[u] + peso;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }

    cout << "Vertice   Distancia da Origem" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
    
    return;
}


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
        strParaIntAux.clear();
        Grafo G(V);
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

            G.adicionarAresta(orig, dest, peso);
        }
        file.close();

        int origemDesejada;
        cout << "Vertices disponiveis:" << endl;
        for(auto item : vertices)
            cout << item << " ";
        cout << endl << "Insira o vertice de origem desejado: ";
        cin >> origemDesejada;
        G.dijkstra(origemDesejada);
    }


    return 0;
}
