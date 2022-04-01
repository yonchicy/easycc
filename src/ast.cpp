#include "../include/error.h"
#include "../include/node.h"
#include <cstdio>
#include <cstdlib>
static int tree_depth;
static inline void push_depth() {
  for (int i = 0; i < tree_depth; ++i) {
    TRACE("-");
  }
  tree_depth++;
}
static inline void pop_depth() { tree_depth--; }
void NProgram::show_ast() const {
  // Emit code
  TRACE("program\n");
  push_depth();
  FuncDeclaration.show_ast();
  pop_depth();
}

void NFunctionDeclaration::show_ast() const {
  TRACE("FuncDeclaration(%s %s) stataments:\n", (this->type).name.c_str(),
        (this->id.c_str()));
  push_depth();
  this->statements->show_ast();
  pop_depth();
}

// TODO
// statements
void NStatements::show_ast() const {
  for (auto &stmt : this->stmts) {
    push_depth();
    stmt->show_ast();
    pop_depth();
  }
}
// statement
void NStatementExpr::show_ast() const {
  TRACE("NStatementExpr\n");
  push_depth();
  this->expr->show_ast();
  pop_depth();
}
void NStatementNull::show_ast() const { TRACE("NStatementNull\n"); }
void NStatementDeclaration::show_ast() const {
  if (this->declaration != nullptr) {
    push_depth();
    this->declaration->show_ast();
    pop_depth();
  } else {
    TRACE("Varible declaration without init\n");
  }
}
// declaration
void NDeclarationWithAssign::show_ast() const {
    TRACE("Varible declaration with init\n");
    push_depth();
    this->expr->show_ast(); 
    pop_depth();
}
void NReturnStatement::show_ast() const {
  TRACE("NReturnStatement\n");
  push_depth();
  expr.show_ast();
  pop_depth();
}
void NInteger::show_ast() const { TRACE("Integer(%lld)\n", value); }

void NType::show_ast() const { TRACE("Type(%s)", this->name.c_str()); }

void NAdditiveMultipicative::show_ast() const {
  TRACE("NAdditiveMultipicative\n");
  push_depth();
  this->multiplicative.show_ast();
  pop_depth();
}
void NAddtiveOprtMulti::show_ast() const {
  TRACE("NAddtiveOprtMulti(%s)\n", this->oprt.c_str());
  push_depth();
  additive.show_ast();
  pop_depth();
  push_depth();
  multiplicate->show_ast();
  pop_depth();
}
void NMultiplicativeUnary::show_ast() const {
  TRACE("NMultiplicativeUnary\n");
  push_depth();
  this->unary.show_ast();
  pop_depth();
}
void NMultiplicativeOprtUnary::show_ast() const {
  TRACE("NMultiplicativeOprtUnary(%s)\n", this->oprt.c_str());
  push_depth();
  this->left.show_ast();
  pop_depth();
  push_depth();
  this->unary.show_ast();
  pop_depth();
}
// TODO
// expression
void NExpressionAssign::show_ast() const {
    TRACE("NExpressionAssign\n");
    push_depth();
    this->assignment->show_ast(); 
    pop_depth();
}
// assignment
void NAssignLogicOr::show_ast() const {
    TRACE("NAssignLogicOr\n");
    push_depth();
    this->logical_or->show_ast(); 
    pop_depth();
}
void NAssignAssign::show_ast() const { 
    TRACE("NAssignAssign (%s=something)\n",this->id.c_str());
    push_depth();
    this->expr->show_ast(); 
    pop_depth();
}
// logical_or
void NLogicalOrAnd::show_ast() const {
    TRACE("NLogicalOrAnd\n");
    push_depth();
    this->logical_and->show_ast();
    pop_depth();
}
void NLogicalORBinary::show_ast() const {
    TRACE("NLogicalORBinary\n");
    push_depth();
    this->l->show_ast();
    pop_depth();
    push_depth();
    this->r->show_ast();
    pop_depth();
}
// logical_and
void NLogicalAndEquality::show_ast() const {
    TRACE("NLogicalAndEquality\n");
    push_depth();
    this->equality->show_ast();
    pop_depth();

}
void NLogicalAndBinary::show_ast() const {
    TRACE("NLogicalAndBinary\n");
    push_depth();
    this->l->show_ast();
    pop_depth();
    push_depth();
    this->r->show_ast();
    pop_depth();


}
// equality
void NEqualityRelational::show_ast() const {
    TRACE("NEqualityRelational\n");
    push_depth();
    this->relational->show_ast();
    pop_depth();

}
void NEqualityBinary::show_ast() const {
    TRACE("NEqualityBinary (%s)\n",this->_oprt.c_str());
    push_depth();
    this->l->show_ast();
    pop_depth();
    push_depth();
    this->r->show_ast();
    pop_depth();

}
// relational
void NRelationalAdditive::show_ast() const {
    TRACE("NRelationalAdditive\n");
    push_depth();
    this->additive->show_ast();
    pop_depth();
}
void NRelationalBinary::show_ast() const {
    TRACE("NRelationalBinary (%s)\n",this->_oprt.c_str());
    push_depth();
    this->l->show_ast();
    pop_depth();
    push_depth();
    this->r->show_ast();
    pop_depth();

}
void NUnaryPrimary::show_ast() const {
  TRACE("NUnaryPrimary\n");
  push_depth();
  this->primary.show_ast();
  pop_depth();
}
void NUnaryWithOperator::show_ast() const {
  TRACE("NUnaryWithOperator(%s)\n", this->oprt.c_str());
  push_depth();
  this->unary.show_ast();
  pop_depth();
}
void NPrimaryExpression::show_ast() const {

  push_depth();
  this->exp.show_ast();
  pop_depth();
}
// TODO
void NPrimaryId::show_ast() const {
    TRACE("NPrimaryId (%s)\n",this->id.c_str());
}
