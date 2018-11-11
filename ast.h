#include <iostream>
#include <cmath>

class Node {
public:
  virtual ~Node() = default;
  virtual double value() const = 0;
};

class Scalar: public Node {
private:
  int scalar;
public:
  Scalar(int scalar): scalar(scalar) {}

  double value() const override { return static_cast<double>(scalar); }
};

class Variable: public Node {
private:
  std::string name;
public:
  Variable(std::string name): name(name) {}

  double value() const override { return 0; }
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

  double value() const override { return left->value() + right->value(); }
};

class Sub: public BinaryOp {
public:
  Sub(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value() const override { return left->value() - right->value(); }
};

class Mul: public BinaryOp {
public:
  Mul(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value() const override { return left->value() * right->value(); }
};

class Div: public BinaryOp {
public:
  Div(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value() const override { return left->value() / right->value(); }
};

class Pow: public BinaryOp {
public:
  Pow(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : BinaryOp(std::move(left), std::move(right)) {}

  double value() const override { return std::pow(left->value(), right->value()); }
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

  double value() const override { return std::sin(child->value()); }
};

class Cos: public UnaryOp {
public:
  Cos(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  double value() const override { return std::cos(child->value()); }
};

class Exp: public UnaryOp {
public:
  Exp(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  double value() const override { return std::exp(child->value()); }
};

class NatLog: public UnaryOp {
public:
  NatLog(std::unique_ptr<Node> child): UnaryOp(std::move(child)) {}

  double value() const override { return std::log(child->value()); }
};
