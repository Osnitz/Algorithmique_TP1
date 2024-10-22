//
// Created by matthieu on 17/10/24.
//
// Function to find the Longest Increasing Subsequence (LIS) using dynamic programming with print at each step

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void longest_increasing_subsequence_with_print(const vector<int>& A, vector<int>& lis, vector<int>& indexs)
{
    int n = A.size();
    vector<int> a(n, 1); // `a[i]`: Length of the longest increasing subsequence ending at index i
    vector<int> parent(n, -1); // Array to track the indices of elements in the subsequence

    // Build the `a[]` array
    for (int i = n - 2; i >= 0; --i)
    {
        cout << "Considering element A[" << i << "] = " << A[i] << endl;
        for (int j = i + 1; j < n; ++j)
        {
            if (A[j] > A[i] && a[i] < 1 + a[j])
            {
                a[i] = 1 + a[j];
                parent[i] = j; // Keep track of index `j` to reconstruct the sequence
                cout << "  A[" << j << "] = " << A[j] << " is greater than A[" << i << "] = " << A[i]
                     << ", updating a[" << i << "] = " << a[i] << " and parent[" << i << "] = " << j << endl;
            }
        }
        cout << "  a[" << i << "] after processing: " << a[i] << ", parent[" << i << "] = " << parent[i] << endl;
    }

    // Find the index of the longest increasing subsequence
    int max_len = 0, start_index = 0;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] > max_len)
        {
            max_len = a[i];
            start_index = i;
        }
    }
    cout << "Max length of LIS: " << max_len << " starting at index " << start_index << endl;

    // Reconstruct the subsequence starting from `start_index`
    cout << "Reconstructing LIS:" << endl;
    while (start_index != -1)
    {
        lis.push_back(A[start_index]); // Add the element to the sequence
        indexs.push_back(start_index + 1); // 1-based indexing for output
        cout << "  Adding A[" << start_index << "] = " << A[start_index] << " to LIS." << endl;
        start_index = parent[start_index];
    }
}


int main()
{
    ifstream infile("../INPMONOSEQ.txt");
    if (!infile)
    {
        cerr << "Error opening input file INPMONOSEQ.txt" << endl;
        return 1;
    }

    int n;
    infile >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i)
    {
        infile >> A[i];
    }
    infile.close();

    vector<int> lis, indexs;
    longest_increasing_subsequence_with_print(A, lis, indexs);

    ofstream output_file("../OUTMONOSEQ.txt");
    if (!output_file)
    {
        cerr << "Error opening output file OUTMONOSEQ.txt" << endl;
        return 1;
    }

    // Write the result to the OUTMONOSEQ.TXT file
    output_file << lis.size() << endl;
    for (size_t i = 0; i < lis.size(); ++i)
    {
        output_file << "a[" << indexs[i] << "] = " << lis[i] << endl;
    }

    output_file.close();

    // Print the result to the console
    cout << "The length of the longest increasing subsequence is: " << lis.size() << endl;
    cout << "The longest increasing subsequence is: ";
    for (int num : lis)
    {
        cout << num << " ";
    }
    cout << endl;

    cout << "The indexs of this subsequence are: ";
    for (size_t i = 0; i < lis.size(); ++i)
    {
        cout << "A[" << indexs[i] << "] ";
    }
    cout << endl;

    return 0;
}
