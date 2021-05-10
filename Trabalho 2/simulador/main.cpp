#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "utilities.h"
#include "simulator.h"


int main(int argc, char *argv[]) {
    
    string filename;
    vector <string > output_lines = {};
    if (argc != 2) {

        cout << "Número de argumentos diferente de 2" << "\n";

    } else {

        filename = argv[1];
        //cout << filename.find(".asm") << "\n";
        if (filename.find(".obj") != string::npos) {

            //cout << filename << endl;
            output_lines = simulate_object_file(filename);
            filename = filename.substr(0, filename.find(".obj"));
            filename += ".out";
            ofstream out_file(filename);
            for (size_t i = 0; i < output_lines.size(); i++) {

                out_file << output_lines[i] << endl;

            }
            out_file.close();

        } else {

            cout << "Arquivo de entrada com extensao invalida" << "\n";

        }

    }

}  
    
