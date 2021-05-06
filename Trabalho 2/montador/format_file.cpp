#include <iostream>
#include <fstream>
#include <string>
#include <vector> 

#include "format_file.h"
#include "utilities.h"

using namespace std;

string formatFile(string filename, vector <string > &original_filer, bool &multiple_filesr) {

    fstream file;
    string line;
    int i = 0;
    bool section_data = false;
    bool begin = false;
    bool end = false;
    vector <string > formatted_lines;
    //int section_text_position = 0;
    file.open(filename);                //abre o arquivo que foi passado como argumento
    if (file.is_open() != false) {

        while (getline(file, line)) {

            original_filer.push_back(line);
            for (size_t j = 0; j < line.length(); j++) {

                if ((line[j] == ' ' && (line[j + 1] == ' ' || line[j + 1] == '\t')) || (line[j] == '\t' && (line[j + 1] == ' ' || line[j + 1] == '\t'))) { //remove espaços repetidos

                    line.erase(line.begin() + j + 1);
                    j--;

                }
                if ((j == 0 && line[j] == ' ') || (j == 0 && line[j] == '\t')) { //remove espaço no início da linha

                    line.erase(line.begin());
                    j--;

                } else if ((j + 1 == line.length() && line[j] == ' ') || (j + 1 == line.length() && line[j] == '\t')) {

                    line.erase(line.begin() + j);
                    j--;

                }
                if (line[j] == ';') {

                    line.erase(line.begin() + j, line.end());

                }
                line[j] = toupper(line[j]); //coloca tudo em caixa-alta

            }
            //cout << line << endl;
            /*if (line == "SECTION TEXT") { //caso quisesse colocar no final do arquivo de saída

                section_text_position = i;

            }*/
            if (line == "SECTION DATA") {

                section_data = true;

            }
            if (line.find_first_of("BEGIN") != string::npos && section_data == false && begin == false) {

                begin = true;
                //cout << line << endl;

            }
            formatted_lines.push_back(line); //retorna para o vetor de linhas
            i++;

        }
        if (line == "END") {

            end = true;
            //cout << line << endl;

        }
        if (begin && end && !multiple_filesr) {

            cout << "Ha as diretivas begin e end no arquivo sendo que ha uma chamada de um unico arquivo pro programa" << endl;
            return "FAILED";

        } else if ((!begin || !end) && multiple_filesr) {

            cout << "Nao estao presentes a(s) diretiva(s) begin e/ou end no arquivo sendo que ha uma chamada de varios arquivos pro programa" << endl;
            return "FAILED";

        }

    } else { //caso o arquivo seja inválido

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
    for (size_t k = 0; k < formatted_lines.size(); k++) { //coloca as linhas num arquivo de saída

        file_aux << formatted_lines[k] + "\n";

    }
    file_aux.close();
    return filename_aux;

}