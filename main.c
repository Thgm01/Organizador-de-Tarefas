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
    int opt;
    do{
        opt=-1;
        system(clear_terminal);
        print_tela_inicial();

        printf("\nDigite sua opção: ");
        scanf("%d", &opt);               

        switch (opt)  //
        {
        case 1: //Seleciona o que deve ser executado em cada opção
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

    for(int i=0; i<4; i++) // Recebe as informações
    {
        char *buffer[SIZE_TASK-2];
        printf("Digite %s", perguntas[i]);
        fgets(respostas[i], (SIZE_TASK-2), stdin);
        respostas[i][strcspn(respostas[i], "\n")] = 0; // Retira o \n das strigns lidas 

    }

    char formated[4*SIZE_TASK];

    snprintf(formated, sizeof(formated), "%s,%s,%s,%s,%s\n", respostas[0], respostas[1], dia_atual(), respostas[2], respostas[3]); //transforma o array de strings em uma unica separada por virgula
    printf("%s\n", formated);
    fprintf(dados, "%s", formated); //insire nos arquivos

    fclose(dados);
    
}

void print_all_tasks() //Função para imprimir todas as tarefas do arquivo
{
    
    struct DadosTarefa *data = le_tarefas(); // função para abrir o arquivo, caso não abra ele é criado e abre

    int size = size_file();
    if (size==0) //Caso não exista tarefas
    {
        center_text(SIZE_MENU, "NENHUMA TAREFA!", 1);
        draw_blank_line(SIZE_MENU);
    }
    else
    {
        for(int i=0; i<size -1; i+=2) //imprime na tela os pares de tarefas
        {
            char *titulo[] = {data[i].titulo, data[i+1].titulo};
            char *observacao[] = {data[i].observacao, data[i+1].observacao};
            char *data_criacao[] = {data[i].data_criacao, data[i+1].data_criacao};
            char *data_final[] = {data[i].data_final, data[i+1].data_final};
            char status[] = {data[i].status, data[i+1].status};
            draw_tasks(2, titulo, observacao, data_criacao, data_final, status);
        }
        if(size%2==1) // caso o número de tarefas seja impar ele imprime a última tarefa
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

void print_tela_inicial() //função para imprimir a tela inicial
{
    draw_menu_header("TAREFAS");
    print_all_tasks();
    draw_menu_options();
}

struct DadosTarefa *le_tarefas() // função que le todas as tarefas do arquivo e armazena em um array de struct
{

    struct DadosTarefa *Tarefas = (struct DadosTarefa *)malloc(1*sizeof(struct DadosTarefa));
   
    FILE *dados = open_file("r");

    char buffer[size_file()][SIZE_TASK*4]; //buffer temporário para receber as linhas lidas
    int cont = 0;

    while (fgets(buffer[cont], SIZE_TASK*4, dados) != NULL) // separa as informações em seus respectivos argumentos da struct
    {
        strcpy(Tarefas[cont].titulo, strtok(buffer[cont], ",")); //divide a string quando há uma virgula
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

void exclue_tarefa() // função para apagar a tarefa de número escolido
{
    int task_number;
    printf("Qual Tarefa deseja excluir? ");
    scanf("%d", &task_number);

    rewrite_file(task_number); // função que reescreve o arquivo porém sem a linha que foi escolhida para ser removida

    printf("Tarefa de numero %d excluida!\n\n", task_number);
}

void edita_tarefa() //função para editar tarefa
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
    else edit_task_data(task_number, opt); // remove a taréfa temporariamente e reescreve editada no final do arquivo
        
}
