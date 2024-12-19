#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include <ctype.h>
#include <algorithm>
#include <map>
#include <iterator>

//************************************************************************** */
// Function declarations
//************************************************************************** */
std::vector<std::string> customSplit(std::string str, std::string sep);
std::vector<std::string> readInput(std::string fileName);
int solvePuzzle(std::vector<std::string>);
int walkGuard(int**, int*, int*, int*, int*, int, int);
bool stateHasOccured(std::vector<std::vector<int>>*, std::vector<int>, int);
void printMap(int**, int, int);

//************************************************************************** */
// Main
//************************************************************************** */
int main() {
    // debug flag
    bool debug = false;

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
    int initPosX = 0;
    int initPosY = 0;
    

    // Get the size of the puzzle input
    nRows = puzzleInput.size();
    nCols = puzzleInput[0].size();

    // Init map and populate it
    int** map = new int*[nRows];
    int*  __map = new int[nRows * nCols];
    for (int ii=0; ii<nRows; ii++) {
        map[ii] = __map + nCols*ii;
    }

    int** mapCopy = new int*[nRows];
    int*  __mapCopy = new int[nRows * nCols];
    for (int ii=0; ii<nRows; ii++) {
        mapCopy[ii] = __mapCopy + nCols*ii;
    }

    for (int ii=0; ii<nRows; ii++) {
        for (int jj=0; jj<nCols; jj++) {
            // Find the obstacles
            if (puzzleInput[ii].substr(jj, 1) == "#") {map[ii][jj] = 1;}
            else {map[ii][jj] = 0;}
            // Find the initial position
            if (puzzleInput[ii].substr(jj, 1) == "^") {
                initPosX = jj;
                initPosY = ii;
                map[ii][jj] = -1;
            }   
        }
    }

    int obstaclePositions = 0;
    for (int iiOuter=0; iiOuter < nRows; iiOuter++) {
        for (int jjOuter=0; jjOuter < nCols; jjOuter++) {

            // make a copy of the initial map and add an obstacle
            std::copy(__map, __map + (nRows * nCols), __mapCopy);
            std::vector<std::vector<int>> guardStates = {};

            // Init position and direction
            dirX = 0;
            dirY = -1;
            posX = initPosX;
            posY = initPosY;

            // modify the map
            if (mapCopy[iiOuter][jjOuter] == 0) {
                mapCopy[iiOuter][jjOuter] = 1;
            } else {
                continue;
            }

            int onMap = 1;
            while (true) {
                std::vector<int> guardState = {posX, posY, dirX, dirY};
                // Check if current state in is already in vector of states
                
                if (stateHasOccured(&guardStates, guardState, guardStates.size())) {
                    obstaclePositions++;
                    std::cout << iiOuter << " " << jjOuter << "\n";
                    break;
                } else {
                    guardStates.push_back(guardState);
                }

                // Let the guard walk
                onMap = walkGuard(mapCopy, &posX, &posY, &dirX, &dirY, nRows, nCols);
                if (!onMap) {
                    break;
                }
            }
        }
    }

    delete[] map;
    delete[] __map;
    delete[] mapCopy;
    delete[] __mapCopy;
    
    return obstaclePositions;
}

int walkGuard(int** map, int* posX, int* posY, int* dirX, int* dirY, int nRows, int nCols) {
    // Walks the guard into the current direction until encoutering an obstacle or leaving the area
    int nSteps = 1;
    int ii;
    int jj;
    int lastX = *posX;
    int lastY = *posY;
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
            //std::cout << "Obstacle found!\n";
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
        } else {
            // Mark next position as visited
            map[ii][jj] = -1;
            lastX = jj;
            lastY = ii;
            nSteps++;
        }
    }
    *posY = lastY;
    *posX = lastX;
    return onMap;
}

bool stateHasOccured(std::vector<std::vector<int>>* states, std::vector<int> state, int nStates) {
    bool matchFound = false;

    for (auto ss: *states) {
        if (ss == state) {
            matchFound = true;
            break;
        }
    }
    return matchFound;
}

void printMap(int** map, int nRows, int nCols) {
    for (int ii=0; ii<nRows; ii++) {
        for (int jj=0; jj<nRows; jj++) {
            if (ii==3 and jj==62) {std::cout << "O";}
            else if (map[ii][jj]==0) {std::cout << ".";}
            else if (map[ii][jj]==1) {std::cout << "#";}
            else if (map[ii][jj]==-1) {std::cout << "+";}
        }
        std::cout << "\n";
    }
    std::cout << "\n\n\n\n";
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