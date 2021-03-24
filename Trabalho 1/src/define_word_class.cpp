#include <iostream>
#include <string>
#include <vector>

#include "define_word_class.h"

using namespace std;

line_of_words_t::line_of_words_t(string line, int line_position) {

  this->lines_in_original_file.push_back(line_position);

}

void line_of_words_t::add_line(string line) {

  this->line_position = 1;

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