#ifndef _UI_H_
#define _UI_H_

#define SIZE_MENU 160
#define SIZE_TASK SIZE_MENU/2 - 2

#include "main.h"



void draw_menu_header(char* title);
void draw_tasks(int qnt_tasks, char ** titles, char **descriptions, char **initial_dates, char **final_dates, char *status);
void draw_menu_options();
void draw_empty_tasks();
void draw_menu_edit_options(int stage, struct DadosTarefa *D);
void draw_credits();

#endif
