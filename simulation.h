#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct QueueExams QueueExams; /* Fila de Exames, que armazena somente o ID dos novos pacientes */
typedef struct ExamRecord ExamRecord; /* Registro dos exames */

typedef struct Patient patient; /* Definição da estrutura Patient, relativa aos pacientes */
typedef struct ListOfPatients ListPatient; /* Lista de Pacientes, nosso banco de dados */

typedef struct ListOfMachines ListMachines;
typedef struct Machines Machines; /* Estrutura para armazenamento dos aparelhos utilizados nos exames */

typedef struct QueueReport QueueReport; /* Fila de Laudos, que armazena os registros de exames */
typedef struct Pathologies Pathologie; /* Estrutura relativa as características da patologia (condição e gravidade) */

typedef struct ListOfRadiologist ListRadiologist; /* Lista dos Radiologistas */
typedef struct Radiologist Radiologist; /* Estrutura relativa aos Radiologistas e o processo de preparação do laudo */

typedef struct list_node ListNode;    /* Auxiliar para implementação de ListOfPatients*/
typedef struct Queue_Node QueueNode; /* Auxiliar para implementação de QueueExams*/

typedef struct LogEvent LogEvent;  /* Definição da estrutura LogEvent, relativa ao evento a ser registrado */
typedef struct log Log;             /* Definição da estrutura Log, que contém os principais eventos */

typedef struct PatologyWaitTime PatologyWaitTime;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                # PACIENTES #                                                      */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

patient *newPatient(char *name, char *cpf, int age, int id); /* Função para criar novo paciente, com ID sequencial */

ListPatient *ListPatient_create(); /* Função que cria uma de lista de pacientes */

int ListPatient_size(ListPatient *list); /* Função para saber o tamanho da lista de pacientes */

int ListEmpty(ListPatient *list); /* Função que verifica se a lista esta vazia */

void ListPatient_insert(ListPatient *list, patient *patients); /* Função que insere um novo paciente à Lista de Pacientes */

int ListPatient_remove(ListPatient *list, patient *patients); /* Função que remove um paciente da Lista de Pacientes */

void ListPatient_free(ListPatient *list); /* Função que libera memória da Lista de Pacientes */


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                  # EXAMES #                                                       */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


QueueExams *QueueExams_create(); /* Função que cria uma fila de exames vazia */

int QueueEmpty(QueueExams *q); /* Função que verifica se a fila de exames está vazia */

void QueueEnqueue(QueueExams *q, int newID); /* Função que insere um novo exame (ou seja, insere um novo ID) no início da fila */

void QueueDequeue(QueueExams *q); /* Função para desenfileirar um elemento da lista, ou seja, remover o nó inicial da lista */

void QueueFree(QueueExams *q); /* Função para liberar memória usada para armazenamento da fila de exames */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                 # APARELHOS #                                                     */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ListEmpty_Machines(ListMachines *m); /* Função de verificação da ocupação das máquinas (se estão vazias ou não) */

ListMachines *ListMachines_create();    /* Função que cria uma lista para armazenar as máquinas */

void initializeMachines(int qtd, ListMachines *m);  /* Função para iniciar o funcionamento dos aparelhos (todos iniciam disponíveis (0)) */

void insert_machines(ListMachines *m, QueueExams *patient, int time);

int machine_disponible(ListMachines * machine);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                      # LAUDOS #                                                   */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QueueReport *QueueReport_create(); /* Função que cria uma fila de laudos vazia */

int QueueReportEmpty(QueueReport *q); /* Função que verifica se a fila de laudos está vazia */

void Exam_Record(QueueReport *report, ListMachines *m, int time, Log *log); /* Função que verifica se o paciente terminou o exame e transferi para a fila de laudo */

Pathologie *Assessing_Pathologies(); /* Função que avalia/computa as patologias, com suas respectivas probabilidades de ocorrência */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                               # RADIOLOGISTAS #                                                   */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ListEmpty_Radiologist(ListRadiologist *r); /* Verifica se a lista de radiologista está vazia */

ListRadiologist *Radiologist_create(); /* Função que cria a lista de radiologista */

void initializeRadiologist(int qtd, ListRadiologist *r); /* Função que inicializa o trabalho dos radiologistas */

void insert_radio(ListRadiologist *r, QueueReport *patient, int time); /* Alocação do primeiro exame de QueueReport para radiologista livre */

void remove_radio(ListRadiologist *r,int time, Log *l); /* Remoção do paciente (conclusao do laudo) */


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                       # PRINTS #                                                  */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void patient_print(ListPatient *l); /* Função que printa a lista de pacientes */

void QueueExams_print(QueueExams *exams); /* Função que printa a fila de exames */

void machine_print(ListMachines *machine); /* Função que printa as maquinas e sua disponibilidade */

void QueueReport_print(QueueReport *r); /* Função que printa a fila para laudos */

void radio_print(ListRadiologist *radio); /* Função que printa os radiologistas e sua disponibilidade */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          # FUNÇÃO PARA METRICAS #                                                 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int total_path(QueueReport *r, const char *p); /* Função que calcula total de exames relacionados a essa patologia */
int tempWait_path(QueueReport *r, const char *p); /* Função que calcula total de exames relacionados a essa patologia */

float averageReportTime(QueueReport *report); /* Função que calcula o tempo médio do relatório */
void averageReportTimePerPatology(QueueReport *report, PatologyWaitTime *patologyWaitTimes, int numPatologies);
int examsBeyondTimeLimit(QueueReport *report, int timeLimit); /*Função que calcula a soma dos tempos de espera dos exames de uma patologia específica */
void printMetrics(QueueReport *report);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                               # LOGGING #                                                         */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Log* create_log(); /* Função que cria o Log */
void log_event(Log *log, const char *message); /* Função para registro de novo evento no log*/
void save_log_to_file(const Log *log, const char *filename); /* Função que salva o log (registro de evento) no arquivo .txt */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                               # FUNÇÃO PARA LIMPAR MEMORIA & AUXILIARES #                                         */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void listpatient_free(ListPatient *p); /* Função que limpa a lista de pacientes */
void listmach_free(ListMachines *mach); /* Função que limpa a lista de máquinas */
void listradiologist_free(ListRadiologist *radio); /* Função que limpa a lista de radiologistas */
void qexam_free(QueueExams *exam); /* Função que limpa a fila de exames */
void qreport_free(QueueReport *report); /* Função que limpa a fila de laudos */

void sleepMicroseconds(unsigned long microseconds);


void save_log_to_file(const Log *log, const char *filename);
void log_event(Log *log, const char *message);
void msg_newPatient(Log *log, int time, patient *p);
void msg_record(ExamRecord *r, Log *log, int num);
void msg_radio(Log *log, Radiologist *radio);
void msg_Metrics(QueueReport *report, Log *log);

#endif