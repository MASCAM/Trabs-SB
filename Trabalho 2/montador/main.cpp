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
    bool *multiple_files = new bool;
    bool &multiple_filesr = *multiple_files;
    vector <string > *original_file = new vector <string >;
    vector <string > &original_filer = *original_file;
    if (argc < 2) {

        cout << "Número de argumentos menor do que 2" << "\n";

    } else {

        if (argc > 2) {

            multiple_filesr = true;

        }
        for (int i = 1; i < argc; i++) {

            vector <string > *errors = new vector <string >;
            vector <string > &errorsr = *errors;
            vector <line_of_words_t > *lines = new vector <line_of_words_t >;
            vector <line_of_words_t > &linesr = *lines;
            filename = argv[i];
            //cout << filename.find(".asm") << "\n";
            if (filename.find(".asm") != string::npos) {

                filename_aux = formatFile(filename, original_filer, multiple_filesr);
                if (filename_aux != "FAILED") {

                    map <string, int> symbols_table = get_symbols_table(filename_aux, errorsr, linesr, original_filer);
                    /*for (map<string, int>::const_iterator it = symbols_table.begin(); it != symbols_table.end(); ++it) {

                        std::cout << it->first << " " << to_string(it->second) << "\n";

                    }*/
                    remove(filename_aux.c_str()); //deleta o arquivo auxiliar criado
                    string object_file_string = create_object_string(symbols_table, errorsr, linesr, original_filer);
                    if (errorsr.size() > 0) {

                        for (size_t j = 0; j < errorsr.size(); j++) {

                            cout << errorsr[j] << endl << endl;

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

                    cout << "Houve um erro na formatacao e/ou pre-processamento do arquivo" << endl;
                    break;

                }
                
            } else {

                cout << "Arquivo de entrada com extensao invalida" << "\n";
                break;

            }

        }

    }

}