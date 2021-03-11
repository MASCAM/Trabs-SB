#include <iostream>
#include <fstream>

using namespace std;

int main(){

    ifstream arquivo_entrada;
    string linha;

    arquivo_entrada.open("../arquivos_testes/bin.asm");

    if(arquivo_entrada.is_open()){
        while(getline(arquivo_entrada,  linha)){
            cout << linha << endl;
        }
        arquivo_entrada.close();
    }else{
        cout << "Não foi possível abrir o arquivo" << endl;
    }

  return 0;
}