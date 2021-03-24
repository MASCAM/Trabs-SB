#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

map <string, vector<int>> getInstructionsTable();

map <string, vector<int>> getDirectivesTable();

vector <string > split(string line, string delimiter);

#endif