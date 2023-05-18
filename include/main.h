#ifndef _MAIN_H_
#define _MAIN_H_

#if defined(_WIN32) || defined(_WIN64)
    #define clear_terminal "cls"
#else
    #define clear_terminal "clear"
#endif 

struct DadosTarefa
{
    char *titulo;
    char *observacao;
    char *data_criacao;
    char *data_final;
    char status;

};

FILE *open_file(char* filename, char* mode);
struct DadosTarefa *le_tarefas(char *filename);
char **strip_data(char *data_to_strip, char *delim); 
void print_tela_inicial(struct DadosTarefa *data);


#endif