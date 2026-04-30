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
    size_t spamCount;
    size_t hamCount;
    Node * next;
    Node(std::string _word){
        word = _word;
        spamCount = 0;
        hamCount = 0;
        next = NULL;
    }
};

class SmartFilter {
private:
    Node * headPtr;
    Node * tailPtr;
    size_t size;
    size_t totalSpamCount;     
    size_t totalHamCount;
    std::string lowerCaseAll(std::string rawWord);
public:
    SmartFilter();
    ~SmartFilter();
    //getters - size, headptr, tail
    Node * get_headPtr() const;
    Node * get_tailPtr() const;
    size_t get_size() const;
    size_t getTotalSpam() const;
    size_t getTotalHam() const;

    void addWord(std::string rawWord, std::string label);
    void displayResults();//debug
    void saveToFile(std::string filename);
};
#include "smartFiltering.cpp"
#endif