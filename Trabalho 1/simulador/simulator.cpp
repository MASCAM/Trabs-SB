#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "utilities.h"
#include "simulator.h"

using namespace std;

vector <string > simulate_object_file(string filename) {

    fstream file;
    string line;
    vector <string > aux = {};
    vector <string > OUTPUT = {};
    string output_string = "";
    int *found = new int;
    int &foundr = *found;
    int *PC = new int;
    int &PCr = *PC;
    int *ACC = new int;
    int &ACCr = *ACC;
    foundr = 0;
    PCr = 0;
    ACCr = 0;
    vector <int > *object_code = new vector <int >;
    vector <int > &object_coder = *object_code;
    file.open(filename);
    if (getline(file, line)) {  //se o arquivo é válido

        aux.push_back(line);
        aux = split(aux, " ", foundr);
        for (size_t l = 0; l < aux.size(); l++) {   //lê todos os números e os passa pra um vetor de inteiros

            object_coder.push_back(atoi(aux[l].c_str()));
            //cout << to_string(object_code[l]) << endl;

        }
        while (true) {  //executa até o STOP

            output_string = execute_instruction(PCr, ACCr, object_coder);   //chamada da função que realiza as instruções
            if (output_string == "break") {     //caso for STOP, quebra a repetição

                break;

            } else if (output_string != "") {   //caso há um OUTPUT o armazena para posteriormente passar para o arquivo .out

                OUTPUT.push_back(output_string);

            }

        }


    } else {

        cout << "Nao foi possivel abrir o arquivo especificado." << endl;
        file.close();

    }
    return OUTPUT;

}

string execute_instruction(int &PC, int &ACC, vector <int > &object_code) {

    string output_string = "";
    int opcode = object_code[PC];
    switch (opcode) {

        case 1: //OPERAÇÃO ADD
            ACC += object_code[object_code[PC + 1]];
            PC += 2;
            break;

        case 2: //OPERAÇÃO SUB
            ACC -= object_code[object_code[PC + 1]];
            PC += 2;
            break;

        case 3: //OPERAÇÃO MUL
            ACC *= object_code[object_code[PC + 1]];
            PC += 2;
            break;

        case 4: //OPERAÇÃO DIV
            ACC /= object_code[object_code[PC + 1]];
            PC += 2;
            break;

        case 5: //OPERAÇÃO JMP
            PC = object_code[PC + 1];
            break;

        case 6: //OPERAÇÃO JMPN
            if (ACC < 0) {

                PC = object_code[PC + 1];

            } else {

                PC += 2;

            }
            break;

        case 7: //OPERAÇÃO JMPP
            if (ACC > 0) {

                PC = object_code[PC + 1];

            } else {

                PC += 2;

            }
            break;

        case 8: //OPERAÇÃO JMPZ
            if (ACC == 0) {

                PC = object_code[PC + 1];

            } else {

                PC += 2;

            }
            break;

        case 9: //OPERAÇÃO COPY
            object_code[object_code[PC + 2]] = object_code[object_code[PC + 1]];
            PC += 3;
            break;

        case 10: //OPERAÇÃO LOAD
            ACC = object_code[object_code[PC + 1]];
            PC += 2;
            break;

        case 11: //OPERAÇÃO STORE
            object_code[object_code[PC + 1]] = ACC;
            PC += 2;
            break;

        case 12: //OPERAÇÃO INPUT
            cout << "DIGITE UM NUMERO INTEIRO VALIDO E APERTE ENTER:" << endl;
            cin >> object_code[object_code[PC + 1]];
            PC += 2;
            break;

        case 13: //OPERAÇÃO OUTPUT
            output_string = "OUTPUT: " + to_string(object_code[object_code[PC + 1]]);
            PC += 2;
            break;

        case 14: //OPERAÇÃO STOP
            PC += 1;
            cout << "PC <- " << to_string(PC) << endl;
            cout << "ACC <- " << to_string(ACC) << endl;
            return "break";
    
        default:
            break;

    }
    cout << "PC <- " << to_string(PC) << endl;
    cout << "ACC <- " << to_string(ACC) << endl;
    cout << output_string << endl << endl;
    output_string.erase(0, output_string.find_first_of("-0123456789")); //separa somente o número do output para passar pro arquivo
    return output_string;

}

