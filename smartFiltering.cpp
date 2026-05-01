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
size_t SmartFilter::totalWords() {return (getTotalHam() + getTotalSpam());}

void SmartFilter::addWord(std::string rawWord, std::string label) {
    std::string updatedWord = lowerCaseAll(rawWord);// create func tolower 
    if (updatedWord == "") return;
 
//search
    Node * temp = headPtr;
    while (temp != NULL) {
        if (temp->word == updatedWord) {
            if (label == "spam") {
                totalSpamCount++;
            }
            else if (label == "ham") {
                totalHamCount++;
            }
            return;
        }
        temp = temp->next;
    }
//create if not found
    Node * newNode = new Node(updatedWord);
        if (label == "spam") {
                totalSpamCount++;
        }
        else if (label == "ham") {
            totalHamCount++;
        }
//insert na tail

    if (headPtr == NULL) {
        headPtr = newNode;
        tailPtr = newNode;
    } else {
        tailPtr->next = newNode;
        tailPtr = newNode;
    }
}

// void SmartFilter::displayResults() {
//     Node * curr = headPtr;
//     while (curr != NULL) {
//         if ((curr->spamCount + curr->hamCount) > 1) {
//             std::cout << curr->word << "\tSpam: " << curr->spamCount 
//                  << "\tHam: " << curr->hamCount << std::endl;
//         }
//         curr = curr->next;
//     }
// }

void SmartFilter::saveToFile(std::string filename) {
    std::ofstream outFile(filename); \

    if (outFile.is_open()) {
        outFile << "Spam count: " << getTotalSpam();
        outFile << "\nHam Count: " << getTotalHam();
        outFile << "\nTotal Words: " << totalWords();
        outFile.close();
        std::cout << "Results saved to " << filename << std::endl;
    }
}