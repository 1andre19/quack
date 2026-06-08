#include "FunctionDirectory.h"

bool FunctionDirectory::add_entry(const std::string &funcName,
                                  const std::vector<FuncParam> &params,
                                  func_resources resources, Type return_type,
                                  int start_quad) {
    if (directory.find(funcName) != directory.end()) {
        return false;
    }
    // allows us to pass the constructor arguments of a pair
    directory.emplace(funcName,
                      FunctionDirectoryEntry(funcName, params, resources,
                                             return_type, start_quad));
    // std::cout << "Function added with name: " + funcName << std::endl;
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

void FunctionDirectoryEntry::print_resources() {
    std::cout << "function " << name << " resources" << std::endl;
    std::cout << "local integers: " << std::to_string(resources.local_int)
              << std::endl;
    std::cout << "local floats: " << std::to_string(resources.local_float)
              << std::endl;
    std::cout << "local strs: " << std::to_string(resources.local_string)
              << std::endl;
    std::cout << "temp int: " << std::to_string(resources.temp_int)
              << std::endl;
    std::cout << "temp float: " << std::to_string(resources.temp_float)
              << std::endl;
    std::cout << "temp str: " << std::to_string(resources.temp_str)
              << std::endl;
    std::cout << "entry quad: " << std::to_string(start_quad) << std::endl;
}
