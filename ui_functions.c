#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "include/ui_functions.h"
#include "include/ui.h"
#include "include/main.h"
#include "include/file_functions.h"

void new_line()
{
    printf("\n");
}

void draw_horizontal_line(int length)
{
    for(int i=0; i<length;i++) printf("%s", HL);
}

void draw_top_line(int length, int end_line)
{
    printf("%s", LT);
    draw_horizontal_line(length);
    printf("%s", RT);
    if(end_line)
    {
        new_line();
    }
}

void draw_line_cross(int length, int end_line)
{
    printf("%s", LC);
    draw_horizontal_line(length);
    printf("%s", RC);
    if(end_line)
    {
        new_line();
    }

}

void draw_botton_line(int length, int end_line)
{
    printf("%s", LB);
    draw_horizontal_line(length);
    printf("%s", RB);
    if(end_line)
    {
        new_line();
    }
}

void center_text(int length, char* text, int end_line)
{
    int text_length = strlen(text);
    int space_length = (length - text_length)/2;

    draw_vertical_line(1);
    
    //Add spaces before the text
    for(int i=0; i<space_length; i++){
        printf("%s", SP);
    }
    printf("%s", text);

    //If the text is odd, we need to add one more space after the text
    if(text_length%2 != 0){
        space_length++;
    }

    for(int i=0; i<space_length; i++)
    {
        printf("%s", SP);
    }
    
    draw_vertical_line(1);
    if(end_line)
    {
        new_line();
    }
}

void draw_vertical_line(int length)
{
    for(int i = 0; i < length-1; i++){
        printf("%s\n", VL);
    }
    printf("%s", VL);
}

void draw_blank_line(int length)
{
    draw_vertical_line(1);
    for(int i = 0; i < length; i++){
        printf("%s", SP);
    }
    draw_vertical_line(1);
    new_line();
}

void draw_top_tasks(int qnt_tasks)
{
    draw_vertical_line(1);
    for(int i=0; i< qnt_tasks; i++)
    {
        draw_top_line(SIZE_TASK, 0);
    }
    draw_spaces(160 - (SIZE_TASK+2)*qnt_tasks);
    draw_vertical_line(1);
    new_line();
}

void draw_spaces(int size)
{
    for(int i=0; i<size; i++) printf("%s", SP);
}

void draw_task_titles(int qnt_tasks, char ** titles)
{
    draw_vertical_line(1);
    for(int i=0; i<qnt_tasks; i++)
    {
        center_text(SIZE_TASK, titles[i], 0);
    }
    draw_spaces(160 - (SIZE_TASK+2)*qnt_tasks);
    draw_vertical_line(1);
    new_line();
}

void draw_tasks_cross(int qnt_tasks)
{
    draw_vertical_line(1);
    for(int i=0; i<qnt_tasks; i++)
    {
        draw_line_cross(SIZE_TASK, 0);
    }
    draw_spaces(160 - (SIZE_TASK+2)*qnt_tasks);
    draw_vertical_line(1);
    new_line();
}

void write_descriptions(int qnt_tasks, char ** descriptions)
{
    draw_vertical_line(1);
    for(int i=0; i<qnt_tasks; i++)
    {
        center_text(SIZE_TASK, descriptions[i], 0);
    }
    draw_spaces(160 - (SIZE_TASK+2)*qnt_tasks);
    draw_vertical_line(1);
    new_line();
}

void write_date(int qnt_tasks, char ** inicial_dates, char** final_dates)
{
    draw_vertical_line(1);
    for(int i=0; i<qnt_tasks; i++)
    {
        char formated_dates[SIZE_TASK];
        
        snprintf(formated_dates, SIZE_TASK, "Criado em %s / Data Final %s", inicial_dates[i], final_dates[i]);
        center_text(SIZE_TASK, formated_dates, 0);
    }
    draw_spaces(160 - (SIZE_TASK+2)*qnt_tasks);
    draw_vertical_line(1);
    new_line();
}

void write_status(int qnt_tasks, int *status) // 0 - a fazer, 1 - fazendo, 2 - Travado, 3 - Feito
{
    draw_vertical_line(1);

    for(int i=0; i<qnt_tasks; i++)
    {
        char status_text[30] = "Status: ";

        switch (status[i])
        {
        case 0:
            strcat(status_text, "A Fazer.");
            break;
        
        case 1:
            strcat(status_text, "Fazendo.");
            break;
        
        case 2:
            strcat(status_text, "Travado.");
            break;

        case 3:
            strcat(status_text, "Feito.");
            break;
        } 
        center_text(SIZE_TASK, status_text, 0);
    }
    draw_spaces(160 - (SIZE_TASK+2)*qnt_tasks);
    draw_vertical_line(1);
    new_line();
}

void draw_botton_tasks(int qnt_tasks)
{
    draw_vertical_line(1);
    for(int i=0; i< qnt_tasks; i++)
    {
        draw_botton_line(SIZE_TASK, 0);
    }
    draw_spaces(160 - (SIZE_TASK+2)*qnt_tasks);
    draw_vertical_line(1);
    new_line();
}

void draw_options()
{
    
    center_text(SIZE_MENU, "1 - Adicionar Tarefa",1);
    center_text(SIZE_MENU, "2 - Editar Tarefa",1);
    center_text(SIZE_MENU, "3 - Excluir Tarefa",1);
    center_text(SIZE_MENU, "4 - Alterar Status da tarefa", 1);
    center_text(SIZE_MENU, "5 - Sair do Programa", 1);
    
}


char *dia_atual()
{
    time_t t = time(NULL);
    struct tm *data = localtime(&t);

    int dia = data->tm_mday;
    int mes = data->tm_mon + 1;
    int ano = data->tm_year + 1900;
    
    char formatado[15];
    snprintf(formatado, sizeof(formatado), "%d/%d/%d",dia, mes, ano);
    char *aux = formatado;
    return aux;
}