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
    vector <map <string, vector<int >>> *global_uses_table = new vector <map <string, vector<int >>>;
    vector <map <string, vector<int >>> &global_uses_tabler = *global_uses_table;
    vector <vector <int >> *numbers_string = new vector<vector <int >>; 
    vector <vector <int >> &numbers_stringr = *numbers_string; 
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
        string final_object_string = create_final_object_string(filenamer, general_definitions_tabler, object_file_namer, global_uses_tabler, numbers_stringr);
        ofstream object_file(object_file_namer + "bj");
        object_file << final_object_string << endl;
        object_file.close();

    } 
    return 0;

}  
    
