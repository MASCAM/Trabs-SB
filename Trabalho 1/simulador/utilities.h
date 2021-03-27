#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

map <string, vector<int>> get_instructions_table();

map <string, vector<int>> get_directives_table();

vector <string > split(vector<string > sentences, string delimiter, int &foundr);

bool is_number(const string s);

#endif