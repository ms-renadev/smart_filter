#include "smartFiltering.h"

std::string SmartFilter::lowerCaseAll(std::string rawWord) {
    std::string updatedWord = "";
    for (size_t i = 0; i < rawWord.length(); i++) {
        updatedWord += tolower(rawWord[i]);
    }
    return updatedWord;
}
SmartFilter::SmartFilter() {
    headPtr = NULL;
    tailPtr = NULL;
    totalSpamCount = 0;    
    totalHamCount = 0;
    size = 0;
}

SmartFilter::~SmartFilter() {
    Node * curr = headPtr;
    while (curr != NULL) {
        Node * next = curr->next;
        delete curr;
        curr = next;
    }
}

Node * SmartFilter::get_headPtr() const{return headPtr;};
Node * SmartFilter::get_tailPtr() const {return tailPtr;};
size_t SmartFilter::getTotalSpam() const {return totalSpamCount;};
size_t SmartFilter::getTotalHam() const {return totalHamCount;};
size_t SmartFilter::getSize() const {return size;};

void SmartFilter::addWord(std::string rawWord, std::string label) {
    std::string updatedWord = lowerCaseAll(rawWord);// create func tolower 
    if (updatedWord == "") return;
    size++;
//search if naay duplicate, if yes na ayaw na idagdaga sa count
    Node * temp = headPtr;
    while (temp != NULL) {
        if (temp->updatedWord == updatedWord){ 
            return;
        }
        temp = temp->next;
    }
//if wala sa list then add sa listahan, and increment
    if (label == "spam") {
        totalSpamCount++;
    }
    else if (label == "ham") {
        totalHamCount++;
    }
//insert na tail
    Node * newNode = new Node(updatedWord);
    if (headPtr == NULL) {
        headPtr = newNode;
        tailPtr = newNode;
    } else {
        tailPtr->next = newNode;
        tailPtr = newNode;
    }
}


void SmartFilter::saveToFile(std::string filename) {
    std::ofstream outFile(filename); \

    if (outFile.is_open()) {
        outFile << "Spam count: " << totalSpamCount;
        outFile << "\nHam Count: " << totalHamCount;
        outFile << "\nTotal Unique Words (U): " << getTotalUniqueWords();
        outFile << "\nNumber of words in email (N): " << size;
        outFile.close();
        std::cout << "Results saved to " << filename << std::endl;
    }
}
 size_t SmartFilter::getTotalUniqueWords(){ return totalHamCount + totalSpamCount;};