#include <iostream>
#include <vector>
#include <fstream> // For file input/output

using namespace std;

// Depth-first search to explore all vertices in the component
void dfsMatriceAdj(int v, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& composante) {
    visited[v] = true; // Mark the vertex as visited
    composante.push_back(v + 1);  // Add the vertex to the component (with offset +1)

    // Explore all neighbors of vertex v
    for (int i = 0; i < adj.size(); i++) {
        if (adj[v][i] == 1 && !visited[i]) { // If there is an edge and the neighbor is not visited
            dfsMatriceAdj(i, adj, visited, composante); // Recursive DFS call
        }
    }
}

// Function to find all connected components using adjacency matrix
void composantesConnexesMatriceAdj(int n, const vector<vector<int>>& adj, ofstream& outFile) {
    vector<bool> visited(n, false);  // Marks visited vertices
    vector<vector<int>> composantes; // List of components

    // Explore all vertices to find components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) { // If the vertex is not visited
            vector<int> composante; // Create a new component
            dfsMatriceAdj(i, adj, visited, composante); // Explore the component
            composantes.push_back(composante); // Store the component
        }
    }

    // Write results to the output file
    outFile << composantes.size() << endl; // Number of connected components
    for (int i = 0; i < composantes.size(); i++) {
        outFile << "composante connexe " << i + 1 << endl; // Component label
        for (int sommet : composantes[i]) {
            outFile << sommet << " "; // Print vertices of the component
        }
        outFile << endl; // New line after each component
    }
}

int main() {
    // Open input and output files
    ifstream inFile("INPCONGRAPH.txt");
    ofstream outFile("OUTCONGRAPH.txt");
    
    // Check if files opened successfully
    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1; // Exit with an error code
    }

    // Read the number of vertices and edges
    int n, m;
    inFile >> n >> m;

    // Initialize adjacency matrix
    vector<vector<int>> adj(n, vector<int>(n, 0)); // Adjacency matrix with n x n size

    // Read edges and fill the adjacency matrix
    for (int i = 0; i < m; i++) {
        int u, v;
        inFile >> u >> v; // Read the edge
        adj[u - 1][v - 1] = 1; // Mark edge in the adjacency matrix (1-based to 0-based)
        adj[v - 1][u - 1] = 1; // Mark the undirected edge
    }

    // Find and write connected components
    composantesConnexesMatriceAdj(n, adj, outFile);

    // Close the input and output files
    inFile.close();
    outFile.close();

    return 0; // Return success
}
