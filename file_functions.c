#include <stdio.h>
#include <stdlib.h>

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
    while (stc[size].titulo !=NULL)
    {
        size++;
    }
    
    return size;
}