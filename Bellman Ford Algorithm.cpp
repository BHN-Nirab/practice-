#include<iostream>
using namespace std;

struct Edge{
    int u;
    int v;
    int w;
};

struct Graph{
    int V;
    int E;

    struct Edge *edge;
};

void printDistance(int source, int distance[], int V, bool hasCycle)
{
    cout << source << " -> " << endl;
    for(int i=0; i<V; i++)
        cout << i << "\t" << distance[i] << endl;
    cout << endl;

    if(hasCycle)
        cout << "Graph has cycle!" << endl;

}

void bellmanFord(struct Graph *graph, int source)
{
    int V = graph->V;
    int E = graph->E;
    int distance[V];

    for(int i=0; i<V; i++)
        distance[i] = INT_MAX;

    distance[source] = 0;

    for(int j=0; j<V-1; j++)
    {

        for(int i=0; i<E; i++)
        {
            int u = graph->edge[i].u;
            int v = graph->edge[i].v;
            int w = graph->edge[i].w;

            if(distance[u]!=INT_MAX && distance[v]>(distance[u]+w))
                distance[v] = distance[u]+w;
        }

    }

    bool hasCycle = false;

    for(int i=0; i<E; i++)
        {
            int u = graph->edge[i].u;
            int v = graph->edge[i].v;
            int w = graph->edge[i].w;

            if(distance[u]!=INT_MAX && distance[v]>(distance[u]+w))
            {
                hasCycle = true;
                break;
            }

        }

    printDistance(source, distance, V, hasCycle);


}

int main()
{
    int V,E;
    cin >> V >> E;

    struct Graph *graph = new struct Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new struct Edge[E];

    for(int i=0; i<E; i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        graph->edge[i].u = u;
        graph->edge[i].v = v;
        graph->edge[i].w = w;
    }

    bellmanFord(graph, 1);

    return 0;
}

/*
6 10
2 4 4
0 1 5
1 2 2
0 2 3
3 4 -1
1 3 6
2 3 7
2 5 2
4 5 -2
3 5 1

*/
