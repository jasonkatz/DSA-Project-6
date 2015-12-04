/*
*****************************************
Jason Katz
ECE-165 Project 4: Dynamic Programming

Solution to string merging problem

File: main.cpp
*****************************************
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

bool checkMerge(string, string, string *);

int main() {

	// Prompt for filenames
	string inputFileName, outputFileName;
	cout << "Enter the name of an input file: ";
	cin >> inputFileName;
	cout << "Enter the name of an output file: ";
	cin >> outputFileName;

	ifstream inFile(inputFileName);
	ofstream outFile(outputFileName);
	string s1, s2, s;
	while (getline(inFile, s1) && getline(inFile, s2) && getline(inFile, s)) {
		// Write appropriate output based on result of checkMerge
		if (checkMerge(s1, s2, &s)) {
			outFile << s << endl;
		} else {
			outFile << "*** NOT A MERGE ***" << endl;
		}
	}

	inFile.close();
	outFile.close();

	return 0;
}

char M[1001][1001]; // Make 1001x1001 since that is the maximum size
bool checkMerge(string s1, string s2, string * s) {
	if (s1.length() + s2.length() != s->length()) {
		return false;
	}

	// Reset M
	for (int n = 0; n < 1001; ++n) {
		for (int m = 0; m < 1001; ++m) {
			M[n][m] = 0;
		}
	}
	M[0][0] = 1;

	// Fill out M
	char s1Char = 'f', s2Char = 's';
	for (int j = 0; (unsigned) j <= s2.length(); ++j) {
		for (int i = 0; (unsigned) i <= s1.length(); ++i) {
			if (!M[i][j]) {
				continue;
			}
			if (s1[i] == (*s)[i + j] && !M[i + 1][j]) {
				M[i + 1][j] = s1Char;
			}
			if (s2[j] == (*s)[i + j] && !M[i][j + 1]) {
				M[i][j + 1] = s2Char;
			}
		}
	}

	// Walk up matrix to see if s is a valid merge
	int i = s1.length(), j = s2.length(), index;
	while (i + j > 0) {
		// Check failed case
		if (!M[i][j]) {
			return false;
		}

		index = i + j - 1;
		if (M[i][j] == s1Char) {
			(*s)[index] -= 32; // Convert to uppercase if from s1
		}

		// Prioritize first string
		if (j > 0 && M[i][j - 1]) {
			--j;
		} else if (i > 0 && M[i - 1][j]) {
			--i;
		}
	}

	return true;
}