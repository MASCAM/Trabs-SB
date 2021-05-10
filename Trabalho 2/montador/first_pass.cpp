#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector> 
#include <sstream>

#include "utilities.h"
#include "define_word_class.h"
#include "first_pass.h"

using namespace std;

map <string, vector<int >> get_symbols_table(string filename_aux, vector <string > &errorsr, vector <line_of_words_t > &linesr, vector <string > &original_filer,  map <string, vector<int >> &symbols_tabler, map <string, int> &definitions_tabler) {

    fstream file;
    string line;
    string erro;
    map <string, vector<int>> instructions = get_instructions_table();
    map <string, vector<int>> directives = get_directives_table();
    file.open(filename_aux);
    int i = 0;
    int PC = 0;
    //bool only_labels = false;
    while (line != "SECTION TEXT") { //primeiro percorre-se a seção de texto

        if (getline(file, line)) {

            i++;

        } else {

            break;

        }

    }
    while (getline(file, line)) {

        if (!(line.empty() || line.find_first_not_of(' ') == string::npos || line[line.find_first_not_of(' ')] == ';')) {
        //a linha acima ignora linhas vazias ou que possuem somente comentários
            line_of_words_t actual_line;
            actual_line.PC = PC;
            actual_line.add_line(line, i, original_filer, errorsr); //pega uma linha do arquivo de entrada e separa suas palavras
            /*for (size_t l = 0; l < actual_line.line.size(); l++) {

                cout << actual_line.line[l].word << endl;

            }*/
            

            while (actual_line.line.back().is_label == true) {  //para o caso de linhas que só contêm rótulos
        
                if (getline(file, line)) {

                    i++;
                    actual_line.add_line(line, i, original_filer, errorsr);

                } else {

                    break;

                }

            }
            linesr.push_back(actual_line);

        } 
        i++;

    }
    file.close();
    line = "";
    i = 0;
    file.open(filename_aux);
    while (line != "SECTION DATA" ) { //após a seção de texto percorre-se a seção de dados

        if (getline(file, line)) {

            i++;

        } else {

            break;

        }
        

    }
    while (getline(file, line)) {

        if (line == "SECTION TEXT") {

            break;

        }
        if (!(line.empty() || line.find_first_not_of(' ') == string::npos || line[line.find_first_not_of(' ')] == ';')) {
        //a linha acima ignora linhas vazias ou que possuem somente comentários
            line_of_words_t actual_line;
            actual_line.PC = PC;
            actual_line.add_line(line, i, original_filer, errorsr);
            /*for (size_t l = 0; l < actual_line.line.size(); l++) {

                cout << actual_line.line[l].word << endl;

            }*/
            
            /*if (actual_line.line.front().is_label == false) { //presume-se que todas as linhas da seção de dados devem ter rótulos

                erro = "ERRO SINTATICO NA LINHA " + to_string(actual_line.line[i].line_position + 1) + ":\n"  + original_filer[i + 1] + "\n" + "NAO HA ROTULO NA LINHA DA SECAO DE DADOS";
                errorsr.push_back(erro);
                continue;

            }*/
            while (actual_line.line.back().is_label == true) {  //para o caso de linhas que só contêm rótulos
        
                if (getline(file, line)) {

                    i++;
                    actual_line.add_line(line, i, original_filer, errorsr);

                } else {

                    break;

                }

            }
            linesr.push_back(actual_line);

        } 
        i++;

    }
    for (size_t j = 0; j < linesr.size(); j++) { //laço de repetição que irá construir a tabela de símbolos

        linesr[j].PC = PC;
        line_of_words_t actual_line;
        actual_line = linesr[j];
        for (size_t l = 0; l < actual_line.line.size(); l++) {  //para todas as palavras de uma linha

            
            if (actual_line.line[l].is_label == true) { //se for um rótulo

                
                if (symbols_tabler.find(actual_line.line[l].word) != symbols_tabler.end()) { //se está duplicado é erro


                    erro = "ERRO SEMANTICO NA LINHA " + to_string(actual_line.line[l].line_position + 1) + ":\n"  + original_filer[actual_line.line[l].line_position] + "\n" + "SIMBOLO REDEFINIDO";
                    errorsr.push_back(erro);
                    break;

                } else {    //senão adiciona à tabela de símbolos com o PC atual

                    symbols_tabler[actual_line.line[l].word] = {PC, 0};
                    if (definitions_tabler.find(actual_line.line[l].word) != definitions_tabler.end()) {

                        definitions_tabler[actual_line.line[l].word] = PC;

                    }

                }

            } else { //caso não seja um rótulo

                if (instructions.find(actual_line.line[l].word) != instructions.end()) { //se existe na tabela de instruções

                    PC += instructions[actual_line.line[l].word][1]; //incrementa o PC
                    break;

                } else if (directives.find(actual_line.line[l].word) != directives.end()) { //se existe na tabela de diretivas

                    PC += directives[actual_line.line[l].word][1]; //incrementa o PC
                    break;

                } else { //caso a instrução ou diretiva seja inválida é erro

                    //cout << actual_line.line[l].word << endl;
                    erro = "ERRO SINTATICO NA LINHA " + to_string(actual_line.line[l].line_position + 1) + ":\n"  + original_filer[actual_line.line[l].line_position] + "\n" + "INSTRUCAO OU DIRETIVA INVALIDA";
                    errorsr.push_back(erro);
                    break;

                }

            }

        }

    }
    return symbols_tabler; //retorna a tabela de símbolos montada (map)

}


