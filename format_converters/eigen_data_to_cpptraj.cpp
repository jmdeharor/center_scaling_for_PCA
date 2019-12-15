#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " [eigenvalues] [eigenvectors] [means]" << endl;
    }


    ifstream inputFile(argv[1]);
    auto advancePos = [&](int numPos){
        for (int j = 0; j < numPos; ++j) {
            double eigenvector;
            inputFile >> eigenvector;
        }
    };

    vector<double> eigenvalues(10);
    vector<vector<double>> eigenvectors(10);
    vector<double> means(2028);

    advancePos(2018);
    for (int i = 0; i < 10; ++i) {
        inputFile >> eigenvalues[10 - i - 1];
    }

    inputFile.close();
    inputFile.open(argv[2]);

    advancePos(2028*2018);
    for (int i = 0; i < 10; ++i) {
        vector<double>& vectors = eigenvectors[10 - i - 1];
        vectors.resize(2028);
        for (int j = 0; j < 2028; ++j) {
            inputFile >> vectors[j];
        }
    }

    inputFile.close();
    inputFile.open(argv[3]);

    for (int i = 0; i < 2028; ++i) {
        inputFile >> means[i];
    }

    inputFile.close();

    ofstream outputFile("out.dat");

    outputFile << " Eigenvector file: COVAR nmodes 10 width 11" << endl << " 2028 2028" << endl;

    for (int i = 0; i < 2028; i += 7) {
        for (int j = 0; j < 5; ++j) {
            outputFile << std::fixed << setprecision(5) << setw(11) << means[i+j];
        }
        if (i+7 < 2028) {
            for (int j = 5; j < 7; ++j) {
                outputFile << std::fixed << setprecision(5) << setw(11) << means[i+j];
            }
        }
        outputFile << endl;
    }

    for (int i = 0; i < 10; ++i) {
        outputFile << " ****" << endl;
        outputFile << setw(5) << i+1 << setw(12) << eigenvalues[i] << endl;
        for (int j = 0; j < 2028; j += 7) {
            for (int k = 0; k < 5; ++k) {
                outputFile << std::fixed << setprecision(5) << setw(11) << eigenvectors[i][j+k];
            }
            if (j+7 < 2028) {
                for (int k = 5; k < 7; ++k) {
                    outputFile << std::fixed << setprecision(5) << setw(11) << eigenvectors[i][j+k];
                }
            }
            outputFile << endl;
        }
    }
}
