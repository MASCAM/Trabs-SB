#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "utilities.h"
#include "binder.h"

using namespace std;



string create_final_object_string(vector <string > &filenamer, map <string, int> &general_definitions_tabler, string &object_filenamer, vector <map <string, vector<int >>> &global_uses_tabler, vector <vector <int >> &numbers_stringr) {

    int *found = new int;
    int &foundr = *found;
    string line;
    string realocator;
    map <string, int> correction_factors_table; 
    int correction_factor = 0;
    vector <string > aux = {};
    map <string, vector<int >> aux_map;
    string aux2;
    fstream file;
    string final_object_string = "";
    for (size_t i = 0; i < filenamer.size(); i++) {

        aux = {};
        foundr = 0;
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
            /*for (map<string, int>::const_iterator it2 = correction_factors_table.begin(); it2 != correction_factors_table.end(); ++it2) {

                std::cout << it2->first << " " << to_string(it2->second) << "\n";

            }*/
            getline(file, line);
            aux.push_back(split({ line }, "H: ", foundr)[1]);
            correction_factor += atoi(aux[0].c_str());
            aux.pop_back();
            getline(file, line);
            aux.push_back(split({ line }, "R: ", foundr)[1]);
            realocator = aux[0];
            //cout << realocator << endl;
            aux.pop_back();
            foundr = 0;
            getline(file, line);
            aux = split({ line }, "D: ", foundr);
            global_uses_tabler.push_back(aux_map);
            if (aux[0].find("T: ") == string::npos) {

                //cout << "disney" << endl;
                while (foundr <= 0 || aux[0].find("T: ") != string::npos) {

                    foundr = 0;
                    aux = split({ line }, "U: ", foundr);
                    if (foundr > 0) {

                        aux.erase(aux.begin());
                        aux = split(aux, " ", foundr);
                        aux2 = aux[0];
                        aux.erase(aux.begin());
                        //cout << aux2 << endl;
                        for (size_t j = 0; j < aux.size(); j++) {

                            //cout << aux[j] << endl;
                            global_uses_tabler[i][aux2].push_back(atoi(aux[j].c_str()));
                            //cout << to_string(global_uses_tabler[i][aux2][j]) << endl;

                        }

                    }
                    foundr = 0;
                    getline(file, line);
                    aux = split({ line }, "D: ", foundr);

                } 

            } else {

                foundr = 0;

            }
            while (foundr > 0) {

                aux.erase(aux.begin());
                aux = split(aux, " ", foundr);
                //cout << aux[0] << endl;
                general_definitions_tabler[aux[0]] = atoi(aux[1].c_str()) + correction_factors_table[filenamer[i].substr(0, filenamer[i].find(".o"))];
                foundr = 0;
                getline(file, line);
                aux = split({ line }, "D: ", foundr);

            }
            /*for (map<string, int>::const_iterator it2 = general_definitions_tabler.begin(); it2 != general_definitions_tabler.end(); ++it2) {

                std::cout << it2->first << " " << to_string(it2->second) << "\n";

            }*/
            aux = split(aux, "T: ", foundr);
            aux.erase(aux.begin());
            aux = split(aux, " ", foundr);
            numbers_stringr.push_back({ });
            for (size_t it = 0; it < aux.size(); it++) {

                int sum = atoi(aux[it].c_str());
                if (realocator[it] == '1') {

                    sum += correction_factors_table[filenamer[i].substr(0, filenamer[i].find(".o"))];
                    

                }
                numbers_stringr[i].push_back(sum);

            }
            
            
        }
        file.close();

    }
    for (size_t it = 0; it < numbers_stringr.size(); it++) {

        for (map<string, vector<int >>::const_iterator it2 = global_uses_tabler[it].begin(); it2 != global_uses_tabler[it].end(); it2++) {

            //cout << it2->first << " Definido como: " << to_string(general_definitions_tabler[it2->first]) << endl;
            for (size_t j = 0; j < it2->second.size(); j++) {

                //cout << it2->second[j] << endl;
                numbers_stringr[it][it2->second[j]] = general_definitions_tabler[it2->first];

            }

        }

    }
    for (size_t it = 0; it < numbers_stringr.size(); it++) {

        for (size_t it2 = 0; it2 < numbers_stringr[it].size(); it2++) {

            final_object_string += to_string(numbers_stringr[it][it2]) + " ";

        }

    }
    final_object_string = final_object_string.substr(0, final_object_string.length() - 1);
    return final_object_string;

}

