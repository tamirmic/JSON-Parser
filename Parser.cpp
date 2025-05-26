#include "Parser.h"
#include <cctype>

Parser::Parser(const string &input) : text(input), pos(0) {}

vector<pair<string, string>> Parser::parse()
{
    orderedPairs.clear();
    skipWhitespace();
    if (peek() == '{')
    {
        parseObject("", 0);
    }
    return orderedPairs;
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
    get();
    while (peek() != '"')
    {
        result += get();
    }
    get();
    return result;
}

string Parser::parseArray()
{
    get();
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
    get();
    arrayStr += "]";
    return arrayStr;
}

void Parser::parseObject(const string &prefix, int indentLevel)
{
    get();
    skipWhitespace();

    while (peek() != '}')
    {
        string key = parseString();
        skipWhitespace();
        get();
        skipWhitespace();

        string fullKey = prefix + key;

        if (peek() == '"')
        {
            string value = parseString();
            orderedPairs.push_back({string(indentLevel * 2, ' ') + key, value});
        }
        else if (isdigit(peek()) || peek() == '-')
        {
            string num;
            if (peek() == '-')
                num += get();
            while (isdigit(peek()))
                num += get();
            orderedPairs.push_back({string(indentLevel * 2, ' ') + key, num});
        }
        else if (peek() == '[')
        {
            orderedPairs.push_back({string(indentLevel * 2, ' ') + key, parseArray()});
        }
        else if (peek() == '{')
        {
            orderedPairs.push_back({string(indentLevel * 2, ' ') + key + ":", ""});
            parseObject(fullKey + ".", indentLevel + 1);
        }
        else
        {
            string literal;
            while (isalpha(peek()))
            {
                literal += get();
            }
            orderedPairs.push_back({string(indentLevel * 2, ' ') + key, literal});
        }

        skipWhitespace();
        if (peek() == ',')
        {
            get();
            skipWhitespace();
        }
    }

    get();
}