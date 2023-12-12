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
O Trabalho 3 consiste na continuação do que já foi implementado na primeira parte do trabalho (TP2), que pode ser conferida [aqui](https://github.com/sofialctv/TP2_ED).

O objetivo principal do TP3 é a implementação de um registro de eventos significativos (logging), tais como a chegada de pacientes, o início/fim dos exames e o início/fim dos laudos. Cada novo evento deve ser registrado em um TAD chamado `Log`. Ao concluir a execução, o registro de eventos deve ser armazenado em um arquivo denominado `log.txt`. 

> 📰 _A especificação completa do trabalho pode ser lida acessando o arquivo specification.pdf_

# Instalação e Execução
Certifique-se de conter pré-instalado em seu sistema um **compilador C (por exemplo, GCC)**. 
 
Para instalar o programa em seu computador, siga os passos a seguir:
1. Clone o repositório em seu Desktop e salve-o no local desejado:
```bash
git clone https://github.com/sofialctv/TP3_ED
```

2. Abra seu terminal, escreva ```cd``` e cole o caminho no qual o repositório está salvo, como no exemplo:
```
cd C:\Users\ThiagoPX\Documents\Estrutura-de-dados-TP-3\TP3_ED
```
3. Compile o código e execute-o digitando o seguinte comando:
```
make
```
Como resultado, serão gerados os arquivos ```hospital.exe```, ```main.o``` e ```simulation.o```. 

4. Agora, você terá a opção de definir o intervalo (em segundos) das impressões de Atualizações de Métricas - leia mais [aqui](#funcionamento-do-programa).

````
Digite a velocidade de impressão das Atualizações de Métricas [segundos]:
````
Recomendamos utilizar o intervalo de 0.5s para uma visualização agradável das aparição das métricas.

5. Por fim, em seu terminal digite o nome do arquivo:
```
data.txt
````
Uma opção alternativa consiste em baixar o .zip com a pasta do projeto, extrair os arquivos, compilar e executar.

⚠️ **Atenção**: Durante a execução do programa, atente-se às orientações dadas no terminal, bem como as mensagens de erro que podem ser apresentadas.

# Organização do projeto
O trabalho conta com os principais arquivos:

- **`data.txt`**: contém nosso banco de dados de pacientes, com seus respectivos nomes, CPF e idade;
- **`simulation.c`**: contém as principais funções e structs que viabilizam a simulação do exame de raio-X;
- **`simulation.h`**: contém o cabeçalho das funções utilizadas;
- **`main.c`**: onde as funções e structs da simulação são implementadas;

# Funcionamento do programa
Ao executar o programa, o usuário será informado a cada **10 unidades de tempo (t)**, o relatório das métricas do sistema, que são as seguintes:
- **Tempo médio de laudo (TML):** Esta métrica calcula o tempo médio que os exames ocupam a fila para laudo. Quanto menor o tempo médio de espera, mais eficiente é o sistema.
- **Tempo médio de laudo por patologia (TMP):** Calcula o tempo médio que os exames de uma patologia específica aguardam na fila antes de serem laudados, o que ajuda a identificar se alguma patologia está enfrentando atrasos significativos.
- **Quantidade de exames realizados após o limite de tempo estabelecido (QEL):** Esta métrica rastreia quantos exames foram laudados após o limite de tempo aceitável estabelecido pelo hospital (7.200 unidades de tempo). Isso ajuda a avaliar a capacidade do sistema de cumprir prazos críticos.

> 🚨 Vale ressaltar que, no total, a simulação tem tempo máximo de 43.200 unidades de tempo. O resultado final (saída com métricas e arquivo `log.txt`) pode não ser visualizado de forma confortável. <br> Por isso, o arquivo atual conta com a possibilidade de escolher o intervalo, em segundos, da aparição das Atualizações das Métricas. Valores baixos tornam a impressão mais rápida, enquanto valos mais altos, tornam a impressão mais lenta, mas proporcionando melhor visualização dos valores.

**A saída do programa segue o padrão a seguir:**
````
--- Atualização de Métricas --- 
[TML] - Tempo médio de laudo: 176.00t
[TMP] - Saúde Normal: 185.00t
[TMP] - Bronquite: 167.00t
[QEL] - Exames realizados após o limite (7200t): 0
````

# Logging
Como dito anteriormente, ao concluir a execução do programa, o registro de eventos deve ser armazenado em um arquivo denominado `log.txt`. Utilizamos como base de implementação a interface básica de _log_ fornecida pelo professor na especificação. **O resultado do nosso logging está seguindo o padrão apresentado abaixo:**

````
[TEMPO 14t : event] Entrada de novo paciente no hospital. [ID: 1000   Nome: Carolina    CPF: 781.184.422-80    Idade: 31]
[TEMPO 23t : event] Exame do paciente de ID 1000 realizado. [Condição: Fratura de Fêmur    Qtd. de Máquinas Disponíveis: 4]
[TEMPO 33t : event] Laudo de Exame do paciente de ID 1000 finalizado pelo radiologista. [Duração do laudo: 10t]
[TEMPO 94t : metric] (TMP) Tempo médio de laudo - Pneumonia: 94.00t
[TEMPO 94t : metric] (TML) Tempo médio de laudo: 94.00t
[TEMPO 43198t : metric] (QEL) Qtd. de exames realizados após o limite de tempo estabelecido (Tempo limite = 7200t): 2406
````
Foram escolhidas as seguintes informações para comporem o logging:
- Chegada de pacientes ao hospital (informando ID, nome, CPF e idade de cada um);
- Realização de exame de um paciente (informando ID, condição e quantidade de máquinas disponíveis naquele instante);
- Relatório de métricas que são atualizadas a cada instante;
