#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/main.h"
#include "include/ui.h"
#include "include/ui_functions.h"
#include "include/file_functions.h"


int main(void) 
{
    // print_all_tasks();
    int opt=-1;
    do{
        opt=-1;
        system(clear_terminal);
        print_tela_inicial();

        printf("\nDigite sua opção: ");
        scanf("%d", &opt);               

        switch (opt)
        {
        case 1: //
            adiciona_tarefa();
            break;

        case 2:
            edita_tarefa();            
            break;

        case 3:
            exclue_tarefa();
            break;

        case 4:
            draw_credits();
            break;
        case 5:
            break;

        default:
            system(clear_terminal);
            draw_menu_header("VALOR INVALIDO!");
            draw_botton_line(SIZE_MENU, 1);
            getchar();
            
            break;
        }
        sleep(5e-3);
    }while (opt != 5);

    system(clear_terminal);
    draw_menu_header("Programa Encerrado!");
    draw_botton_line(SIZE_MENU, 1);

    return 0;
}

void adiciona_tarefa()
{
    FILE *dados = open_file("a");
    char *perguntas[4] = {"o titulo da tarefa: ", "a descricao da tarefa: ", "a data final[dd/mm/aaa]: ", "status: "};
    char respostas[4][SIZE_TASK-2];
    getchar();

    for(int i=0; i<4; i++)
    {
        char *buffer[SIZE_TASK-2];
        printf("Digite %s", perguntas[i]);
        fgets(respostas[i], (SIZE_TASK-2), stdin);
        respostas[i][strcspn(respostas[i], "\n")] = 0;

    }

    char formated[4*SIZE_TASK];

    snprintf(formated, sizeof(formated), "%s,%s,%s,%s,%s\n", respostas[0], respostas[1], dia_atual(), respostas[2], respostas[3]);
    printf("%s\n", formated);
    fprintf(dados, "%s", formated);

    fclose(dados);
    
}

void print_all_tasks() //terminar
{
    
    struct DadosTarefa *data = le_tarefas();

    int size = size_file();
    if (size==0)
    {
        center_text(SIZE_MENU, "NENHUMA TAREFA!", 1);
        draw_blank_line(SIZE_MENU);
    }
    else
    {
        for(int i=0; i<size -1; i+=2)
        {
            char *titulo[] = {data[i].titulo, data[i+1].titulo};
            char *observacao[] = {data[i].observacao, data[i+1].observacao};
            char *data_criacao[] = {data[i].data_criacao, data[i+1].data_criacao};
            char *data_final[] = {data[i].data_final, data[i+1].data_final};
            char status[] = {data[i].status, data[i+1].status};
            draw_tasks(2, titulo, observacao, data_criacao, data_final, status);
        }
        if(size%2==1)
        {
            char *titulo[] = {data[size-1].titulo};
            char *observacao[] = {data[size-1].observacao};
            char *data_criacao[] = {data[size-1].data_criacao};
            char *data_final[] = {data[size-1].data_final};
            char status[] = {data[size-1].status};
            draw_tasks(1, titulo, observacao, data_criacao, data_final, status);

        }
    }
    free(data);
    
}

void print_tela_inicial()
{
    draw_menu_header("TAREFAS");
    print_all_tasks();
    draw_menu_options();
}

struct DadosTarefa *le_tarefas()
{

    struct DadosTarefa *Tarefas = (struct DadosTarefa *)malloc(1*sizeof(struct DadosTarefa));
   
    FILE *dados = open_file("r");

    char buffer[size_file()][SIZE_TASK*4];
    // testar deixar sem o size
    int cont = 0;

    while (fgets(buffer[cont], SIZE_TASK*4, dados) != NULL) 
    {
        strcpy(Tarefas[cont].titulo, strtok(buffer[cont], ","));
        strcpy(Tarefas[cont].observacao, strtok(NULL, ","));
        strcpy(Tarefas[cont].data_criacao, strtok(NULL, ","));
        strcpy(Tarefas[cont].data_final, strtok(NULL, ","));        
        Tarefas[cont].status = strtok(NULL, ",")[0];
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

void exclue_tarefa()
{
    int task_number;
    printf("Qual Tarefa deseja excluir? ");
    scanf("%d", &task_number);

    rewrite_file(task_number);

    printf("Tarefa de numero %d excluida!\n\n", task_number);
}

void edita_tarefa()
{  
    draw_menu_edit_options(0);

    int task_number;
    scanf("%d%*c", &task_number);
    printf("%d\n", task_number);

    if(task_number == -1) return;

    draw_menu_edit_options(1);
    print_task(task_number-1);
    draw_blank_line(SIZE_MENU);
    draw_botton_line(SIZE_MENU, 1);

    int opt;
    scanf("%d", &opt);

    if(opt==5) return;
    else edit_task_data(task_number, opt);
        
}
