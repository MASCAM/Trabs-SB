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
  bool *found = new bool;
  bool &foundr = *found;
  string erro = "";
  words.push_back(line); 
  words = split(words, ":", foundr);
  if (foundr == true) {

    foundr = false;

  }
  words = split(words, " ", foundr);
  for (size_t i = 0; i < words.size(); i++) {

    /*if (words[i] == "" || words[i] == " " || words[i] == "\n") {

      words.erase(words.begin() + i);

    } else*/ if (words[i].length() > 50) {

      erro = "ERRO LEXICO NA LINHA " + to_string(line_position + 1) + ":\n"  + original_filer[line_position] + "\n" + "PALAVRA POSSUI MAIS DE 50 CARACATERES";
      errorsr.push_back(erro);

    }

  }

}

bool word_t::validate_char(char c, int position) {

  if (position == 0) {

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {

      return true;

    } else {

      return false;

    }

  } else {

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9')) {

      return true;

    } else {

      return false;

    }

  }

}