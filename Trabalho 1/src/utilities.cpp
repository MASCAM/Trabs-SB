#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "utilities.h"

using namespace std;

map <string, vector<int>> getInstructionsTable() {
    //retorna uma estrutura mapeada de instruções na qual estão especificadas o nome da instrução em sua chave
    //e os valores correspondentes ao código da instrução e seu tamanho em palavras
    map <string, vector<int>> instructions;
    instructions["ADD"] = { 1, 2 };       // ACC <- ACC + mem(OP)
    instructions["SUB"] = { 2, 2 };       // ACC <- ACC - mem(OP)
    instructions["MUL"] = { 3, 2 };       // ACC <- ACC x mem(OP)
    instructions["DIV"] = { 4, 2 };       // ACC <- ACC ÷ mem(OP)
    instructions["JMP"] = { 5, 2 };       // PC <- OP
    instructions["JMPN"] = { 6, 2 };      // Se ACC<0 então PC <- OP
    instructions["JMPP"] = { 7, 2 };      // Se ACC>0 então PC <- OP
    instructions["JMPZ"] = { 8, 2 };      // Se ACC=0 então PC <- OP
    instructions["COPY"] = { 9, 3 };      // mem(OP2) <- mem(OP1)
    instructions["LOAD"] = { 10, 2 };     // ACC <- mem(OP)
    instructions["STORE"] = { 11, 2 };    // mem(OP) <- ACC
    instructions["INPUT"] = { 12, 2 };    // mem(OP) <- entrada
    instructions["OUTPUT"] = { 13, 2 };   // saída <- mem(OP)
    instructions["STOP"] = { 14, 1 };     // Suspende a execução
    return instructions;

}


map <string, vector<int>> getDirectivesTable() {
    //retorna uma estrutura mapeada de dieretivas cujos nomes estão especificados nas chaves
    //os valores dentro de cada chave correspondem respectivamente ao número de operandos e ao número de espaços de memória reservados
    map <string, vector<int>> directives;
    directives["SPACE"] = { 0, 1 };
    directives["CONST"] = { 1, 1 };
    return directives;

}

vector <string > split(string line, string delimiter) { //função split semelhante à encontrada em javascript

    string word = "";
    vector <string > words = {};
    size_t pos;
    while ((pos = line.find(delimiter)) != string::npos) {

        word = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        words.push_back(word);

    }
    return words;

}
