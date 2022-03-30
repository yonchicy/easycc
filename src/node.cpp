#include "../include/node.h"
#include "../include/error.h"
#include <cstdio>
extern FILE *output;
void push(const char *reg) {
  // debug("PUSH %s\n", reg);
  fprintf(output, "\taddi sp, sp, -%d\n", 4);
  fprintf(output, "\tsw %s, 0(sp)\n", reg);
}

void pop(const char *reg) {
  // debug("POP %s\n", reg);
  fprintf(output, "\tlw %s, 0(sp)\n", reg);
  fprintf(output, "\taddi sp, sp, %d\n", 4);
}

void NProgram::gen() const {
  fprintf(output, "\t.text\n");
  // Emit code
  FuncDeclaration.gen();
}

void NFunctionDeclaration::gen() const {
    fprintf(output, "\t.global %s\n", id.c_str());
    fprintf(output, "%s:\n", id.c_str());
    statement.gen(); }



void NReturnStatement::gen() const {
  expr.gen();
  pop("a0");
  fprintf(output, "\tret\n");
}
void NInteger::gen() const {
  fprintf(output, "\tli t0, %lld\n", value);
  push("t0");
}

void NType::gen() const {}

void NAdditiveMultipicative::gen() const { this->multiplicative.gen(); }
void NAddtiveOprtMulti::gen() const {
  additive.gen();
  multiplicate->gen();
  pop("t1");
  pop("t0");
  if (this->oprt == "+") {
    fprintf(output, "\tadd t0,t0,t1\n");
  } else if (this->oprt == "-") {
    fprintf(output, "\tsub t0,t0,t1\n");
  } else {
    ERROR("error in NAddtiveOprtMulti::gen()\n");
  }
  push("t0");
}
// expression
void NExpressionLogicalOr::gen() const { this->logical_or->gen(); }

// logical_or
void NLogicalOrAnd::gen() const { this->logical_and->gen(); }
void NLogicalORBinary::gen() const {
  this->l->gen();
  this->r->gen();
  pop("t1");
  pop("t0");
  fprintf(output, "\tor t0,t0,t1\n");
  fprintf(output, "\tsnez t0,t0\n");
  push("t0");
}
// logical_and
void NLogicalAndEquality::gen() const { this->equality->gen(); }
void NLogicalAndBinary::gen() const {
  this->l->gen();
  this->r->gen();
  pop("t1");
  pop("t0");
  fprintf(output, "\tsnez t0,t0\n");
  fprintf(output, "\tsnez t1,t1\n");
  fprintf(output, "\tand t0,t0,t1\n");
  push("t0");
}
// equality
void NEqualityRelational::gen() const { this->relational->gen(); }
void NEqualityBinary::gen() const {
  l->gen();
  r->gen();
  pop("t1");
  pop("t0");
  if (this->_oprt == "!=") {
    fprintf(output, "\tsub t0,t0,t1\n");
    fprintf(output, "\tsnez t0,t0\n");
  } else if (this->_oprt == "==") {
    fprintf(output, "\tsub t0,t0,t1\n");
    fprintf(output, "\tseqz t0,t0\n");
  } else {
    ERROR("error in NEqualityRelational::gen()\n");
  }
  push("t0");
}
// relational
void NRelationalAdditive::gen() const { this->additive->gen(); }
void NRelationalBinary::gen() const {
  this->l->gen();
  this->r->gen();
  if (this->_oprt == "<") {
    pop("t1");
    pop("t0");
    fprintf(output, "\tslt t0,t0,t1\n");
  } else if (this->_oprt == "<=") {
    pop("t1");
    pop("t0");
    fprintf(output, "\tsgt t0,t0,t1\n");
    fprintf(output, "\tseqz t0,t0\n");
  } else if (this->_oprt == ">") {
    pop("t0");
    pop("t1");
    fprintf(output, "\tslt t0,t0,t1\n");
  } else if (this->_oprt == ">=") {
    pop("t0");
    pop("t1");
    fprintf(output, "\tsgt t0,t0,t1\n");
    fprintf(output, "\tseqz t0,t0\n");
  }
  else {
  ERROR("error in NRelationalBinary::gen()\n");
  }
  push("t0");
}

void NMultiplicativeUnary::gen() const { this->unary.gen(); }
void NMultiplicativeOprtUnary::gen() const {
  this->left.gen();
  this->unary.gen();
  pop("t1");
  pop("t0");
  if (this->oprt == "*") {
    fprintf(output, "\tmul t0,t0,t1\n");
  } else if (this->oprt == "/") {
    fprintf(output, "\tdiv t0,t0,t1\n");
  } else if (this->oprt == "%") {
    fprintf(output, "\trem t0,t0,t1\n");
  } else {
    ERROR("error in NMultiplicativeOprtUnary::gen()\n");
  }
  push("t0");
}

void NUnaryPrimary::gen() const { this->primary.gen(); }
void NUnaryWithOperator::gen() const {
  this->unary.gen();
  pop("t0");
  if (this->oprt == "-") {
    fprintf(output, "\tneg t0,t0\n");
  } else if (this->oprt == "!") {
    fprintf(output, "\tseqz t0,t0\n");
  } else if (this->oprt == "~") {
    fprintf(output, "\tnot t0,t0\n");
  } else {
    ERROR("error in NUnaryWithOperator::gen()\n ");
  }
  push("t0");
}
void NPrimaryExpression::gen() const { this->exp.gen(); }
