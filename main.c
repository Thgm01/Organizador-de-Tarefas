#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/main.h"
#include "include/ui.h"
#include "include/utils.h"

int main(void) 
{  
    print_tela_inicial(le_tarefas("data.txt"));
    return 0;
}

void print_tela_inicial(struct DadosTarefa *data)
{
    system(clear_terminal);
    draw_menu_header("TAREFAS");
}


struct DadosTarefa *le_tarefas(char *filename) 
{
    struct DadosTarefa *Tarefas = (struct DadosTarefa *)malloc(1*sizeof(struct DadosTarefa));

    FILE *dados = open_file(filename, "r");

    char buffer[SIZE_TASK * 4];
    char **buffer_separado;

    int cont = 0;

    while (fgets(buffer, sizeof(buffer), dados) != NULL) 
    {
        buffer_separado = strip_data(buffer, ",");
        Tarefas[cont].titulo = buffer_separado[0];
        Tarefas[cont].observacao = buffer_separado[1];
        Tarefas[cont].data_criacao = buffer_separado[2];
        Tarefas[cont].data_final = buffer_separado[3];
        Tarefas[cont].status = buffer_separado[4][0];
        cont++;
        Tarefas = (struct DadosTarefa *) realloc(Tarefas,(cont+1)*sizeof(struct DadosTarefa));
    }
    fclose(dados);

    return Tarefas;
}

char **strip_data(char *data_to_strip, char *delim) 
{
    char *stripped_data[5];

    stripped_data[0] = strtok(data_to_strip, ",");
    for (int i = 1; i < 5; i++) 
    {
        stripped_data[i] = strtok(NULL, ",");
    }
    char **res = stripped_data;

    return res;
}

FILE *open_file(char *filename, char *mode) {
  FILE *f;
  f = fopen(filename, mode);
  if (!f) {
    f = open_file(filename, "w");
  }
  return f;
}

// char *teste[] = {"Fazer o ex1", "Terminar relatorios"};
// char * titles[] = {"Tarefa 1", "Tarefa 2"};
// char *descriptions[]= teste[];
// char *initial_dates[] = {"18/03/2023", "20/04/2023"};
// char *final_dates[] = {"26/05/2023", "12/06/2023"};
// int status[] = {1, 3};
// system(clear_terminal);

// draw_menu_header("TAREFAS");

// draw_tasks(2, titles, descriptions, initial_dates, final_dates, status);
// draw_tasks(2, titles, descriptions, initial_dates, final_dates, status);
// draw_menu_options();
