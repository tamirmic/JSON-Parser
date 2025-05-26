#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

using namespace std;

class Parser
{
public:
    Parser(const string &input);
    vector<pair<string, string>> parse();

private:
    string text;
    size_t pos;
    vector<pair<string, string>> orderedPairs;

    char peek();
    char get();
    void skipWhitespace();
    string parseString();
    string parseArray();
    void parseObject(const string &prefix, int indentLevel);
};

#endif
