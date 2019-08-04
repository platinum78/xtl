#include <iostream>
#include "../CPP/graph.h"

typedef xtl::Graph<int, double> GraphID;

int main(int argc, char **argv)
{
    GraphID graph(true);

    int nodeCnt = atoi(argv[1]);
    
    for (int i = 1; i <= nodeCnt; i++)
        graph.AddNode(i);

    for (int i = 1; i <= nodeCnt; i++)
        for (int j = 1; j <= nodeCnt; j++)
            if (i < j)
                graph.ConnectNodes(i, j, 1.5);


    return 0;
}