#include <string>
#include <unordered_map>

int getStackOff();
class VaribleInfo{
public:
    std::string type;
    int offset;
    VaribleInfo(    std::string& type
                ):type(type),offset(getStackOff()){}
};

extern std::unordered_map<std::string, VaribleInfo> VaribleTable;
