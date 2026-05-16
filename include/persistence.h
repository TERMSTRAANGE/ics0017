#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>

namespace Persistence {
    void save_funds(int funds, const std::string& filename);
    int load_funds(const std::string& filename);
}

#endif
