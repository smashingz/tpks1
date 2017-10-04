/*Вариант №1*/
#include "graphwork.h"
#include "matgen.h"
#include <string.h>

typedef struct {
	unsigned int random: 1;
	unsigned int quiet: 1;
	unsigned int file: 1;
	unsigned int help: 1;
} flags;

void print_help();

int main(int argc, char **argv) {
	matr mi, ms;
	int x,y;
	char *infile, *mi_outfile, *ms_outfile;
	if(argc==1) {
		print_help();
		exit(0);
	}
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

void parse_arg(char **argv, flags *f) {
	return;
}
	
void print_help() {
	printf(
		"Синтаксис:\n"
		"\t./programm [параметры] [имя файла]\n"
		"Параметры:\n"
		"\t-r\tСгенерировать случайную матрицу инцидентности\n"
		"\t-q\tЗапустить программу без вывода матриц на экран\n"
		"\t-f\tЗадать вывод матриц в опрелелённый файл\n"
		"\t-h\tВывести эту информацию\n"
		"Описание:\n"
		"\tПрограмма преобразует матрицу инцидентности в матрицу связности. При задании имени файла вывод матриц происходит в файлы <имя_файла>.im  и <имя_файла>.am, иначе имя файла заменяется стандартным именем.\n"
	);
	return;
}
