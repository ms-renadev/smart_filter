#include"avl_version.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>


int main() {
    
    const int RUNS = 3; 
    long long totalDuration = 0;
   for (int run = 1; run <= RUNS; run++) {
        AVLFilter myFilter;
        std::cout << "\nRUNTIME NO. " << run << " \n\n";
        //1. let's record the time started:
        auto start = std::chrono::high_resolution_clock::now();
        std::ifstream testIndex("../trec06p/full/index");
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

        //2. then end time niya
        auto end = std::chrono::high_resolution_clock::now();

        //3. last na calc run time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalDuration = totalDuration + duration.count();
        std::cout << "\n--- Performance Statistics [RUN " << run << " ]---" << std::endl;
        std::cout << "Total runtime: " << duration.count() << " ms (" 
                << duration.count() / 1000.0 << " seconds or " << duration.count()/(1000.0 * 60.0 * 60.0) 
                << " hours )" << std::endl;

        std::cout << "Unique words processed: " << myFilter.getTotalUniqueWords()<< std::endl;
        std::cout << "Number of words in email is " << myFilter.getSize() << std::endl;
        std::cout << "\n-------------------------------------------------------\n";
        std::cout << "Spam count: " << myFilter.getTotalSpam();
        std::cout << "\nHam Count: " << myFilter.getTotalHam();
        std::cout << "\nTotal Unique Words (U): " << myFilter.getTotalUniqueWords();
        std::cout << "\nNumber of words in email (N): " << myFilter.getSize();
        std::cout << "\n-------------------------------------------------------\n";
    }
    //start at 4:13 AM
    double average = (totalDuration * 1.0) / RUNS;
    double averageHours = average / (1000.0 * 60.0 * 60.0);
    std::cout << "\n\nAverage Runtime (sec): " << average / 1000.0 << " s" << std::endl;
    std::cout << "Average Runtime (hours): " << averageHours << " hours" << std::endl;

    return 0;
}

