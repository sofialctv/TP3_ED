#include "simulation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {

  srand(time(NULL));

  /* Variáveis usadas durante o código */
  int relatorio = 11; 
  int nextID = 1000;
  int max_time = 43200;
  char filename[10];
  patient *patient;

  /* Variáveis para métricas */
  int time_report_med;
  float avgTime;

  int cont_Normal = 0;
  int cont_NormalTemp = 0;
  int calc_normal = 0;

  int cont_Pneumonia = 0;
  int cont_PneumoniaTemp = 0;
  int calc_Pneumonia = 0;

  int cont_Bronquite = 0;
  int cont_BronquiteTemp = 0;
  int calc_Bronquite = 0;

  int cont_Fratura = 0;
  int cont_FraturaTemp = 0;
  int calc_Fratura = 0;

  int cont_Apendicite = 0;
  int cont_ApendiciteTemp = 0;
  int calc_Apendicite = 0;

  /* Acesso ao arquivo */
  printf("Digite o nome do arquivo: ");
  scanf("%s", filename);

  /* Inicializando variáveis (Alocando memória) */
  ListPatient *list_patient = ListPatient_create();
  QueueExams *exams = QueueExams_create();
  QueueReport *report = QueueReport_create();
  ListMachines *Machine = ListMachines_create();
  ListRadiologist *Radio = Radiologist_create();

  /* Lendo o arquivo como o nome dado anteriormente */
  FILE *arquivo = fopen(filename, "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo.\n\n");
    return 1;
  }

  /* Inicialização das maquinas e dos radiologistas */
  initializeMachines(5, Machine);
  initializeRadiologist(3, Radio);

  /* Horário (USANDO LOOP FOR) */
  for(int time=1; time <= max_time; time++) {

    /* Chegada do paciente (20% de chance de chegar um paciente) */
    if (rand() % 5 + 1 == 1) {
      
      char name[50];
      int age = 0;
      char cpf[20];

      fscanf(arquivo, "%49s\n%15s\n%d\n", name, cpf, &age);

        /* Lista de pacientes */
        patient = newPatient(name, cpf, age, nextID);
        ListPatient_insert(list_patient, patient);
        
        /* Fila de pacientes */
        QueueEnqueue(exams, nextID);
        nextID++;
    }

    /* Funçoes de exame até radiologia */
    insert_machines(Machine, exams, time);
    Exam_Record(report, Machine, time);

    /* Tempo que o paciente saí da QueueReport (fila de laudo) e é alocado para o Radiologista */
    insert_radio(Radio, report, time); 
    remove_radio(Radio,time);

    /* Cálculo das métricas */
    avgTime = averageReportTime(report);

    cont_Normal = total_path(report, "Saúde Normal");
    cont_NormalTemp = tempWait_path(report, "Saúde Normal");

    calc_normal = (cont_Normal != 0) ? (cont_NormalTemp / cont_Normal) : 0;
   

    cont_Bronquite = total_path(report, "Bronquite");
    cont_BronquiteTemp = tempWait_path(report, "Bronquite");

    calc_Bronquite = (cont_Bronquite != 0) ? (cont_BronquiteTemp / cont_Bronquite) : 0;

    cont_Pneumonia = total_path(report, "Pneumonia");
    cont_PneumoniaTemp = tempWait_path(report, "Pneumonia");

    calc_Pneumonia = (cont_Pneumonia != 0) ? (cont_PneumoniaTemp / cont_Pneumonia) : 0;

    cont_Fratura = total_path(report, "Fratura de Fêmur");
    cont_FraturaTemp = tempWait_path(report, "Fratura de Fêmur");

    calc_Fratura = (cont_Fratura != 0) ? (cont_FraturaTemp / cont_Fratura) : 0;

    cont_Apendicite = total_path(report, "Apendicite");
    cont_ApendiciteTemp = tempWait_path(report, "Apendicite");

    calc_Apendicite = (cont_Apendicite != 0) ? (cont_ApendiciteTemp / cont_Apendicite) : 0;

    time_report_med = examsBeyondTimeLimit(report, 7200);
    

    /* RELATÓRIO DE MÉTRICAS */
    if((relatorio % 10) == 0){
      printf("\nRELATÓRIO DE MÉTRICAS - Unidade de Tempo: %d\n", time);

      printf("TML (Tempo médio de laudo): %.0f\n", avgTime);

      printf("TMP (Tempo médio de laudo por patologia (Saúde Normal)): %d\n", calc_normal);

      printf("TMP (Tempo médio de laudo por patologia (Bronquite)): %d\n", calc_Bronquite);

      printf("TMP (Tempo médio de laudo por patologia (Pneumonia)): %d\n", calc_Pneumonia);

      printf("TMP (Tempo médio de laudo por patologia (Fratura de Fêmur)): %d\n", calc_Fratura);

      printf("TMP (Tempo médio de laudo por patologia (Apendicite)): %d\n", calc_Apendicite);

      printf("QEL (Quantidade de exames realizados após o limite de tempo estabelecido): %d\n\n", time_report_med);
    }
    
    sleep(1);
    relatorio = relatorio + 1;
  }

  /*Limpando memória das lista e das filas implementadas */
  listpatient_free(list_patient);
  listmach_free(Machine);
  listradiologist_free(Radio);
  qexam_free(exams);
  qreport_free(report);

  fclose(arquivo);
  return 0;
}