#include "FunctionDirectory.h"

bool FunctionDirectory::add_entry(const std::string &funcName,
                                  const std::vector<FuncParam> &params,
                                  Type return_type) {
    if (directory.find(funcName) != directory.end()) {
        return false;
    }
    // allows us to pass the constructor arguments of a pair
    directory.emplace(funcName,
                      FunctionDirectoryEntry(funcName, params, return_type));
    std::cout << "Function added with name: " + funcName << std::endl;
    return true;
}

FunctionDirectoryEntry *
FunctionDirectory::lookup_entry(const std::string &name) {
    auto it = directory.find(name);
    if (it == directory.end()) {
        return nullptr;
    }
    return &it->second;
}
