#include <iostream>
#include <string>

using namespace std;

/*int main() {

    string line = "teste caralho ";
    cout << line.length() << endl;
    for (size_t j = 0; j < line.length(); j++) {

        if (line[j] == ' ' && line[j + 1] == ' ') { //remove espaços repetidos

            line.erase(line.begin() + j + 1);
            j--;

        }
        if (j == 0 && line[j] == ' ') { //remove espaço no início da linha

            line.erase(line.begin());
            j--;

        }
        if (line[j] == ';') {

            line.erase(line.begin() + j, line.end());

        }
        if (line[j] == ' ' && line[j + 1] == '\n') {

            line.erase(line.begin() + j);
            j--;

        }
        line[j] = toupper(line[j]); //coloca tudo em caixa-alta

    }
    cout << line.length() << endl;
    return 0;

}*/