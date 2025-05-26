// Tamir Michaely
// Pretty JSON implementation
// Assumes JSON properly formatted
/*
Input:
{
  "name": "Alice",
  "age": 30,
  "address": {
    "street": {
      "name": "Main St",
      "number": 123
    },
    "city": "Seattle"
  }
}

Ouput: (Tab indented ouput)

name = Alice
age = 30
address:
  street:
    name = Main St
    number = 123
  city = Seattle
*/

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
    vector<pair<string, string>> result = parser.parse();

    cout << "Parsed JSON:" << endl
         << endl;

    for (const auto &[key, value] : result)
    {
        if (!key.empty() && key.back() == ':')
            cout << key << endl;
        else
            cout << key << " = " << value << endl;
    }

    return 0;
}