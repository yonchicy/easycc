#include "../include/runtime.h"
std::unordered_map<std::string, VaribleInfo> VaribleTable;
int scope_offset;
int test (int argc, char *argv[])
{
    
    return 0;
}
int getStackOff(){
    return scope_offset--;
}
