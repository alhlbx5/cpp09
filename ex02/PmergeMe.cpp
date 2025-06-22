#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vectorSortTime(0), _listSortTime(0)
{
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
	}
	return (*this);
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
		_originalSequence.push_back(value);
		_vectorContainer.push_back(value);
		_listContainer.push_back(value);
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
