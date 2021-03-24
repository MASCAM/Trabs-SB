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

vector <string > split(vector<string > sentences, string delimiter, bool &foundr) { //função split semelhante à encontrada em javascript

    string word = "";
    string sentence = "";
    size_t i = 0;
    vector <string > words = {};
    size_t pos;
    for (i = 0; i < sentences.size(); i++) {

        sentence = sentences[i];
        while ((pos = sentence.find(delimiter)) != string::npos) {

            foundr = true;
            word = sentence.substr(0, pos);
            sentence.erase(0, pos + delimiter.length());
            words.push_back(word);

        }
        if (sentence != "" && sentence != " " && sentence != "\n") {

            words.push_back(sentence);

        }

    }
    if (words.size() == 0) {

        words = sentences;

    }
    return words;

}
