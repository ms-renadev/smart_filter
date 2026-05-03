#include<iostream>
#include<fstream>
#include"smartFiltering.h"
#include <chrono>
//processdata path

// int main(){
//  load map file
//      after reading one line
            // go to the file
            // process and get the words
            // if it has duplicate words, wag mo ba i add sa list
// }

int main() {
    const int RUNS = 3;
    long long totalDuration = 0;
    SmartFilter myFilter;
    for (int run = 1; run <= RUNS; run++) {

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

        std::cout << "Unique words processed: " << myFilter.totalWords() << std::endl;
        std::cout << "-------------------------------------------------------\n";
    }
    //start at 4:13 AM
    double average = (totalDuration * 1.0) / RUNS;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Average Runtime (sec): " << average / 1000.0 << " s" << std::endl;

    double averageHours = average / (1000.0 * 60.0 * 60.0);
    std::cout << "Average Runtime (hours): " << averageHours << " hours" << std::endl;
   
}