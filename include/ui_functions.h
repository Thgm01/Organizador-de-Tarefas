#ifndef _UI_FUNCTIONS_H_
#define _UI_FUNCTIONS_H_

#define RB "\e(0\x6a\e(B" // 188 Right Bottom corner
#define RT "\e(0\x6b\e(B" // 187 Right Top corner
#define LT "\e(0\x6c\e(B" // 201 Left Top cornet
#define LB "\e(0\x6d\e(B" // 200 Left Bottom corner
#define MC "\e(0\x6e\e(B" // 206 Midle Cross
#define HL "\e(0\x71\e(B" // 205 Horizontal Line
#define LC "\e(0\x74\e(B" // 204 Left Cross
#define RC "\e(0\x75\e(B" // 185 Right Cross
#define BC "\e(0\x76\e(B" // 202 Bottom Cross
#define TC "\e(0\x77\e(B" // 203 Top Cross
#define VL "\e(0\x78\e(B" // 186 Vertical Line
#define SP " " 		  // space string

void new_line();
void draw_horizontal_line(int length);
void draw_top_line(int length, int end_line);
void draw_botton_line(int length, int end_line);
void draw_line_cross(int length, int end_line);
void center_text(int length, char* text, int end_line);
void draw_vertical_line(int length);
void draw_blank_line(int length);
void draw_top_tasks(int qnt_tasks);
void draw_spaces(int size);
void draw_task_titles(int qnt_tasks, char ** titles);
void draw_tasks_cross(int qnt_tasks);
void write_descriptions(int qnt_tasks, char ** descriptions);
void write_date(int qnt_tasks, char ** inicial_dates, char** final_dates);
void write_status(int qnt_tasks, char *status);
void draw_botton_tasks(int qnt_tasks);
void draw_options();
void draw_edit_options(int stage);


char *dia_atual();



#endif