#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "utilities.h"
#include "binder.h"


int main(int argc, char *argv[]) {
    
    vector <string > *filename = new vector<string >;
    vector <string > &filenamer = *filename;
    string *object_file_name = new string;
    string &object_file_namer = *object_file_name;
    map <string, int> *general_definitions_table = new map <string, int>;
    map <string, int> &general_definitions_tabler = *general_definitions_table;
    string filename_aux;
    vector <string > object_string = {};
    if (argc < 3 || argc > 4) {

        cout << "Número de argumentos menor que 3 ou maior que 4 (sao aceitos 2 ou 3 arquivos de entrada)" << "\n";

    } else {

        for (int i = 1; i < argc; i++) {

            filenamer.push_back(argv[i]);
        
        }
        //cout << argc << endl;
        for (int i = 1; i < argc; i++) {

            if (filenamer[i - 1].find(".o") == string::npos) {

                cout << "Ha um arquivo de entrada com extensao invalida" << "\n";
                return 0;

            }

        }
        general_definitions_tabler = create_general_definitions_table(filenamer, general_definitions_tabler, object_file_namer);
        for (int i = 1; i < argc; i++) {


            //cout << filename.find(".asm") << "\n";
            //cout << filenamer[i - 1] << endl;
            //cout << filename << endl;
            /*object_string = create_object_file(filenamer);
            filenamer[i] = filenamer[i].substr(0, filenamer[i].find(".o"));
            filenamer[i] += ".obj";
            ofstream object_file(filenamer[i]);
            for (size_t i = 0; i < object_string.size(); i++) {

                object_file << object_string[i] << endl;

            }
            object_file.close();*/
        
        }

    } 
    return 0;

}  
    
