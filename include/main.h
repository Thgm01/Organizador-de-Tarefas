#ifndef _MAIN_H_
#define _MAIN_H_

#if defined(_WIN32) || defined(_WIN64)
    #define clear_terminal "cls"
#else
    #define clear_terminal "clear"
#endif 

#define FILENAME "data.txt"

struct DadosTarefa
{
    char titulo[85];
    char observacao[85];
    char data_criacao[15];
    char data_final[15];
    char status;

};

struct DadosTarefa *le_tarefas();
char **strip_data(char *data_to_strip); 
void print_tela_inicial();
void print_all_tasks();
void adiciona_tarefa();
void exclue_tarefa();
void edita_tarefa();



#endif