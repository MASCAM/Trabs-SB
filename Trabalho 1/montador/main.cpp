#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "format_file.h"
#include "utilities.h"
#include "first_pass.h"
#include "define_word_class.h"

int main(int argc, char *argv[]) {
    
    string filename;
    string filename_aux;
    vector <string > *original_file = new vector <string >;
    vector <string > &original_filer = *original_file;
    vector <string > *errors = new vector <string >;
    vector <string > &errorsr = *errors;
    vector <line_of_words_t > *lines = new vector <line_of_words_t >;
    vector <line_of_words_t > &linesr = *lines;
    if (argc != 2) {

        cout << "Número de argumentos diferente de 2" << "\n";

    } else {

        filename = argv[1];
        //cout << filename.find(".asm") << "\n";
        if (filename.find(".asm") != string::npos) {

            filename_aux = formatFile(filename, original_filer);
            map <string, int> teste = getSymbolsTable(filename_aux, errorsr, linesr, original_filer);
            if (errorsr.size() > 0) {

                for (size_t i = 0; i < errorsr.size(); i++) {

                    cout << errorsr[i] << endl;

                }

            }
            
        } else {

            cout << "Arquivo de entrada com extensao invalida" << "\n";

        }

    }

}