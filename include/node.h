#ifndef _NODE_H_
#define _NODE_H_
#include "error.h"
#include "runtime.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
class Node;
class NStatements;
class NStatement;
class NDeclaration;
class NExpression;
class NAssign;
class NIdentifier;
class NUnary;
class NFunctionDeclaration;
class NType;
class NProgram;
class NMultiplicative;
class NAdditive;
class NPrimary;
class NLogicalOr;
class NLogicalAnd;
class NEquality;
class NRelational;

class Node {
public:
  Node() = default;
  Node(Node &&) = default;
  Node(const Node &) = default;
  Node &operator=(Node &&) = default;
  Node &operator=(const Node &) = default;
  virtual void gen() const = 0;
  virtual void show_ast() const = 0;
};
class NProgram : public Node {
public:
  const NFunctionDeclaration &FuncDeclaration;
  explicit NProgram(const NFunctionDeclaration &FuncDeclaration)
      : FuncDeclaration(FuncDeclaration){};
  void gen() const override;
  void show_ast() const override;
};
class NFunctionDeclaration : public Node {
public:
  const NType &type;
  const std::string id;
  const NStatements *statements;
  NFunctionDeclaration(const NType &_type, std::string _id,
                       const NStatements *_statements)
      : type(_type), id((std::move(_id))), statements(_statements) {}
  void gen() const override;
  void show_ast() const override;
};

class NType : public Node {
public:
  std::string name;
  explicit NType(std::string _name) : name{(_name)} {}
  void gen() const override;
  void show_ast() const override;
};
// statemets node
class NStatements : public Node {
public:
  std::vector<NStatement *> stmts;
  void gen() const override;
  void show_ast() const override;
};
// statement
class NStatement : public Node {};
class NReturnStatement : public NStatement {
public:
  const NExpression &expr;
  explicit NReturnStatement(const NExpression &_expr) : expr(_expr) {}

  void gen() const override;
  void show_ast() const override;
};
class NStatementNull : public NStatement {
public:
  NStatementNull() = default;
  void gen() const override;
  void show_ast() const override;
};

class NStatementExpr : public NStatement {
public:
  const NExpression *expr;
  explicit NStatementExpr(const NExpression *_expr) : expr(_expr) {}

  void gen() const override;
  void show_ast() const override;
};
class NStatementDeclaration : public NStatement {
public:
  const NDeclaration *const declaration;
  explicit NStatementDeclaration(const NDeclaration *const declaration)
      : declaration(declaration) {}
  void gen() const override;
  void show_ast() const override;
};

// declaration
class NDeclaration : public Node {};
class NDeclarationWithAssign : public NDeclaration {
public:
  std::string id;
  const NExpression *const expr;
  NDeclarationWithAssign(std::string id, const NExpression *const expr)
      : id(id), expr(expr) {}
  void gen() const override;
  void show_ast() const override;
};
// multiplicative
class NMultiplicative : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};
class NMultiplicativeUnary : public NMultiplicative {
public:
  const NUnary &unary;
  NMultiplicativeUnary(const NUnary &_unary) : unary(_unary) {}
  void gen() const override;
  void show_ast() const override;
};
class NMultiplicativeOprtUnary : public NMultiplicative {
public:
  const NMultiplicative &left;
  const std::string oprt;
  const NUnary &unary;
  explicit NMultiplicativeOprtUnary(const NMultiplicative &_left,
                                    std::string _oprt, const NUnary &_unary)
      : left(_left), oprt((_oprt)), unary(_unary) {}
  void gen() const override;
  void show_ast() const override;
};

// ADDTITIVE

class NAdditive : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};

class NAdditiveMultipicative : public NAdditive {
public:
  const NMultiplicative &multiplicative;
  explicit NAdditiveMultipicative(const NMultiplicative &_multiplicative)
      : multiplicative(_multiplicative){};
  void gen() const override;
  void show_ast() const override;
};
class NAddtiveOprtMulti : public NAdditive {
public:
  const NAdditive &additive;
  const std::string oprt;
  const NMultiplicative *multiplicate;
  NAddtiveOprtMulti(const NAdditive &_additive, const std::string _oprt,
                    const NMultiplicative *_multiplicate)
      : additive(_additive), oprt((_oprt)), multiplicate(_multiplicate) {}
  void gen() const override;
  void show_ast() const override;
};
// exprsssion
class NExpression : public Node {
public:
  void gen() const override {}
  void show_ast() const override{};
};
class NExpressionAssign : public NExpression {
public:
  const NAssign *const assignment;
  NExpressionAssign(const NAssign *const assignment) : assignment(assignment) {}
  void gen() const override;
  void show_ast() const override;
};
// assign
class NAssign : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};

