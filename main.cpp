#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    ifstream file("example.json");
    if (!file)
    {
        cerr << "Error: Could not open data.json" << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string json = buffer.str();

    Parser parser(json);
    vector<string> result = parser.parse();

    for (const string &line : result)
    {
        cout << line << endl;
    }

    return 0;
}