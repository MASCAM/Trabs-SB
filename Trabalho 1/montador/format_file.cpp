#include <iostream>
#include <fstream>
#include <string>
#include <vector> 

#include "format_file.h"

using namespace std;

string formatFile(string filename, vector <string > &original_filer) {

    fstream file;
    string line;
    int i = 0;
    //int section_text_position = 0;
    file.open(filename);                //abre o arquivo que foi passado como argumento
    if (file.is_open() != false) {

        while (getline(file, line)) {

            for (size_t j = 0; j < line.length(); j++) {

                if (line[j] == ' ' && line[j + 1] == ' ') { //remove espaços repetidos

                    line.erase(line.begin() + j + 1);
                    j--;

                }
                if (j == 0 && line[j] == ' ') { //remove espaço no início da linha

                    line.erase(line.begin());
                    j--;

                }
                if (line[j] == ';') {

                    line.erase(line.begin() + j, line.end());

                }
                if (line[j] == ' ' && j + 2 == line.length()) {

                    line.erase(line.begin() + j);
                    j--;

                }
                line[j] = toupper(line[j]); //coloca tudo em caixa-alta

            }
            /*if (line == "SECTION TEXT") { //caso quisesse colocar no final do arquivo de saída

                section_text_position = i;

            }*/
            original_filer.push_back(line); //retorna para o vetor de linhas
            i++;

        }

    } else {

        cout << "Nao foi possivel abrir o arquivo especificado." << "\n";
        return "FAILED";

    }
    file.close();
    string filename_aux = "_out.asm"; 
    filename_aux = filename.replace(filename.find(".asm"), 9, filename_aux);
    ofstream file_aux(filename_aux); //cria um arquivo de saída
    /*for (size_t k = section_text_position; k < lines_from_file.size(); k++) { //coloca o section text primeiro num arquivo de sa´´ida

        file_aux << lines_from_file[k] + "\n";

    }
    for (int l = 0; l < section_text_position; l++) { //e finalmente a seção de dados

        file_aux << lines_from_file[l] + "\n";

    }*/
    for (size_t k = 0; k < original_filer.size(); k++) { //coloca o section text primeiro num arquivo de sa´´ida

        file_aux << original_filer[k] + "\n";

    }
    file_aux.close();
    return filename_aux;

}