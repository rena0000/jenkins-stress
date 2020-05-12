#include <iostream>
#include <string>
#include "Graph.h"
#include "DisjointSet.h"

void delimit(int, std::string);

// Static
std::string delimited_inputs[3];
std::string to_delimit;
std::string delimiter = ";";
std::string input_stream;

int num_nodes = 0;

void delimit(int n, std::string input) {
    for (int i=0; i < n - 1; i++) {
        std::size_t pos = input.find(delimiter);
        delimited_inputs[i] = input.substr(0, pos);
        input.erase(0, pos+1);
    }
    delimited_inputs[n-1] = input;

    // Print delimited values - remove later
    // for (int i=0; i < n; i++) {
    //     std::cout << i << ": " << delimited_inputs[i] << std::endl;
    // }
}

int main() {
    // Create graph
    std::cin >> input_stream;
    //std::cout << "creating mst" << std::endl;
    std::cin >> num_nodes;
    
    try {
        // Initialize
        Graph new_graph = Graph(num_nodes);
        std::cout << "success" << std::endl;

        while(true) {
            if (std::cin.eof()) {
                break;
            }
            input_stream = "";
            std::cin >> input_stream;

            // Inserting edge
            if (input_stream == "i") {
                //std::cout << "insert" << std::endl;
                std::cin >> to_delimit;
                delimit(3, to_delimit);

                try {
                    new_graph.insert_edge(std::stoi(delimited_inputs[0]), std::stoi(delimited_inputs[1]), std::stod(delimited_inputs[2]));
                    std::cout << "success" << std::endl;
                }
                catch(illegal_arguement e) {
                    std::cout << "failure" << std::endl;
                }
            }
            // Deleting edge
            else if (input_stream == "d") {
                //std::cout << "delete" << std::endl;
                std::cin >> to_delimit;
                delimit(2, to_delimit);

                try {
                    if (new_graph.delete_edge(std::stoi(delimited_inputs[0]), std::stoi(delimited_inputs[1]))) {
                        std::cout << "failure" << std::endl;
                    }
                    else {
                        std::cout << "success" << std::endl;
                    }
                }
                catch (illegal_arguement e) {
                    std::cout << "failure" << std::endl;
                }
            }
            // Degree of vertex
            else if (input_stream == "degree") {
                //std::cout << "degree" << std::endl;
                int node_id;
                std::cin >> node_id;

                try {
                    int degree = new_graph.get_degree(node_id);
                    std::cout << "degree of " << node_id << " is " << degree << std::endl;
                }
                catch (illegal_arguement e) {
                    std::cout << "failure" << std::endl;
                }
            }
            // Edge count
            else if (input_stream == "edge_count") {
                //std::cout << "edge count" << std::endl;
                std::cout << "edge count is " << new_graph.get_num_edges() << std::endl;
            }
            // Clear graph
            else if (input_stream == "clear") {
                //std::cout << "clear" << std::endl;
                new_graph.clear();
                std::cout << "success" << std::endl;
            }
            // Find MST
            else if (input_stream == "mst") {
                //std::cout << "mst" << std::endl;

                double mst_value = new_graph.get_mst_weight();
                if (mst_value == -1) {
                    std::cout << "not connected" << std::endl;
                }
                else {
                    std::cout << "mst " << mst_value << std::endl;
                }
            }
            else {

            }
            //std::cout << std::endl;
            
        }
    }
    catch(illegal_arguement e) {
        std::cout << "failure" << std::endl;
    }

    return 0;
}

