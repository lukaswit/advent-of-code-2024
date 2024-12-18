#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include <ctype.h>
#include <algorithm>

std::vector<std::string> customSplit(std::string str, std::string sep);
std::vector<std::string> readInput(std::string fileName);
int solvePuzzle(std::vector<std::string>);


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

int main(){
    std::string fileName {"puzzle_input.txt"};
    std::vector<std::string> puzzleInput {readInput(fileName)};
    int solution;

    // process the input
    bool debug {false};

    if (debug) {
        for (int ii=0; ii<puzzleInput.size(); ii++) {
            std::cout << puzzleInput[ii] << "\n";
        }
    }  
    
    solution = solvePuzzle(puzzleInput);
    std::cout << "The solution is: " << solution << "\n";
    return 0;
}

int solvePuzzle(std::vector<std::string> puzzleInput){
    // Convert input to two lists of integers
    // First, get the lenght of the puzzle input
    size_t nLines {puzzleInput.size()};
    std::vector<std::string> tmp;
    // init lists
    int list_0[nLines] = {0};
    int list_1[nLines] = {0};
    int diff[nLines] = {0};
    int diffsum {0};
    
    // converst strings to integers and populate the lists
    for (int ii=0; ii<nLines; ii++){
        tmp = customSplit(puzzleInput[ii], " ");
        // convert strings to integers
        list_0[ii] = std::stoi(tmp[0]);
        list_1[ii] = std::stoi(tmp[1]);
    }

    // Sort
    std::sort(list_0, list_0 + nLines);
    std::sort(list_1, list_1 + nLines);

    // Print the lists
    for (int ii=0; ii<nLines; ii++) {
        std::cout << list_0[ii] << "::" << list_1[ii] << "\n";
    }

    // Compute the sum of differences - the puzzle solution
    for (int ii=0; ii<nLines; ii++) {
        diff[ii] = abs(list_0[ii] - list_1[ii]);
        diffsum = diffsum + diff[ii];
    }
      
    return diffsum;
}

// ****************************************************************************
// Function for splitting a string
// ****************************************************************************
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