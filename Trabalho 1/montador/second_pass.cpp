#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector> 
#include <sstream>

#include "utilities.h"
#include "define_word_class.h"
#include "second_pass.h"

using namespace std;

string createObjectFile(string filename, string filename_aux, vector <string >* errors);
