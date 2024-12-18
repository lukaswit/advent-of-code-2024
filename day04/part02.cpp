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
int checkXMAS(std::vector<std::string>, int, int);

//************************************************************************** */
// Main
//************************************************************************** */
int main() {
    // debug flag
    bool debug = true;

    // Read the puzzle input
    std::string fileName {"puzzle_input.txt"};
    std::vector<std::string> puzzleInput {readInput(fileName)};
    
    if (debug) {
        for (int ii=0; ii<puzzleInput.size(); ii++) {
            std::cout << puzzleInput[ii] << "\n";
        }
    }

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
    size_t nRows = puzzleInput.size();
    size_t nCols = puzzleInput[0].length();
    std::cout << "Number of rows: " << nRows << "\n";
    std::cout << "Number of columns: " << nCols << "\n";

    std::string currentLine;
    int checkResult;
    int xmasCounter = 0;
    int nn;

    // OUTER LOOP
    for (int ii = 0; ii < nRows; ii++) {
        currentLine = puzzleInput[ii];
        // INNER LOOP
        for (int jj = 0; jj < nCols; jj++) {
            if (currentLine.substr(jj, 1) == "A") {
                nn = checkXMAS(puzzleInput, ii, jj);
                xmasCounter = xmasCounter + nn;
            }
        }
    }
        
    return xmasCounter;
}

int checkXMAS(std::vector<std::string> puzzleInput, int iRow, int iCol) {
    int deltaCol[2] = { 1, 1};
    int deltaRow[2] = {-1, 1};
    size_t nRows = puzzleInput.size();
    size_t nCols = puzzleInput[0].length();
    std::string charSequ = "";
    int ii;
    int jj;
    bool iValid;
    bool jValid;
    bool xmas;
    int counter = 0;

    for (int dirIdx = 0; dirIdx < 2; dirIdx++) {
        xmas = false;
        charSequ = "";
        for (int nn = -1; nn < 2; nn++) {
            // create current indices
            ii = iRow + deltaRow[dirIdx] * nn;
            jj = iCol + deltaCol[dirIdx] * nn;
            
            // Check index validity
            if (ii >= 0 and ii < nRows) {iValid = true;} else {iValid = false;}
            if (jj >= 0 and jj < nCols) {jValid = true;} else {jValid = false;}

            if (iValid and jValid) {
                charSequ += puzzleInput[ii].substr(jj, 1);
            } else {break;}
        }
        
        if (charSequ == "MAS" or charSequ == "SAM") {
            xmas = true;
        } else {
            xmas = false;
            break;
        }
    }
    
    if (xmas) {
        return 1;
    } else {
        return 0;
    }
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