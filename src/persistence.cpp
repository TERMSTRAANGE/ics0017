#include <persistence.h>
#include <exceptions.h>
#include <fstream>
#include <string>

namespace Persistence {
    void save_funds(int funds, const std::string& filename) {
        std::ofstream file(filename, std::ios::out);
        if (!file.is_open()) {
            throw FileOpenError();
        }
        file << funds << std::endl;
    }
    int load_funds(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw FileOpenError();
        }
        std::string line;
        getline(file, line);
        int funds;
        try {
            funds = std::stoi(line);
        }
        catch (const std::invalid_argument&) {
            throw InvalidFileFormat();
        }
        return funds;
    }
}