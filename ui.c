#include <stdio.h>
#include <stdlib.h>

#include "include/utils.h"
#include "include/ui.h"

void draw_menu_header(char* title)
{
    draw_top_line(SIZE_MENU, 1);
    center_text(SIZE_MENU, title, 1);
    draw_line_cross(SIZE_MENU, 1);
    draw_blank_line(SIZE_MENU);
}

void draw_tasks(int qnt_tasks, char ** titles, char **descriptions, char **initial_dates, char **final_dates, int *status)
{
    if(qnt_tasks == 0)
    {
        draw_blank_line(SIZE_MENU);
        center_text(SIZE_MENU, "Nenhuma Tarefa!", 1);
        draw_blank_line(SIZE_MENU);
        draw_blank_line(SIZE_MENU);
    }
    else 
    {
        draw_top_tasks(qnt_tasks);
        draw_task_titles(qnt_tasks, titles);
        draw_tasks_cross(qnt_tasks);
        write_descriptions(qnt_tasks, descriptions);
        draw_tasks_cross(qnt_tasks);
        write_date(qnt_tasks, initial_dates, final_dates);
        draw_tasks_cross(qnt_tasks);
        write_status(qnt_tasks, status);
        draw_botton_tasks(qnt_tasks);
        draw_blank_line(SIZE_MENU);
    }
}

void draw_menu_options()
{
    draw_line_cross(SIZE_MENU, 1);
    draw_blank_line(SIZE_MENU);
    draw_options();
    draw_blank_line(SIZE_MENU);
    draw_botton_line(SIZE_MENU, 1);

}