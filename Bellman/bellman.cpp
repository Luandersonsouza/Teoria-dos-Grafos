#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int u;
    int v;
    int peso;
};

int main(int argc, char **argv)
{
    int arq_in = 0, arq_out = 0, init = 0;
    bool set_arq = false, output = false, set_init = false;
    ifstream arquivo;

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-f"))
        {
            set_arq = true;
            arq_in = i + 1;
        }

        if (!strcmp(argv[i], "-i"))
            set_init = true;

        if (!strcmp(argv[i], "-o"))
        {
            arq_out = i + 1;
            output = true;
        }

        if (!strcmp(argv[i], "-h"))
        {
            cout << "\n---- HELP ---- " << endl;
            cout << "\n-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
            cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contem o grafo de entrada" << endl;
            cout << "-i : vertice inicial" << endl;
        }
    }

    if (set_arq)
        arquivo.open(argv[arq_in]);

    if (arquivo.fail() == 1)
    {
        cout << "File not found, please input the file name after -f!\n\nExample: ./bin -f input_file.txt\n\n";
        return 1;
    }

    int n, m;
    arquivo >> n >> m;

    vector<edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        int v, w, p;

        arquivo >> v >> w >> p;

        edge e;

        e.u = v - 1;
        e.v = w - 1;
        e.peso = p;

        edges.push_back(e);
    }

    arquivo.close();

    if (set_init)
    {
        int j;
        for (j = 0; j < argc; j++)
        {
            int i, neg = 0;
            for (i = 0; i < strlen(argv[j]); i++)
            {   
                if (argv[j][i] >= 48 && argv[j][i] <= 57 || argv[j][i] == '-')
                {
                    if (argv[j][i] == '-')
                    {
                        neg = 1;
                    }
                    else
                    {
                        init = init * 10 + argv[j][i] - '0';
                    }
                }
                else
                {
                    init = 0;
                    break;
                }

            } 

            if (neg)
                init *= (-1);

            if (i == strlen(argv[j]))
            {
                init -= 1;
                break;
            }
        }
    }

    if (init >= n || init < 0)
    {
        cout << "Vertex provided by -i does not belong to the graph!\n";
        return 1;
    }

    vector<int> dist(n, INT_MAX);
    vector<int> parent(n);

    dist[init] = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        for (auto edge : edges)
        {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.peso < dist[edge.v])
            {
                dist[edge.v] = dist[edge.u] + edge.peso;
                parent[edge.v] = edge.v;
            }
        }
    }

    bool up = false;

    for (auto edge : edges)
    {
        if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.peso < dist[edge.v])
        {
            cout << "The graph has a negative cycle!\n";
            return 1;
        }
    }
    
    if (output)
    {
        ofstream out_file;
        out_file.open(argv[arq_out]);

        if (out_file.fail() == 1)
        {
            cout << "Error creating file, please input the file name after -o!\n\nExample: ./bin -o output_file.txt\n\n";
            return 1;
        }

        for (int i = 0; i < n; i++)
        {
            if (dist[i] == INT_MAX)
            {
                out_file << i + 1 << ":-1 ";
            }
            else
            {
                out_file << i + 1 << ":" << dist[i] << " ";
            }
        }

        out_file << endl;
    }

    
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (dist[i] == INT_MAX)
            {
                cout << i + 1 << ":n ";
            }
            else
            {
                cout << i + 1 << ":" << dist[i] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
