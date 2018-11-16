#include "parser.tab.hpp"
#include "model.h"

void optimize(Model& model, int steps, double mom, double lr);
void gdm(Model& model, int steps, double mom, double lr);
std::map<std::string, double> gradient(const Model& model);
void info(const Model& model);

int main(int argc, char* argv[]) {
  Model model;
  yy::parser parser(model);
  int parseRes = parser.parse();

  if (parseRes != 0) {
    std::cerr << "Parse error: " << parseRes << std::endl;
    return parseRes;
  }

  for (const auto& farg : model.arguments) {
    if (model.vars.find(farg) == model.vars.end()) {
      std::cerr << "Uninitialized variable: " << farg << std::endl;
      return 1;
    }
  }

  if (argc == 3 && strcmp(argv[1], "-steps") == 0) {
    if (model.arguments.empty()) {
      std::cerr << "Function is constant" << std::endl;
      return 1;
    }

    int steps = std::stoi(argv[2]);
    optimize(model, steps, 0.9, 0.01);
  } else {
    info(model);
  }

  return 0;
}

void optimize(Model& model, int steps, double mom, double lr) {
  gdm(model, steps, mom, lr);

  double fvalue = model.ast->value(model.vars, "").first;
  std::cout << "Function value: " << fvalue << std::endl;
  for (const auto& var: model.vars) {
    std::cout << var.first << ": " << var.second << std::endl;
  }
}

void gdm(Model& model, int steps, double mom, double lr) {
  std::map<std::string, double> rates;
  for (const auto& arg: model.arguments) {
    rates.insert(std::make_pair(arg, 0.0));
  }

  for (int step = 0; step < steps; step++) {
    std::map<std::string, double> grad = gradient(model);

    for (const auto& partial : grad) {
      rates[partial.first] = mom * rates[partial.first] + lr * partial.second;
      model.vars[partial.first] -= rates[partial.first];
    }
  }
}

std::map<std::string, double> gradient(const Model& model) {
  std::map<std::string, double> grad;
  for (const auto& farg: model.arguments) {
    Dual dual = model.ast->value(model.vars, farg);
    grad.insert(std::make_pair(farg, dual.second));
  }

  return grad;
}

void info(const Model& model) {
  double fvalue = model.ast->value(model.vars, "").first;
  std::map<std::string, double> grad = gradient(model);

  std::cout << "Function value: " << fvalue << std::endl;
  for (const auto& partial: grad) {
    std::cout << "Derivative d/d" << partial.first << ": " << partial.second << std::endl;
  }
}
