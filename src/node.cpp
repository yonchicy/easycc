#include "../include/node.h"
#include <cstdio>
extern FILE* output;
void gen_push(const char* reg) {
    // debug("PUSH %s\n", reg);
    fprintf(output,"\taddi sp, sp, -%d\n", 4);
    fprintf(output,"\tsw %s, 0(sp)\n", reg);
}

void gen_pop(const char* reg) {
    // debug("POP %s\n", reg);
    fprintf(output,"\tlw %s, 0(sp)\n", reg);
    fprintf(output,"\taddi sp, sp, %d\n", 4);
}

void* NProgram::gen()const {
    fprintf(output,"\t.text\n");
        fprintf(output,"\t.global %s\n", FuncDeclaration.id.c_str());
        fprintf(output,"%s:\n", FuncDeclaration.id.c_str());
        // Emit code
    return FuncDeclaration.gen();
}

void *NFunctionDeclaration::gen() const{
    return statement.gen(); 
}


void *NReturnStatement::gen()const{
    expr.gen();
    gen_pop("a0");
    fprintf(output,"\tret\n");
    return nullptr;
}
void* NInteger::gen()const{
    fprintf(output,"\tli t0, %lld\n",value);
    gen_push("t0");
    return nullptr;
}

void* NType::gen()const{
    return nullptr;
}
void* NUnary::gen()const{
    unary.gen();
    gen_pop("t0");
    if(_operator=="!"){
        fprintf(output,"\tseqz t0, t0\n");
    }
    else if (_operator == "~"){
        fprintf(output,"\tnot t0, t0\n");
    }
    else if (_operator == "-"){
        fprintf(output,"\tneg t0, t0\n");
    }
    gen_push("t0");
    return nullptr;
}
void* NExpression::gen()const{
    unary.gen();
    return nullptr;
}
