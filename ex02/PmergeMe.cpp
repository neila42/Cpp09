#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {
	*this = other;
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other){
	if (this != &other) {}
	return (*this);
}

PmergeMe::~PmergeMe() {}

//vecteur
std::vector<int> PmergeMe::mergeInsert(std::vector<int> input) {
    std::vector<std::vector<int> > initialPairs;
    std::vector<std::vector<int> > maxSortedPairs;
    std::vector<int> resultVector;

    bool isOdd = input.size() % 2;
    int lastElement = 0;

    if (isOdd) {
        lastElement = input.back();
        input.pop_back();
    }

    initialPairs = pairing(input);
    maxSortedPairs = sortByMaxVec(sortPairs(initialPairs));

    if (isOdd)
        resultVector = assembleVector(maxSortedPairs, lastElement);
    else
        resultVector = assembleVector(maxSortedPairs);

    return resultVector;
}

std::vector<std::vector<int> > PmergeMe::pairing(std::vector<int> numbers) {
    std::vector<std::vector<int> > pairedGroups;
    std::vector<int> currentPair;

    for (std::vector<int>::size_type i = 0; i < numbers.size(); ++i) {
        currentPair.push_back(numbers[i]);

        // push pair to grouped pairs if complete or if last element
        if (currentPair.size() == 2 || (i == numbers.size() - 1)) {
            pairedGroups.push_back(currentPair);
            currentPair.clear();
        }
    }
    return pairedGroups;
}

std::vector<std::vector<int> > PmergeMe::sortPairs(std::vector<std::vector<int> > pairs) {
    for (std::vector<std::vector<int> >::size_type i = 0; i < pairs.size(); ++i) {
        // is pair complete/needs to be sorted?
        if (pairs[i].size() == 2 && pairs[i][0] > pairs[i][1]) {
            int temp = pairs[i][0];
            pairs[i][0] = pairs[i][1];
            pairs[i][1] = temp;
        }
    }
    return pairs;
}

