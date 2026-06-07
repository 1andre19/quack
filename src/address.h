#pragma once
#include <ostream>
#include <string>
#include <variant>

// literal string for now
using Address = std::variant<int, std::string>;
inline std::ostream &operator<<(std::ostream &out, const Address &addr) {
    std::visit([&out](const auto &val) { out << val; }, addr);
    return out;
}
