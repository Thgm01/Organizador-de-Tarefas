#ifndef _FILE_FUNCTIONS_H_
#define _FILE_FUNCTIONS_H_


FILE *open_file(char *mode);
int size_struct(struct DadosTarefa *stc);
int size_file();

void rewrite_file(int line);



#endif