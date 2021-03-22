#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef __DEFINE_WORD_CLASS_H__
#define __DEFINE_WORD_CLASS_H__



class word_t {

    public:
        string word;
        int line_position;
        word_t(string line, int line_position);
        bool validate_char(char c, int position);

    };

class line_of_words : word_t {

    public:
        vector <word_t > line;
        int PC;

};

#endif
