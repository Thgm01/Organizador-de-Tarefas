#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "include/ui_functions.h"
#include "include/ui.h"
#include "include/main.h"
#include "include/file_functions.h"

FILE *open_file(char *mode) {
  FILE *f;
  f = fopen(FILENAME, mode);
  if (!f) {
    f = open_file("w");
  }
  return f;
}

int size_struct(struct DadosTarefa *stc)
{
    int size=0;
    while (stc[size].titulo != "")
    {
      printf("%s\n", stc[size].titulo);
      size++;
    }
    
    return size;
}

int size_file()
{
  FILE *dados = open_file("r");

  char lixo[SIZE_TASK*4];

  int cont = 0;
  while (fgets(lixo, sizeof(lixo), dados) != NULL) 
  {
    cont++;
  }
  return cont;

  fclose(dados);

}

void rewrite_file(int line)
{
  int size = size_file();

  FILE *dados = open_file("r");

  char buffer[size][SIZE_TASK*4];

  for(int i=0; i<size; i++)
  {
    fgets(buffer[i], SIZE_TASK*4, dados);
  }
  fclose(dados);

  FILE *dados_2 = open_file("w");
  for(int i=0; i<size; i++)
  {
    if(i != line-1){
      fprintf(dados_2, "%s", buffer[i]);
    }
  }
  fclose(dados_2);
}

void edit_task_data(int task_number, int opt)
{
  char buffer[SIZE_TASK];
  char *perguntas[] = {"o novo titulo: ", "a nova descricao: ", "a nova data final: ", "o novo status: "};
  printf("Digite ");

  printf("%s", perguntas[opt-1]);  
  getchar();
  fgets(buffer, SIZE_TASK, stdin);
  buffer[strcspn(buffer, "\n")] = 0;

  struct DadosTarefa *data = le_tarefas();

  switch (opt)
  {
  case 1:
    strcpy(data[task_number-1].titulo, buffer);
    break;
  
  case 2:
    strcpy(data[task_number-1].observacao , buffer);
    break;

  case 3:
    strcpy(data[task_number-1].data_final, buffer);
    break;

  case 4:
    data[task_number-1].status = buffer[0];
    break;
  default:
    break;
  }

  

  char formated[4*SIZE_TASK];

  snprintf(formated, sizeof(formated), "%s,%s,%s,%s,%c\n", data[task_number-1].titulo , data[task_number-1].observacao, data[task_number-1].data_criacao, data[task_number-1].data_final, data[task_number-1].status);
  

  rewrite_file(task_number);

  FILE *dados = open_file("a");
  fprintf(dados, "%s", formated);
  fclose(dados);


  free(data);


  return;
}