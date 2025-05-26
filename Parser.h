#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

using namespace std;

class Parser
{
public:
    Parser(const string &input);
    vector<string> parse();

private:
    string text;
    size_t pos;
    vector<string> output;

    char peek();
    char get();
    void skipWhitespace();
    string parseString();
    void parseObject();
    string parseArray();
};

#endif
