#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
  ifstream arquivo_entrada;
  string linha;
  arquivo_entrada.open("../arquivos_testes/bin.asm");
  
  // Criação de um container dec chave-valor com o map.
  map<int, string>programa_mapeado;

  if (arquivo_entrada.is_open())
  {
    int i = 0;
    while (getline(arquivo_entrada, linha))
    {
      programa_mapeado[i] = linha;
      i++;
    }
    arquivo_entrada.close();
  }
  else
  {
    cout << "Não foi possível abrir o arquivo" << endl;
  }

  for(auto it:programa_mapeado){
    cout << it.first << " - " << it.second << endl;
  }
  
  return 0;
}