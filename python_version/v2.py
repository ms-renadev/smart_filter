import time
import os

class Node:
    def __init__(self, word):
        self.word = word
        self.next = None

class SmartFilter:
    def __init__(self):
        self.headPtr = None
        self.tailPtr = None
        self.totalSpamCount = 0
        self.totalHamCount = 0
        self.size = 0 

    def lowerCaseAll(self, raw_word):
        return raw_word.strip().lower()

    def addWord(self, rawWord, label):
        updatedWord = self.lowerCaseAll(rawWord)
        if not updatedWord: return

        if label == "spam": self.totalSpamCount += 1
        elif label == "ham": self.totalHamCount += 1

        temp = self.headPtr
        while temp is not None:
            if temp.word == updatedWord:
                return 
            temp = temp.next

        newNode = Node(updatedWord)
        if self.headPtr is None:
            self.headPtr = newNode
            self.tailPtr = newNode
        else:
            self.tailPtr.next = newNode
            self.tailPtr = newNode
        self.size += 1

    def saveToFile(self, filename):
        with open(filename, "w") as f:
            # 1. Write the summary header first
            f.write("--- SmartFilter Statistics ---\n")
            f.write(f"Total Spam Words: {self.totalSpamCount}\n")
            f.write(f"Total Ham Words: {self.totalHamCount}\n")
            f.write(f"Total Unique Words (U): {self.size}\n")
            f.write("------------------------------\n\n")

def main():
    RUNS = 3
    total_ms = 0

    # Ensure these paths are correct relative to where you run the script!
    index_path = "trec06p/full/index"
    base_dir = "trec06p/data/"
    for run in range(1, RUNS + 1):
        my_filter = SmartFilter() 
        start_time = time.perf_counter()

        try:
            with open(index_path, "r") as test_index:
                for line in test_index:
                    parts = line.split()
                    if len(parts) < 2: continue
                    
                    label, file_path = parts[0], parts[1]
                    
                    # Fix: Remove the relative prefix if it exists in the index file
                    clean_path = file_path.replace("../data/", "")
                    full_path = os.path.normpath(os.path.join(base_dir, clean_path))

                    try:
                        with open(full_path, "r", encoding="latin-1") as email_file:
                            for raw_word in email_file.read().split():
                                my_filter.addWord(raw_word, label)
                        print(f"Processed: {full_path} [{label}]")
                    except FileNotFoundError:
                        print(f"Failed to open email: {full_path}")

        except FileNotFoundError:
            print(f"Error: Index file not found at {os.path.abspath(index_path)}")
            return

        end_time = time.perf_counter()
        duration_ms = (end_time - start_time) * 1000
        total_ms += duration_ms
        print(f"Run {run} completed: {duration_ms:.2f} ms")
        
        if run == RUNS:
            my_filter.saveToFile("outputPython.txt")

    print(f"\nAverage runtime: {total_ms / RUNS:.2f} ms")
    print(f"Unique words: {my_filter.size}")

if __name__ == "__main__":
    main()