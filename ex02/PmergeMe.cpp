#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vectorSortTime(0), _listSortTime(0)
{
	_jacobsthalNumbers.push_back(0);
	_jacobsthalNumbers.push_back(1);
	for (int i = 2; i < 30; ++i)
	{
		_jacobsthalNumbers.push_back(_jacobsthalNumbers[i - 1] + 2
			* _jacobsthalNumbers[i - 2]);
	}
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vectorContainer = other._vectorContainer;
		this->_listContainer = other._listContainer;
		this->_originalSequence = other._originalSequence;
		this->_vectorSortTime = other._vectorSortTime;
		this->_listSortTime = other._listSortTime;
		this->_jacobsthalNumbers = other._jacobsthalNumbers;
	}
	return (*this);
}

void PmergeMe::generateJacobsthalNumbers(int n)
{
	_jacobsthalNumbers.clear();
	_jacobsthalNumbers.push_back(0);
	_jacobsthalNumbers.push_back(1);
	for (int i = 2; i <= n; ++i)
	{
		_jacobsthalNumbers.push_back(_jacobsthalNumbers[i - 1] + 2
			* _jacobsthalNumbers[i - 2]);
	}
}

int PmergeMe::getNextJacobsthalIndex(int n)
{
	int	i;

	i = 0;
	while (_jacobsthalNumbers[i] <= n)
	{
		++i;
		if (i >= (int)_jacobsthalNumbers.size())
		{
			generateJacobsthalNumbers(i);
		}
	}
	return (_jacobsthalNumbers[i - 1]);
}

template <typename T> void PmergeMe::insertionSort(T &container,
	typename T::iterator begin, typename T::iterator end)
{
	(void)container;
	for (typename T::iterator i = begin; i != end; ++i)
	{
		typename T::iterator j = i;
		typename T::value_type temp = *i;
		while (j != begin)
		{
			typename T::iterator prev_j = j;
			--prev_j;
			if (!(*prev_j > temp))
				break ;
			*j = *prev_j;
			j = prev_j;
		}
		*j = temp;
	}
}

template <typename T> void PmergeMe::mergeInsertSort(T &container,
	typename T::iterator begin, typename T::iterator end)
{
	T	tempContainer;

	if (std::distance(begin, end) <= 16)
	{
		insertionSort(container, begin, end);
		return ;
	}
	typename T::iterator middle = begin;
	std::advance(middle, std::distance(begin, end) / 2);
	mergeInsertSort(container, begin, middle);
	mergeInsertSort(container, middle, end);
	typename T::iterator it1 = begin;
	typename T::iterator it2 = middle;
	while (it1 != middle && it2 != end)
	{
		if (*it1 < *it2)
		{
			tempContainer.push_back(*it1);
			++it1;
		}
		else
		{
			tempContainer.push_back(*it2);
			++it2;
		}
	}
	while (it1 != middle)
	{
		tempContainer.push_back(*it1);
		++it1;
	}
	while (it2 != end)
	{
		tempContainer.push_back(*it2);
		++it2;
	}
	typename T::iterator tempIt = tempContainer.begin();
	for (typename T::iterator it = begin; it != end; ++it, ++tempIt)
	{
		*it = *tempIt;
	}
}

template <typename T> void PmergeMe::fordJohnsonSort(T &container)
{
	if (container.size() > 1000)
	{
		mergeInsertSort(container, container.begin(), container.end());
		return ;
	}
	mergeInsertSort(container, container.begin(), container.end());
}

bool PmergeMe::parseArguments(int argc, char **argv)
{
		int value;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		for (size_t j = 0; j < arg.length(); ++j)
		{
			if (!isdigit(arg[j]))
			{
				std::cerr << "Error" << std::endl;
				return (false);
			}
		}
		std::istringstream iss(arg);
		iss >> value;
		if (value < 0)
		{
			std::cerr << "Error" << std::endl;
			return (false);
		}
		if (value > INT_MAX)
		{
			std::cerr << "Error: Integer overflow" << std::endl;
			return (false);
		}
		_originalSequence.push_back(value);
		_vectorContainer.push_back(value);
		_listContainer.push_back(value);
	}
	return (true);
}

bool PmergeMe::validateSorting()
{
	int	prev;

	for (size_t i = 1; i < _vectorContainer.size(); ++i)
	{
		if (_vectorContainer[i - 1] > _vectorContainer[i])
		{
			return (false);
		}
	}
	std::list<int>::iterator it = _listContainer.begin();
	prev = *it;
	++it;
	for (; it != _listContainer.end(); ++it)
	{
		if (prev > *it)
		{
			return (false);
		}
		prev = *it;
	}
	return (true);
}

void PmergeMe::displayResults()
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _originalSequence.size(); ++i)
	{
		std::cout << _originalSequence[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "After: ";
	for (size_t i = 0; i < _vectorContainer.size(); ++i)
	{
		std::cout << _vectorContainer[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vectorContainer.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << _vectorSortTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _listContainer.size() << " elements with std::list : " << std::fixed << std::setprecision(5) << _listSortTime << " us" << std::endl;
}

bool PmergeMe::processArguments(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (false);
	}
	if (!parseArguments(argc, argv))
	{
		return (false);
	}
	std::cout << "Before: ";
	for (size_t i = 0; i < _originalSequence.size(); ++i)
	{
		std::cout << _originalSequence[i] << " ";
	}
	std::cout << std::endl;
	clock_t start, end;
	start = clock();
	fordJohnsonSort(_vectorContainer);
	end = clock();
	_vectorSortTime = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	start = clock();
	fordJohnsonSort(_listContainer);
	end = clock();
	_listSortTime = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	if (!validateSorting())
	{
		std::cerr << "Error: Sorting failed!" << std::endl;
		return (false);
	}
	std::cout << "After: ";
	for (size_t i = 0; i < _vectorContainer.size(); ++i)
	{
		std::cout << _vectorContainer[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vectorContainer.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << _vectorSortTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _listContainer.size() << " elements with std::list : " << std::fixed << std::setprecision(5) << _listSortTime << " us" << std::endl;
	return (true);
}

bool PmergeMe::runLargeTest(int size)
{
	int	value;

	_originalSequence.clear();
	_vectorContainer.clear();
	_listContainer.clear();
	srand(time(NULL));
	for (int i = 0; i < size; ++i)
	{
		value = rand() % 10000;
		_originalSequence.push_back(value);
		_vectorContainer.push_back(value);
		_listContainer.push_back(value);
	}
	std::cout << "Running large test with " << size << " elements..." << std::endl;
	clock_t start, end;
	start = clock();
	fordJohnsonSort(_vectorContainer);
	end = clock();
	_vectorSortTime = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	start = clock();
	fordJohnsonSort(_listContainer);
	end = clock();
	_listSortTime = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	if (!validateSorting())
	{
		std::cerr << "Error: Sorting failed!" << std::endl;
		return (false);
	}
	std::cout << "Time to process a range of " << _vectorContainer.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << _vectorSortTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _listContainer.size() << " elements with std::list : " << std::fixed << std::setprecision(5) << _listSortTime << " us" << std::endl;
	return (true);
}
