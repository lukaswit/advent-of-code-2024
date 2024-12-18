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
int checkInstructionValid(std::string, int);
int evalInstruction(std::string);

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
    
    std::vector<std::vector<int>> levels;
    size_t nLines {puzzleInput.size()};
    int score = 0;
    bool mulEnabled = true;
    std::string currentFragment {""};
    
    for (int ii=0; ii<nLines; ii++) {
        // Loop over lines
        size_t nChars = puzzleInput[ii].size();
        std::cout << "Thee current line has " << nChars << " characters\n";
        std::string dontToken = "don't()";
        std::string doToken = "do()";
        std::string mulToken = "mul()";

        for (int pos=0; pos<nChars - 3; pos++) {
            // check for don't() fragment first
            currentFragment = puzzleInput[ii].substr(pos, dontToken.size());
            if (currentFragment == dontToken) {mulEnabled = false;}
            currentFragment = puzzleInput[ii].substr(pos, doToken.size());
            if (currentFragment == doToken) {mulEnabled = true;}

            if (mulEnabled) {
                currentFragment = puzzleInput[ii].substr(pos, 3);
                if (currentFragment == "mul") {
                std::cout << "Found a 'mul' fragment at position: " << pos << "\n";
                int prod = checkInstructionValid(puzzleInput[ii], pos);
                score = score + prod;
                }
            }
            
        }
    }

    return score;
}

int checkInstructionValid(std::string line, int pos) {
    // check if the next character is an opening parenthesis
    pos = pos + 3; // advance to where the opening parenthesis should be
    if (line.substr(pos, 1) == "(") {
        std::cout << "Opening parenthesis found!\n";
    } else {
        return 0;
    }
    bool valid = false;
    int initPos = pos + 1;
    int lastPos = -1;
    std::string allowed {"0123456789,"};
    // Now we expect a number, a comma and another number
    while (true) {
        pos++;
        std::string mychar = line.substr(pos, 1);
        if (allowed.find(mychar) != std::string::npos) {
            // The next character appears to be a valid character
            // pass
        } else {
            if (mychar == ")") {
                std::cout << "Found closing parenthesis at position " << pos << "\n";
                valid = true;
                lastPos = pos - 1;
                break;
            } else {break;}
        }
    }
    int result;
    if (valid) {
        result = evalInstruction(line.substr(initPos, lastPos - initPos + 1));    
    } else {result=0;}

    return result;
}

int evalInstruction(std::string instruction) {
    std::cout << instruction << "\n";
    auto numbersStr = customSplit(instruction, ",");
    int num0;
    int num1;
    num0 = std::stoi(numbersStr[0]);
    num1 = std::stoi(numbersStr[1]);
    return num0 * num1;
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