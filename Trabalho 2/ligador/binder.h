#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef __BINDER_H__
#define __BINDER_H__

string create_final_object_string(vector <string > &filenamer, map <string, int> &general_definitions_tabler, string &object_filenamer, vector <map <string, vector<int >>> &global_uses_tabler, vector <vector <int >> &numbers_stringr);

#endif