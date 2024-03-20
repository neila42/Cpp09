#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string dbFilename = "data.csv";
    std::map<std::string, float> rates = readExchangeRates(dbFilename);
    processInputFile(inputFilename, rates);

    return 0;
}

// Vérifie les arguments du programme
// Lit les taux de change avec `readExchangeRates`
// Traite le fichier d'entrée avec `processInputFile`