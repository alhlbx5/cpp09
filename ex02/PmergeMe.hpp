#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <climits>

class PmergeMe {
private:
    std::vector<int> _vectorContainer;
    std::list<int> _listContainer;
    std::vector<int> _originalSequence;
    double _vectorSortTime;
    double _listSortTime;
    
    std::vector<int> _jacobsthalNumbers;
    
    template <typename T>
    void insertionSort(T& container, typename T::iterator begin, typename T::iterator end);
    
    template <typename T>
    void mergeInsertSort(T& container, typename T::iterator begin, typename T::iterator end);
    
    template <typename T>
    void fordJohnsonSort(T& container);
    
    void generateJacobsthalNumbers(int n);
    int getNextJacobsthalIndex(int n);
    
    bool parseArguments(int argc, char** argv);
    void displayResults();
    bool validateSorting();

public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    
    bool processArguments(int argc, char** argv);
    bool runLargeTest(int size);
};

#endif
