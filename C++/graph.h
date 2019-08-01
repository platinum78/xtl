#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>

namespace xtl
{
template <typename T_data> class Node;
template <typename T_node, typename T_weight> class Edge;
template <typename T_data, typename T_weight> class Graph;

template <typename T_data>
class Node
{
public:
    Node();
    Node(T_data);
    Node(Node &);
    ~Node();

public:
    T_data GetData();

public:
    T_data SetData();

private:
    T_data data_;
    std::list<Edge<Node<T_data> *, >
};

template <typename T_node, typename T_weight>
class Edge
{
public:
    Edge();
    Edge(T_node node1, T_node node2, T_weight weight);
    Edge(Edge &);
    ~Edge();

private:
    T_node node1_;
    T_node node2_;
    T_weight weight_;
    bool bidirectional_;
};

template <typename T_data, typename T_weight>
class Graph
{
};
}; // namespace xtl

#endif