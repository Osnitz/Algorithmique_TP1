#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest; // Source and destination vertices of the edge
};

// Comparison function to sort edges by source vertex
bool compare(Edge a, Edge b) {
    return a.src < b.src; // Sort by source vertex
}

// Function to find the parent of a vertex using path compression
int findParent(int v, vector<int>& parent) {
    if (parent[v] == -1)
        return v; // If parent is -1, v is the root
    return findParent(parent[v], parent); // Recursive call to find the root
}

// Function to union two sets by connecting their roots
void unionSets(int src, int dest, vector<int>& parent) {
    int srcRoot = findParent(src, parent); // Find root of src
    int destRoot = findParent(dest, parent); // Find root of dest
    if (srcRoot != destRoot) {
        parent[srcRoot] = destRoot; // Connect the roots
    }
}

// Function to perform Kruskal's algorithm using adjacency matrix representation
void kruskalAdjacencyMatrix(int** graph, int n, ofstream& outFile) {
    vector<Edge> edges; // Vector to store all edges of the graph

    // Fill the edges vector from the adjacency matrix
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (graph[i][j] != 0) { // Check if there is an edge
                edges.push_back({i + 1, j + 1}); // Store edge with 1-based indexing
            }
        }
    }

    // Sort the edges based on the source vertex
    sort(edges.begin(), edges.end(), compare);

    // Initialize the parent array for union-find
    vector<int> parent(n + 1, -1);

    // Construct the spanning tree using the sorted edges
    for (const auto& edge : edges) {
        int srcRoot = findParent(edge.src, parent); // Find root of the source
        int destRoot = findParent(edge.dest, parent); // Find root of the destination

        if (srcRoot != destRoot) { // If they are in different sets
            outFile << edge.src << " " << edge.dest << endl; // Add edge to the spanning tree
            unionSets(edge.src, edge.dest, parent); // Union the sets
        }
    }
}

int main() {
    ifstream inFile("INPARBGRAPH.txt"); // Open input file
    ofstream outFile("OUTARBGRAPH.txt"); // Open output file
    int n, m; // Variables to store number of vertices (n) and edges (m)
    inFile >> n >> m; // Read n and m from input file

    // Create an adjacency matrix
    int** graph = new int*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n](); // Initialize each row to zero
    }

    // Fill the adjacency matrix with edges
    for (int i = 0; i < m; ++i) {
        int u, v; // Variables to store the vertices of an edge
        inFile >> u >> v; // Read vertices from the input file
        graph[u - 1][v - 1] = 1; // Set edge for undirected graph
        graph[v - 1][u - 1] = 1; // Set edge for undirected graph
    }

    // Apply Kruskal's algorithm to find the spanning tree
    kruskalAdjacencyMatrix(graph, n, outFile);

    // Free the allocated memory for the adjacency matrix
    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;

    inFile.close(); // Close the input file
    outFile.close(); // Close the output file
    return 0; // Return success
}
