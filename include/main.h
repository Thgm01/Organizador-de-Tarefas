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
    char *titulo;
    char *observacao;
    char *data_criacao;
    char *data_final;
    char status;

};

struct DadosTarefa *le_tarefas();
char **strip_data(char *data_to_strip); 
void print_tela_inicial(struct DadosTarefa *data);
void print_all_tasks(struct DadosTarefa *data);
void adiciona_tarefa();


#endif