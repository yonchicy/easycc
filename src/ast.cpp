#include "../include/node.h"
#include "../include/error.h"
#include <cstdio>
static int tree_depth;
static void push_depth(){
  for (int i = 0; i < tree_depth; ++i) {
    TRACE("-");
  }
  tree_depth++;
}
static void pop_depth(){
  tree_depth--;
}
void NProgram::show_ast() const {
  // Emit code
  TRACE("program\n");
  push_depth();
  FuncDeclaration.show_ast();
  pop_depth();
}

void NFunctionDeclaration::show_ast() const {
  TRACE("FuncDeclaration(%s %s) stataments:\n",(this->type).name.c_str(),(this->id.c_str()));
  push_depth();
  this->statement.show_ast();
  pop_depth();
}

void NReturnStatement::show_ast() const {
  TRACE("NReturnStatement\n");
  push_depth();
  expr.show_ast();
  pop_depth();
}
void NInteger::show_ast() const {
  TRACE( "Integer(%lld)\n", value);
}

void NType::show_ast() const {
  TRACE( "Type(%s)", this->name.c_str());
}

void NAdditiveMultipicative::show_ast() const {
  TRACE( "NAdditiveMultipicative\n");
  push_depth();
  this->multiplicative.show_ast();
  pop_depth();
}
void NAddtiveOprtMulti::show_ast() const {
    TRACE( "NAddtiveOprtMulti(%s)\n",this->oprt.c_str());
  push_depth();
  additive.show_ast();
  pop_depth();
  push_depth();
  multiplicate->show_ast();
  pop_depth();
}
void NMultiplicativeUnary::show_ast() const {
    TRACE( "NMultiplicativeUnary\n");
  push_depth();
    this->unary.show_ast();
  pop_depth();
}
void NMultiplicativeOprtUnary::show_ast() const {
    TRACE( "NMultiplicativeOprtUnary(%s)\n",this->oprt.c_str());
    push_depth();
    this->left.show_ast();
    pop_depth();
    push_depth();
    this->unary.show_ast();
    pop_depth();
}
// TODO
// expression
void NExpressionLogicalOr:: show_ast()const {
}
// logical_or
void NLogicalOrAnd:: show_ast()const {
}
void NLogicalORBinary:: show_ast()const {

}
// logical_and
void NLogicalAndEquality:: show_ast()const {
    
}
void NLogicalAndBinary:: show_ast()const {
    
}
// equality
void  NEqualityRelational::show_ast() const{

}
void  NEqualityBinary::show_ast() const{

}
// relational
void  NRelationalAdditive::show_ast() const{

}
void  NRelationalBinary::show_ast() const{

}
// END TODO
void NUnaryPrimary::show_ast() const { 
    TRACE( "NUnaryPrimary\n");
    push_depth();
    this->primary.show_ast();
    pop_depth();
}
void NUnaryWithOperator::show_ast() const {
  TRACE("NUnaryWithOperator(%s)\n",this->oprt.c_str());
  push_depth();
    this->unary.show_ast();
    pop_depth();
}
void NPrimaryExpression::show_ast() const {

  push_depth();
  this->exp.show_ast();
  pop_depth();
}
