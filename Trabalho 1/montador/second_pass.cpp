#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector> 
#include <sstream>

#include "utilities.h"
#include "define_word_class.h"
#include "second_pass.h"

using namespace std;

string create_object_string(map <string, int> symbols_table, vector <string > &errorsr, vector <line_of_words_t > &linesr, vector <string > &original_filer) {

    string object_string;
    vector <int > object_code;
    vector <int > operation_code;
    vector <word_t > operation_words; 
    map <string, vector<int>> instructions = get_instructions_table();
    map <string, vector<int>> directives = get_directives_table();
    string erro;
    //int PC = 0;
    int operation_number = 0;
    int operators_number = 0;
    bool found_instruction = false;
    for (size_t i = 0; i < linesr.size(); i++) {    //para cada linha armazenada na primeira passagem

        //cout << to_string(linesr[i].line[0].line_position + 1) << ", ";
        for (size_t j = 0; j < linesr[i].line.size(); j++) {    //para cada palavra

            //cout << linesr[i].line[j].word << ", ";
            if (linesr[i].line[j].is_label == false) { //ignorando os rótulos da linha

                if (found_instruction == true) { //se achou a instrução

                    vector <int > operation_code = get_operation_code(symbols_table, errorsr, original_filer, operation_words, operation_number);
                    //a função acima gera um vetor com os códigos que serão passados para o arquivo objeto
                    for (size_t l = 0; l < operation_code.size(); l++) { //passa para o código objeto

                        object_code.push_back(operation_code[l]);

                    }
                    found_instruction = false;
                    break;

                } else {    //senão

                    if (instructions.find(linesr[i].line[j].word) != instructions.end()) { //se achou a instrução

                        operation_number = instructions[linesr[i].line[j].word][0];
                        if (operation_number == 14) {

                            object_code.push_back(operation_number);
                            break;

                        }
                        operators_number = instructions[linesr[i].line[j].word][1] - 1; //pega os dados da instrução, opcode e número de operandos
                        if (operators_number == 2) { //se for copy

                            operators_number -= 1;  //decrementa o número de operandos, pois a palavra está emendada

                        }
                        if (j + 1 + operators_number < linesr[i].line.size()) { //se houver mais operandos que o desejado

                            erro = "ERRO SINTATICO NA LINHA " + to_string(linesr[i].line[j].line_position + 1) + ":\n"  + original_filer[linesr[i].line[j].line_position] + "\n" + "NUMERO DE OPERANDOS MAIOR DO QUE O ESPERADO";
                            errorsr.push_back(erro);
                            break;

                        } else if (j + 1 + operators_number > linesr[i].line.size()) { //se houver menos operandos que o desejado

                            erro = "ERRO SINTATICO NA LINHA " + to_string(linesr[i].line[j].line_position + 1) + ":\n"  + original_filer[linesr[i].line[j].line_position] + "\n" + "NUMERO DE OPERANDOS MENOR DO QUE O ESPERADO";
                            errorsr.push_back(erro);
                            break;

                        } else { //senão

                            size_t k = j + 1;
                            while (k < linesr[i].line.size()) { //coloca o resto da linha num vetor pra ser tratado

                                operation_words.push_back(linesr[i].line[k]);
                                k++;

                            }

                        }
                        found_instruction = true;

                    } else if (directives.find(linesr[i].line[j].word) != directives.end()) { //se achou a diretiva

                        if (directives[linesr[i].line[j].word][0] == 0) { //se for SPACE reserva 0 no codigo objeto

                            if (j + 1 < linesr[i].line.size()) { //se houver mais operandos que o desejado

                                erro = "ERRO SINTATICO NA LINHA " + to_string(linesr[i].line[j].line_position + 1) + ":\n"  + original_filer[linesr[i].line[j].line_position] + "\n" + "NUMERO DE OPERANDOS MAIOR DO QUE O ESPERADO";
                                errorsr.push_back(erro);
                                break;

                            }  else {

                                object_code.push_back(0);
                                break;

                            }


                        } else if (directives[linesr[i].line[j].word][0] == 1) { //se for CONST grava a constante no código objeto

                            if (j + 2 < linesr[i].line.size()) { //se houver mais operandos que o desejado

                                erro = "ERRO SINTATICO NA LINHA " + to_string(linesr[i].line[j].line_position + 1) + ":\n"  + original_filer[linesr[i].line[j].line_position] + "\n" + "NUMERO DE OPERANDOS MAIOR DO QUE O ESPERADO";
                                errorsr.push_back(erro);
                                break;

                            } else if (j + 2 > linesr[i].line.size()) { //se houver menos operandos que o desejado

                                erro = "ERRO SINTATICO NA LINHA " + to_string(linesr[i].line[j].line_position + 1) + ":\n"  + original_filer[linesr[i].line[j].line_position] + "\n" + "NUMERO DE OPERANDOS MENOR DO QUE O ESPERADO";
                                errorsr.push_back(erro);
                                break;

                            } else if (is_number(linesr[i].line[j + 1].word)) {

                                object_code.push_back(atoi(linesr[i].line[j + 1].word.c_str())); //converte de string pra int

                            } else {

                                erro = "ERRO SINTATICO NA LINHA " + to_string(linesr[i].line[j + 1].line_position + 1) + ":\n"  + original_filer[linesr[i].line[j + 1].line_position] + "\n" + "TIPO INVALIDO DE OPERANDO, OPERANDO NAO E UM NUMERO INTEIRO";
                                errorsr.push_back(erro);

                            }

                        }

                    } else {

                        break;

                    }

                }

            } else {

                continue;

            }

        }
        operation_words = {};
        found_instruction = false;
        //cout << to_string(linesr[i].PC) << endl;

    }
    for (size_t i = 0; i < object_code.size(); i++) {   //passa os números para o arquivo objeto

        if ((i + 1) == object_code.size()) {

            object_string += to_string(object_code[i]);

        } else {

            object_string += to_string(object_code[i]) + " ";

        }

    }
    return object_string;

}

