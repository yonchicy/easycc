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

void *NProgram::gen() const {
    INFO("program\n");
  fprintf(output, "\t.text\n");
  fprintf(output, "\t.global %s\n", FuncDeclaration.id.c_str());
  fprintf(output, "%s:\n", FuncDeclaration.id.c_str());
  // Emit code
  return FuncDeclaration.gen();
}

void *NFunctionDeclaration::gen() const { return statement.gen(); }

void *NReturnStatement::gen() const {
    INFO("NReturnStatement\n");
  expr.gen();
  gen_pop("a0");
  fprintf(output, "\tret\n");
  return nullptr;
}
void *NInteger::gen() const {
    INFO("NInteger\n");
  fprintf(output, "\tli t0, %lld\n", value);
  gen_push("t0");
  return nullptr;
}

void *NType::gen() const { return nullptr; }

// TODO
//
void *NExpressionAdditive::gen() const {
    INFO("NExpressionAdditive\n");
  this->additive.gen();
  return nullptr;
}
void *NAddtiveMultipicative::gen() const {
    INFO("NAddtiveMultipicative\n");
  this->multiplicative.gen();
  return nullptr;
}
void *NAddtiveOprtMulti::gen() const {
    INFO("NAddtiveOprtMulti\n");
  additive.gen();
  multiplicate.gen();
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
  return nullptr;
}
void *NMultiplicativeUnary::gen() const {
    INFO("NMultiplicativeUnary\n");
    this->unary.gen();
    return nullptr; 
}
void *NMultiplicativeOprtUnary::gen() const {
    INFO("NMultiplicativeOprtUnary\n");
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

    return nullptr; 
}
void *NUnaryPrimary::gen() const { 
    INFO("NUnaryPrimary\n");
    this->primary.gen();
    return nullptr; 
}
void *NUnaryWithOperator::gen() const {
    INFO("NUnaryWithOperator\n");
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
    return nullptr;
}
void *NPrimaryExpression::gen() const { 
    INFO("NPrimaryExpression\n");
    this->exp.gen();
    return nullptr; 
}
