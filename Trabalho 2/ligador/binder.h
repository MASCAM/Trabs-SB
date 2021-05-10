#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef __BINDER_H__
#define __BINDER_H__

string create_object_string(vector <string > &filenamer, map <string, int> &general_definitions_tabler);

map <string, int> create_general_definitions_table(vector <string > &filenamer, map <string, int> &general_definitions_tabler, string &object_filenamer);

#endif