#include <iostream>
#include <fstream>
#include <string>
#include "../libraries/format_file.h"

int main(int argc, char *argv[]) {

    string filename;
    if (argc != 2) {

        cout << "Número de argumentos diferente de 2" << "\n";

    } else {

        filename = argv[1];
        //cout << filename.find(".asm") << "\n";
        if (filename.find(".asm") != string::npos) {

            cout << filename << endl;

        } else if (filename.find(".obj") != string::npos) {

            cout << filename << endl;

        } else {

            cout << "Arquivo de entrada com extensao invalida" << "\n";

        }

    }

}