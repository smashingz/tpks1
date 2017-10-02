/*Вариант №1*/
#include "graphwork.h"
#include "matgen.h"
#include <string.h>

int main(int argc, char **argv) {
	matr mi, ms;
	int x,y;
	char *infile, *mi_outfile, *ms_outfile;
	infile=argv[1];
	x=atoi(argv[2]);
	y=atoi(argv[3]);
	mi_outfile=malloc(strlen(infile));
	ms_outfile=malloc(strlen(infile));
	strcpy(mi_outfile, infile);
	strcpy(ms_outfile, infile);
	strcat(mi_outfile, ".im");
	strcat(ms_outfile, ".am");
	/*Генерация матрицы в файле*/
	create_inc_matr(infile, y, x);
	mi=read_mi(infile);
	write_matr(&mi, mi_outfile);
	printf("Матрица инцидентности:\n");
	check_file(mi_outfile, 'i', mi.x);
	printf("\n");
	ms=get_ms(&mi);
	write_matr(&ms, ms_outfile); 
	printf("Матрица смежности:\n");
	check_file(ms_outfile, 'a', ms.x);
	return 0;
}
