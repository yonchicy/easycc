#include <iostream>
#include <vector>
class Node;
class NStatement ;
class NExpression ;
class NIdentifier ;
class NFunctionDeclaration ;
class NType ;
class NProgram ;
class Node {
public:
    Node()=default;
    Node(Node &&) = default;
    Node(const Node &) = default;
    Node &operator=(Node &&) = default;
    Node &operator=(const Node &) = default;
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

class NReturnStatement:public NStatement{
    public:
        const NExpression &expr;
        NReturnStatement(const NExpression& _expr):expr(_expr){}
};
class NFunctionDeclaration : public NStatement {
public:
  const NType &type;
  const std::string id;
  const NStatement &statement;
  NFunctionDeclaration(const NType &_type, const std::string &_id,const NStatement& _statement)
      : type(_type), id(_id) ,statement(_statement){}
};
class NProgram:public NStatement{
    public:
        const NFunctionDeclaration& FuncDeclaration;
        NProgram(const NFunctionDeclaration& _FuncDeclaration):FuncDeclaration(_FuncDeclaration){
            std::cout<<"get a program"<<std::endl;
        }
};
