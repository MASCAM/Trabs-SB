#include <iostream>
#include <string>
#include <vector>
#include <map> 
#include "define_word_class.h"

using namespace std;

#ifndef __FIRST_PASS_H__
#define __FIRST_PASS_H__

map <string, int> getSymbolsTable(string filename, string filename_aux, vector <string > &errorsr, vector <line_of_words_t > &linesr);

#endif