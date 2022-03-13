#include <cstddef>
#include <iostream>
#include <vector>
class Node;
class NStatement ;
class NExpression ;
class NIdentifier ;
class NUnary ;
class NUnaryBase ;
class NFunctionDeclaration ;
class NType ;
class NProgram ;
enum class NodeClass {
    NProgram,
    NFunctionDeclaration,
    NReturnStatement,
    NInteger,
    NType,
    NUnary,

};
class Node {
public:
    Node()=default;
    Node(Node &&) = default;
    Node(const Node &) = default;
    Node &operator=(Node &&) = default;
    Node &operator=(const Node &) = default;
    virtual void* gen()const=0;

};
class NUnaryBase : public Node{
    public:
    void *gen() const override {return nullptr;}
};
class NUnary : public NUnaryBase {
public:
    std::string _operator;
    const NUnaryBase& unary;
    NUnary(const std::string __operator,const NUnaryBase& _unary):
        _operator(__operator),
        unary(_unary)
    {}

    void *gen() const override ;

};
class NExpression : public Node{
    public:
    const NUnaryBase& unary;
    NExpression(NUnaryBase& _unary):unary(_unary){}
    void *gen() const override;
};

class NInteger : public NUnaryBase {
public:
  long long value;
  NInteger(long long _value) :
      value(_value)
    {};
  void *gen()const override;
};


class NIdentifier : public Node {
public:
  std::string name;
  NIdentifier(const std::string _name) :
      name(_name) {
  }
};

class NType : public Node {
public:
  std::string name;
  NType(const std::string _name) :
      name{_name} {}
  void *gen() const override;
};

class NStatement : public Node{
    public:
        void*gen() const override{return nullptr; }
};
class NReturnStatement:public NStatement{
    public:
        const NExpression &expr;
        NReturnStatement(const NExpression& _expr):
            expr(_expr){}
        void *gen()const  override;
        
};
class NFunctionDeclaration : public Node {
public:
  const NType &type;
  const std::string id;
  const Node &statement;
  NFunctionDeclaration(const NType &_type, const std::string &_id,const Node& _statement):
            type(_type),
            id(_id) ,
            statement(_statement){}
  void *gen()const  override;
};
class NProgram:public Node{
    public:
        const NFunctionDeclaration& FuncDeclaration;
        NProgram(const NFunctionDeclaration& _FuncDeclaration):
            FuncDeclaration(_FuncDeclaration){
        };
        void *gen()const  override;
};
