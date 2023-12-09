#include "simulation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estrutura do paciente */
struct Patient {

  char name[50]; /* Nome do paciente */
  char cpf[20];  /* CPF do paciente */
  int age;       /* Idade do paciente */
  int id;        /* Identificador do paciente */
};

/* Lista de paciente */
struct ListOfPatients {
  int count;       /* Contador de pacientes */
  ListNode *first; /* Ponteiro para o primeiro paciente da lista */
  ListNode *last;  /* Ponteiro para o último paciente da lista */
};

/* Nó da lista paciente  */
struct list_node {
  patient *patients; /* Registro do paciente */
  ListNode *next;    /* Ponteiro para o próximo paciente */
  ListNode *prev;    /* Ponteiro para o paciente anterior */
};

/* Fila de Exames, que armazena somente o ID dos novos pacientes */
struct QueueExams {

  QueueNode *front; /* Ponteiro para o primeiro exame da fila */
  QueueNode *rear;  /* Ponteiro para o último exame da fila */
};

/* Auxiliar para implementação de QueueExams */
struct Queue_Node {
  int id;          /* Identificador dos pacientes da fila */
  QueueNode *next; /* Ponteiro para o próximo paciente da fila */
};

/* Lista de maquinas */
struct ListOfMachines {
  int count;       /* Contador de máquinas */
  Machines *first; /* Ponteiro para a primeiro máquina da lista */
  Machines *last;  /* Ponteiro para a último máquina da lista */
};

/* Estrutura das maquinas */
struct Machines {
  int examDuration; /* Duração de exame do aparelho */
  int patientID;    /* ID do paciente que está ocupando a máquina */
  int time;
  Machines *next;
  Machines *prev;
};

struct QueueReport {
  ExamRecord *front;       /* Ponteiro para o primeiro registro de exame na fila de laudos */
  ExamRecord *rear;        /* Ponteiro para o último registro de exame na fila de laudos */
};

struct ExamRecord {
  int id;
  int finishTime;   /* Paciente sai da máquina    */
  Pathologie *path;
  ExamRecord *next;
};

struct Pathologies {

  char condition[20]; /* Condição do Paciente */
  int urgency;        /* Gravidade da condição */
};

struct ListOfRadiologist {
  int count;       /* Contador de máquinas */
  Radiologist *first; /* Ponteiro para a primeiro máquina da lista */
  Radiologist *last;  /* Ponteiro para a último máquina da lista */
};

struct Radiologist {
  int occupation;
  int patientID;
  int durationRad;  /* Duração do processo de preparação do laudo */
  int time;
  Radiologist *next;
  Radiologist *prev;
};

struct LogEvent {
  char message[256];
  time_t timestamp;
};

