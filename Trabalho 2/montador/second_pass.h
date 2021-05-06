#include <iostream>
#include <string>
#include <vector>
#include <map> 

using namespace std;

#ifndef __SECOND_PASS_H__
#define __SECOND_PASS_H__

string create_object_string(map <string, int> symbols_table, vector <string > &errorsr, vector <line_of_words_t > &linesr, vector <string > &original_filer);

vector <int > get_operation_code(map <string, int> symbols_table, vector <string > &errorsr, vector <string > &original_filer, vector <word_t > operation_words, int operation_number);

#endif