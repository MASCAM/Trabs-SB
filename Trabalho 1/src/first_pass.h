#include <iostream>
#include <string>
#include <vector>
#include <map> 

using namespace std;

#ifndef __FIRST_PASS_H__
#define __FIRST_PASS_H__

map <string, int> getSymbolsTable(string filename, string filename_aux, vector <string >* errors);

#endif