#pragma once

#include "ast.h"
#include <map>

struct ParseResult {
  std::unique_ptr<Node> ast;
  std::map<std::string, double> vars;
};
