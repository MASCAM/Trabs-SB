#include <iostream>
#include <string>
#include <vector>

#include "define_word_class.h"
#include "utilities.h"

using namespace std;

/*line_of_words_t::line_of_words_t(string line, int line_position, vector <string > &original_filer, vector <string > &errorsr) {

  this->lines_in_original_file.push_back(line_position);

}*/

void line_of_words_t::add_line(string line, int line_position, vector <string > &original_filer, vector <string > &errorsr) {

  //this->lines_in_original_file.push_back(line_position);
  vector <string > words;
  word_t word;
  word.is_label = false;
  //bool validate_word = false;
  int *found = new int;
  int &foundr = *found;
  foundr = 0;
  string erro = "";
  words.push_back(line); 
  words = split(words, ":", foundr);
  if (foundr != 0) {  //se existe label

    word.is_label = true;
    if (foundr > 1) { //se há mais de uma é erro

      erro = "ERRO SINTATICO NA LINHA " + to_string(line_position + 1) + ":\n"  + original_filer[line_position] + "\n" + "DUPLA DECLARACAO DE ROTULO OU ':' DUPLICADO";
      errorsr.push_back(erro);

    }

  }
  foundr = 0;
  words = split(words, " ", foundr);
  for (size_t i = 0; i < words.size(); i++) { //para todas as palvras encontradas numa linha

    if (words[i].find_first_not_of(' ') == string::npos) { //se for vazia pula

      continue;

    }
    word.word = words[i];
    /*if (words[i] == "" || words[i] == " " || words[i] == "\n") {

      words.erase(words.begin() + i);

    } else*/ 
    if (word.word.length() > 50) { // se tem mais de 50 caracteres é erro

      erro = "ERRO LEXICO NA LINHA " + to_string(line_position + 1) + ":\n"  + original_filer[line_position] + "\n" + "PALAVRA POSSUI MAIS DE 50 CARACATERES";
      errorsr.push_back(erro);

    } else {

      if (!is_number(word.word)) { //se não é um número

        word.validate_word(line_position, original_filer, errorsr);

      }


    }
    word.line_position = line_position;
    //cout << to_string(word.line_position + 1) << ", " << word.word << ", "<< to_string(word.is_label) << endl;
    this->line.push_back(word);
    word.is_label = false;

  }

}

void word_t::validate_word(int line_position, vector <string > &original_filer, vector <string > &errorsr) {

  string erro;
  //bool validate_word = true;
  for (size_t position = 0; position < word.length(); position++) {

    if (position == 0) {

      if ((word[position] >= 'a' && word[position] <= 'z') || (word[position] >= 'A' && word[position] <= 'Z') || (word[position] == '_')) {

        continue;

      } else {

        erro = "ERRO LEXICO NA LINHA " + to_string(line_position + 1) + ":\n"  + original_filer[line_position] + "\n" + "CARACTERE INVALIDO NO INICIO DA PALAVRA";
        errorsr.push_back(erro);
        break;

      }

    } else {

      if ((word[position] >= 'a' && word[position] <= 'z') || (word[position] >= 'A' && word[position] <= 'Z') || (word[position] == '_') || (word[position] >= '0' && word[position] <= '9') || (word[position] == ',')) {

        continue;

      } else {

        erro = "ERRO LEXICO NA LINHA " + to_string(line_position + 1) + ":\n"  + original_filer[line_position] + "\n" + "CARACTERE INVALIDO NO MEIO DA PALAVRA";
        errorsr.push_back(erro);
        break;

      }

    }

  }
  //return validate_word;

}