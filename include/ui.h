#ifndef _UI_H_
#define _UI_H_

#define SIZE_MENU 160
#define SIZE_TASK SIZE_MENU/2 - 2




void draw_menu_header(char* title);
void draw_tasks(int qnt_tasks, char ** titles, char **descriptions, char **initial_dates, char **final_dates, int *status);
void draw_menu_options();


#endif
