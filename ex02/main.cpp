#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include "PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac == 1) {
        return 1;
    }

    PmergeMe pm;

    try {
        std::vector<int> a = pm.parseAndCheckVec(ac, av);
        std::list<int> b = pm.parseAndCheckList(ac, av);

        std::cout << "Before: ";
        for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;

        double tBegVec = pm.getTime();
        a = pm.mergeInsert(a);
        double deltaTVec = pm.getDelta(tBegVec);
        
        double tBegList = pm.getTime();
        pm.mergeInsert(b);
        double deltaTList = pm.getDelta(tBegList);

        std::cout << "After: ";
        for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;

        std::cout << "Time to process " << ac - 1 << " elements with std::vector: " << std::setprecision(5) << deltaTVec << " us" << std::endl;
        std::cout << "Time to process " << ac - 1 << " elements with std::list: " << std::setprecision(5) << deltaTList << " us" << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
