Sistema operacional utilizado: Windows 10 Pro 64 bits 20H2.  
Versão do compilador GNU g++: (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0.  
Como base para a ligação foram utilizados os arquivos fat_mod_A e fat_mod_B (não são os de Cópia) nos quais as diretivas public e extern estão  
localizados acima da seção de dados.

Para compilar montador, ligador e simulador, basta abrir a pasta respectiva no vscode e executar o seguinte comando no terminal:  
$make *(é necessário ter o Chocolatey instalado e executar o comando: $choco install make)*  

Para executar respectivamente montador e simulador, seguem os comandos:  
$./montador.exe *caminho_do_arquivo1.asm*  (*caminho_do_arquivo2.asm*)  (*caminho_do_arquivo2.asm*)  
$./ligador.exe *caminho_do_arquivo1.o*  (*caminho_do_arquivo2.o*)  (*caminho_do_arquivo2.o*) (são saídas do montador, ambos montador e ligador aceitam até 3 arquivos)  
$./simulador.exe *caminho_do_arquivo.obj (saída do ligador)*  

