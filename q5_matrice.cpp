#include <iostream>
#include <vector>
#include <climits>
#include <fstream>  // For file input/output
#include <algorithm> // For reverse function

using namespace std;

const int INF = INT_MAX;

// Dijkstra's algorithm to find the shortest path in a graph represented as an adjacency matrix
void dijkstraMatriceAdj(int n, int start, int end, const vector<vector<int>>& adj, ofstream& outFile) {
    vector<int> dist(n, INF);  // Stores the minimum distance from the start vertex
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

        if (dist[u] == INF) break;  // If the smallest distance is infinity, we stop

        visited[u] = true;  // Mark the vertex as visited

        // Update distances of neighboring vertices
        for (int v = 0; v < n; v++) {
            if (adj[u][v] != 0 && !visited[v]) {
                int alt = dist[u] + adj[u][v];  // New potential distance via u
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;  // Store the previous vertex to reconstruct the path
                }
            }
        }
    }

    // Write results to the output file
    if (dist[end] == INF) {
        outFile << "No path found between " << start + 1 << " and " << end + 1 << endl; // +1 for human-readable format
    } else {
        outFile << dist[end] << endl;  // Shortest distance

        // Reconstruct the path
        vector<int> path;
        for (int at = end; at != -1; at = prev[at]) {
            path.push_back(at + 1);  // +1 for human-readable format
        }
        reverse(path.begin(), path.end()); // Reverse the path to get it from start to end

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

    vector<vector<int>> adj(n, vector<int>(n, 0));  // Initialize adjacency matrix to 0

    // Read edges and fill the adjacency matrix
    for (int i = 0; i < m; i++) {
        int u, v, w;
        inFile >> u >> v >> w; // Read edge
        u--; v--;  // Convert to zero-based indexing
        adj[u][v] = w;  // Set weight for edge u-v
        adj[v][u] = w;  // Set weight for edge v-u (undirected graph)
    }

    // Find the shortest path and write the result to the output file
    dijkstraMatriceAdj(n, start, end, adj, outFile);

    // Close the input and output files
    inFile.close();
    outFile.close();

    return 0; // Return success
}
