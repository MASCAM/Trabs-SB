#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "utilities.h"
#include "format_file.h"
#include "define_word_class.h"
#include "first_pass.h"
#include "second_pass.h"


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
            map <string, int> symbols_table = get_symbols_table(filename_aux, errorsr, linesr, original_filer);
            /*for (map<string, int>::const_iterator it = symbols_table.begin(); it != symbols_table.end(); ++it) {

                std::cout << it->first << " " << to_string(it->second) << "\n";

            }*/
            remove(filename_aux.c_str()); //deleta o arquivo auxiliar criado
            string object_file_string = create_object_string(symbols_table, errorsr, linesr, original_filer);
            if (errorsr.size() > 0) {

                for (size_t i = 0; i < errorsr.size(); i++) {

                    cout << errorsr[i] << endl << endl;

                }

            } else {

                //cout << object_file_string << endl;
                filename = filename.substr(0, filename.find(".asm"));
                filename += ".obj";
                //cout << filename << endl;
                ofstream obj_file(filename);
                obj_file << object_file_string << endl;
                obj_file.close();

            }
            
        } else {

            cout << "Arquivo de entrada com extensao invalida" << "\n";

        }

    }

}