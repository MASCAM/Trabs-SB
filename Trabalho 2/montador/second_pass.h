#include <iostream>
#include <string>
#include <vector>
#include <map> 

using namespace std;

#ifndef __SECOND_PASS_H__
#define __SECOND_PASS_H__

string create_object_string(vector <string > &errorsr, vector <line_of_words_t > &linesr, vector <string > &original_filer, map <string, vector<int >> &symbols_tabler, map <string, vector<int >> &uses_tabler, string &realocatorr);

vector <int > get_operation_code(map <string, vector<int >> symbols_tabler, vector <string > &errorsr, vector <string > &original_filer, vector <word_t > operation_words, int operation_number);

#endif