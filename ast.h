#pragma once

#include <iostream>
#include <cmath>
#include <map>

using Variables = std::map<std::string, double>;

class Node {
public:
  virtual ~Node() = default;
  virtual double value(const Variables& vars) const = 0;
};

class Scalar: public Node {
private:
  double scalar;
public:
  Scalar(double scalar): scalar(scalar) {}

  double value(const Variables& vars) const override {
    return scalar;
  }
};

class Variable: public Node {
private:
  std::string name;
public:
  Variable(std::string name): name(name) {}

  double value(const Variables& vars) const override {
    return vars.at(name);
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

  double value(const Variables& vars) const override {
    return left->value(vars) + right->value(vars);
  }
};

class Sub: public BinaryOp {
public:
  Sub(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value(const Variables& vars) const override {
    return left->value(vars) - right->value(vars);
  }
};

class Mul: public BinaryOp {
public:
  Mul(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value(const Variables& vars) const override {
    return left->value(vars) * right->value(vars);
  }
};

class Div: public BinaryOp {
public:
  Div(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value(const Variables& vars) const override {
    return left->value(vars) / right->value(vars);
  }
};

class Pow: public BinaryOp {
public:
  Pow(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value(const Variables& vars) const override {
    return std::pow(left->value(vars), right->value(vars));
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

  double value(const Variables& vars) const override {
    return std::sin(child->value(vars));
  }
};

class Cos: public UnaryOp {
public:
  Cos(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  double value(const Variables& vars) const override {
    return std::cos(child->value(vars));
  }
};

class Exp: public UnaryOp {
public:
  Exp(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  double value(const Variables& vars) const override {
    return std::exp(child->value(vars));
  }
};

class NatLog: public UnaryOp {
public:
  NatLog(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  double value(const Variables& vars) const override {
    return std::log(child->value(vars));
  }
};
