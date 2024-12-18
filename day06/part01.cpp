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
int walkGuard(int**, int*, int*, int*, int*, int, int);

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
    
    // Parse the puzzle input
    size_t nRows = 0;
    size_t nCols = 0;
    int posX = 0;
    int posY = 0;
    int dirX = 0;
    int dirY = -1;

    // Get the size of the puzzle input
    nRows = puzzleInput.size();
    nCols = puzzleInput[0].size();

    // Init map and populate it
    int** map = new int*[nRows];
    int*  mapMem = new int[nRows * nCols];
    for (int ii=0; ii<nRows; ii++) {
        map[ii] = mapMem + nCols*ii;
    }
    
    for (int ii=0; ii<nRows; ii++) {
        for (int jj=0; jj<nCols; jj++) {
            // Find the obstacles
            if (puzzleInput[ii].substr(jj, 1) == "#") {map[ii][jj] = 1;}
            else {map[ii][jj] = 0;}
            // Find the initial position
            if (puzzleInput[ii].substr(jj, 1) == "^") {
                posX = jj;
                posY = ii;
                map[ii][jj] = -1;
            }   
        }
    }

    std::cout << "Initial position it: (" << posX << "," << posY << ")\n";
    int onMap = 1;
    while (true) {
        // Let the guard walk
        std::cout << "The current direction is: (" << dirX << "," << dirY << ")\n";
        std::cout << "The current position is: (" << posX << "," << posY << ")\n";
        onMap = walkGuard(map, &posX, &posY, &dirX, &dirY, nRows, nCols);
        if (!onMap) {break;}
    }

    int counter = 0;
    // Count the number of visited positions
    for (int ii=0; ii<nRows; ii++) {
        for (int jj=0; jj<nCols; jj++) {
            if (map[ii][jj] == -1) {counter++;}
        }
    }
    
    return counter;
}

int walkGuard(int** map, int* posX, int* posY, int* dirX, int* dirY, int nRows, int nCols) {
    // Walks the guard into the current direction until encoutering an obstacle or leaving the area
    int nSteps = 1;
    int ii;
    int jj;
    int lastX;
    int lastY;
    int onMap = 1;
    
    while (true) {
        // Generate new positions
        ii = (*posY + nSteps * (*dirY));
        jj = (*posX + nSteps * (*dirX));
        
        // Check if the next position is off the map
        if (ii < 0 || ii >= nRows) {
            onMap = 0;
            break;
        }
        if (jj < 0 || jj >= nCols) {
            onMap = 0;
            break;
        }
        
        // Check if the next position is an obstacle
        if (map[ii][jj] == 1) {
            std::cout << "Obstacle found!\n";
            // change direction
            if (*dirY == -1) {
                *dirY = 0;
                *dirX = 1;
            } else if (*dirY == 1) {
                *dirY = 0;
                *dirX = -1;
            } else if (*dirX == 1) {
                *dirY = 1;
                *dirX = 0;
            } else if (*dirX == -1) {
                *dirY = -1;
                *dirX = 0;
            }
            onMap = 1;
            break;
        }

        // Mark next position as visited
        map[ii][jj] = -1;
        lastX = jj;
        lastY = ii;
        nSteps++;
    }
    *posY = lastY;
    *posX = lastX;
    return onMap;
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