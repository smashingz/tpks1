/*Вариант №1*/
#include "graphwork.h"
#include <string.h>

int main(int argc, char **argv) {
	matr mi, ms;
	char *infile, *mi_outfile, *ms_outfile;
	infile=argv[1];
	mi_outfile=malloc(sizeof(infile));
	ms_outfile=malloc(sizeof(infile));
	strcpy(mi_outfile, infile);
	strcpy(ms_outfile, infile);
	strcat(mi_outfile, ".im");
	strcat(ms_outfile, ".am");
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
