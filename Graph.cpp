#include "Graph.h"
#include "DisjointSet.h"

/**
 * Logic for sorting edges by increasing weight
 */
bool sortByWeight(Edge edge1, Edge edge2) {
    return (edge1.m_weight < edge2.m_weight);
}

/**
 * Constructs a node given a number value
 * @param int number
 */
Node::Node(int id) {
    m_id = id;
}

/**
 * Destructor for a node
 */
Node::~Node() {

}

/**
 * Constructs an edge given a source node, destination node, and weight
 * @param Node* source node
 * @param Node* destination node
 * @param double weight
 */
Edge::Edge(Node *source, Node *dest, double weight) {
    m_source = source;
    m_dest = dest;
    m_weight = weight;
}

/**
 * Destructor for an edge
 */
Edge::~Edge() {

}

/**
 * Constructs a graph given the number of vertices
 * @param int number of vertices
 */
Graph::Graph(int nodes) {
    if(nodes <= 0) {
        throw illegal_arguement();
    }
    m_num_nodes = nodes;

    // Create nodes
    for (int i=0; i < nodes; i++) {
        Node *new_node = new Node(i);
        new_node->m_id = i;
        new_node->m_degree = 0;
        m_nodes.push_back(new_node);
    }
}

/**
 * Destructor for a graph; deletes all vertices (nodes)
 */
Graph::~Graph() {
    for (int i=0; i < m_num_nodes; i++) {
        delete m_nodes.at(i);
    }
}

/**
 * Inserts a weighted edge into a graph
 * @param int source node
 * @param int destination node
 * @param double weight
 * @return boolean success or failure
 */
bool Graph::insert_edge(int source_id, int dest_id, double weight){
    if (weight <= 0) {
        throw illegal_arguement();
    }
    if (source_id < 0 || source_id >= m_num_nodes) {
        throw illegal_arguement();
    }
    if (dest_id < 0 || dest_id>= m_num_nodes) {
        throw illegal_arguement();
    }
    if(source_id == dest_id) {
        throw illegal_arguement();
    }

    Node *source = m_nodes.at(source_id);
    Node *dest = m_nodes.at(dest_id);

    // Check if edge already exists
    for (int i=0; i < m_edges.size(); i++) {
        Edge current_edge = m_edges.at(i);

        if(current_edge.m_source == source && current_edge.m_dest == dest) {
            m_edges.at(i).m_weight = weight; // Update weight
            return 0;
        }
        else if (current_edge.m_source == dest && current_edge.m_dest == source) {
            m_edges.at(i).m_weight = weight; // Update weight
            return 0;
        }
    }

    // New edge
    Edge new_edge = Edge(source, dest, weight);
    m_edges.push_back(new_edge);
    // Increment degrees
    source->m_degree++;
    dest->m_degree++;
    return 0;
}       

/**
 * Deletes an edge from a graph
 * @param int source node
 * @param int destination node
 * @return boolean success or failure
 */
bool Graph::delete_edge(int source_id, int dest_id){
    if (source_id < 0 || source_id >= m_num_nodes) {
        throw illegal_arguement();
    }
    if (dest_id < 0 || dest_id>= m_num_nodes) {
        throw illegal_arguement();
    }
    if(source_id == dest_id) {
        throw illegal_arguement();
    }

    Node *source = m_nodes.at(source_id);
    Node *dest = m_nodes.at(dest_id);

    // Check if edge exists
    for (int i=0; i < m_edges.size(); i++) {
        Edge current_edge = m_edges.at(i);
        if(current_edge.m_source == source && current_edge.m_dest == dest) {
            m_edges.erase(m_edges.begin() + i);
            source->m_degree--;
            dest->m_degree--;
            return 0;
        }
    }
    return 1;
}

/**
 * Returns the degree of a vertex
 * @param int vertex number
 * @return degree
 */
int Graph::get_degree(int node_id){
    if (node_id < 0 || node_id>= m_num_nodes) {
        throw illegal_arguement();
    }
    Node *node = m_nodes.at(node_id);

    return node->m_degree;
}

/**
 * Returns the number of edges in the current graph
 * @return number of edges
 */
int Graph::get_num_edges(){
    return m_edges.size();
}

/**
 * Removes all edges from the graph
 * @return success
 */
bool Graph::clear(){
    // Reset node degrees
    for (int i=0; i < m_num_nodes; i++) {
        m_nodes.at(i)->m_degree = 0;
    }
    // Remove all edges
    m_edges.clear();
    return 0;
}

/**
 * Calculates the total weight of the graph's MST using Kruskal's algorithm
 * @return total weight
 */
double Graph::get_mst_weight() {
    double weight = 0;
    int edges_count = 0;
    //std::cout << "sorting" << std::endl;
    std::sort(m_edges.begin(), m_edges.end(), sortByWeight);

    DisjointSet dj_set = DisjointSet(m_num_nodes);

    for (int i=0; i < m_edges.size(); i++) {
        Edge current_edge = m_edges.at(i);
        int node1 = current_edge.m_source->m_id;
        int node2 = current_edge.m_dest->m_id;

        int node1_parent = dj_set.find(node1);
        int node2_parent = dj_set.find(node2);

        // for(int i=0; i < m_edges.size(); i++) {
        //     std::cout <<m_edges.at(i).m_weight << " ";
        // }
        // std::cout << std::endl;

        // Nodes are from disconnected sets
        if (node1_parent != node2_parent) {
            //std::cout << "connected " << node1 << " and " << node2 << "; + " << current_edge.m_weight<< std::endl;
            weight += current_edge.m_weight;
            //std::cout << "weight = " << weight << std::endl;
            dj_set.merge(node1_parent, node2_parent);
            edges_count++;
        }
        // Graph has been connected
        if (edges_count == (m_num_nodes - 1)) {
            break;
        }
    }

    // Not enough edges connected - return error value
    if (edges_count != (m_num_nodes - 1)) {
        return -1;
    }
    else {
        return weight;
    }
}