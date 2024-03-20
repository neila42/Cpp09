#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

// string cle date/ float valeur taux de change
std::map<std::string, float> readExchangeRates(const std::string& filename) {
    std::map<std::string, float> rates;
    std::ifstream file(filename);
    std::string line, date; 
    float rate;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line); //flux d'entree parsing auto int float espace
        std::getline(iss, date, ',');
        iss >> rate;
        rates[date] = rate;
    }

    return rates;
}

float findClosestRate(const std::map<std::string, float>& rates, const std::string& date) {
    std::map<std::string, float>::const_iterator it = rates.lower_bound(date); //pr trouver it
    if (it == rates.begin()) return it->second;
    if (it == rates.end() || it->first != date) --it;
    return it->second;
}

void processInputFile(const std::string& filename, const std::map<std::string, float>& rates) {
    std::ifstream file(filename);
    std::string line, date;
    float value;

    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!std::getline(iss, date, '|') || !(iss >> value) || value < 0 || value > 1000) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        float rate = findClosestRate(rates, date);
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}

