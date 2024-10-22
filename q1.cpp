//
// Created by matthieu on 11/10/24.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

void print_vector_subseq(const vector<vector<int>>& vec) {
    cout << "Éléments du vecteur : ";
    for (const auto& subvec : vec) {
        for (int elem : subvec) {
            cout << elem << " ";
        }
        cout << "| "; // Separator between sub-vectors
    }
    cout << endl;
}

void longest_increasing_subsequence(vector<int>& A) {
    vector<vector<int>> subsequences;
    vector<vector<int>> indices;

    for (int i = A.size() - 1; i >= 0; i--) {
        int value = A[i];
        int best_subseq = -1;
        int max_length = 0;

        // Cross existing subsequences
        for (int j = 0; j < subsequences.size(); j++) {

            if (value < subsequences[j][0]) {
                if (subsequences[j].size() > max_length) {
                    best_subseq = j;
                    max_length = subsequences[j].size();
                }
                // If same size, we choose the more recent one
                else if (subsequences[j].size() == max_length && j > best_subseq) {
                    best_subseq = j;
                }
            }
        }

        if (best_subseq != -1) {
            subsequences[best_subseq].insert(subsequences[best_subseq].begin(), value);
            indices[best_subseq].insert(indices[best_subseq].begin(), i);
        } else {
            subsequences.push_back({value});
            indices.push_back({i});
        }
        //print_vector_subseq(subsequences);
    }

    vector<int> longest_subseq;
    vector<int> longest_indices;
    for (int k = 0; k < subsequences.size(); ++k) {
        if (subsequences[k].size() > longest_subseq.size()) {
            longest_subseq = subsequences[k];
            longest_indices = indices[k];
        }
    }


    ofstream output_file("OUTMONOSEQ.txt");
    if (!output_file) {
        cerr << "Erreur lors de l'ouverture du fichier !" << endl;
        return;
    }

    output_file << longest_subseq.size() << endl;

    for (size_t i = 0; i < longest_subseq.size(); ++i) {
        output_file << "a[" << longest_indices[i] + 1 << "] = " << longest_subseq[i] << endl;  // +1 pour l'indice 1-based
    }

    output_file.close();
}

void generaate_random_inpput_seq(const int N)
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

int main() {

    //generaate_random_inpput_seq(10);

    ifstream infile("../INPMONOSEQ.txt");
    if (!infile) {
        cerr << "Error opening input file INPMONOSEQ.txt" << endl;
        return 1;
    }

    int n;
    infile >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        infile >> A[i];
    }

    longest_increasing_subsequence(A);

    infile.close();

    return 0;
}