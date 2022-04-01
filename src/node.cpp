#include "../include/node.h"
#include "../include/error.h"
#include "../include/runtime.h"
#include <cstdio>
#include <type_traits>

// ----DEBUG HELPER
// static int tree_depth;
// static inline void push_depth() {
//   for (int i = 0; i < tree_depth; ++i) {
//     TRACE("-");
//   }
//   tree_depth++;
// }
// static inline void pop_depth() { tree_depth--; }
// ----DEBUG HELPER
extern FILE *output;
bool last_statement_is_return;
static std::string func_name;
void store_var(const char *reg, VaribleInfo &var) {
  fprintf(output, "\tsw %s, %d(fp)\n", reg, var.offset);
}
void load_var(const char *reg, VaribleInfo &var) {
  fprintf(output, "\tlw %s, %d(fp)\n", reg, var.offset);
}
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
  func_name = FuncDeclaration.id;
  FuncDeclaration.gen();
}

void NFunctionDeclaration::gen() const {
  WARNNING("NFunctionDeclaration\n");

  fprintf(output, "\t.global %s\n", id.c_str());
  fprintf(output, "%s:\n", id.c_str());
  //
  int local_stack_size = FunctionTable[func_name].stack_size;
  fprintf(output, "\taddi sp,sp, -%d\n", local_stack_size);
  fprintf(output, "\tsw   ra,%d-4(sp)\n", local_stack_size);
  fprintf(output, "\tsw   fp,%d-8(sp)\n", local_stack_size);
  fprintf(output, "\taddi fp,sp,%d\n", local_stack_size);

  statements->gen();
  auto last_statement=--(this->statements->stmts.end());
  if(!last_statement_is_return){
  fprintf(output, "\tlw a0,0\n");

  }
  fprintf(output, ".L.f.%s:\n", func_name.c_str());
  fprintf(output, "\taddi sp,fp\n");
  fprintf(output, "\tlw   ra,-4(sp)\n");
  fprintf(output, "\tlw   fp,-8(sp)\n");
  fprintf(output, "\tret\n");
}
// TODO
// statements
void NStatements::gen() const {
  WARNNING("NStatements\n");
  for (auto &stmt : this->stmts) {
    stmt->gen();
  }
}
// statement
void NStatementExpr::gen() const {
  WARNNING("NStatementExpr\n");
  this->expr->gen();
}
void NStatementNull::gen() const { WARNNING("NStatementNull\n"); }
void NStatementDeclaration::gen() const {
  WARNNING("NStatementDeclaration\n");
  if (this->declaration != nullptr) {
    this->declaration->gen();
  }
}
// declaration
void NDeclarationWithAssign::gen() const {
  WARNNING("NDeclarationWithAssign\n");
  this->expr->gen();
  pop("t0");
  store_var("t0", FunctionTable[func_name].VaribleTable[this->id]);
  push("t0");
}
void NReturnStatement::gen() const {
  WARNNING("NReturnStatement\n");
  expr.gen();
  pop("a0");
  fprintf(output, "\tj .L.f.%s\n", func_name.c_str());
}
void NInteger::gen() const {
  WARNNING("NInteger\n");
  fprintf(output, "\tli t0, %lld\n", this->value);
  push("t0");
}

void NType::gen() const { WARNNING("NType\n"); }

void NAdditiveMultipicative::gen() const {
  WARNNING("NAdditiveMultipicative\n");
  this->multiplicative.gen();
}
void NAddtiveOprtMulti::gen() const {
  WARNNING("NAddtiveOprtMulti\n");
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
void NExpressionAssign::gen() const {
  WARNNING("NExpressionAssign\n");
  this->assignment->gen();
}
// assignment
void NAssignLogicOr::gen() const {
  WARNNING("NAssignLogicOr\n");
  this->logical_or->gen();
}
void NAssignAssign::gen() const {
  WARNNING("NAssignAssign\n");
  this->expr->gen();
  pop("t0");
  store_var("t0", FunctionTable[func_name].VaribleTable[this->id]);
  push("t0");
}

// logical_or
void NLogicalOrAnd::gen() const {
  WARNNING("NLogicalOrAnd\n");
  this->logical_and->gen();
}
void NLogicalORBinary::gen() const {
  WARNNING("NLogicalORBinary\n");
  this->l->gen();
  this->r->gen();
  pop("t1");
  pop("t0");
  fprintf(output, "\tor t0,t0,t1\n");
  fprintf(output, "\tsnez t0,t0\n");
  push("t0");
}
// logical_and
void NLogicalAndEquality::gen() const {
  WARNNING("NLogicalAndEquality\n");
  this->equality->gen();
}
void NLogicalAndBinary::gen() const {
  WARNNING("NLogicalAndBinary\n");
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
void NEqualityRelational::gen() const {
  WARNNING("NEqualityRelational\n");
  this->relational->gen();
}
void NEqualityBinary::gen() const {
  WARNNING("NEqualityBinary\n");
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
void NRelationalAdditive::gen() const {
  WARNNING("NRelationalAdditive\n");
  this->additive->gen();
}
void NRelationalBinary::gen() const {
  WARNNING("NRelationalBinary\n");
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
  } else {
    ERROR("error in NRelationalBinary::gen()\n");
  }
  push("t0");
}

void NMultiplicativeUnary::gen() const {
  WARNNING("NMultiplicativeUnary\n");
  this->unary.gen();
}
void NMultiplicativeOprtUnary::gen() const {
  WARNNING("NMultiplicativeOprtUnary\n");
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

void NUnaryPrimary::gen() const {
  WARNNING("NUnaryPrimary\n");
  this->primary.gen();
}
void NUnaryWithOperator::gen() const {
  WARNNING("NUnaryWithOperator\n");
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
void NPrimaryExpression::gen() const {
  WARNNING("NPrimaryExpression\n");
  this->exp.gen();
}
void NPrimaryId::gen() const {
  WARNNING("NPrimaryId\n");
  load_var("t0", FunctionTable[func_name].VaribleTable[this->id]);
}
