#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <sys/time.h>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    std::vector<int> mergeInsert(std::vector<int> numbers);
    void mergeInsert(std::list<int> numbers);
    double getTime();
    double getDelta(double Time);
    std::vector<int> parseAndCheckVec(int argc, char** argv);
    std::list<int> parseAndCheckList(int argc, char** argv);

    class InvalidArgument : public std::exception
    {
    public:
        const char *what() const throw() { return "Error. Invalid argument."; }
    };

    class DuplicateException : public std::exception
    {
    public:
        const char *what() const throw() { return "Error. Duplicate value in arguments."; }
    };

private:
    //utils
    std::vector<std::vector<int> > pairing(std::vector<int> numbers);
    std::list<std::vector<int> > pairing(std::list<int> numbers);
    std::vector<std::vector<int> > sortPairs(std::vector<std::vector<int> > pairs);
    std::list<std::vector<int> > sortPairs(std::list<std::vector<int> > pairs);
    std::vector<std::vector<int> > sortByMaxVec(std::vector<std::vector<int> > sortedPairs);
    int jacobSequence(int n);
    std::vector<int> jacobInsertionSequence(std::vector<int> pendingNumbers);
    std::vector<int>::iterator insertPoint(std::vector<int>& numbers, int value);
    std::list<int>::iterator insertPoint(std::list<int>& numbers, int value);
    std::vector<int> assembleVector(std::vector<std::vector<int> > sortedPairs, int extra);
    std::list<int> assembleList(std::list<std::vector<int> > sortedPairs, int extra);
    std::vector<int> assembleVector(std::vector<std::vector<int> > sortedPairs);
    std::list<int> assembleList(std::list<std::vector<int> > sortedPairs);
};

bool sortByMaxList(const std::vector<int>& firstPair, const std::vector<int>& secondPair);

#endif
