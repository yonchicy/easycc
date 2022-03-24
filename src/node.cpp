#include "../include/node.h"
#include "../include/error.h"
#include <cstdio>
extern FILE *output;
void gen_push(const char *reg) {
  // debug("PUSH %s\n", reg);
  fprintf(output, "\taddi sp, sp, -%d\n", 4);
  fprintf(output, "\tsw %s, 0(sp)\n", reg);
}

void gen_pop(const char *reg) {
  // debug("POP %s\n", reg);
  fprintf(output, "\tlw %s, 0(sp)\n", reg);
  fprintf(output, "\taddi sp, sp, %d\n", 4);
}

void NProgram::gen() const {
  fprintf(output, "\t.text\n");
  fprintf(output, "\t.global %s\n", FuncDeclaration.id.c_str());
  fprintf(output, "%s:\n", FuncDeclaration.id.c_str());
  // Emit code
  FuncDeclaration.gen();
}

void NFunctionDeclaration::gen() const {
  statement.gen();
}

void NReturnStatement::gen() const {
  expr.gen();
  gen_pop("a0");
  fprintf(output, "\tret\n");
}
void NInteger::gen() const {
  fprintf(output, "\tli t0, %lld\n", value);
  gen_push("t0");
}

void NType::gen() const {
}

void NExpressionAdditive::gen() const {
  this->additive.gen();
}
void NAdditiveMultipicative::gen() const {
  this->multiplicative.gen();
}
void NAddtiveOprtMulti::gen() const {
  additive.gen();
  multiplicate->gen();
  gen_pop("t1");
  gen_pop("t0");
  if (this->oprt == "+") { 
    fprintf(output, "\tadd t0,t0,t1\n");
  } else if (this->oprt == "-") {
    fprintf(output, "\tsub t0,t0,t1\n");
  } else {
    ERROR("error in NAddtiveOprtMulti::gen()\n");
  }
  gen_push("t0");
}
void NMultiplicativeUnary::gen() const {
    this->unary.gen();
}
void NMultiplicativeOprtUnary::gen() const {
    this->left.gen();
    this->unary.gen();
    gen_pop("t1");
    gen_pop("t0");
    if(this->oprt == "*"){
        fprintf(output, "\tmul t0,t0,t1\n");
    }
    else if (this->oprt == "/"){
        fprintf(output, "\tdiv t0,t0,t1\n");
    }
    else if (this->oprt == "%"){
        fprintf(output, "\trem t0,t0,t1\n");
    }
    else {
        ERROR("error in NMultiplicativeOprtUnary::gen()\n");
    }
    gen_push("t0");

}
void NUnaryPrimary::gen() const {
    this->primary.gen();
}
void NUnaryWithOperator::gen() const {
    this->unary.gen();
    gen_pop("t0");
    if(this->oprt == "-"){
        fprintf(output, "\tneg t0,t0\n");
    }
    else if (this->oprt== "!"){
        fprintf(output, "\tseqz t0,t0\n");
    }
    else if (this->oprt== "~"){
        fprintf(output, "\tnot t0,t0\n");
    }
    else {
        ERROR("error in NUnaryWithOperator::gen()\n ");
    }
    gen_push("t0");
}
void NPrimaryExpression::gen() const {
    this->exp.gen();
}