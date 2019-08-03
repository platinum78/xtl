#include <iostream>
#include "../CPP/graph.h"

typedef xtl::Graph<int, double> GraphID;

int main(void)
{
    GraphID graph(true);
    graph.AddNode(1);
    graph.AddNode(2);
    std::cout << graph.NodesConnected(1, 2) << std::endl;

    graph.ConnectNodes(1, 2, 3.2);
    std::cout << graph.NodesConnected(1, 2) << std::endl;

    return 0;
}