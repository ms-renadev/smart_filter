#include "avl_version.h"

AVLFilter::AVLFilter() {
    root = NULL;
    totalSpamCount = 0;    
    totalHamCount = 0;
    size = 0;
}

int AVLFilter::getHeight(BTNode * n) {
    if (n == NULL) return 0;
    return n->height;
}

int AVLFilter::getBalance(BTNode * n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

size_t AVLFilter::getTotalSpam() const {return totalSpamCount;};
size_t AVLFilter::getTotalHam() const {return totalHamCount;};
size_t AVLFilter::getSize() const {return size;};
BTNode * AVLFilter::rotateRight(BTNode * y) { //right rotation
    BTNode * x = y->left;
    BTNode * T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; 
}

BTNode * AVLFilter::rotateLeft(BTNode * x) { //left roration
    BTNode * y = x->right;
    BTNode * T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; 
}

std::string AVLFilter::lowerCaseAll(std::string rawWord) {
    std::string updatedWord = "";
    for (size_t i = 0; i < rawWord.length(); i++) {
        updatedWord += tolower(rawWord[i]);
    }
    return updatedWord;
}
bool AVLFilter::searchDuplicate(BTNode * node, std::string word) {
    if (node == NULL) return false;
    if (word == node->word) return true;
    
    if (word < node->word) 
        return searchDuplicate(node->left, word);
    else 
        return searchDuplicate(node->right, word);
}

BTNode * AVLFilter::insert(BTNode * node, std::string updatedWord) {
    // 1. Standard BST insertion or update
    if (node == NULL) {
        return new BTNode(updatedWord); 
    }
    if (updatedWord < node->word) {
        node->left = insert(node->left, updatedWord);
    } else if (updatedWord > node->word) {
        node->right = insert(node->right, updatedWord);
    }

    // 2. Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // 3. Get balance factor to check if it became unbalanced
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && updatedWord < node->left->word)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && updatedWord > node->right->word)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && updatedWord > node->left->word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && updatedWord < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLFilter::addWord(std::string rawWord, std::string label) {
    std::string updatedWord = lowerCaseAll(rawWord);
    if (updatedWord == "") return;
    size++;
    if (!searchDuplicate(root, updatedWord)) {
        // ONLY if it's not a duplicate, we increment the category counts
        if (label == "spam") {
            totalSpamCount++;
        } else if (label == "ham") {
            totalHamCount++;
        }
        // Now actually put it in the tree
        root = insert(root, updatedWord);
    }
}

void AVLFilter::inOrderSave(BTNode * node, std::ofstream& file) {
    if (node != NULL) {
        inOrderSave(node->left, file);
        file << node->word << std::endl;
        inOrderSave(node->right, file);
    }
}
 size_t AVLFilter::getTotalUniqueWords(){ return totalHamCount + totalSpamCount;};
void AVLFilter::saveToFile(std::string filename) {
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