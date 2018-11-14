#include "parser.tab.hpp"
#include "parseresult.h"

int main(int argc, char* argv[]) {
  ParseResult parseResult;
  yy::parser parser(parseResult);
  int parseRes = parser.parse();

  if (parseRes != 0) {
    std::cout << "Parse error: " << parseRes << std::endl;
    return parseRes;
  }

  for (const auto& farg : parseResult.arguments) {
    if (parseResult.vars.find(farg) == parseResult.vars.end()) {
      std::cout << "Uninitialized variable: " << farg << std::endl;
      return 1;
    }
  }

  double fvalue = parseResult.ast->value(parseResult.vars, "").first;

  std::map<std::string, double> grad;
  for (const auto& farg: parseResult.arguments) {
    Dual res = parseResult.ast->value(parseResult.vars, farg);
    grad.insert(std::make_pair(farg, res.second));
  }

  std::cout << "Function value: " << fvalue << std::endl;
  for (const auto& partial: grad) {
    std::cout << "Partial derivative d/d" << partial.first << ": " << partial.second << std::endl;
  }
}
