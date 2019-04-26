#include<iostream>
#include<stdio.h>
#include<stack>
#define WHITE 1
#define GRAY 2
#define BLACK 3
using namespace std;

int numberOfNode, numberOfEdge;
int graph[100][100];
int color[100];
int st[100];
int ft[100];
int time = 0;

void dodfs(int startingNode)
{

    color[startingNode] = GRAY;
    ++time;
    st[startingNode] = time;

    for(int i=0; i<numberOfNode; i++)
    {
        if(graph[startingNode][i] == 1)
        {
            if(color[i] == WHITE)
                dodfs(i);
        }
    }

    color[startingNode] = BLACK;
    ++time;
    ft[startingNode] = time;
}

void dfs()
{
    for(int i=0; i<numberOfNode; i++)
        color[i] = WHITE;
    for(int i=0; i<numberOfNode; i++)
    {
        if(color[i] == WHITE)
        {
            dodfs(i);
        }

    }

}

void printdfs()
{
    int tmpstime[numberOfNode];
    for(int i=0; i<numberOfNode; i++)
        tmpstime[i] = st[i];

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

        cout << (char)('A' + minIndex) << " -> ";
        tmpstime[minIndex] = INT_MAX;
    }

    cout << endl;

}

void printSFT()
{
    for(int i=0; i<numberOfNode; i++)
        cout << (char)('A'+i) << " (" << st[i] << " / " << ft[i] << ")" << endl;
}

void printTopologicalOrder()
{
    int tmpftime[numberOfNode];
    for(int i=0; i<numberOfNode; i++)
        tmpftime[i] = ft[i];

    for(int i=0; i<numberOfNode; i++)
    {
        int max = tmpftime[i];
        int maxIndex = i;
        for(int j=0; j<numberOfNode; j++)
        {
            if(tmpftime[j]>=max) {
                max = tmpftime[j];
                maxIndex = j;
            }
        }

        cout << (char)('A' + maxIndex) << " -> ";
        tmpftime[maxIndex] = INT_MIN;
    }

    cout << endl;
}

int main()
{

    cin >> numberOfNode >> numberOfEdge;

    int n1, n2;
    for(int i=0; i<numberOfEdge; i++)
    {
        cin >> n1 >> n2;
        graph[n1][n2] = 1;
    }

    dfs();
    printdfs();
    printSFT();
    printTopologicalOrder();


    return 0;
}
/*
10 13
0 1
0 5
1 7
3 2
3 4
3 7
3 8
4 8
6 0
6 1
6 2
8 2
9 4*/
