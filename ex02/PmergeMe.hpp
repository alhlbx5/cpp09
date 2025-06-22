#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <cstdlib>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <list>
# include <sstream>
# include <string>
# include <vector>

class PmergeMe
{
  private:
	std::vector<int> _vectorContainer;
	std::list<int> _listContainer;
	std::vector<int> _originalSequence;
	double _vectorSortTime;
	double _listSortTime;

	template <typename T> void insertionSort(T &container,
		typename T::iterator begin, typename T::iterator end);

	template <typename T> void mergeInsertSort(T &container,
		typename T::iterator begin, typename T::iterator end);

	template <typename T> void fordJohnsonSort(T &container);

	bool parseArguments(int argc, char **argv);
	void displayResults();

  public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);

	bool processArguments(int argc, char **argv);
};

#endif
