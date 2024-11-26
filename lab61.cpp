#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find LCS between two sequences
vector<string> findLCS(const vector<string>& seq1, const vector<string>& seq2) {
    int m = seq1.size();
    int n = seq2.size();
    // 2D DP array to store the LCS at each step
    vector<vector<vector<string>>> dp(m + 1, vector<vector<string>>(n + 1));

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (seq1[i - 1] == seq2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                dp[i][j].push_back(seq1[i - 1]);
            } else {
                dp[i][j] = (dp[i - 1][j].size() > dp[i][j - 1].size()) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    return dp[m][n];
}

// Function to find the longest common sequence across multiple student grade lists
vector<string> longestCommonSequence(const vector<vector<string>>& grades) {
    vector<string> common_sequence = grades[0];
    for (size_t i = 1; i < grades.size(); i++) {
        common_sequence = findLCS(common_sequence, grades[i]);
    }
    return common_sequence;
}

// Helper function to print the LCS result
void printResult(const vector<string>& result) {
    if (result.empty()) {
        cout << "No common sequence found.\n";
    } else {
        cout << "Longest Common Sequence: ";
        for (const string& grade : result) {
            cout << grade << " ";
        }
        cout << endl;
    }
}

// Main function with 10 test cases
int main() {
    vector<vector<vector<string>>> testCases = {
        // Positive Test Cases
        {{"AA", "AB", "BB", "CC", "DD"}, {"AA", "BB", "CC", "DD", "EE"}, {"AA", "BB", "CC", "FF", "DD"}}, // Expected: AA BB CC DD
        {{"AA", "CC", "DD", "EE", "FF"}, {"CC", "DD", "FF", "GG"}, {"BB", "CC", "DD", "FF", "HH"}},         // Expected: CC DD FF
        {{"AA", "BB", "CC"}, {"BB", "CC", "DD"}, {"BB", "CC", "EE"}},                                      // Expected: BB CC
        {{"AA", "BB", "CC", "DD"}, {"AA", "DD", "EE", "FF"}, {"","","",""}},                    // Expected: AA DD
        {{"AA", "AB", "AC", "AD"}, {"AB", "AC", "AD", "AE"}, {"AA", "AC", "AD", "AF"}},                    // Expected: AC AD

        // Negative Test Cases
        {{"AA", "BB", "CC", "DD"}, {"EE", "FF", "GG", "HH"}, {"II", "JJ", "KK", "LL"}},                    // Expected: No common sequence
        {{"AA", "BB", "CC"}, {"DD", "EE", "FF"}, {"GG", "HH", "II"}},                                      // Expected: No common sequence
        {{"AA", "BB", "CC", "DD"}, {"BB", "CC", "EE", "FF"}, {"GG", "HH", "II", "JJ"}},                    // Expected: No common sequence
        {{"AA", "BB", "CC"}, {"CC", "DD", "EE"}, {"FF", "GG", "HH"}},                                      // Expected: No common sequence
        {{"AA", "BB", "CC", "DD"}, {"EE", "FF", "GG", "HH"}, {"II", "JJ", "KK", "LL"}, {"MM", "NN", "OO", "PP"}} // Expected: No common sequence
    };

    // Running each test case
    for (size_t i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i + 1 << ":\n";
        vector<string> result = longestCommonSequence(testCases[i]);
        printResult(result);
        cout << "---------------------------\n";
    }

    // Test case: 20 students, each with 10 grades
    vector<vector<string>> grades = {
    {"AA", "BB", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "NN"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "OO", "PP"},
    {"AA", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "QQ"},
    {"BB", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "RR"},
    {"CC", "DD", "EE", "FF", "GG", "HH", "JJ", "LL", "MM", "SS"},
    {"AA", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "TT"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "UU", "VV"},
    {"AA", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "WW"},
    {"BB", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "XX"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "YY", "ZZ"},
    {"AA", "BB", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "AA", "BB"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "CC", "DD"},
    {"AA", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "EE"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "FF", "GG"},
    {"BB", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "HH"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "II", "JJ"},
    {"AA", "CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "KK"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "LL", "MM"},
    {"CC", "DD", "FF", "GG", "HH", "JJ", "LL", "MM", "MM", "NN"}
};

    cout << "Finding the Longest Common Sequence among 20 students:\n";
    vector<string> result = longestCommonSequence(grades);
    printResult(result);

    return 0;
}
