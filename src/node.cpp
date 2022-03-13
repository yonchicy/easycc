#include "../include/node.hpp"
#include <cstdio>

void gen_push(const char* reg) {
    // debug("PUSH %s\n", reg);
    printf("\taddi sp, sp, -%d\n", 4);
    printf("\tsw %s, 0(sp)\n", reg);
}

void gen_pop(const char* reg) {
    // debug("POP %s\n", reg);
    printf("\tlw %s, 0(sp)\n", reg);
    printf("\taddi sp, sp, %d\n", 4);
}

void* NProgram::gen()const {
    printf("\t.text\n");
        printf("\t.global %s\n", FuncDeclaration.id.c_str());
        printf("%s:\n", FuncDeclaration.id.c_str());
        // Emit code
    return FuncDeclaration.gen();
}

void *NFunctionDeclaration::gen() const{
    return statement.gen(); 
}


void *NReturnStatement::gen()const{
    expr.gen();
    gen_pop("a0");
    printf("\tret\n");
    return nullptr;
}
void* NInteger::gen()const{
    printf("\tli t0, %lld\n",value);
    gen_push("t0");
    return nullptr;
}

void* NType::gen()const{
    return nullptr;
}
void* NUnary::gen()const{
    return nullptr;
}
void* NExpression::gen()const{
    return nullptr;
}
