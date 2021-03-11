#include <iostream> 
#include <string>

using namespace std;

int main( int argc, char *argv[ ] )
{
    // A quantidade de argumentos é igual a qtd + 1, 
    // pois o primeiro argumento é sempre o nome do programa.
    int qtd_argumentos = argc;
    string nome_programa = argv[0];
    string primeiro_argumento = argv[1];

    cout << "Qtd argumentos: " << qtd_argumentos << "\n";
    cout << "Nome programa: " << nome_programa << "\n";
    cout << "Argumento 1: " << primeiro_argumento << "\n";

    return 0;
}