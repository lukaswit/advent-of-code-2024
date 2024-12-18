#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include <ctype.h>
#include <algorithm>
#include <map>

//************************************************************************** */
// Function declarations
//************************************************************************** */
std::vector<std::string> customSplit(std::string str, std::string sep);
std::vector<std::string> readInput(std::string fileName);
int solvePuzzle(std::vector<std::string>);

//************************************************************************** */
// Main
//************************************************************************** */
int main() {
    // Read the puzzle input
    std::string fileName {"puzzle_input_01.txt"};
    std::vector<std::string> puzzleInput {readInput(fileName)};
    
    // Other declarations
    int solution;

    // Solve puzzle
    solution = solvePuzzle(puzzleInput);
    std::cout << "The solution is: " << solution << "\n";

    return 0;
}

//************************************************************************** */
// SOLVING THE PUZZLE
//************************************************************************** */
int solvePuzzle(std::vector<std::string> puzzleInput) {
    // Convert input to two lists of integers
    // First, get the lenght of the puzzle input
    size_t nLines {puzzleInput.size()};
    std::vector<std::string> tmp;
    // init lists
    int list_0[nLines] = {0};
    int list_1[nLines] = {0};
    int diff[nLines] = {0};
    int score {0};
    
    // converst strings to integers and populate the lists
    for (int ii=0; ii<nLines; ii++){
        tmp = customSplit(puzzleInput[ii], " ");
        // convert strings to integers
        list_0[ii] = std::stoi(tmp[0]);
        list_1[ii] = std::stoi(tmp[1]);
    }

    // Sort the lists
    std::sort(list_0, list_0 + nLines);
    std::sort(list_1, list_1 + nLines);

    // Count how often each element if list_1 occurs
    std::map<int, int> counts;
    for (int ii=0; ii<nLines; ii++) {
        counts[list_1[ii]]++;
    }
    for (auto const &ent1 : counts) {
        std::cout << ent1.first << ":" << ent1.second << "\n";
    }

    // determine the final score
    
    for (int ii=0; ii<nLines; ii++) {
        
        if (auto searchResult = counts.find(list_0[ii]); searchResult != counts.end()) {
            score = score + list_0[ii] * counts[list_0[ii]];
        }

    }
    
    return score;
}

/* ========================================================================= */
//
// HELPER FUNCTIONS
//
/* ========================================================================= */

//************************************************************************** */
// Read the contents of a text file and return the lines as a vector of strings
//************************************************************************** */
std::vector<std::string> readInput(std::string fileName){
    // Declarations
    std::ifstream fileStream{fileName};
    std::vector<std::string> puzzleInput;
    std::string line;
    
    // Read input from file
    while (std::getline(fileStream, line)){
        puzzleInput.push_back(line);
    }
    
    // Return file contents as vector of strings
    return puzzleInput;
}

//************************************************************************** */
// Function for splitting a string
//************************************************************************** */
std::vector<std::string> customSplit(std::string myStr, std::string sep) {
    // variables
    std::vector<std::string> subStrings;
    std::string currentStr;
    int pos;
    
    // main loop
    while (myStr.find(sep) != std::string::npos) {
        pos = myStr.find(sep);
        currentStr = myStr.substr(0, pos);
        if (currentStr.length() > 0) {
            subStrings.push_back(myStr.substr(0, pos));
        }
        myStr.erase(0, pos + sep.length());
        // std::cout << "str after erase: " << str << std::endl;
    }

    // Add remaining string to vector
    if (myStr.length() > 0) {
        subStrings.push_back(myStr);
    }

    return subStrings;
}