vector <int > get_operation_code(map <string, int> symbols_table, vector <string > &errorsr, vector <string > &original_filer, vector <word_t > operation_words, int operation_number) {

    //verifica possíveis erros e gera o código objeto para cada instrução da entrada
    int *found = new int;
    int &foundr = *found;
    foundr = 0;
    string erro;
    vector <string > words = {};
    /*for (size_t l = 0; l < operation_words.size(); l++) {

        cout << operation_words[l].word << ", ";

    }
    cout << endl;*/
    vector <int > operation_code = {};
    //cout << to_string(operation_number) << endl;
    operation_code.push_back(operation_number);
    switch (operation_number) {

        case 1:
        case 2:
        case 3:
        case 4:
            if (is_number(operation_words[0].word)) {

                erro = "ERRO SINTATICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "TIPO INVALIDO DE OPERANDO, ESPERAVA-SE UM SIMBOLO E OBTEVE-SE UM NUMERO INTEIRO";
                errorsr.push_back(erro);

            } else if (symbols_table.find(operation_words[0].word) != symbols_table.end()) { //se achou o símbolo na tabela

                operation_code.push_back(symbols_table[operation_words[0].word]);

            } else {

                erro = "ERRO SEMANTICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "OPERANDO NAO E UM SIMBOLO VALIDO (NAO DEFINIDO)";
                errorsr.push_back(erro);

            }
            break;

        case 5:
        case 6:
        case 7:
        case 8:
            if (is_number(operation_words[0].word)) {

                erro = "ERRO SINTATICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "TIPO INVALIDO DE OPERANDO, ESPERAVA-SE UM SIMBOLO E OBTEVE-SE UM NUMERO INTEIRO";
                errorsr.push_back(erro);

            } else if (symbols_table.find(operation_words[0].word) != symbols_table.end()) { //se achou o símbolo na tabela

                operation_code.push_back(symbols_table[operation_words[0].word]);

            } else {

                erro = "ERRO SEMANTICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "OPERANDO NAO E UM SIMBOLO VALIDO (NAO DEFINIDO)";
                errorsr.push_back(erro);

            }
            break;

        case 9:
            words.push_back(operation_words[0].word);
            words = split(words, ",", foundr);
            if (foundr > 0) {

                if (foundr > 1) {

                    erro = "ERRO SINTATICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "FORAM ENCONTRADOS DOIS OU MAIS TOKENS DE SEPARACAO DE OPERANDOS ','";
                    errorsr.push_back(erro);

                } else {

                    if (is_number(words[0])) {

                        erro = "ERRO SINTATICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "TIPO DO PRIMEIRO OPERANDO E INVALIDO, ESPERAVA-SE UM SIMBOLO E OBTEVE-SE UM NUMERO INTEIRO";
                        errorsr.push_back(erro);

                    } else if (symbols_table.find(words[0]) != symbols_table.end()) { //se achou o símbolo na tabela

                        if (is_number(words[1])) {

                            erro = "ERRO SINTATICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "TIPO DO SEGUNDO OPERANDO E INVALIDO, ESPERAVA-SE UM SIMBOLO E OBTEVE-SE UM NUMERO INTEIRO";
                            errorsr.push_back(erro);

                        } else if (symbols_table.find(words[1]) != symbols_table.end()) { //se achou o símbolo na tabela

                            operation_code.push_back(symbols_table[words[0]]);
                            operation_code.push_back(symbols_table[words[1]]);

                        } else {

                            erro = "ERRO SEMANTICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "SEGUNDO OPERANDO NAO E UM SIMBOLO VALIDO (NAO DEFINIDO)";
                            errorsr.push_back(erro);

                        }

                    } else {

                        erro = "ERRO SEMANTICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "PRIMEIRO OPERANDO NAO E UM SIMBOLO VALIDO (NAO DEFINIDO)";
                        errorsr.push_back(erro);

                    }

                }
            
            } else {

                erro = "ERRO SINTATICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "NAO FOI ENCONTRADO O TOKEN DE SEPARACAO DE OPERANDOS ','";
                errorsr.push_back(erro);

            }
            break;

        case 10:
        case 11:
        case 12:
        case 13:
            if (is_number(operation_words[0].word)) {

                erro = "ERRO SINTATICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "TIPO INVALIDO DE OPERANDO, ESPERAVA-SE UM SIMBOLO E OBTEVE-SE UM NUMERO INTEIRO";
                errorsr.push_back(erro);

            } else if (symbols_table.find(operation_words[0].word) != symbols_table.end()) { //se achou o símbolo na tabela

                operation_code.push_back(symbols_table[operation_words[0].word]);

            } else {

                erro = "ERRO SEMANTICO NA LINHA " + to_string(operation_words[0].line_position + 1) + ":\n"  + original_filer[operation_words[0].line_position] + "\n" + "OPERANDO NAO E UM SIMBOLO VALIDO (NAO DEFINIDO)";
                errorsr.push_back(erro);

            }
            break;

        case 14:
            break;

        default:
            break;

    }
    return operation_code;

}

