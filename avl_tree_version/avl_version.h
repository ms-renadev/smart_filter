#ifndef AVL_VERSION_H
#define AVL_VERSION_H

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cassert>
#include <cstdlib>

struct BTNode {
    std::string word;
    BTNode * left, * right;
    int height;

    BTNode(std::string w){
        word = w;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class AVLFilter {
private:
    BTNode * root;
    size_t totalSpamCount;     
    size_t totalHamCount;
    size_t size;

public:
    AVLFilter();

    int getHeight(BTNode * n);    
    int getBalance(BTNode * n);  
    
    size_t getTotalSpam() const;
    size_t getTotalHam() const;
    size_t getSize() const;
    size_t getTotalUniqueWords();

    BTNode * rotateRight(BTNode* y);  
    BTNode * rotateLeft(BTNode* x);  

    std::string lowerCaseAll(std::string rawWord);
    bool searchDuplicate(BTNode * node, std::string word);
    BTNode * insert(BTNode * node, std::string rawWord);
    void inOrderSave(BTNode * node, std::ofstream& file); 

    void addWord(std::string rawWord, std::string label);
    void saveToFile(std::string filename);
};

#include "avl_version.cpp"
#endif