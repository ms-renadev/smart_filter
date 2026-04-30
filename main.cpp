#include<iostream>
#include<fstream>

// #include"smartFiltering.h"
#include"smartFiltering.h"
//processdata path

// int main(){
//  load map file
//      after reading one line
            // go to the file
            // process and get the words
            // if it has duplicate words, wag mo ba i add sa list
// }


int main() {
    SmartFilter myFilter;

    std::ifstream testIndex("../trec06p/ham25/experiment1");
    if (!testIndex.is_open()) {
        std::cout << "Error: File system not found.\n";
        return 1;
    }

    std::string label, filePath;
    std::string baseDir = "../trec06p/data/";
    std::cout << "Reading map file and processing files..." << std::endl;

    while (testIndex >> label >> filePath) {

        std::string actualFile = filePath;

        std::string fullPath = baseDir + actualFile;

        std::ifstream emailFile(fullPath);

        if (emailFile.is_open()) {
           std:: string rawWord;
            while (emailFile >> rawWord) {
                myFilter.addWord(rawWord, label);
            }
            emailFile.close();
            std::cout << "Processed: " << fullPath << " [" << label << "]" << std::endl;
        } else {
            std::cout << "Failed to open content at: " << fullPath << std::endl;
        }
    }
    testIndex.close();
 
    myFilter.saveToFile("output.txt");

 

    return 0; 
}