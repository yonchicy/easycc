#include <iostream>
#include <vector>
class Node {
public:
  Node();
  Node(Node &&) = default;
  Node(const Node &) = default;
  Node &operator=(Node &&) = default;
  Node &operator=(const Node &) = default;
  virtual ~Node();
};

class NStatement : public Node {};

class NExpression : public Node {};
class NInteger : public NExpression {
public:
  long long value;
  NInteger(long long _value) : value{_value} {}
};

class NIdentifier : public NExpression {
public:
  std::string name;
  NIdentifier(const std::string _name) : name{_name} {
  }
};

class NType : public NExpression {
public:
  std::string name;
  NType(const std::string _name) : name{_name} {}
};

class NFunctionDeclaration : public NStatement {
public:
  const NType &type;
  const NIdentifier &id;
  const NStatement &statement;
  NFunctionDeclaration(const NIdentifier &_type, const NIdentifier &_id,const NStatement& _statement)
      : type(_type), id(_id) ,statement(_statement){}
};
