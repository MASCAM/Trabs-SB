#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "utilities.h"
#include "binder.h"

using namespace std;

string create_object_string(vector <string > &filenamer, map <string, int> &general_definitions_tabler) {

    fstream file;
    string line;
    vector <string > aux = {};
    string object_string = "";
    string output_string = "";
    int *found = new int;
    int &foundr = *found;
    foundr = 0;
    vector <int > *object_code = new vector <int >;
    vector <int > &object_coder = *object_code;
    //file.open(filename);
    if (getline(file, line)) {  //se o arquivo é válido




    } else {

        cout << "Nao foi possivel abrir o arquivo especificado." << endl;
        file.close();

    }
    return object_string;

}

map <string, int> create_general_definitions_table(vector <string > &filenamer, map <string, int> &general_definitions_tabler, string &object_filenamer) {

    int *found = new int;
    int &foundr = *found;
    string line;
    string realocator;
    map <string, int> correction_factors_table; 
    int correction_factor = 0;
    vector <string > aux = {};
    fstream file;
    for (size_t i = 0; i < filenamer.size(); i++) {

        aux = {};
        fstream file;
        file.open(filenamer[i]);
        if (file.is_open() != false) {

            getline(file, line);
            aux.push_back(split({ line }, "H: ", foundr)[1]);
            //aux.pop_back();
            if (foundr > 0 && i == 0) {

                /*for (size_t j = 0; j < aux.size(); j++) {

                    cout << aux[j] << endl;

                }*/

                object_filenamer = aux[0] + ".o";
                //cout << object_filenamer << endl;

            }
            correction_factors_table[aux[0]] = correction_factor;
            aux.pop_back();
            for (map<string, int>::const_iterator it2 = correction_factors_table.begin(); it2 != correction_factors_table.end(); ++it2) {

                std::cout << it2->first << " " << to_string(it2->second) << "\n";

            }
            getline(file, line);
            aux.push_back(split({ line }, "H: ", foundr)[1]);
            correction_factor += atoi(aux[0].c_str());
            aux.pop_back();
            getline(file, line);
            aux.push_back(split({ line }, "R: ", foundr)[1]);
            realocator = aux[0];
            cout << realocator << endl;
            aux.pop_back();
            foundr = 0;
            getline(file, line);
            aux = split({ line }, "D: ", foundr);
            while (foundr <= 0) {

                aux = {};
                foundr = 0;
                getline(file, line);
                aux = split({ line }, "D: ", foundr);

            }
            while (foundr > 0) {

                aux.erase(aux.begin());
                aux = split(aux, " ", foundr);
                //general_definitions_tabler[aux[0]] = 
                aux = split({ line }, "D: ", foundr);

            }
            cout << aux[1] << endl;
            file.close();

        }

        

    }
    return general_definitions_tabler;

}

