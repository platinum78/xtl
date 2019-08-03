#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>

#define SUCCESS             0b00000000
#define NODE_EXISTS         0b00000001
#define EDGE_EXISTS         0b00000010
#define NODE_NOT_EXISTS     0b00000100
#define EDGE_NOT_EXISTS     0b00001000

////////////////////////////////////////////////////////////////////////////////
//                              Classes declaration                           //
////////////////////////////////////////////////////////////////////////////////

namespace xtl
{
template <typename T_data, typename T_weight>
class Graph
{
public:
    Graph(bool);
    ~Graph();

public: // Define sub-classes for nodes and edges.
    class Node;
    class Edge;

    class Node
    {
    public:
        Node();
        Node(T_data);
        Node(Node &node);
        ~Node();

    public:
        T_data GetData();
        void SetData(T_data data);

    public:
        int AddEdge(Edge *edge_ptr);
        int DelEdge(Edge *edge_ptr);
        int DisconnectEdge(Edge *edge_ptr);
        bool EdgeExists(Edge *edge_ptr);

    private:
        T_data data_;
        std::list<Edge *> neighbors_;
    };

    class Edge
    {
    public:
        Edge();
        Edge(Node * node1_ptr, Node *node2_ptr, T_weight, bool bidirectional);
        Edge(Edge &edge);
        ~Edge();

    public:
        Node *GetNode1();
        Node *GetNode2();
        T_weight GetWeight();
        bool IsBidirectional();

    public:
        void SetNode1(Node *node1_ptr);
        void SetNode2(Node *node2_ptr);
        void SetWeight(T_weight weight);
        void SetBidirectional(bool bidirectional);

    private:
        Node *node1_ptr_;
        Node *node2_ptr_;
        T_weight weight_;
        bool bidirectional_;
    };

public:
    int AddNode(T_data data);
    int DelNode(T_data data);
    int ConnectNodes(T_data node1_data, T_data node2_data, T_weight weight);
    int ConnectNodes(Node *node1_ptr, Node *node2_ptr, T_weight weight);
    int DisconnectNodes(T_data node1_data, T_data node2_data);
    int DisconnectNodes(Node *node1_ptr, Node *node2_ptr);

public:
    Node *GetNodeAddr(T_data data);
    bool NodeExists(T_data data);
    bool NodesConnected(T_data node1_data, T_data node2_data);
    bool NodesConnected(Node * node1_ptr, Node *node2_ptr);

private:
    std::list<Node *> node_list_;
    std::list<Edge *> edge_list_;
    int node_cnt_;
    int edge_cnt_;
    bool bidirectional_;
};
}; // namespace xtl


////////////////////////////////////////////////////////////////////////////////
//                          Graph object definition                           //
////////////////////////////////////////////////////////////////////////////////

// Empty constructor of graph.
template <typename T_data, typename T_weight>
xtl::Graph<T_data, T_weight>::Graph(bool bidirectional)
    : node_cnt_(0), edge_cnt_(0), bidirectional_(bidirectional)
{
    node_list_.resize(0);
    edge_list_.resize(0);
}

// Destructor of Graph.
template <typename T_data, typename T_weight>
xtl::Graph<T_data, T_weight>::~Graph()
{
    node_list_.resize(0);
    edge_list_.resize(0);
}

// Add node to Graph using data.
template <typename T_data, typename T_weight>
int xtl::Graph<T_data, T_weight>::AddNode(T_data data)
{
    if (NodeExists(data))
        return NODE_EXISTS;
    
    Node *node_ptr = new Node;
    node_ptr->SetData(data);
    node_list_.push_back(node_ptr);
    return SUCCESS;
}

// Delete node from Graph.
template <typename T_data, typename T_weight>
int xtl::Graph<T_data, T_weight>::DelNode(T_data data)
{
    Node *node_ptr = GetNodeAddr(data);
    if (node_ptr == nullptr)
        return NODE_NOT_EXISTS;
    delete node_ptr;
    return SUCCESS;
}

template <typename T_data, typename T_weight>
int xtl::Graph<T_data, T_weight>::ConnectNodes(T_data node1_data, T_data node2_data, T_weight weight)
{
    Node *node1_ptr = GetNodeAddr(node1_data);
    Node *node2_ptr = GetNodeAddr(node2_data);

    if (node1_ptr == nullptr || node2_ptr == nullptr)
        return NODE_NOT_EXISTS;
    
    return ConnectNodes(node1_ptr, node2_ptr, weight);
}

