#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector> 
#include <sstream>

#include "utilities.h"
#include "define_word_class.h"
#include "first_pass.h"

using namespace std;

map <string, int> getSymbolsTable(string filename_aux, vector <string > &errorsr, vector <line_of_words_t > &linesr, vector <string > &original_filer) {

    fstream file;
    string line;
    file.open(filename_aux);
    int i = 0;
    int PC = 0;
    bool only_labels = false;
    map <string, int> symbolsTable;
    while (getline(file, line)) {

        if (!(line.empty() || line.find_first_not_of(' ') == string::npos || line[line.find_first_not_of(' ')] == ';')) {
        //a linha acima ignora linhas vazias ou que possuem somente comentários
            line_of_words_t actual_line;
            actual_line.PC = PC;
            actual_line.add_line(line, i, original_filer, errorsr);
            /*while (actual_line.line.back().is_label == true) {
                
                
                if (getline(file, line)) {

                    i++;
                    actual_line.add_line(line, i, original_filer, errorsr);

                } else {

                    break;

                }

            }*/

        } 
        i++;

    }
    return symbolsTable;

}


