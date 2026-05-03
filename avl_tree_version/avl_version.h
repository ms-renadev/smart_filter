#ifndef AVL_VERSION_H
#define AVL_VERSION_H

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cassert>
#include <cstdlib>

struct Node {
    std::string word;
    Node * left, * right;
    int height;

    Node(std::string w){
        word = w;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class AVLFilter {
private:
    Node * root;
    int getHeight(Node* n);    
    int getBalance(Node* n);   
    
    Node * rotateRight(Node* y);  
    Node * rotateLeft(Node* x);  

    Node * insert(Node * node, std::string word, std::string label);
    void inOrderSave(Node * node, std::ofstream& file); 

public:
    AVLFilter();
    void addWord(std::string rawWord, std::string label);
    void saveToFile(std::string filename);
};

#include "avl_version.cpp"
#endif