template <typename T_data, typename T_weight>
int xtl::Graph<T_data, T_weight>::ConnectNodes(Node *node1_ptr, Node *node2_ptr, T_weight weight)
{
    if (NodesConnected(node1_ptr, node2_ptr))
        return EDGE_EXISTS;
    
    Edge *edge_ptr = new Edge;
    edge_ptr->SetNode1(node1_ptr);
    edge_ptr->SetNode2(node2_ptr);
    edge_ptr->SetWeight(weight);
    edge_ptr->SetBidirectional(bidirectional_);

    edge_list_.push_back(edge_ptr);
    return SUCCESS;
}

template <typename T_data, typename T_weight>
typename xtl::Graph<T_data, T_weight>::Node *xtl::Graph<T_data, T_weight>::GetNodeAddr(T_data data)
{
    typename std::list<Node *>::iterator iter;
    for (iter = node_list_.begin(); iter != node_list_.end(); iter++)
        if ((*iter)->GetData() == data)
            return *iter;
    return nullptr;
}

template <typename T_data, typename T_weight>
bool xtl::Graph<T_data, T_weight>::NodeExists(T_data data)
{
    typename std::list<Node *>::iterator iter;
    for (iter = node_list_.begin(); iter != node_list_.end(); iter++)
        if ((*iter)->GetData() == data)
            return true;
    return false;
}

template <typename T_data, typename T_weight>
bool xtl::Graph<T_data, T_weight>::NodesConnected(T_data node1_data, T_data node2_data)
{
    typename std::list<Edge *>::iterator iter;

    for (iter = edge_list_.begin(); iter != edge_list_.end(); iter++)
    {
        if ((*iter)->GetNode1()->GetData() == node1_data &&
            (*iter)->GetNode2()->GetData() == node2_data)
            return true;
        else
            if ((*iter)->IsBidirectional())
                if ((*iter)->GetNode1()->GetData() == node2_data &&
                    (*iter)->GetNode2()->GetData() == node1_data)
                    return true;
    }
    return false;
}

