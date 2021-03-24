Sistema operacional utilizado: Windows 10 Pro 64 bits 20H2
Versão do compilador GNU g++: (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0

Para compilar ambos montador e simulador, basta abrir a pasta respectiva no vscode e executar o seguinte comando no terminal:
$make (é necessário ter o Chocolatey instalado e executar o comando: $choco install make)

Para executar respectivamente montador e simulador, seguem os comandos:
$./montador.exe *caminho_do_arquivo.asm*
$./simulador.exe *caminho_do_arquivo.obj (saída do montador)*
