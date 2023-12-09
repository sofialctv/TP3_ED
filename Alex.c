#include <stdio.h>
#include "simulacao.h"

void realizarSimulacao(Simulacao *simulacao, Paciente listaPacientes[], int numeroPacientes) {
    srand((unsigned int)time(NULL));  // Inicializa a semente para geração de números aleatórios

    int tempoTotalSimulacao = 43200; // Número total de unidades de tempo para a simulação
    
    // Lógica da simulação para cada unidade de tempo
    for (int tempo = 0; tempo < tempoTotalSimulacao; tempo++) {
        // 1. Chegada de pacientes
        for (int i = 0; i < numeroPacientes; i++) {
            if (rand() % 100 < 20) {
                int idPaciente = listaPacientes[i].id;
                enfileirar(&simulacao->filaExames, idPaciente);
            }
        }

        int aparelhoIndex;  // Escolhe um aparelho de forma cíclica
        int radiologistaIndex;  // Escolhe um radiologista de forma cíclica

        // 2. Realização de exames
        for (int i = 0; i < 5; i++) {
            aparelhoIndex = i;
            if (!filaVazia(&simulacao->filaExames) && aparelhoDisponivel(&simulacao->aparelhos[aparelhoIndex])) {
                ocuparAparelho(&simulacao->aparelhos[aparelhoIndex]);
                int idPaciente = desenfileirar(&simulacao->filaExames);
                exibirPaciente(listaPacientes[idPaciente]);
                int tempoExame = rand() % 6 + 5; // Tempo do exame entre 5 e 10 unidades
                int condicao = rand() % 100 < 30 ? 1 : // Saúde Normal
                               rand() % 100 < 20 ? 2 : // Bronquite
                               rand() % 100 < 20 ? 3 : // Pneumonia
                               rand() % 100 < 15 ? 4 : // Fratura de Fêmur
                               4;                      // Apendicite

                Exame exame = criarExame(idPaciente, tempoExame, condicao);
                enfileirar(&simulacao->filaLaudos, exame.id);

                printf("Tempo %ds: Exame do paciente %d realizado no aparelho %d. Condição sugerida: %d\n", tempo, idPaciente, aparelhoIndex, condicao);

                liberarAparelho(&simulacao->aparelhos[aparelhoIndex]);
            } else {
                printf("Aparelho %d ocupado!\n", aparelhoIndex);
            }
        }

        // 3. Realização de laudos
        for (int j = 0; j < 3; j++) {
            radiologistaIndex = j;
            if (!filaVazia(&simulacao->filaLaudos) && radiologistaDisponivel(&simulacao->radiologistas[j])) {
                ocuparRadiologista(&simulacao->radiologistas[j]);

                Exame exame = desenfileirarExame(&simulacao->filaLaudos, listaPacientes);
                int tempoLaudo = rand() % 21 + 10; // Tempo do laudo entre 10 e 30 unidades
                printf("Tempo %ds: Laudo do exame do paciente %d realizado por radiologista %d. Tempo de laudo: %ds\n", tempo, exame.id, j, tempoLaudo);
                printf("\n");

                liberarRadiologista(&simulacao->radiologistas[radiologistaIndex]);
            } else {
                printf("Radiologista %d ocupado!\n", radiologistaIndex);
            }
        }

        // 4. Atualização do relatório de métricas a cada 10 unidades de tempo (ajuste conforme necessário)
        if (tempo % 10 == 0) {
            printf("Atualização do relatório de métricas: %ds\n", tempo);
            // Implemente as métricas de desempenho aqui
            // Tempo médio de laudo, tempo médio de laudo por patologia, quantidade de exames após o limite de tempo
        }
    }

    // Libera a memória utilizada pelas filas
    destruirFila(&simulacao->filaLaudos);
    destruirFila(&simulacao->filaExames);
}

int main() {
    // Inicializa a simulação
    Simulacao simulacao = iniciarSimulacao();

    // Lista de pacientes
    Paciente listaPacientes[100];
    int numeroPacientes = sizeof(listaPacientes) / sizeof(listaPacientes[0]);

    // Preenche a lista de possíveis pacientes com dados aleatórios
    for (int i = 0; i < numeroPacientes; i++) {
        listaPacientes[i] = gerarPacienteAleatorio(i);
    }

    realizarSimulacao(&simulacao, listaPacientes, numeroPacientes);

    return 0;
}