std::vector<std::vector<int> > PmergeMe::sortByMaxVec(std::vector<std::vector<int> > pairs) {
    for (std::vector<std::vector<int> >::size_type i = 0; i < pairs.size(); ++i) {
        for (std::vector<std::vector<int> >::size_type j = i + 1; j < pairs.size(); ++j) {
            // Swap pairs if second element of jpair is less than ipair
            if (pairs[j][1] < pairs[i][1]) {
                std::vector<int> temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return pairs;
}

std::vector<int>::iterator	PmergeMe::insertPoint(std::vector<int>& input, int value) {
	for (unsigned int i = 0; i < input.size(); i++) {
		if (input[i] > value)
			return (input.begin() + i);
	}
	return (input.end());
}

std::vector<int> PmergeMe::assembleVector(std::vector<std::vector<int> > pairs, int lastItem) {
    std::vector<int> assembled;
    std::vector<int> leadingElements;
    std::vector<int> jacobSequence;

    // Build initial sequences from pairs
    for (size_t i = 0; i < pairs.size(); ++i) {
        assembled.push_back(pairs[i][1]);
        leadingElements.push_back(pairs[i][0]);
    }
    // Place first leading element at the beginning
    assembled.insert(assembled.begin(), leadingElements[0]);
    leadingElements.erase(leadingElements.begin());
    // Calculate Jacob sequence for insertion positions
    jacobSequence = PmergeMe::jacobInsertionSequence(leadingElements);

    size_t insertIndex = 1;
    std::vector<int> insertionOrder;
    std::string status = "default";
    int currentElement;

    while (insertIndex <= leadingElements.size()) {
        if (!jacobSequence.empty() && status != "jacob") {
            insertionOrder.push_back(jacobSequence[0]);
            currentElement = leadingElements[jacobSequence[0] - 1];
            jacobSequence.erase(jacobSequence.begin());
            status = "jacob";
        } else {
            if (std::find(insertionOrder.begin(), insertionOrder.end(), insertIndex) != insertionOrder.end())
                ++insertIndex;
            currentElement = leadingElements[insertIndex - 1];
            insertionOrder.push_back(insertIndex);
            status = "standard";
        }
        std::vector<int>::iterator insertPos = PmergeMe::insertPoint(assembled, currentElement);
        assembled.insert(insertPos, currentElement);
        ++insertIndex;
    }

    // Insert last item in correct position
    std::vector<int>::iterator finalPos = PmergeMe::insertPoint(assembled, lastItem);
    assembled.insert(finalPos, lastItem);
    return assembled;
}

std::vector<int> PmergeMe::assembleVector(std::vector<std::vector<int> > pairGroups) {
    std::vector<int> resultVector;
    std::vector<int> pendingValues;
    std::vector<int> specialSequence;

    // Initial size of resultVector and pendingValues from pairGroups
    for (size_t i = 0; i < pairGroups.size(); ++i) {
        resultVector.push_back(pairGroups[i][1]);
        pendingValues.push_back(pairGroups[i][0]);
    }

    // Move the first pending value to the start of the resultVector
    resultVector.insert(resultVector.begin(), pendingValues[0]);
    pendingValues.erase(pendingValues.begin());

    specialSequence = jacobInsertionSequence(pendingValues);

    size_t index = 1;
    std::vector<int> insertionIndexes;
    std::string mode = "default";
    int currentValue;
    std::vector<int>::iterator insertPoint;

    while (index <= pendingValues.size()) {
        if (!specialSequence.empty() && mode != "jacob") {
            insertionIndexes.push_back(specialSequence[0]);
            currentValue = pendingValues[specialSequence[0] - 1];
            specialSequence.erase(specialSequence.begin());
            mode = "jacob";
        } else {
            if (std::find(insertionIndexes.begin(), insertionIndexes.end(), index) != insertionIndexes.end())
                ++index;
            currentValue = pendingValues[index - 1];
            insertionIndexes.push_back(index);
            mode = "standard";
        }
        insertPoint = this->insertPoint(resultVector, currentValue);
        resultVector.insert(insertPoint, currentValue);
        ++index;
    }

    return resultVector;
}

//list
void PmergeMe::mergeInsert(std::list<int> input) {
    std::list<std::vector<int> > initialGrouped;
    std::list<std::vector<int> > maxSortedGrouped;
    std::list<int> finalList;

    bool isListOdd = input.size() % 2;
    int tailElement = 0;

    if (isListOdd) {
        tailElement = input.back();
        input.pop_back();
    }

    initialGrouped = pairing(input);
    maxSortedGrouped = sortPairs(initialGrouped);
    maxSortedGrouped.sort(sortByMaxList);

    if (isListOdd) {
        finalList = assembleList(maxSortedGrouped, tailElement);
    } else {
        finalList = assembleList(maxSortedGrouped);
    }
}

std::list<std::vector<int> > PmergeMe::pairing(std::list<int> numbers) {
    std::list<std::vector<int> > pairedGroups;
    std::vector<int> currentPair;

    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        currentPair.push_back(*it);

        // If pair complete or if last element add to pair grps
        if (currentPair.size() == 2 || (std::distance(it, numbers.end()) == 1)) {
            pairedGroups.push_back(currentPair);
            currentPair.clear();
        }
    }
    return pairedGroups;
}

std::list<std::vector<int> > PmergeMe::sortPairs(std::list<std::vector<int> > pairsList) {
    for (std::list<std::vector<int> >::iterator it = pairsList.begin(); it != pairsList.end(); ++it) {
        // is pair complete and first element is > than second?alors tri
        if (it->size() == 2 && (*it)[0] > (*it)[1]) {
            int swapTemp = (*it)[0];
            (*it)[0] = (*it)[1];
            (*it)[1] = swapTemp;
        }
    }
    return pairsList;
}

bool	sortByMaxList(const std::vector<int>& first, const std::vector<int>& second) {
	if (first[1] < second[1])
		return (true);
	return (false);
}

std::list<int> PmergeMe::assembleList(std::list<std::vector<int> > pairGroups, int extraValue) {
    std::list<int> resultList;
    std::vector<int> pendingInserts;
    std::vector<int> specialSequence;

    for (std::list<std::vector<int> >::iterator it = pairGroups.begin(); it != pairGroups.end(); ++it) {
        resultList.push_back((*it)[1]);
        pendingInserts.push_back((*it)[0]);
    }
    resultList.insert(resultList.begin(), pendingInserts[0]);
    pendingInserts.erase(pendingInserts.begin());
    specialSequence = jacobInsertionSequence(pendingInserts);

    size_t index = 1;
    std::vector<int> insertionIndexes;
    std::string insertionMode = "default";
    int currentItem;
    std::list<int>::iterator insertPointIter;

    while (index <= pendingInserts.size()) {
        if (!specialSequence.empty() && insertionMode != "jacob") {
            insertionIndexes.push_back(specialSequence[0]);
            currentItem = pendingInserts[specialSequence[0] - 1];
            specialSequence.erase(specialSequence.begin());
            insertionMode = "jacob";
        } else {
            if (std::find(insertionIndexes.begin(), insertionIndexes.end(), index) != insertionIndexes.end()) {
                ++index;
                continue;
            }
            currentItem = pendingInserts[index - 1];
            insertionIndexes.push_back(index);
            insertionMode = "standard";
        }
        insertPointIter = insertPoint(resultList, currentItem);
        resultList.insert(insertPointIter, currentItem);
        ++index;
    }

    insertPointIter = insertPoint(resultList, extraValue);
    resultList.insert(insertPointIter, extraValue);
    return resultList;
}

std::list<int> PmergeMe::assembleList(std::list<std::vector<int> > pairGroups) {
    std::list<int> resultList;
    std::vector<int> pendingInsertions;
    std::vector<int> specialInsertionSequence;

    // meme comm que pour vecteur 
    for (std::list<std::vector<int> >::iterator it = pairGroups.begin(); it != pairGroups.end(); ++it) {
        resultList.push_back((*it)[1]);
        pendingInsertions.push_back((*it)[0]);
    }

    resultList.insert(resultList.begin(), pendingInsertions[0]);
    pendingInsertions.erase(pendingInsertions.begin());
    specialInsertionSequence = jacobInsertionSequence(pendingInsertions);

    size_t currentIndex = 1;
    std::vector<int> insertionIndices;
    std::string insertionMode = "default";
    int currentValue;
    std::list<int>::iterator targetInsertionPoint;

    while (currentIndex <= pendingInsertions.size()) {
        if (!specialInsertionSequence.empty() && insertionMode != "jacob") {
            insertionIndices.push_back(specialInsertionSequence[0]);
            currentValue = pendingInsertions[specialInsertionSequence[0] - 1];
            specialInsertionSequence.erase(specialInsertionSequence.begin());
            insertionMode = "jacob";
        } else {
            if (std::find(insertionIndices.begin(), insertionIndices.end(), currentIndex) != insertionIndices.end()) {
                ++currentIndex;
                continue;
            }
            currentValue = pendingInsertions[currentIndex - 1];
            insertionIndices.push_back(currentIndex);
            insertionMode = "standard";
        }
        targetInsertionPoint = insertPoint(resultList, currentValue);
        resultList.insert(targetInsertionPoint, currentValue);
        ++currentIndex;
    }

    return resultList;
}

std::list<int>::iterator	PmergeMe::insertPoint(std::list<int>& input, int value) {
	for (std::list<int>::iterator it = input.begin(); it != input.end(); it++) {
		if ((*it) > value)
			return (it);
	}
	return (input.end());
}

//util
double	PmergeMe::getTime() {
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

double	PmergeMe::getDelta(double time) {
	return (PmergeMe::getTime() - time);
}

std::vector<int> PmergeMe::parseAndCheckVec(int argc, char** argv) {
    std::vector<int> args;
    std::set<int> seen;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        int val = std::atoi(arg.c_str());

        // pas neg
        if (val < 0) {
            throw PmergeMe::InvalidArgument();
        }

        // pas dup
        if (!seen.insert(val).second) {
            throw PmergeMe::DuplicateException();
        }

        args.push_back(val);
    }

    return args;
}

std::list<int> PmergeMe::parseAndCheckList(int argc, char** argv) {
    std::list<int> args;
    std::set<int> seen;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        int val = std::atoi(arg.c_str());

        // pas neg
        if (val < 0) {
            throw PmergeMe::InvalidArgument();
        }

        // pas dup
        if (!seen.insert(val).second) {
            throw PmergeMe::DuplicateException();
        }

        args.push_back(val);
    }

    return args;
}

int	PmergeMe::jacobSequence(int i) {
	if (i == 0)
		return (0);
	if (i == 1)
		return (1);
	return (PmergeMe::jacobSequence(i - 1) + 2 * PmergeMe::jacobSequence(i - 2));
}

std::vector<int> PmergeMe::jacobInsertionSequence(std::vector<int> pendingValues) {
    int sequenceLength = static_cast<int>(pendingValues.size());
    std::vector<int> insertionIndices;
    int sequenceIndex = 3; // Starting index for Jacob sequence calculations
    while (jacobSequence(sequenceIndex) < sequenceLength - 1) {
        insertionIndices.push_back(jacobSequence(sequenceIndex));
        sequenceIndex++;
    }
    return insertionIndices;
}

