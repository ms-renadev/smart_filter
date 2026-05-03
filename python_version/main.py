import time
import os

class Node:
    def __init__(self, word):
        self.word = word
        self.next = None

class SmartFilter:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0
        self.totalSpamCount = 0
        self.totalHamCount = 0

    def lowerCaseAll(self, raw_word):
        return raw_word.strip().lower()
    
    def add_word(self, raw_word, label):
        # 1. Pre-process (lower case)
        # 2. Search logic (O(U)), ehere U stands for unique words 
            #O(U) means that the time it takes to find a word is directly 
            # proportional to how many nodes are already in your list.
        # 3. Create and Insert (if not found)
            updatedWord = self.lowerCaseAll(raw_word)
            if not updatedWord: return

            if label == "spam": self.totalSpamCount += 1
            elif label == "ham": self.totalHamCount += 1

            temp = self.head
            while temp is not None:
                if temp.word == updatedWord:
                    return 
                temp = temp.next

            newNode = Node(updatedWord)
            if self.head is None:
                self.head = newNode
                self.tail = newNode
            else:
                self.tail.next = newNode
                self.tail = newNode
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

    print("Starting 3-Run Performance Test (Python)...")
    print("-" * 36)
    index_path = "trec06p/ham25/experiment2"
    base_dir = "trec06p/data/"

    for run in range(1, RUNS + 1):
        my_filter = SmartFilter()
        # 1. let's record the time started:
        start_time = time.perf_counter()

        try:
            with open(index_path, "r") as test_index:
                for line in test_index:
                    parts = line.split()
                    if len(parts) < 2: continue
                    
                    label, file_path = parts[0], parts[1]
                    clean_path = file_path.replace("../data/", "")
                    full_path = os.path.normpath(os.path.join(base_dir, clean_path))

                    try:
                        with open(full_path, "r", encoding="latin-1") as email_file:
                            for raw_word in email_file.read().split():
                                my_filter.add_word(raw_word, label)
                        print(f"Processed: {full_path} [{label}]")
                    except FileNotFoundError:
                        print(f"Failed to open email: {full_path}")

        except FileNotFoundError:
            print(f"Error: Index file not found at {os.path.abspath(index_path)}")
            return
        
        end_time = time.perf_counter()
        total_duration = (end_time - start_time) * 1000
        total_ms += total_duration
        print(f"Run {run} completed: {total_duration:.2f} ms")
        
        if run == RUNS:
            my_filter.saveToFile("output.txt")

    print(f"\nAverage runtime: {total_ms / RUNS:.2f} ms")
    print(f"Unique words: {my_filter.size}")

        

if __name__ == "__main__":
    main()