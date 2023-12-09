# Logging - Simulação de Realização de Exames de Raio-X
Este repositório tem por objetivo armazenar os códigos elaborados no Trabalho de Programação 3 da disciplina de Estruturas de Dados [2023/2], ministrada pelo Prof. Thiago M. Paixão ([@thiagopx](https://github.com/thiagopx)).

### Autores

- Davidson Carvalho dos Santos: [@Davidsonnj](https://github.com/Davidsonnj)
- Sofia de Alcantara: [@sofialctv](https://github.com/sofialctv)

# 📝 Sumário

- [Objetivo do Trabalho](#objetivo-do-trabalho)
- [Instalação e Execução](#instalação-e-execução)
- [Funcionamento do programa](#funcionamento-do-programa)

## Objetivo do Trabalho
O Trabalho 3 consiste na continuação do que já foi implementado na primeira parte do trabalho, que pode ser conferida [aqui](https://github.com/sofialctv/TP2_ED).

O objetivo principal do TP3 é a implementação de um registro de eventos significativos (logging), tais como a chegada de pacientes, o início/fim dos exames e o início/fim dos laudos. Cada novo evento deve ser registrado em um TAD chamado `Log`. Ao concluir a execução, o registro de eventos deve ser armazenado em um arquivo denominado `log.txt`. 

> 📰 _A especificação completa do trabalho pode ser lida acessando o arquivo specification.pdf_

# Instalação e Execução
Certifique-se de conter pré-instalado em seu sistema um **compilador C (por exemplo, GCC)**. 
 
Para instalar o programa em seu computador, siga os passos a seguir:
1. Clone o repositório em seu Desktop e salve-o no local desejado:
```bash
git clone https://github.com/sofialctv/TP2_ED
```

2. Abra seu terminal, escreva ```cd``` e cole o caminho no qual o repositório está salvo, como no exemplo:
```
cd C:\Users\ThiagoPX\Documents\Estrutura-de-dados-TP-2\TP2_ED
```
3. Compile o código e execute-o digitando o seguinte comando:
```
make
```
Como resultado, serão gerados os arquivos ```hospital.exe```, ```main.o``` e ```simulation.o```. 

4. Por fim, em seu terminal digite o nome do arquivo:
```
data.txt
````
Uma opção alternativa consiste em baixar o .zip com a pasta do projeto, extrair os arquivos, compilar e executar.

⚠️ **Atenção**: Durante a execução do programa, atente-se às orientações dadas no terminal, bem como as mensagens de erro que podem ser apresentadas.

# Funcionamento do programa
Ao executar o programa, o usuário será informado a cada 10 unidades de tempo, o relatório das métricas do sistema, que são as seguintes:
- **Tempo médio de laudo (TML):** Esta métrica calcula o tempo médio que os exames ocupam a fila para laudo. Quanto menor o tempo médio de espera, mais eficiente é o sistema.
- **Tempo médio de laudo por patologia (TMP):** Calcula o tempo médio que os exames de uma patologia específica aguardam na fila antes de serem laudados, o que ajuda a identificar se alguma patologia está enfrentando atrasos significativos.
- **Quantidade de exames realizados após o limite de tempo estabelecido (QEL):** Esta métrica rastreia quantos exames foram laudados após o limite de tempo aceitável estabelecido pelo hospital (7.200 unidades de tempo). Isso ajuda a avaliar a capacidade do sistema de cumprir prazos críticos.

Vale ressaltar que, no total, a simulação tem tempo máximo de 43.200 unidades de tempo.

**As seguintes informações foram escolhidas para fazerem parte do logging:**
- Chegada de pacientes (informando ID, nome, CPF e idade de cada um);
- Realização de exames;
- Relatório de métricas, atualizado a cada 10 unidades de tempo;

(add print do logging)