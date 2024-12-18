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

struct pageRule {
    int firstPage;
    int secondPage;
};

pageRule parseRule(std::string);
std::vector<int> parseUpdate(std::string);
bool validateUpdate(std::vector<int>, std::vector<pageRule>);
int getMiddlePage(std::vector<int>);

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
    
    // Declarations
    size_t nRows = puzzleInput.size();
    std::vector<pageRule> rules;
    std::vector<std::vector<int>> updates;
    bool allRulesFound = false;

    /*********************************************************************** */
    // Parse input
    /*********************************************************************** */
    for (int ii = 0; ii < nRows; ii++) {
        // check for blank line
        if (puzzleInput[ii].size() == 0) {
            std::cout << "Found blank line with idx: " << ii << "\n";
            allRulesFound = true;
        }

        // parse rule
        if (!allRulesFound) {
            rules.push_back(parseRule(puzzleInput[ii]));
        }

        if (allRulesFound and puzzleInput[ii].size() > 0) {
            updates.push_back(parseUpdate(puzzleInput[ii]));
        }
    }
    /*********************************************************************** */
    // Process input
    /*********************************************************************** */
    // Loop over updates
    int score = 0;
    for (int ii = 0; ii < updates.size(); ii++) {
        if (validateUpdate(updates[ii], rules)) {
            std::cout << "Update " << ii + 1 << " is valid!\n";
            // find the middle page number
            score += getMiddlePage(updates[ii]);

        }
    }
    
    return score;
}

pageRule parseRule(std::string line) {
    std::vector<std::string> raw_vals;
    pageRule rule;
    raw_vals = customSplit(line, "|");
    rule.firstPage = std::stoi(raw_vals[0]);
    rule.secondPage = std::stoi(raw_vals[1]);

    std::cout << "Found rule definition: " << rule.firstPage << "|" << rule.secondPage << "\n";

    return rule;
}

std::vector<int> parseUpdate(std::string line) {
    std::vector<std::string> raw_vals;
    std::vector<int> vals;
    raw_vals = customSplit(line, ",");
    for (int ii = 0; ii < raw_vals.size(); ii++) {
        vals.push_back(std::stoi(raw_vals[ii]));
    }

    std::cout << "Update: " << line << "\n";

    return vals;
}

bool validateUpdate(std::vector<int> update, std::vector<pageRule> rules) {
    // declarations
    int currentPage;
    pageRule currentRule;
    bool violationFound = false;

    // loop over all pages in the udpate
    for (int ii = 0; ii < update.size(); ii++) {
        currentPage = update[ii];
        // Loop over all rules
        for (int jj = 0; jj < rules.size(); jj++) {
            currentRule = rules[jj];

            // check if the current page is affected by the current rule
            if (currentRule.firstPage == currentPage) {
                //std::cout << "Page " << currentPage << " is affected by rule " << currentRule.firstPage << "|" << currentRule.secondPage << "\n";
                // check if the second page appears before the first page
                for (int kk=0; kk<ii; kk++) {
                    if (update[kk] == currentRule.secondPage) {
                        violationFound = true;
                        break;
                    }
                }
            }
            
            // check if the current page is affected by the current rule
            if (currentRule.secondPage == currentPage) {
                //std::cout << "Page " << currentPage << " is affected by rule " << currentRule.firstPage << "|" << currentRule.secondPage << "\n";
                // check if the first page appears after the second page
                for (int kk=ii+1; kk<update.size(); kk++) {
                    if (update[kk] == currentRule.firstPage) {
                        violationFound = true;
                        break;
                    }
                }
            }

            if (violationFound) {break;}

        }

        if (violationFound) {break;}
    }
    return !violationFound;
}

int getMiddlePage(std::vector<int> update) {
    size_t nn = update.size();
    size_t idx;
    idx = (nn - 1) / 2;
    return update[idx];
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