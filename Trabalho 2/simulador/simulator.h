#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

string execute_instruction(int &PC, int &ACC, vector <int > &object_code);

vector <string > simulate_object_file(string filename);

#endif