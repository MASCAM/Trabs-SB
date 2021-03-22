#include <iostream>
#include <string>
#include <vector>

#include "define_word_class.h"

using namespace std;

word_t::word_t(string line, int line_position) {

  this->word = line;
  this->line_position = line_position;

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