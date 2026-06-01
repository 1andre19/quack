#include <stdexcept>
class SemanticError : public std::runtime_error {
  public:
    SemanticError(const std::string &message) : std::runtime_error(message) {}
};
