#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>       // For iota, accumulate, etc.
#include <iterator>      // For std::back_inserter
#include <random>        // For std::shuffle
#include <functional>    // For std::greater

using namespace std;

int main() {
    vector<int> vec = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    
    // 1. Non-modifying sequence operations
    cout << "1. Non-modifying sequence operations\n";
    cout << "All of the elements are positive: " 
         << (all_of(vec.begin(), vec.end(), [](int x){ return x >= 0; }) ? "Yes" : "No") << endl;
    cout << "Any of the elements are greater than 7: " 
         << (any_of(vec.begin(), vec.end(), [](int x){ return x > 7; }) ? "Yes" : "No") << endl;
    cout << "None of the elements are negative: " 
         << (none_of(vec.begin(), vec.end(), [](int x){ return x < 0; }) ? "Yes" : "No") << endl;

    // 2. Modifying sequence operations
    cout << "\n2. Modifying sequence operations\n";
    vector<int> vec_copy;
    copy(vec.begin(), vec.end(), back_inserter(vec_copy));
    cout << "Copied vector: ";
    for (int n : vec_copy) cout << n << " ";
    cout << endl;

    // Sorting and removing duplicates
    sort(vec_copy.begin(), vec_copy.end());
    auto last = unique(vec_copy.begin(), vec_copy.end());
    vec_copy.erase(last, vec_copy.end());
    cout << "After removing duplicates: ";
    for (int n : vec_copy) cout << n << " ";
    cout << endl;

    // 3. Partitioning operations
    cout << "\n3. Partitioning operations\n";
    vector<int> vec_part = vec;
    partition(vec_part.begin(), vec_part.end(), [](int x){ return x % 2 == 0; });
    cout << "After partitioning (even first): ";
    for (int n : vec_part) cout << n << " ";
    cout << endl;

    // 4. Sorting operations
    cout << "\n4. Sorting operations\n";
    vector<int> vec_sort = vec;
    sort(vec_sort.begin(), vec_sort.end());
    cout << "Sorted vector: ";
    for (int n : vec_sort) cout << n << " ";
    cout << endl;

    // 5. Binary search operations
    cout << "\n5. Binary search operations\n";
    if (binary_search(vec_sort.begin(), vec_sort.end(), 7)) {
        cout << "7 is found in the sorted vector" << endl;
    }

    // 6. Set operations
    cout << "\n6. Set operations\n";
    vector<int> vec1 = {1, 3, 5, 7, 9};
    vector<int> vec2 = {2, 3, 5, 8, 9};
    vector<int> vec_union;
    set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(vec_union));
    cout << "Union of two sets: ";
    for (int n : vec_union) cout << n << " ";
    cout << endl;

    // 7. Heap operations
    cout << "\n7. Heap operations\n";
    vector<int> vec_heap = {3, 5, 1, 9, 6, 7};
    make_heap(vec_heap.begin(), vec_heap.end());
    cout << "Max heap: ";
    for (int n : vec_heap) cout << n << " ";
    cout << endl;

    pop_heap(vec_heap.begin(), vec_heap.end());
    vec_heap.pop_back();
    cout << "Heap after popping the largest element: ";
    for (int n : vec_heap) cout << n << " ";
    cout << endl;

    // 8. Min/Max operations
    cout << "\n8. Min/Max operations\n";
    cout << "Minimum element: " << *min_element(vec.begin(), vec.end()) << endl;
    cout << "Maximum element: " << *max_element(vec.begin(), vec.end()) << endl;

    // 9. Permutations
    cout << "\n9. Permutations\n";
    next_permutation(vec_sort.begin(), vec_sort.end());
    cout << "Next permutation: ";
    for (int n : vec_sort) cout << n << " ";
    cout << endl;

    // 10. Other utilities
    cout << "\n10. Other utilities\n";
    iota(vec.begin(), vec.end(), 1);
    cout << "Vector after iota: ";
    for (int n : vec) cout << n << " ";
    cout << endl;

    int sum = accumulate(vec.begin(), vec.end(), 0);
    cout << "Sum of elements: " << sum << endl;

    return 0;
}
