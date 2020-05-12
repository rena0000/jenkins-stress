#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class DisjointSet {
    public:
        DisjointSet(int num_nodes);
        ~DisjointSet();
        int find(int node);
        bool merge(int node1, int node2);
        std::vector<int> m_parents;
        int m_num_nodes;
};