class NAssignLogicOr : public NAssign {
public:
  const NLogicalOr *const logical_or;
  explicit NAssignLogicOr(const NLogicalOr *const _logical_or)
      : logical_or(_logical_or){};
  void gen() const override;
  void show_ast() const override;
};
class NAssignAssign : public NAssign {
public:
  std::string id;
  const NExpression *const expr;
  explicit NAssignAssign(std::string &id, const NExpression *const expr)
      : id(id), expr(expr){};
  void gen() const override;
  void show_ast() const override;
};
// logical_or
class NLogicalOr : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};
class NLogicalOrAnd : public NLogicalOr {
public:
  const NLogicalAnd *const logical_and;
  explicit NLogicalOrAnd(const NLogicalAnd *const _logical_and)
      : logical_and(_logical_and){};
  void gen() const override;
  void show_ast() const override;
};
class NLogicalORBinary : public NLogicalOr {
public:
  const NLogicalOr *const l;
  const NLogicalAnd *const r;
  explicit NLogicalORBinary(const NLogicalOr *const _l,
                            const NLogicalAnd *const _r)
      : l(_l), r(_r){};
  void gen() const override;
  void show_ast() const override;
};
// logical_and
class NLogicalAnd : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};
class NLogicalAndEquality : public NLogicalAnd {
public:
  const NEquality *const equality;
  NLogicalAndEquality(const NEquality *const _equality) : equality(_equality){};
  void gen() const override;
  void show_ast() const override;
};
class NLogicalAndBinary : public NLogicalAnd {
public:
  const NLogicalAnd *const l;
  const NEquality *const r;
  NLogicalAndBinary(const NLogicalAnd *const _l, const NEquality *const _r)
      : l(_l), r(_r) {}
  void gen() const override;
  void show_ast() const override;
};
// equality
class NEquality : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};
class NEqualityRelational : public NEquality {
public:
  const NRelational *const relational;
  NEqualityRelational(const NRelational *const _relational)
      : relational(_relational){};

  void gen() const override;
  void show_ast() const override;
};
class NEqualityBinary : public NEquality {
public:
  const NEquality *const l;
  std::string _oprt;
  const NRelational *const r;
  NEqualityBinary(const NEquality *const l, std::string _oprt,
                  const NRelational *const r)
      : l(l), _oprt((_oprt)), r(r){};
  void gen() const override;
  void show_ast() const override;
};
// relational
class NRelational : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};
class NRelationalAdditive : public NRelational {
public:
  const NAdditive *const additive;
  NRelationalAdditive(const NAdditive *const additive) : additive(additive) {}
  void gen() const override;
  void show_ast() const override;
};
class NRelationalBinary : public NRelational {
public:
  const NRelational *const l;
  const std::string _oprt;
  const NAdditive *const r;
  NRelationalBinary(const NRelational *const l, const std::string _oprt,
                    const NAdditive *const r)
      : l(l), _oprt((_oprt)), r(r){};
  void gen() const override;
  void show_ast() const override;
};
// primary
class NPrimary : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};
class NPrimaryId : public NPrimary {
public:
  std::string id;
  explicit NPrimaryId(std::string &id) : id(id) {}
  void gen() const override;
  void show_ast() const override;
};
class NInteger : public NPrimary {
public:
  long long value;
  NInteger(long long _value) : value(_value){};
  void gen() const override;
  void show_ast() const override;
};
class NPrimaryExpression : public NPrimary {
public:
  const NExpression &exp;
  explicit NPrimaryExpression(const NExpression &_exp) : exp(_exp) {}
  void gen() const override;
  void show_ast() const override;
};

class NUnary : public Node {
public:
  void gen() const override{};
  void show_ast() const override{};
};
class NUnaryPrimary : public NUnary {
public:
  const NPrimary &primary;
  NUnaryPrimary(const NPrimary &_primary) : primary(_primary) {}
  void gen() const override;
  void show_ast() const override;
};

class NUnaryWithOperator : public NUnary {
public:
  const std::string oprt;
  const NUnary &unary;
  NUnaryWithOperator(std::string _oprt, const NUnary &_unary)
      : oprt((_oprt)), unary(_unary){};
  void gen() const override;
  void show_ast() const override;
};
#endif
