#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class illegal_arguement {
};

class Node {
    public:
        Node(int id);
        ~Node();
        int m_degree;
        int m_id;
};

class Edge {
    public:
        Edge(Node *source, Node *dest, double weight);
        ~Edge();
        Node *m_source;
        Node *m_dest;
        double m_weight;
};


class Graph {
    public:
        Graph(int nodes);
        ~Graph();
        bool insert_edge(int source_id, int dest_id, double weight);
        bool delete_edge(int source_id, int dest_id);
        int get_degree(int node_id);
        int get_num_edges();
        bool clear();
        double get_mst_weight();
    private:
        int m_num_nodes;
        std::vector<Edge> m_edges;
        std::vector<Node*> m_nodes;
};
