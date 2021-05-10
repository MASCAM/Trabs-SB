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
    //cout << symbols_tabler["teste"][1] << endl;
    vector <string > filenames;
    string *realocator = new string;
    string &realocatorr = *realocator;
    size_t j = 0;
    multiple_filesr = false;
    if (argc < 2 || argc > 4) {

        cout << "Número de argumentos menor do que 2 ou maior que 4" << "\n";

    } else {

        if (argc > 2) {

            multiple_filesr = true;

        }
        for (int i = 1; i < argc; i++) {

            vector <string > *errors = new vector <string >;
            vector <string > &errorsr = *errors;
            vector <line_of_words_t > *lines = new vector <line_of_words_t >;
            vector <line_of_words_t > &linesr = *lines;
            map <string, vector<int >> *symbols_table = new map <string, vector<int >>;
            map <string, vector<int >> &symbols_tabler = *symbols_table;
            map <string, int> *definitions_table = new map <string, int>;
            map <string, int> &definitions_tabler = *definitions_table;
            map <string, vector<int >> *uses_table = new map <string, vector<int >>;
            map <string, vector<int >> &uses_tabler = *uses_table;
            vector <string > *original_file = new vector <string >;
            vector <string > &original_filer = *original_file;
            realocatorr = "R: ";
            filename = argv[i];
            //cout << filename.find(".asm") << "\n";
            if (filename.find(".asm") != string::npos) {

                filename_aux = formatFile(filename, original_filer, multiple_filesr, errorsr, symbols_tabler, definitions_tabler);
                if (filename_aux != "FAILED") {

                    symbols_tabler = get_symbols_table(filename_aux, errorsr, linesr, original_filer, symbols_tabler, definitions_tabler);
                    /*for (map<string, int>::const_iterator it = symbols_table.begin(); it != symbols_table.end(); ++it) {

                        std::cout << it->first << " " << to_string(it->second) << "\n";

                    }*/
                    remove(filename_aux.c_str()); //deleta o arquivo auxiliar criado
                    string object_file_string = create_object_string(errorsr, linesr, original_filer, symbols_tabler, uses_tabler, realocatorr);
                    
                    if (errorsr.size() > 0) {

                        for (j = 0; j < errorsr.size(); j++) {

                            cout << errorsr[j] << endl << endl;

                        }
                        if (i > 1) {

                            while (filenames.size() > 0) {

                                filename = filenames.back();
                                filenames.pop_back();
                                //cout << filename << endl;
                                remove(filename.c_str());

                            }

                        }

                    } else if (multiple_filesr) {

                        /*for (map<string, vector<int >>::const_iterator it = symbols_tabler.begin(); it != symbols_tabler.end(); ++it) {

                            std::cout << it->first << " " << to_string(it->second[0]) << " " << to_string(it->second[1]) << "\n";

                        }
                        for (map<string, int>::const_iterator it2 = definitions_tabler.begin(); it2 != definitions_tabler.end(); ++it2) {

                            std::cout << it2->first << " " << to_string(it2->second) << "\n";

                        }
                        for (map<string, vector<int >>::const_iterator it = uses_tabler.begin(); it != uses_tabler.end(); ++it) {

                            std::cout << it->first << " ";
                            for (size_t j = 0; j < it->second.size(); j++) {

                                cout << to_string(it->second[j]) << " ";

                            }
                            cout << endl;

                        }*/
                        object_file_string = "T: " + object_file_string;
                        vector <string > uses_string_arr;
                        string uses_string;
                        for (map<string, vector<int >>::const_iterator it = uses_tabler.begin(); it != uses_tabler.end(); ++it) {

                            uses_string = "U: " + it->first;
                            for (size_t j = 0; j < it->second.size(); j++) {

                                uses_string += " ";
                                uses_string += to_string(it->second[j]);

                            }
                            uses_string_arr.push_back(uses_string);
                            //cout << endl;

                        }
                        vector <string > definitions_string_arr;
                        for (map<string, int>::const_iterator it2 = definitions_tabler.begin(); it2 != definitions_tabler.end(); ++it2) {

                            definitions_string_arr.push_back("D: " + it2->first + " " + to_string(it2->second));

                        }
                        //cout << endl << realocatorr << endl << "Fim de arquivo" << endl << endl;
                        //cout << object_file_string << endl;
                        filename = filename.substr(0, filename.find(".asm"));
                        string title = filename;
                        //header.push_back("H: " + filename);
                        //header.push_back("H: " + to_string(realocatorr.size() - 3));
                        filename += ".o";
                        filenames.push_back(filename);
                        //cout << filename << endl;
                        ofstream obj_file(filename);
                        obj_file << "H: " + title << endl;
                        obj_file << "H: " + to_string(realocatorr.size() - 3) << endl;
                        obj_file << realocatorr << endl;
                        for (j = 0; j < uses_string_arr.size(); j++) {

                            obj_file <<  uses_string_arr[j] << endl;

                        }
                        for (j = 0; j < definitions_string_arr.size(); j++) {

                            obj_file <<  definitions_string_arr[j] << endl;

                        }
                        obj_file << object_file_string << endl;
                        obj_file.close();

                    } else {

                        filename = filename.substr(0, filename.find(".asm"));
                        filename += ".obj";
                        ofstream obj_file(filename);
                        obj_file << object_file_string << endl;
                        obj_file.close();

                    }

                } else {

                    if (i > 1) {

                        while (filenames.size() > 0) {

                            filename = filenames.back();
                            filenames.pop_back();
                            remove(filename.c_str());
                            //cout << "disney" << endl;

                        }

                    }
                    cout << "Houve um erro na formatacao e/ou pre-processamento do arquivo" << endl;
                    break;

                }
                
            } else {

                if (i > 1) {

                    while (filenames.size() > 0) {

                        filename = filenames.back();
                        filenames.pop_back();
                        remove(filename.c_str());
                        //cout << "disney" << endl;

                    }

                }
                cout << "Arquivo de entrada com extensao invalida" << "\n";
                break;

            }

        }

    }
    return 0;

}