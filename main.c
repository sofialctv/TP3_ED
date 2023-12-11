#include "simulation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  /* Variáveis usadas durante o código */
  int relatorio = 11; 
  int nextID = 1000;
  int max_time = 43200;
  char filename[10];
  patient *patient;

  /* Acesso ao arquivo */
  printf("Digite o nome do arquivo: ");
  scanf("%s", filename);

  /* Inicializando variáveis (Alocando memória) */
  ListPatient *list_patient = ListPatient_create();
  QueueExams *exams = QueueExams_create();
  QueueReport *report = QueueReport_create();
  ListMachines *Machine = ListMachines_create();
  ListRadiologist *Radio = Radiologist_create();
  Log *log = create_log();

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

        msg_newPatient(log, time, newPatient);

        nextID++;
    }

    /* Funçoes de exame até radiologia */
    insert_machines(Machine, exams, time);
    Exam_Record(report, Machine, time, log);

    /* Tempo que o paciente saí da QueueReport (fila de laudo) e é alocado para o Radiologista */
    insert_radio(Radio, report, time); 
    remove_radio(Radio,time, log);
    
    if((relatorio % 10) == 0){
      printMetrics(report);
      sleepMicroseconds(300000);
    }
      
    relatorio = relatorio + 1;
  }

  save_log_to_file(log, "log.txt");
  
  /*Limpando memória das lista e das filas implementadas */
  listpatient_free(list_patient);
  listmach_free(Machine);
  listradiologist_free(Radio);
  qexam_free(exams);
  qreport_free(report);

  fclose(arquivo);
  return 0;
}