# R.shell

# Backdoor em C++ - Exemplo de Uso Educacional

Este projeto é um exemplo de um backdoor (porta dos fundos) simples implementado em C++. Ele demonstra como estabelecer uma conexão de rede com um servidor remoto e executar um shell do Windows na máquina cliente. 

**Atenção: O uso deste código para fins maliciosos ou sem permissão é ilegal e antiético. Este código é fornecido apenas para fins educacionais e de aprendizado.**

## Funcionalidades Principais

- Estabelece uma conexão de rede com um servidor remoto.
- Executa um shell do Windows na máquina remota.
- Redireciona a entrada e saída padrão para o shell remoto.

## Pré-Requisitos

Antes de usar este projeto, certifique-se de que você tenha as seguintes dependências instaladas:

- Compilador C++ (como o g++)
- Sistema operacional Windows (para executar o shell remoto)

## Instalação

1. Clone este repositório para o seu computador:

```sh
git clone https://github.com/Vinisantosz/backdoor

Uso
1 - Edite o arquivo main.cpp para fornecer o endereço IP do servidor remoto e a porta desejada.
2 - Execute o programa compilado connection.exe no Windows.
3 - O programa se conectará ao servidor remoto e permitirá a execução de comandos no shell remoto.

comando para compilar: g++ -o connection.exe main.cpp -lws2_32 -lwsock32 -static-libgcc -static-libstdc++ -mwindows
