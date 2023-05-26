#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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