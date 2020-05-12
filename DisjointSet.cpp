#include "DisjointSet.h"

/**
 * Constructs a disjoint set of a given number of vertices
 * @param int number of vertices
 */
DisjointSet::DisjointSet(int num_nodes) {
    m_num_nodes = num_nodes;

    for(int i=0; i < num_nodes; i++) {
        m_parents.push_back(i); // Nodes are all disconnected
    }
}

/**
 * Destructor for disjoint set
 */
DisjointSet::~DisjointSet() {

}

/**
 * Given two nodes, merges the subtrees they are from by updating their parent
 * @param int first node to merge
 * @param int second node to merge
 * @return true
 */
bool DisjointSet::merge(int node1, int node2) {
    // Get parents of nodes
    node1 = find(node1);
    node2 = find(node2);

    // Lower-numbered node becomes parent
    if (node1 > node2) {
        m_parents.at(node1) = node2;
    }
    else {
        m_parents.at(node2) = node1;
    }
    return 0;
}

/**
 * Given a node, returns the parent of the subtree it is contained in
 * @param int node
 * @return parent node ID
 */
int DisjointSet::find(int node) {
    // If parent is not itself, recursively find and replace with highest parent
    if (node != m_parents.at(node)) {
        m_parents.at(node) = find(m_parents.at(node));
    }
    return m_parents.at(node);
}