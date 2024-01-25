#include <iostream>
#include <vector>
#include <string.h>

#include "utils.h"

//before Read CliContextExe 'set aaa shared-secret   "ABC DE"   mode local' _pos=21 s = '   "ABC DE"   mode local'

//std::string cliStr = "set aaa shared-secret   \"ABC DE\"   mode local";// _pos=21 s = '   "ABC DE"   mode local";
std::string cliStr = "set aaa shared-secret   \"A \\\"DE\"   mode local";// _pos=21 s = '   "ABC DE"   mode local";
ssize_t cliPos = 21;

std::vector<std::string> sVec = {
    // " n e",
    // " n\"e c ",
    // " \"q e\" ",
    R"( "q \" e" )",
    R"( "q \ e" )",
    R"( "q \\ e" )",
    R"( "q \\\ e" )",
};

enum E_State {
    normal,
    insidString,
    openQuoteFound,
    escapeFound,
    //closeQuoteFound,
};

ssize_t f1(const std::string& inS, ssize_t pos, std::string& outS)
{
    E_State state = E_State::normal;
    
    for (; pos < strlen(inS.c_str()); ++pos ) {
        char c = inS[pos];
            
        switch (state) {
            
        case E_State::normal:
            if (std::isspace(c))
                break;
            
            if (c == '"') {
                state = E_State::openQuoteFound;
                break;
            }            
            
            state = E_State::insidString;            
            outS += c;
            break;
            
        case E_State::insidString:
            if (std::isspace(c))
                return pos;
            outS += c;
            break;
            
        case E_State::openQuoteFound:
            if (c == '\\') {
                state = E_State::escapeFound;
                break;
            }
            
            if (c == '"')
                return pos;

            outS += c;
            break;
            
        case E_State::escapeFound:
            state = E_State::openQuoteFound;
            if (c == '"') {
                outS += c;
                break;
            }
            
            if (c == '\\') {
                outS += c;
                break;
            }
            
            outS += '\\';
            outS += c;
            break;
        }
    }
        
    return pos;
}

int main()
{
    // const char* s = cliStr.c_str();
    // s += cliPos;
    // printf("'%s'\n", s);
    
    for (auto inS: sVec) {
        std::string outS;
        ssize_t n = f1(inS, 0, outS);
        printf("'%s'\t\t'%s'\n", inS.c_str(), outS.c_str());
    }
    
    return 0;
}
