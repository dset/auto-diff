#pragma once

#include "ast.h"
#include <set>
#include <map>

struct Model {
  std::unique_ptr<Node> ast;
  std::set<std::string> arguments;
  std::map<std::string, double> vars;
};
