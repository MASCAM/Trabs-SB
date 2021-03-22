#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "format_file.h"
#include "utilities.h"

int main(int argc, char *argv[]) {
    
    string filename;
    string filename_aux;
    vector <string >* errors = {};
    if (argc != 2) {

        cout << "Número de argumentos diferente de 2" << "\n";

    } else {

        filename = argv[1];
        //cout << filename.find(".asm") << "\n";
        if (filename.find(".asm") != string::npos) {

            filename_aux = formatFile(filename);
            cout << filename_aux << "\n";
            

        } else if (filename.find(".obj") != string::npos) {

            cout << filename << endl;

        } else {

            cout << "Arquivo de entrada com extensao invalida" << "\n";

        }

    }

}