struct Log {
  LogEvent events[2000];
  int count;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                     FUNÇÕES RELATIVAS AO BANCO DE DADOS (LISTA) DE PACIENTES                                      */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função que cria novo paciente */
patient *newPatient(char name[], char cpf[], int age, int id) {

  patient *newPatient = (patient *)malloc(sizeof(patient));  /* Aloca memoria para registro do pacientes */

  strcpy(newPatient->name, name);   /* Define o nome do paciente */
  strcpy(newPatient->cpf, cpf);     /* Define o cpf do paciente */
  newPatient->age = age;            /* Define a idade do paciente */
  newPatient->id = id;              /* Define o ID do paciente */

  return newPatient;
};

/* Função que cria a lista de paciente */
ListPatient *ListPatient_create() {
ListPatient *list = (ListPatient *)malloc(sizeof(ListPatient)); /* Aloca memoria para lista de pacientes */

  list->count = 0;        /* Inicializa o contador com 0 pacientes */
  list->first = NULL;     /* Inicializa o primeiro elemento da lista como vazio */
  list->last = NULL;      /* Inicializa o último elemento da lista como vazio */

  return list;            /* Retorna a lista de pacientes */
};

/* Função que retorna a quantidade de paciente */
int ListPatient_size(ListPatient *list) {
  return list->count; /* retorna tamanho da lista de pacientes */
};

/* Função que verifica se a lista esta vazia */
int ListEmpty(ListPatient *list) { 
  return ListPatient_size(list) == 0; 
}

/* Função que insere um novo paciente a lista */
void ListPatient_insert(ListPatient *list, patient *patients) {

  ListNode *node = (ListNode *)malloc(sizeof(ListNode));     /* Aloca memoria para cada nó de pacientes */
  node->patients = patients;                                 /* Atribui o paciente ao nó */
  node->next = list->first;                                  /* O próximo nó recebe o primeiro nó */
  node->prev = NULL;                                         /* O nó anterior aponta para NULL */

  /* Verifica se não lista está vazia */
  if (!ListEmpty(list))
    list->first->prev = node;   /* O nó anterior do primeiro elemento da lista (que é um nó) recebe o nó criado */
  else
    list->last = node;          /* Lista recebe o último nó recebe */

  list->first = node;           /* Primeiro elemento da lista pacientes recebe o nó criado */
  list->count++;                /* Quantidade de registro aumentam */
}

/* Função que remove paciente da lista */
int ListPatient_remove(ListPatient *list, patient *patients) {

  ListNode *node = list->first;      /* Cria nó auxiliar para percorrer a lista */
  ListNode *prev = NULL;             /* Aponta para o nó anterior */

  while (node != NULL) {
    if (node->patients == patients)  /* Se o atual nó contém o elemento a ser removido... */
    {
      if (prev == NULL)              /* Se o elemento a ser removido está no começo da lista... */
      {
        list->first = node->next;
      } 
      else /* Caso o elemento esteja no meio ou fim da lista... */
        prev->next = node->next;

      free(node);
      return 1; /* Sucesso ao remover paciente */
    } 
    else 
    {
      prev = node;
      node = node->next;
    }
  }

  return 0; /* Sucesso ao remover paciente */
}

/* Função que remove/libera todos os pacientes da memória */
void ListPatient_free(ListPatient *list) {
  ListNode *node = list->first;

  while (node != NULL) {
    ListNode *temp = node->next;
    free(node);
    node = temp;
  }
  free(list);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                     FUNÇÕES RELATIVAS À FILA DE EXAMES                                            */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função que cria a fila de exames */
QueueExams *QueueExams_create() {
  QueueExams *q = (QueueExams *)malloc(sizeof(QueueExams));   /* Aloca memoria para a fila de exames */
  q->front = q->rear = NULL;                                  /* Declara o primeiro e o último ID como vazios */
  return q;                                                   /* Retorna a fila de exames */
}

/* Verifica se a fila de exame está vazia */
int QueueEmpty(QueueExams *q) { 
  return q->front == NULL; 
}

/* Colocar um no paciente na fila de exames*/
void QueueEnqueue(QueueExams *q, int newID) {
  QueueNode *node = (QueueNode *)calloc(1,sizeof(QueueNode)); /* Aloca memoria para um novo ID */
  node->id = newID;       /* Atribui o identificador (ID) ao novo nó da fila */
  node->next = NULL;      /* O próximo nó da fila fica vazio */

  if (QueueEmpty(q))
    q->front = node;      /* Novo nó vai para frente da fila */
  else
    q->rear->next = node; /* Novo nó vai para o último lugar da fila */

  q->rear = node;         /* Novo nó vai para o último lugar da fila */
}

/* Função que tira o primeiro paciente da fila de exames */
void QueueDequeue(QueueExams *q) {
  QueueNode *temp = q->front;    /* Armazenamento temporario para nó que será removido */

  if (q->front == q->rear) {
    q->front = q->rear = NULL;   /* Se houver apenas um elemento na fila */
  } else {
    q->front = q->front->next;   /* Move o ponteiro da frente para o próximo elemento */
  }
  free(temp);  /* Libera a memória do nó removido */
}

/* Limpa/libera a fila de exames */
void QueueFree(QueueExams *q) {
  QueueNode *p = q->front;

  while (p != NULL) {          /* Enquanto houver elementos na fila... */
    QueueNode *temp = p->next; /* Libera a memória do nó removido */
    free(p);
    p = temp;
  }
  free(q);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                            FUNÇÕES RELATIVAS AOS APARELHOS                                        */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Verifica se a lista de máquinas está vazia */
int ListEmpty_Machines(ListMachines *m){
  return (m->count == 0);
}

/* Função que cria a lista de máquinas */
ListMachines *ListMachines_create() {
ListMachines *list_M = (ListMachines *)malloc(sizeof(ListMachines)); /* Aloca memoria para lista de máquinas */

  list_M->count = 0;        /* Inicializa o contador com 0 máquinas */
  list_M->first = NULL;     /* Inicializa o primeiro elemento da lista como vazio */
  list_M->last = NULL;      /* Inicializa o último elemento da lista como vazio */

  return list_M;            /* Retorna a lista de maquinas */
};

/* Inicializa as máquinas de acordo com a quantidade de máquinas no hospital */
void initializeMachines(int qtd, ListMachines *m){
  for(int i = 0; i < qtd; i++ ){

    Machines *mach = (Machines *)malloc(sizeof(Machines));
    mach->examDuration = 0;
    mach->patientID = 0;
    mach->time = 0;
    mach->next = m->first;
    mach->prev = NULL;

    /* Verifica se não lista está vazia */
    if (!ListEmpty_Machines(m))
      m->first->prev = mach;
    else
      m->last = mach;

    m->first = mach;
    m->count++;
  }
  
}

/* Função para checar a disponibilidade dos aparelhos (RETORNA O APARELHO DISPONÍVEL)*/
static Machines* checkMachinesAvailability(ListMachines *machine){ 

  if(!ListEmpty_Machines(machine)){
    for(Machines *m = machine->first; m != NULL; m = m->next ){
      if(m->examDuration == 0 || m->patientID == 0 || m->time == 0){
        return m;
      }
    }
  }
  return NULL;
}

/* Se houver máquina disponível irá colocar o paciente para realização do exame */
void insert_machines(ListMachines *m, QueueExams *patient, int time) {
  Machines *mach = checkMachinesAvailability(m);

  if (mach != NULL) {
    QueueNode *pat = patient->front;

    if (pat != NULL && pat->id != 0) {

      int numb_rand = rand() % 5 + 5;
      mach->examDuration = numb_rand;
      mach->patientID = pat->id;
      mach->time = time;

      QueueDequeue(patient);
    }
  }
}

/* Se o paciente houver terminado seu exame na máquina irá ser retirado da mesma (RETORNA O ID) */
int machine_check(ListMachines *machine, int time){
  for(Machines *m = machine->first; m != NULL; m = m->next ){
    if(m->examDuration + m->time == time){
      int ID = m->patientID;
      m->patientID = 0;
      m->examDuration = 0;
      m->time = 0;
      return ID;
    }
  }
  return -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                     FUNÇÕES RELATIVAS À FILA DE LAUDOS                                            */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função que verifica se a lista de laudos está vazia */
int QueueReportEmpty(QueueReport *report) { 
  return report->front == NULL; 
}

/* Função que cria a fila de laudos */
QueueReport *QueueReport_create() {
  QueueReport *report = (QueueReport *)malloc(sizeof(QueueReport));
  report->front = report->rear = NULL; /* Fila começa vazia */
  return report;
}

/* Função que verifica se o paciente terminou o exame e transferi para a fila de laudo */
void Exam_Record(QueueReport *report, ListMachines *m, int time){

  int check = machine_check(m, time);
  while ((check) != -1) {

    /* Criação do laudo */
    ExamRecord *r = (ExamRecord *)malloc(sizeof(ExamRecord));
    r->finishTime = time;
    r->id = check;
    r->path = Assessing_Pathologies();
    r->next = NULL;

    /* Adicionando na fila de registro */
    if(QueueReportEmpty(report)){
      report->front = report->rear = r;
    }
    else{
      report->rear->next = r;
      report->rear = r;
    }
    check = machine_check(m, time);
  }
}

void QueueDequeue_report(QueueReport *q) {
  ExamRecord *temp = q->front;    /* Armazenamento temporario para nó que será removido */

  if (q->front == q->rear) {
    q->front = q->rear = NULL;   /* Se houver apenas um elemento na fila */
  } else {
    q->front = q->front->next;   /* Move o ponteiro da frente para o próximo elemento */
  }
  free(temp);  /* Libera a memória do nó removido */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                # PATOLOGIAS #                                                     */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static Pathologie *CreatePathologie(char condition[20], int severity) {

  Pathologie *p = (Pathologie *)malloc(sizeof(Pathologie));
  strcpy(p->condition, condition);
  p->urgency = severity;
  return p;
}

Pathologie *Assessing_Pathologies() {

  int numb_random = rand() % 100 + 1;
  char condition[20];

  switch (numb_random) {
  case 1 ... 30:
    return CreatePathologie(strcpy(condition,"Saúde Normal"), 1);
  case 31 ... 50:
    return CreatePathologie(strcpy(condition,"Bronquite"), 2);
  case 51 ... 70:
    return CreatePathologie(strcpy(condition,"Pneumonia"), 3);
  case 71 ... 85:
    return CreatePathologie(strcpy(condition,"Fratura de Fêmur"), 4);
  case 86 ... 100:
    return CreatePathologie(strcpy(condition, "Apendicite"), 4);
  default:
    return NULL;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                               # RADIOLOGISTAS #                                                   */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Verifica se a lista de radiologista está vazia */
int ListEmpty_Radiologist(ListRadiologist *r){
  return (r->count == 0);
}

/* Função que cria a lista de radiologista */
ListRadiologist *Radiologist_create() {
  ListRadiologist *list_R = (ListRadiologist *)malloc(sizeof(ListRadiologist)); /* Aloca memoria para lista de radiologistas */

  list_R->count = 0;        /* Inicializa o contador com 0 radiologistas */
  list_R->first = NULL;     /* Inicializa o primeiro elemento da lista como vazio */
  list_R->last = NULL;      /* Inicializa o último elemento da lista como vazio */

  return list_R;            /* Retorna a lista de radiologistas */
};

/* Função que inicializa o trabalho dos radiologistas */
void initializeRadiologist(int qtd, ListRadiologist *r){
  for(int i = 0; i < qtd; i++ ){

    Radiologist *rad = (Radiologist *)malloc(sizeof(Radiologist));
    rad->occupation = 0;
    rad->patientID = 0;
    rad->time = 0;
    rad->durationRad = 0;
    rad->next = r->first;
    rad->prev = NULL;

    /* Verifica se não lista está vazia */
    if (!ListEmpty_Radiologist(r))
      r->first->prev = rad;
    else
      r->last = rad;

    r->first = rad;
    r->count++;
  }
  
}

/* Função para checar a disponibilidade dos radiologistas (RETORNA O RADIOLOGISTA DISPONÍVEL) */
static Radiologist* checkRadiologistAvailability(ListRadiologist *radio){ 

  if(!ListEmpty_Radiologist(radio)){
    for(Radiologist *r = radio->first; r != NULL; r = r->next ){
      if(r->occupation == 0){
        return r;
      }
    }
  }
  return NULL;
}

/* Se houver radiologista disponível irá colocar o paciente para realização do laudo */
void insert_radio(ListRadiologist *r, QueueReport *patient, int time) {
  Radiologist *radio = checkRadiologistAvailability(r);

  if (radio != NULL) {
    ExamRecord *pat = patient->front;

    if (pat != NULL && pat->id != 0) {
      
      int numb_rand = rand() % 21 + 10;
      radio->durationRad = numb_rand;
      radio->patientID = pat->id;
      radio->time = time;
      radio->occupation = 1;
      QueueDequeue_report(patient);
    }
  }
}

/* Paciente termina sua consulta com o radiologista */
void remove_radio(ListRadiologist *r,int time){
  for(Radiologist *radio = r->first; radio != NULL; radio = radio->next){

    if(time == (radio->durationRad + radio->time)){
      radio->durationRad = 0;
      radio->occupation = 0;
      radio->patientID = 0;
      radio->time = 0;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                # PRINTS #                                                         */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função que printa a lista de pacientes */
void patient_print(ListPatient *l){
   for (ListNode *p = l->first; p != NULL; p = p->next)
   {
    printf("Name: %s\n", p->patients->name);
    printf("CPF: %s\n", p->patients->cpf);
    printf("Age: %d\n", p->patients->age);
    printf("ID: %d\n", p->patients->id);
    printf("\n");
   }
   printf("\n");
}

/* Função que printa a fila de exames */
void QueueExams_print(QueueExams *exams){
  
  for(QueueNode *patient = exams->front; patient != NULL; patient = patient->next  ){
    printf("%d ", patient->id);
  }
}

/* Função que printa as maquinas e sua disponibilidade */
void machine_print(ListMachines *machine){
  for(Machines *m = machine->first; m != NULL; m = m->next ){
    int ID = m->patientID;
    printf("Duração do exame: %d ID: %d Horario: %d Quantidade de maquinas: %d \n", m->examDuration, ID, m->time, machine->count);

  }
}

void QueueReport_print(QueueReport *r) {
  for (ExamRecord *rec = r->front; rec != NULL; rec = rec->next){

    printf("FILA DO LAUDO - ID do paciente: %d Horário: %d Condição: %s\n", rec->id, rec->finishTime, rec->path->condition);
  }
}

void radio_print(ListRadiologist *radio){
  for(Radiologist *r = radio->first; r != NULL; r = r->next ){
    int ID = r->patientID;
    printf("RADIOLOGISTA - Duração do exame: %d ID: %d Horario: %d Quantidade de maquinas: %d \n", r->durationRad, ID, r->time, radio->count);

  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                        # FUNÇÃO PARA METRICAS #                                                   */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int total_path(QueueReport *r, const char *p){
  int cont = 0;
  for (ExamRecord *record = r->front; record != NULL; record = record->next){
    
    int result = strcmp(record->path->condition, p);
    if(result == 0){
      cont++;
    }
  }
  return cont;
}

int tempWait_path(QueueReport *r, const char *p){
  int cont = 0;
  for (ExamRecord *record = r->front; record != NULL; record = record->next){
    
    int result = strcmp(record->path->condition, p);
    if(result == 0){
      cont = cont + record->finishTime;
    }
  }
  return cont;
}

int examsBeyondTimeLimit(QueueReport *report, int timeLimit) {
    int count = 0;

    for (ExamRecord *record = report->front; record != NULL; record = record->next) {
        if (record->finishTime > timeLimit) {
            count++;
        }
    }

    return count;
}

float averageReportTime(QueueReport *report) {
    if (QueueReportEmpty(report)) {
        return 0.0;
    }

    int totalReports = 0;
    int totalTime = 0;

    for (ExamRecord *record = report->front; record != NULL; record = record->next) {
        totalTime += record->finishTime;
        totalReports++;
    }

    return (float)totalTime / totalReports;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                        # FUNÇÃO PARA LIMPAR MEMORIA #                                             */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void listpatient_free(ListPatient *p){
   ListNode *node_pat = p->first;
   ListNode *temp;
   while (node_pat != NULL){
      temp = node_pat->next;
      free(node_pat);
      node_pat = temp;
   }
   free(p); 
}

void listmach_free(ListMachines *mach){
   Machines *node_mach = mach->first;
   Machines *temp;
   while (node_mach != NULL){
      temp = node_mach->next;
      free(node_mach);
      node_mach = temp;
   }
   free(mach); 
}

void listradiologist_free(ListRadiologist *radio){
   Radiologist *node_radio = radio->first;
   Radiologist *temp;
   while (node_radio != NULL){
      temp = node_radio->next;
      free(node_radio);
      node_radio = temp;
   }
   free(radio); 
}

void qexam_free(QueueExams *exam){
   QueueNode *node_exam = exam->front;
   while (node_exam != NULL){
      QueueNode *temp = node_exam->next;
      free(node_exam);           
      node_exam = temp;              
   }
   free(exam); 
}

void qreport_free(QueueReport *report){
   ExamRecord *record = report->front;
   while (record != NULL){
      ExamRecord *temp = record->next;
      free(record);
      record = temp;
   }
   free(report);
}
