import time
import os

# class Node:
#     def __init__(self, word):
#         self.word = word
#         self.next = None

# class SmartFilter:
#     def __init__(self):
#         self.head = None
#         self.tail = None
#         self.size = 0
#     def lowerAllCase(str rawWord){

#     }
#     def add_word(self, raw_word, label):
#         # 1. Pre-process (lower case)
#         # 2. Search logic (O(U)), ehere U stands for unique words 
#             #O(U) means that the time it takes to find a word is directly 
#             # proportional to how many nodes are already in your list.
#         # 3. Create and Insert (if not found)
     
#     def save_to_file(self, filename):

def main():
    runs = 3
    total_duration = 0

    print("Starting 3-Run Performance Test (Python)...")
    print("-" * 36)
    index_path = "trec06p/ham25/experiment2"
    base_dir = "trec06p/data/"

    for run in range(1, runs + 1):
        my_filter = SmartFilter()
        # 1. let's record the time started:
        start_time = time.perf_counter()

        try:
            with open(index_path, "r") as test_index:
                for line in test_index:
                    # i hlaf mo like label path

                    # full_path = add base dir and the path
                    try:
                        #open the data/files 
                    except FileNotFoundError:
                         print(f"Failed to open email: {var}")


            
            
        except FileNotFoundError:
            print(f"Run {run}: Index file not found.")
            return
        end_time = time.perf_counter()
        total_duration = (end_time - start_time) * 1000
        total_ms += total_duration
        print(f"Run {run} completed: {total_duration:.2f} ms")
        
        if run == runs:
            my_filter.saveToFile("output.txt")

    print(f"\nAverage runtime: {total_ms / runs:.2f} ms")
    print(f"Unique words: {my_filter.size}")

        

if __name__ == "__main__":
    main()