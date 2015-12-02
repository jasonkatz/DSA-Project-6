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

using namespace std;

string checkMerge(string, string, string);

int main() {

	// Prompt for filenames
	string inputFileName, outputFileName;
	cout << "Enter the name of an input file: ";
	cin >> inputFileName;
	cout << "Enter the name of an output file: ";
	cin >> outputFileName;

	ifstream inFile(inputFileName);
	string line;
	string s1, s2, s;
	string result;
	while (getline(inFile, line)) {
		// Get the three strings
		s1 = line;
		getline(inFile, line);
		s2 = line;
		getline(inFile, line);
		s = line;

		result = checkMerge(s1, s2, s);
	}

	inFile.close();

	system("pause");
	return 0;
}

short M[1000][1000]; // Make 1000x1000 since that is the maximum size
string checkMerge(string s1, string s2, string s) {
	string result = "";

	// Fill out M
	for (int n = 0; n < 1000; ++n) {
		for (int m = 0; m < 1000; ++m) {
			M[n][m] = n + m;
		}
	}

	// Use M to check if s is a proper merge of s1 and s2
	int i = 0, j = 0, index;
	while ((unsigned int) i <= s1.length() && (unsigned int) j <= s2.length()) {
		index = M[i][j];

		// Check successful case
		if (index == s.length() - 1) {
			// Add last character
			if (s[index] == s1[i]) {
				result += s1[i] - 32; // Make uppercase
			} else if (s[index] == s2[j]) {
				result += s2[j];
			}
			return result;
		}

		// If they are the same, increase the index that is lower
		if (s[index] == s1[i] && s[index] == s2[j]) {
			if (i > j) {
				result += s2[j++];
			} else {
				result += s1[i++] - 32; // Make uppercase
			}
			continue;
		}

		// Otherwise, check each individual index
		if (s[index] == s1[i]) {
			result += s1[i++] - 32; // Make uppercase
		} else if (s[index] == s2[j]) {
			result += s2[j++];
		} else {
			// Check edge case (s1 = aabc, s2 = aabd, s = aaaabdbc)
			++j;
			--i;
			if (i >= 0 && s[index] == s1[i]) {
				result.pop_back();
				result += s1[i++] - 32; // Make uppercase
			} else if ((unsigned int) j < s2.length() && s[index] == s2[j]) {
				result.pop_back();
				result += s2[j++];
			} else {
				return "";
			}
		}
	}
	return "";
}