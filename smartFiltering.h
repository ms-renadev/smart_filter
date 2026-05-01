#ifndef SPAMFILTERING_H
#define SPAMFILTERING_H

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cctype>

struct Node {
    std::string word;
    Node * next;
    Node(std::string _word){
        word = _word;
        next = NULL;
    }
};

class SmartFilter {
private:
    Node * headPtr;
    Node * tailPtr;
    size_t totalSpamCount;     
    size_t totalHamCount;
    std::string lowerCaseAll(std::string rawWord);
public:
    SmartFilter();
    ~SmartFilter();
    //getters - size, headptr, tail
    Node * get_headPtr() const;
    Node * get_tailPtr() const;
    size_t getTotalSpam() const;
    size_t getTotalHam() const;
    size_t totalWords();
   
    void addWord(std::string rawWord, std::string label);
    void displayResults();//debug
    void saveToFile(std::string filename);
};
#include "smartFiltering.cpp"
#endif