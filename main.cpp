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

Output: (Tab indented ouput)

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

string ReadJSON(string fileName);
void PrintOutput(vector<pair<string, string>> &result);

int main()
{

    string json = ReadJSON("example.json");
    Parser parser(json);
    vector<pair<string, string>> result = parser.parse();

    PrintOutput(result);

    return 0;
}

string ReadJSON(string fileName)
{
    ifstream file(fileName);
    if (!file)
    {
        cerr << "Error: Could not open data.json" << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void PrintOutput(vector<pair<string, string>> &result)
{
    cout << "Parsed JSON:" << endl
         << endl;

    for (const auto &[key, value] : result)
    {
        if (!key.empty() && key.back() == ':')
            cout << key << endl;
        else
            cout << key << " = " << value << endl;
    }
}
