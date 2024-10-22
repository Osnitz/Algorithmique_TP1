//
// Created by matthieu on 18/10/24.
//
#include <iostream>
#include <vector>
#include <fstream> // For file input/output

using namespace std;

// Depth-first search to explore all vertices in the component
void dfsListeAdj(int v, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& composante) {
    visited[v] = true; // Mark the vertex as visited
    composante.push_back(v + 1);  // Add the vertex to the component (with offset +1)

    // Explore all neighbors of vertex v
    for (int voisin : adj[v]) {
        if (!visited[voisin]) { // If the neighbor is not visited
            dfsListeAdj(voisin, adj, visited, composante); // Recursive DFS call
        }
    }
}

// Function to find all connected components using adjacency list
void composantesConnexesListeAdj(int n, const vector<vector<int>>& adj, ofstream& outFile) {
    vector<bool> visited(n, false);  // Marks visited vertices
    vector<vector<int>> composantes; // List of components

    // Explore all vertices to find components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) { // If the vertex is not visited
            vector<int> composante; // Create a new component
            dfsListeAdj(i, adj, visited, composante); // Explore the component
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

    // Initialize adjacency list
    vector<vector<int>> adj(n); // Adjacency list

    // Read edges and fill the adjacency list
    for (int i = 0; i < m; i++) {
        int u, v;
        inFile >> u >> v; // Read the edge
        adj[u - 1].push_back(v - 1); // Add edge from u to v
        adj[v - 1].push_back(u - 1); // Add edge from v to u (undirected graph)
    }

    // Find and write connected components
    composantesConnexesListeAdj(n, adj, outFile);

    // Close the input and output files
    inFile.close();
    outFile.close();

    return 0; // Return success
}
