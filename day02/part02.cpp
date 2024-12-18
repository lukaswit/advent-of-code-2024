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
    std::string fileName {"puzzle_input.txt"};
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
    
    std::vector<std::vector<int>> levels;
    size_t nLines {puzzleInput.size()};
    
    //for (int ii=0; ii<nLines; ii++) {
    //    std::cout << "Line " << ii << ": " << puzzleInput[ii] << "\n";
    //}

    
    for (int ii=0; ii<nLines; ii++) {
        std::vector<int> currentLevels;
        std::vector<std::string> tmp;
        tmp = customSplit(puzzleInput[ii], " ");
        size_t nn {tmp.size()};
        for (int jj=0; jj<nn; jj++) {            
            currentLevels.push_back(std::stoi(tmp[jj]));
        }
        levels.push_back(currentLevels);        
    }

    // Check safety rules
    int safeLevels = 0;
    int oldDiff = 0;
    int newDiff;
    bool isSafe;


    for (int ii=0; ii<nLines; ii++) {
        size_t nLevels = levels[ii].size();
        isSafe = true;

        std::cout << "Line " << ii << ": ";
        for (int jj=0; jj<nLevels; jj++) {
            std::cout << levels[ii][jj] << "::";
        }
        std::cout << "\n";



        for (int jj=0; jj<nLevels - 1; jj++) {
            newDiff = levels[ii][jj + 1] - levels[ii][jj];
            if (abs(newDiff) > 3) {isSafe = false;}
            if (jj > 0) {
                if (newDiff * oldDiff <= 0) {
                    isSafe = false;
                }    
            }
            oldDiff = newDiff;
        }

        // try once more, but now with the element at popIdx removed
        if (!isSafe) { // RETRY
            std::cout << "Retry!\n";
            for (int jj=0; jj<nLevels; jj++) {
                std::vector<int> newLevels = levels[ii];
                newLevels.erase(newLevels.begin() + jj);

                for (int kk=0; kk<newLevels.size(); kk++) {
                    std::cout << newLevels[kk] << "::";
                }
                std::cout << "\n";

                isSafe = true;
                for (int kk=0; kk<newLevels.size() - 1; kk++) {
                    newDiff = newLevels[kk + 1] - newLevels[kk];
                    if (abs(newDiff) > 3) {
                        isSafe = false;
                    }
                    if (kk > 0) {
                        if (newDiff * oldDiff <= 0) {
                            isSafe = false;
                        }    
                    }
                    oldDiff = newDiff;
                }
                if (isSafe) {
                    break;
                }
            }
        }


        if (isSafe) {
            safeLevels++;
            std::cout << "Safe!\n";
        } else {
            std::cout << "NOT safe!\n";
        }
    }

    return safeLevels;
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