template <typename T_data, typename T_weight>
bool xtl::Graph<T_data, T_weight>::NodesConnected(Node *node1_ptr, Node *node2_ptr)
{
    typename std::list<Edge *>::iterator iter;

    for (iter = edge_list_.begin(); iter != edge_list_.end(); iter++)
    {
        if ((*iter)->GetNode1() == node1_ptr &&
            (*iter)->GetNode2() == node2_ptr)
            return true;
        else
            if ((*iter)->IsBidirectional())
                if ((*iter)->GetNode1() == node2_ptr &&
                    (*iter)->GetNode2() == node1_ptr)
                    return true;
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//                           Node object definition                           //
////////////////////////////////////////////////////////////////////////////////

// Default constructor of Node.
template <typename T_data, typename T_weight>
xtl::Graph<T_data, T_weight>::Node::Node()
{
    neighbors_.resize(0);
}

// Argument constructor of Node.
template <typename T_data, typename T_weight>
xtl::Graph<T_data, T_weight>::Node::Node(T_data data)
    : data_(data)
{
    neighbors_.resize(0);
}

// Argument constructor of Node.
template <typename T_data, typename T_weight>
xtl::Graph<T_data, T_weight>::Node::Node(Node &node)
    : data_(node.data_)
{
    neighbors_ = node.neighbors_;
}

// Get data of Node.
template <typename T_data, typename T_weight>
T_data xtl::Graph<T_data, T_weight>::Node::GetData()
{
    return data_;
}

// Set data of Node.
template <typename T_data, typename T_weight>
void xtl::Graph<T_data, T_weight>::Node::SetData(T_data data)
{
    data_ = data;
}

// Check if edge exists; if not, add edge to neighbors_ list.
template <typename T_data, typename T_weight>
int xtl::Graph<T_data, T_weight>::Node::AddEdge(Edge *edge_ptr)
{
    if (EdgeExists(edge_ptr))
        return EDGE_EXISTS;
    neighbors_.push_back(edge_ptr);
    return SUCCESS;
}

// Check if edge exists; if not, add edge to neighbors_ list.
template <typename T_data, typename T_weight>
int xtl::Graph<T_data, T_weight>::Node::DelEdge(Edge *edge_ptr)
{
    typename std::list<Edge *>::iterator iter;
    for (iter = neighbors_.begin(); iter != neighbors_.end(); iter++)
    {
        if (*iter == edge_ptr)
        {
            neighbors_.erase(iter);
            delete edge_ptr;
            return SUCCESS;
        }
    }
    return EDGE_NOT_EXISTS;
}

// Check if edge exists; if not, add edge to neighbors_ list.
template <typename T_data, typename T_weight>
int xtl::Graph<T_data, T_weight>::Node::DisconnectEdge(Edge *edge_ptr)
{
    typename std::list<Edge *>::iterator iter;
    for (iter = neighbors_.begin(); iter != neighbors_.end(); iter++)
    {
        if (*iter == edge_ptr)
        {
            neighbors_.erase(iter);
            return SUCCESS;
        }
    }
    return EDGE_NOT_EXISTS;
}

// Return true if edge exists, false if not.
template <typename T_data, typename T_weight>
bool xtl::Graph<T_data, T_weight>::Node::EdgeExists(Edge *edge_ptr)
{
    typename std::list<Edge *>::iterator iter;
    for (iter = neighbors_.begin(); iter != neighbors_.end(); iter++)
        if (*iter == edge_ptr)
            return true;
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//                           Edge object definition                           //
////////////////////////////////////////////////////////////////////////////////

template <typename T_data, typename T_weight>
xtl::Graph<T_data, T_weight>::Edge::Edge()
    : node1_ptr_(nullptr), node2_ptr_(nullptr),
      weight_(0), bidirectional_(true)
{
}

template <typename T_data, typename T_weight>
xtl::Graph<T_data, T_weight>::Edge::Edge(Node *node1_ptr, Node *node2_ptr,
                                         T_weight weight, bool bidirectional)
    : node1_ptr_(node1_ptr), node2_ptr_(node2_ptr),
      weight_(weight), bidirectional_(bidirectional)
{
}

template <typename T_data, typename T_weight>
typename xtl::Graph<T_data, T_weight>::Node *xtl::Graph<T_data, T_weight>::Edge::GetNode1()
{
    return node1_ptr_;
}

template <typename T_data, typename T_weight>
typename xtl::Graph<T_data, T_weight>::Node *xtl::Graph<T_data, T_weight>::Edge::GetNode2()
{
    return node2_ptr_;
}

template <typename T_data, typename T_weight>
T_weight xtl::Graph<T_data, T_weight>::Edge::GetWeight()
{
    return weight_;
}

template <typename T_data, typename T_weight>
bool xtl::Graph<T_data, T_weight>::Edge::IsBidirectional()
{
    return bidirectional_;
}

template <typename T_data, typename T_weight>
void xtl::Graph<T_data, T_weight>::Edge::SetNode1(Node *node1_ptr)
{
    node1_ptr_ = node1_ptr;
}

template <typename T_data, typename T_weight>
void xtl::Graph<T_data, T_weight>::Edge::SetNode2(Node *node2_ptr)
{
    node2_ptr_ = node2_ptr;
}

template <typename T_data, typename T_weight>
void xtl::Graph<T_data, T_weight>::Edge::SetWeight(T_weight weight)
{
    weight_ = weight;
}

template <typename T_data, typename T_weight>
void xtl::Graph<T_data, T_weight>::Edge::SetBidirectional(bool bidirectional)
{
    bidirectional_ = bidirectional;
}

template <typename T_data, typename T_weight>
std::ostream &operator<<(std::ostream &out, typename xtl::Graph<T_data, T_weight>::Edge &e)
{
    out << "Node 1: " << e.node1_ptr_->GetData() << ", Node 2: " << e.node2_ptr_->GetData();
    out << ", Weight: " << e.node1_ptr_->GetWeight();
    return out;
}

template <typename T_data, typename T_weight>
std::ostream &operator<<(std::ostream &out, typename xtl::Graph<T_data, T_weight>::Node &n)
{
    out << "Data: " << n.data_;
    return out;
}

#endif