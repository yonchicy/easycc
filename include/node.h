#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
class Node;
class NStatement ;
class NExpression ;
class NIdentifier ;
class NUnary ;
class NFunctionDeclaration ;
class NType ;
class NProgram ;
class NMultiplicative ;
class NAdditive ;
class NPrimary ;
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
class NProgram:public Node{
    public:
        const NFunctionDeclaration& FuncDeclaration;
        explicit NProgram(const NFunctionDeclaration& _FuncDeclaration):
            FuncDeclaration(_FuncDeclaration){
        };
        void *gen()const  override;
};
class NFunctionDeclaration : public Node {
public:
  const NType &type;
  const std::string id;
  const Node &statement;
  NFunctionDeclaration(const NType &_type, std::string _id,const Node& _statement):
            type(_type),
            id(std::move(_id)) ,
            statement(_statement){}
  void *gen()const  override;
};

class NType : public Node {
public:
  std::string name;
  explicit NType(std::string  _name) :
      name{std::move(_name)} {}
  void *gen() const override;
};

class NStatement : public Node{
    public:
        void*gen() const override{return nullptr; }
};
class NReturnStatement:public NStatement{
    public:
        const NExpression &expr;
        explicit NReturnStatement(const NExpression& _expr):
            expr(_expr){}
        void *gen()const  override;
        
};

class NMultiplicative :public Node{
    public:
  void *gen() const override{return nullptr;}
};
class NMultiplicativeUnary:public NMultiplicative{
public :
  const NUnary &unary;
  NMultiplicativeUnary(const NUnary&_unary):unary(_unary){}
  void *gen()const  override;

};
class NMultiplicativeOprtUnary:public NMultiplicative{
public  :
  const NMultiplicative & left;
  const std::string oprt;
  const NUnary &unary;
  explicit NMultiplicativeOprtUnary(const NMultiplicative &_left,
                                    std::string _oprt,
                                    const NUnary &_unary):
      left(_left),oprt(std::move(_oprt)) ,unary(_unary){}
  void *gen()const  override;
};


// ADDTITIVE

class NAdditive :public Node{
    public :
        void* gen()const override{return nullptr;};
};

class NAdditiveMultipicative:public NAdditive{
public:
  const NMultiplicative& multiplicative;
  explicit NAdditiveMultipicative(const NMultiplicative & _multiplicative):
      multiplicative(_multiplicative){};
  void*gen()const override;
};
class NAddtiveOprtMulti : public NAdditive{
    public:
        const NAdditive & additive;
        const std::string oprt;
        const NMultiplicative multiplicate;
        NAddtiveOprtMulti(
            const NAdditive & _additive,
            const std::string _oprt,
            const NMultiplicative _multiplicate
                    ):
                additive(_additive),
                oprt(std::move(_oprt)),
                multiplicate(_multiplicate){}
        void*gen()const override;
};

class NExpression : public Node{
    public:
        void*gen()const override{return nullptr;}
};
class NExpressionAdditive : public NExpression{
    public:
    const NAdditive & additive;
    explicit NExpressionAdditive(const NAdditive &_additive):
        additive(_additive){};
    void * gen()const override;
};
class NPrimary :public Node{
public:
  void* gen()const override{return nullptr;};
};
//class NUnaryBase : public Node{
//    public:
//    void *gen() const override {return nullptr;}
//};

class NUnary : public Node {
public:
    void *gen() const override {return nullptr;};
};
class NUnaryPrimary:public NUnary{
public :
  const NPrimary & primary;
    NUnaryPrimary(const NPrimary & _primary):primary(_primary){}
    void *gen() const override ;
};

class NUnaryWithOperator:public NUnary{
    public:
  const std::string oprt;
  const NUnary& unary;
  NUnaryWithOperator(std::string  _oprt,const NUnary& _unary):
  oprt(std::move(_oprt)),unary(_unary){};
  void* gen()const override;
};
class NInteger : public NPrimary {
public:
  long long value;
  NInteger(long long _value) :
      value(_value)
    {};
  void *gen()const override;
};
class NPrimaryExpression : public NPrimary {
public:
  const NExpression& exp;
  explicit NPrimaryExpression(const NExpression & _exp):exp(_exp){}
  void*gen()const override;
};


class NIdentifier : public Node {
public:
  std::string name;
  NIdentifier(const std::string _name) :
      name(std::move(_name)) {
  }
};


