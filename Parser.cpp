#include "Parser.h"
#include <cctype>

Parser::Parser(const string &input) : text(input), pos(0) {}

vector<string> Parser::parse()
{
    output.clear();
    skipWhitespace();
    if (peek() == '{')
    {
        parseObject();
    }
    return output;
}

char Parser::peek()
{
    if (pos < text.size())
    {
        return text[pos];
    }
    else
    {
        return '\0';
    }
}

char Parser::get()
{
    if (pos < text.size())
    {
        return text[pos++];
    }
    else
    {
        return '\0';
    }
}

void Parser::skipWhitespace()
{
    while (isspace(peek()))
        get();
}

string Parser::parseString()
{
    string result;
    get(); // skip opening quote
    while (peek() != '"')
    {
        result += get();
    }
    get(); // skip closing quote
    return result;
}

void Parser::parseObject()
{
    get(); // skip '{'
    skipWhitespace();

    while (peek() != '}')
    {
        string key = parseString();
        skipWhitespace();
        get(); // skip ':'
        skipWhitespace();

        if (peek() == '"')
        {
            string value = parseString();
            output.push_back(key + " = " + value);
        }
        else if (isdigit(peek()))
        {
            string num;
            while (isdigit(peek()))
                num += get();
            output.push_back(key + " = " + num);
        }
        else if (peek() == '[')
        {
            output.push_back(key + " = " + parseArray());
        }
        else if (peek() == '{')
        {
            output.push_back(key + " = [Object]");
            parseObject();
        }
        else
        {
            string literal;
            while (isalpha(peek()))
                literal += get();
            output.push_back(key + " = " + literal);
        }

        skipWhitespace();
        if (peek() == ',')
        {
            get(); // skip ','
            skipWhitespace();
        }
    }

    get(); // skip '}'
}

string Parser::parseArray()
{
    get(); // skip '['
    string arrayStr = "[";
    bool first = true;
    while (peek() != ']')
    {
        skipWhitespace();
        if (peek() == '"')
        {
            if (!first)
            {
                arrayStr += ", ";
            }
            string item = parseString();
            arrayStr += item;
            first = false;
            skipWhitespace();
            if (peek() == ',')
                get();
        }
    }
    get(); // skip ']'
    arrayStr += "]";
    return arrayStr;
}
