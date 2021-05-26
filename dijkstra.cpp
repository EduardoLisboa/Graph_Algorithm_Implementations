#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
using namespace std;

#define INF 0x3f3f3f3f


/* -------------------------------------------------- */
/* --------------------- CLASSES -------------------- */
/* -------------------------------------------------- */

class Graph
{
    int V;
    list<pair<int, int>> *adj;

public:
    Graph(int V);
    void adicionarAresta(int orig, int dest, int peso);
    void dijkstra(int origem);
};


/* -------------------------------------------------- */
/* --------------------- FUNÇÕES -------------------- */
/* -------------------------------------------------- */

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<pair<int, int>>[V];
}


void Graph::adicionarAresta(int orig, int dest, int peso)
{
    adj[orig].push_back(make_pair(dest, peso));
    adj[dest].push_back(make_pair(orig, peso));
}


void Graph::dijkstra(int origem)
{
    set<pair<int, int>> setds;

    vector<int> dist(V, INF);

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
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));

                dist[v] = dist[u] + weight;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }

    cout << "Vertice   Distancia da Origem" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
}


/* --------------------------------------------------- */
/* ----------------------- MAIN ---------------------- */
/* --------------------------------------------------- */

int main(int argc, char **argv)
{
    string line;
    string sub;
    stringstream aux;
    list<int> vertices;
    int i = 0;
    int V, E;
    int orig = 0, dest = 0, peso = 0;

    fstream file;
    file.open(argv[1], ios::in);
    if(file.is_open())
    {
        getline(file, line);
        for(int lineIndex = 0; lineIndex < line.length(); lineIndex++)
        {
            if (line[lineIndex] != ' ')
                sub += line[lineIndex];
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
        Graph G(V);
        while(getline(file, line))
        {
            i = 0;
            sub.clear();
            for(int lineIndex = 0; lineIndex < line.length(); lineIndex++)
            {
                if (line[lineIndex] != ' ')
                    sub += line[lineIndex];
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
