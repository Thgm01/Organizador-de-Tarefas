#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/main.h"
#include "include/ui.h"
#include "include/utils.h"

int main(void) 
{
    int opt=-1;
    struct DadosTarefa *dados = le_tarefas("data.txt");
    do{
        opt=-1;

        print_tela_inicial(dados);

        printf("\nDigite sua opção: ");
        scanf("%d", &opt);
               

        switch (opt)
        {
        case 1:
            adiciona_tarefa();
            break;
        
        case 2:
            
            break;


        case 3:
            
            break;

        case 4:
            
            break;

        default:
            draw_menu_header("VALOR INVÁLIDO!");
            break;
        }



        sleep(5e-3);
    }while (opt != 5);

    free(dados);

    system(clear_terminal);
    draw_menu_header("Programa Encerrado!");

    return 0;
}

void adiciona_tarefa()
{
    FILE *dados = open_file("a");
    char *perguntas[4] = {"o titulo da tarefa: ", "a descricao da tarefa: ", "a data final[dd/mm/aaa]: ", "status: "};
    char respostas[4][SIZE_TASK-2];
    for(int i=0; i<4; i++)
    {
        printf("Digite %s", perguntas[i]);
        // getchar();
        gets(respostas[i]);

    }

    char formated[4*SIZE_TASK];

    snprintf(formated, sizeof(formated), "%s,%s,%s,%s,%s\n", respostas[0], respostas[1], dia_atual(), respostas[2], respostas[3]);
    printf("%s\n", formated);
    fprintf(dados, "%s", formated);

    fclose(dados);
    
}

void print_tela_inicial(struct DadosTarefa *data)
{
    system(clear_terminal);
    draw_menu_header("TAREFAS");
    print_all_tasks(data);
    draw_menu_options();
}

void print_all_tasks(struct DadosTarefa *data) //terminar
{
    int size = size_struct(data);
    if(size == 0)
    {
        draw_empty_tasks();
    }
    else
    {
        int aux = 0;
        // char **titles = {data[0].titulo, data[1].titulo};
        // char **descriptions = {data[0].observacao, data[1].observacao};
        // char **ini_date = {data[0].data_criacao, data[1].data_criacao};
        // char **fin_date = {data[0].data_final, data[1].data_final}; 
        // int *status = {atoi(data[0].status), atoi(data[1].status)};
        // draw_tasks(2, titles, descriptions, ini_date, fin_date, status);
    }
    
}

int size_struct(struct DadosTarefa *stc)
{
    int size=0;
    while (stc[size].titulo !=NULL)
    {
        size++;
    }
    
    return size;
}

struct DadosTarefa *le_tarefas()
{
    struct DadosTarefa *Tarefas = (struct DadosTarefa *)malloc(1*sizeof(struct DadosTarefa));

    FILE *dados = open_file("r");

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

char **strip_data(char *data_to_strip) 
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

FILE *open_file(char *mode) {
  FILE *f;
  f = fopen(FILENAME, mode);
  if (!f) {
    f = open_file("w");
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
