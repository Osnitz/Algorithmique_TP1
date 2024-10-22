#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void max_subsequence_divisible_by_k(const vector<int>& A, int k) {
    int n = A.size(); // Get the size of the input vector A
    vector dp(k, -1); // `dp[r]`: max length of subsequence for sum % k == r
    vector<vector<int>> track(k); // `track[r]`: subsequence for remainder `r`
    vector<vector<int>> indices(k); // `indices[r]`: indices of the subsequence for remainder `r`

    dp[0] = 0; // A sum of 0 with 0 elements is divisible by `k`

    // Iterate over each element in A
    for (int i = 0; i < n; ++i) {
        // Create temporary arrays to store updated results
        vector<int> next_dp = dp;
        vector<vector<int>> next_track = track;
        vector<vector<int>> next_indices = indices;

        // Update `dp` for each possible remainder
        for (int r = 0; r < k; ++r) {
            if (dp[r] != -1) { // Check if `dp[r]` is valid
                int new_r = (r + A[i]) % k; // Calculate new remainder
                // Check if we can improve the subsequence length for this new remainder
                if (next_dp[new_r] < dp[r] + 1) {
                    next_dp[new_r] = dp[r] + 1; // Update max length for new remainder
                    next_track[new_r] = track[r]; // Copy the previous subsequence
                    next_track[new_r].push_back(A[i]); // Add the current element
                    next_indices[new_r] = indices[r]; // Copy the previous indices
                    next_indices[new_r].push_back(i + 1); // Add the current index (1-based)
                }
            }
        }

        // Update `dp`, `track`, and `indices` with the new results
        dp = next_dp;
        track = next_track;
        indices = next_indices;
    }

    // Retrieve the subsequence with remainder `0` (sum divisible by `k`)
    vector<int> result = track[0]; // Get the subsequence for remainder 0
    vector<int> result_indices = indices[0]; // Get the corresponding indices
    int max_length = result.size(); // Get the length of the subsequence
    int sum = 0; // Initialize the sum variable
    for (int num : result) {
        sum += num; // Calculate the sum of the subsequence
    }

    // Write the output to the file `OUTDIVSEQ.txt`
    ofstream outfile("../OUTDIVSEQ.txt");
    if (!outfile) {
        cerr << "Error opening output file OUTDIVSEQ.txt" << endl; // Error handling
        return;
    }

    // Output the results
    outfile << max_length << endl; // Output the length of the subsequence
    for (size_t i = 0; i < result.size(); ++i) {
        outfile << "a[" << result_indices[i] << "] = " << result[i] << endl; // Output the format "a[index] = value"
    }
    outfile << "Sum = " << sum << endl; // Output the sum of the subsequence

    outfile.close(); // Close the output file
}

int main() {
    // Open the input file `INPDIVSEQ.txt`
    ifstream infile("../INPDIVSEQ.txt");
    if (!infile) {
        cerr << "Error opening input file INPDIVSEQ.txt" << endl; // Error handling
        return 1;
    }

    int n, k; // Declare variables for the size of the sequence and the divisor
    infile >> n >> k; // Read n and k from the input file
    vector<int> A(n); // Create a vector to store the input sequence
    for (int i = 0; i < n; ++i) {
        infile >> A[i]; // Read the elements of the sequence
    }

    infile.close(); // Close the input file

    // Call the function to solve the problem
    max_subsequence_divisible_by_k(A, k);

    return 0; // Return 0 to indicate successful completion
}
