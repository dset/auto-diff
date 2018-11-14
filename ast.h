#pragma once

#include <iostream>
#include <cmath>
#include <map>

using Variables = std::map<std::string, double>;
using Dual = std::pair<double, double>;

class Node {
 public:
  virtual ~Node() = default;
  virtual Dual value(const Variables& vars, const std::string& d) const = 0;
};

class Scalar: public Node {
 private:
  double scalar;
 public:
 Scalar(double scalar): scalar(scalar) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    return std::make_pair(scalar, 0.0);
  }
};

class Variable: public Node {
 private:
  std::string name;
 public:
 Variable(std::string name): name(name) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    double e = name == d ? 1.0 : 0.0;
    return std::make_pair(vars.at(name), e);
  }
};

class BinaryOp: public Node {
 protected:
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
 public:
 BinaryOp(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
   : left(std::move(left)), right(std::move(right)) {}
};

class Add: public BinaryOp {
 public:
 Add(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
   : BinaryOp(std::move(left), std::move(right)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual l = left->value(vars, d);
    Dual r = right->value(vars, d);
    return std::make_pair(l.first + r.first, l.second + r.second);
  }
};

class Sub: public BinaryOp {
 public:
 Sub(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
   : BinaryOp(std::move(left), std::move(right)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual l = left->value(vars, d);
    Dual r = right->value(vars, d);
    return std::make_pair(l.first - r.first, l.second - r.second);
  }
};

class Mul: public BinaryOp {
 public:
 Mul(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
   : BinaryOp(std::move(left), std::move(right)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual l = left->value(vars, d);
    Dual r = right->value(vars, d);
    return std::make_pair(l.first * r.first, l.second * r.first + l.first * r.second);
  }
};

class Div: public BinaryOp {
 public:
 Div(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
   : BinaryOp(std::move(left), std::move(right)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual l = left->value(vars, d);
    Dual r = right->value(vars, d);
    return std::make_pair(l.first / r.first, (l.second * r.first - l.first * r.second) / (r.first * r.first));
  }
};

class Pow: public Node {
 private:
  std::unique_ptr<Node> child;
  double scalar;
 public:
 Pow(std::unique_ptr<Node> child, double scalar): child(std::move(child)), scalar(scalar) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual c = child->value(vars, d);
    return std::make_pair(std::pow(c.first, scalar), scalar * std::pow(c.first, scalar - 1) * c.second);
  }
};

class UnaryOp: public Node {
 protected:
  std::unique_ptr<Node> child;
 public:
 UnaryOp(std::unique_ptr<Node> child): child(std::move(child)) {}
};

class Sin: public UnaryOp {
 public:
 Sin(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual c = child->value(vars, d);
    return std::make_pair(std::sin(c.first), c.second * std::cos(c.first));
  }
};

class Cos: public UnaryOp {
 public:
 Cos(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual c = child->value(vars, d);
    return std::make_pair(std::cos(c.first), - c.second * std::sin(c.first));
  }
};

class Exp: public UnaryOp {
 public:
 Exp(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual c = child->value(vars, d);
    return std::make_pair(std::exp(c.first), c.second * std::exp(c.first));
  }
};

class NatLog: public UnaryOp {
 public:
 NatLog(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  Dual value(const Variables& vars, const std::string& d) const override {
    Dual c = child->value(vars, d);
    return std::make_pair(std::log(c.first), c.second / c.first);
  }
};
