#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
using namespace std;

// Merge sort
vector<int> mergeSort(vector <int> content, int start, int end) {

    // Make and populate new vector endSort from subsection of given vector
    vector <int> endSort;
    for(int i = start; i < end; i++){
        endSort.push_back(content[i]);
    }

    // Find current split point of original vector
    int midpoint = (end - start) / 2 + start;

    // If provided list is too small to be halved, return endSort
    if(midpoint == 0 || endSort.size() == 1){
        return endSort;
    }

    // Recursively halve list
    vector <int> firstHalf = mergeSort(content, start, midpoint);
    vector <int> secondHalf = mergeSort(content, midpoint, end);

    //Compare halves' contents and merge
    int index = 0;
    int firstIndex = 0;
    int secondIndex = 0;

    while(firstIndex < (int)firstHalf.size() || secondIndex < (int)secondHalf.size()){
        if(firstHalf[firstIndex] > secondHalf[secondIndex] || secondIndex >= (int)secondHalf.size()){
            endSort[index ++] = firstHalf[firstIndex ++];
        }
        else{
            endSort[index ++] = secondHalf[secondIndex ++];
        }
    }

    return endSort;
}

// K Largest
vector<int> kSort(vector<int> content, int k){
    // Make a min priority queue to hold all given ints
    priority_queue<int, vector<int>, greater<int> > sorter;
    vector<int> endSort;

    // Iterate through the given vector, filling the priority queue up to k elements
    for(int i = 0; i < k; i++){
        sorter.push(content[i]);
    }

    // For the remaining elements, if an int is larger than the top of the queue,
    // pop the smallest element from the priority queue and add that int
    for(int i = k; i < content.size(); i++){
        if(sorter.top() < content[i]){
            sorter.pop();
            sorter.push(content[i]);
        }
    }

    // Add priority queue elements to a vector and return it
    for(int i = 0; i < k; i++){
        endSort.push_back(sorter.top());
        sorter.pop();
    }

    return endSort;
}

int main(){

    // Merge test
    cout << "Merge" << endl;
    vector<int> values;
    values.push_back(2);
    values.push_back(4);
    values.push_back(3);
    values.push_back(1);
    values.push_back(10);
    values.push_back(5);
    values.push_back(300);
    values.push_back(20);

    // (Chrono clock objects and manipulation sourced from GeeksforGeeks 
    // https://www.geeksforgeeks.org/measure-execution-time-function-cpp/)

    // Get start and end timepoints and then subtract them to find duration of functions
    auto start1 = std::chrono::high_resolution_clock::now();
    vector<int> tester = mergeSort(values, 0, values.size());
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = duration_cast<std::chrono::microseconds>(stop1 - start1);


    for(int i = 0; i < 5; i++){
        cout << tester[i] << endl;
    }

    // K Largest Test
    cout << "\nK largest" << endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    vector<int> tester2 = kSort(values, 5);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = duration_cast<std::chrono::microseconds>(stop2 - start2);

    for(int i = 4; i > -1; i--){
        cout << tester2[i] << endl;
    }

    cout << "\nTime taken by Merge: " << duration1.count() << " microseconds" << endl;
    cout << "Time taken by K Largest: " << duration2.count() << " microseconds" << endl;


    return 0;
}