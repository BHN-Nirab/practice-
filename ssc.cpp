#include<iostream>
#define WHITE 1
#define GRAY 2
#define BLACK 3

using namespace std;

int numberOfNode, numberOfEdge;
int graph[100][100];
int color[100];
int startingTime[100];
int finishingTime[100];
int time = 0;

int topologicalOrder[100];

int graphT[100][100];

int scc[100];
int counter = 0;

void dodfsForGraph(int x)
{
    color[x] = GRAY;
    ++time;
    startingTime[x] = time;

    for(int i=0; i<numberOfNode; i++)
    {
        if(graph[x][i] == 1)
        {
            if(color[i] == WHITE)
                dodfsForGraph(i);
        }

    }

    color[x] = BLACK;
    ++time;
    finishingTime[x] = time;
}

void dfsForGraph()
{
    for(int i=0; i<numberOfNode; i++)
        color[i] = WHITE;

    for(int i=0; i<numberOfNode; i++)
        if(color[i] == WHITE)
            dodfsForGraph(i);

}

void dotopologicalOrder()
{
    int tmpfinishingtime[numberOfNode];
    for(int i=0; i<numberOfNode; i++)
        tmpfinishingtime[i] = finishingTime[i];

    for(int i=0; i<numberOfNode; i++)
    {
        int max = tmpfinishingtime[i];
        int maxIndex = i;
        for(int j=0; j<numberOfNode; j++)
        {
            if(tmpfinishingtime[j]>=max){
                max = tmpfinishingtime[j];
                maxIndex = j;
            }
        }

        topologicalOrder[i] = maxIndex;
        tmpfinishingtime[maxIndex] = INT_MIN;
    }
}

void makeTransposeOfGraph()
{
    for(int i=0; i<numberOfNode; i++)
    {
        for(int j=0; j<numberOfNode; j++)
            graphT[j][i] = graph[i][j];
    }

}

void dodfsForGraphT(int x)
{
    color[x] = GRAY;
    ++time;
    startingTime[x] = time;

    for(int i=0; i<numberOfNode; i++)
    {
        if(graphT[x][i] == 1)
        {
            if(color[i] == WHITE)
                dodfsForGraphT(i);
        }

    }

    color[x] = BLACK;
    ++time;
    finishingTime[x] = time;
    scc[counter] = x;
    counter++;

}

void dfsForGraphT()
{
    for(int i=0; i<numberOfNode; i++)
    {
        color[i] = WHITE;
        startingTime[i] = 0;
        finishingTime[i] = 0;
    }

    time = 0;

    for(int i=0; i<numberOfNode; i++)
    {
        if(color[topologicalOrder[i]] == WHITE)
        {
            dodfsForGraphT(topologicalOrder[i]);
            scc[counter] = -1;
            counter++;
        }
    }
}

void printDfsForGraph()
{
    int tmpstime[numberOfNode];
    for(int i=0; i<numberOfNode; i++)
        tmpstime[i] = startingTime[i];

    for(int i=0; i<numberOfNode; i++)
    {
        int min = tmpstime[i];
        int minIndex = i;
        for(int j=0; j<numberOfNode; j++)
        {
            if(tmpstime[j]<=min) {
                min = tmpstime[j];
                minIndex = j;
            }
        }

        cout <<  minIndex << " (" << startingTime[minIndex] << "/" << finishingTime[minIndex] << ") " << " -> ";
        tmpstime[minIndex] = INT_MAX;
    }

    cout << endl;

}

void printTopologicalOrderForGraph()
{
    for(int i=0; i<numberOfNode; i++)
        cout << topologicalOrder[i] << " ";

    cout << endl;
}

int main()
{
    cin >> numberOfNode >> numberOfEdge;

    for(int i=0; i<numberOfEdge; i++)
    {
        int n1,n2;
        cin >> n1 >> n2;
        graph[n1][n2] = 1;
    }

    dfsForGraph();

    printDfsForGraph();

    dotopologicalOrder();

    printTopologicalOrderForGraph();

    makeTransposeOfGraph();

    for(int i=0; i<numberOfNode; i++)
    {
        for(int j=0; j<numberOfNode; j++)
        {
            if(graphT[i][j] ==1 )
                cout << i << " -> " << j << endl;

        }
    }

    dfsForGraphT();

    cout << endl;

    for(int i=0; i<counter; i++)
        cout << scc[i] << " ";

    cout << endl;

    return 0;
}

/*
8 12
0 1
1 5
1 6
2 6
2 3
3 7
4 1
5 4
5 2
6 5
6 7
7 3
*/
