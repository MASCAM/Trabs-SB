#include <iostream>
#include <string>
#include <vector>
#include <map> 
#include "define_word_class.h"

using namespace std;

#ifndef __FIRST_PASS_H__
#define __FIRST_PASS_H__

map <string, vector<int >> get_symbols_table(string filename_aux, vector <string > &errorsr, vector <line_of_words_t > &linesr, vector <string > &original_filer, map <string, vector<int >> &symbols_tabler, map <string, int> &definitions_tabler);

#endif