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
    std::string updatedWord;
    Node * next;
    Node(std::string _word){
        updatedWord = _word;
        next = NULL;
    }
};
Node * insertHead(Node* &headPtr, std::string word);
class SmartFilter {
private:
    Node * headPtr;
    Node * tailPtr;
    size_t totalSpamCount;     
    size_t totalHamCount;
    size_t size;
    std::string lowerCaseAll(std::string rawWord);
public:
    SmartFilter();
    ~SmartFilter();

    Node * get_headPtr() const;
    Node * get_tailPtr() const;
    size_t getTotalSpam() const;
    size_t getTotalHam() const;
    size_t getSize() const;
   
    void addWord(std::string rawWord, std::string label);
    void saveToFile(std::string filename);
    size_t getTotalUniqueWords();
};
#include "smartFiltering.cpp"
#endif