#include <iostream>
#include <vector>
#include <climits>
#include <fstream>  // For file input/output
#include <algorithm> // For reverse function

using namespace std;

const int INF = INT_MAX;

// Dijkstra's algorithm for shortest paths using an adjacency list
void dijkstraListeAdj(int n, int start, int end, const vector<vector<pair<int, int>>>& adj, ofstream& outFile) {
    vector<int> dist(n, INF);  // Stores the minimum distances from the start vertex
    vector<bool> visited(n, false);  // Marks visited vertices
    vector<int> prev(n, -1);  // To reconstruct the path

    dist[start] = 0;  // Distance from start to itself is 0

    for (int i = 0; i < n; i++) {
        // Find the unvisited vertex with the smallest distance
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;  // If the smallest distance is infinite, we stop

        visited[u] = true;  // Mark the vertex as visited

        // Update distances of neighboring vertices
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;  // Update distance
                prev[v] = u;  // Store previous vertex for path reconstruction
            }
        }
    }

    // Write results to the output file
    if (dist[end] == INF) {
        outFile << "Aucun chemin trouvé" << endl; // Output if no path found
    } else {
        outFile << dist[end] << endl;  // Shortest distance

        // Reconstruct the path
        vector<int> path;
        for (int at = end; at != -1; at = prev[at]) {
            path.push_back(at + 1);  // +1 for human-readable format
        }
        reverse(path.begin(), path.end()); // Reverse to get the path from start to end

        for (int i = 0; i < path.size(); i++) {
            outFile << path[i]; // Print vertices of the path
            if (i != path.size() - 1) outFile << " → "; // Add arrow between vertices
        }
        outFile << endl; // New line at the end of the output
    }
}

int main() {
    // Open input and output files
    ifstream inFile("INPDIJGRAPH.txt");
    ofstream outFile("OUTDIJGRAPH.txt");

    // Check if files opened successfully
    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1; // Exit with an error code
    }

    // Read the number of vertices, edges, start and end vertices
    int n, m, start, end;
    inFile >> n >> m >> start >> end;
    start--;  // Convert to zero-based indexing
    end--;

    vector<vector<pair<int, int>>> adj(n); // Initialize adjacency list

    // Read edges and fill the adjacency list
    for (int i = 0; i < m; i++) {
        int u, v, w;
        inFile >> u >> v >> w; // Read edge
        u--; v--;  // Convert to zero-based indexing
        adj[u].push_back({v, w});  // Add edge to the adjacency list
        adj[v].push_back({u, w});  // Add reverse edge for undirected graph
    }

    // Find the shortest path and write the result to the output file
    dijkstraListeAdj(n, start, end, adj, outFile);

    // Close the input and output files
    inFile.close();
    outFile.close();

    return 0; // Return success
}
