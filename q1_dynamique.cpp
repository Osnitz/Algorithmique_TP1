#include <iostream>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

// Function to find the Longest Increasing Subsequence (LIS) using dynamic programming
void longest_increasing_subsequence(const vector<int>& A, vector<int>& lis, vector<int>& indexs)
{
    int n = A.size();
    vector a(n, 1); // `a[i]`: Length of the longest increasing subsequence ending at index i
    vector parent(n, -1); // Array to track the indices of elements in the subsequence

    // Build the `a[]` array from the end of the original sequence to the beginning
    for (int i = n - 2; i >= 0; --i)
    {
        // Start from the second-last element down to the begining
        for (int j = i + 1; j < n; ++j)
        {
            if (A[j] > A[i] && a[i] < 1 + a[j]) // If A[j] > A[i] it means that the sub-sequence can be extended
            {
                a[i] = 1 + a[j];
                parent[i] = j; // Keep track of index `j` to reconstruct the sequence
            }
        }
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

    // Reconstruct the subsequence starting from `start_index`
    while (start_index != -1)
    {
        lis.push_back(A[start_index]); // Add the element to the sequence
        indexs.push_back(start_index + 1); // 1-based indexing for output
        start_index = parent[start_index];
    }
}

void generate_random_inpput_seq(const int N)
{
    vector<int> values(N);

    // Create a random number generator
    random_device rd;  // Seed generator
    mt19937 gen(rd()); // Mersenne Twister, pseudo-random number generator
    uniform_int_distribution<> distrib(-10000, 10000);  // Uniform distribution between -10000 and 10000

    // Fill the vector with random values
    for (int i = 0; i < N; ++i) {
        values[i] = distrib(gen);
    }

    ofstream output_file("INPMONOSEQ.txt");
    if (!output_file) {
        cerr << "Error opening output file!" << endl;
        throw;
    }

    // Write the values to the file on the same line
    output_file<<N<<endl;
    for (int i = 0; i < N; ++i) {
        output_file << values[i];
        if (i < N - 1) {
            output_file << " ";  // Add a space between values
        }
    }
    output_file.close();
}

int main()
{
    //generate_random_inpput_seq(10);
    ifstream infile("INPMONOSEQ.txt");
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
    longest_increasing_subsequence(A, lis, indexs);

    ofstream output_file("OUTMONOSEQ.txt");
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
