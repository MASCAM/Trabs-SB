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
        bool is_label;
        bool validate_char(char c, int position);

    };

class line_of_words_t : word_t {

    public:
        vector <word_t > line;
        //vector <int > lines_in_original_file;
        int PC;

        //line_of_words_t(string line, int line_position, vector <string > &original_filer, vector <string > &errorsr);
        void add_line(string line, int line_position, vector <string > &original_filer, vector <string > &errorsr);
        

};

#endif
