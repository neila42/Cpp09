#ifndef BTC_HPP
#define BTC_HPP

#include <string>
#include <map>

// taux de change
struct ExchangeRate {
    std::string date;
    float rate;
};

std::map<std::string, float> readExchangeRates(const std::string& filename);
float findClosestRate(const std::map<std::string, float>& rates, const std::string& date);
void processInputFile(const std::string& filename, const std::map<std::string, float>& rates);

#endif
