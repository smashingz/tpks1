/*Вариант №1*/
#include "graphwork.h"
#include "matgen.h"
#include <string.h>
#include <ctype.h>

typedef struct {
	unsigned int random: 1;
	unsigned int quiet: 1;
} flags;

void parse_arg(int ac, char **av, flags *f, char **file, int *x, int *y);
void print_help();

int main(int argc, char **argv) {
	flags f;
	f.random=f.quiet=0;
	matr mi, ms;
	int x,y;
	char *infile="", *mi_outfile, *ms_outfile;
	if(argc==1) {
		print_help();
		exit(0);
	}
	parse_arg(argc, argv, &f, &infile, &x, &y);
	mi_outfile=malloc(strlen(infile));
	ms_outfile=malloc(strlen(infile));
	strcpy(mi_outfile, infile);
	strcpy(ms_outfile, infile);
	strcat(mi_outfile, ".im");
	strcat(ms_outfile, ".am");
	/*Генерация матрицы в файле*/
	if(f.random)
		create_inc_matr(infile, y, x);
	mi=read_mi(infile);
	write_matr(&mi, mi_outfile);
	if(!f.quiet) {
		printf("Матрица инцидентности:\n");
		check_file(mi_outfile, 'i', mi.x);
		printf("\n");
	}
	ms=get_ms(&mi);
	write_matr(&ms, ms_outfile); 
	if(!f.quiet) {
		printf("Матрица смежности:\n");
		check_file(ms_outfile, 'a', ms.x);
	}
	return 0;
}

void parse_arg(int ac, char **av, flags *f, char **file, int *x, int *y) {
	int i=0, j=0;
	for(i=1;i<ac;i++)
		if(av[i][0]=='-')
			for(j=1;j<strlen(av[i]);j++)
				switch(av[i][j]) {
					case 'r':
						f->random=1;
					break;
					case 'q':
						f->quiet=1;
					break;
					default:
						printf("Введён неправильный аргумент: \"-%c\"\n",av[i][j]);
					exit(1);
					break;
					case 'h':
						print_help();
					break;
				}	
		else {
			*file=av[i];
			/*file=calloc(strlen(av[i]), sizeof(char));
			strcpy(file, av[i]);	*/
			if(!isdigit(*av[i+1])) {
				printf("Неправильно введен параметр х.\n");
				exit(1);
			}
			else
				*x=strtol(av[i+1], NULL, 10);
			if(!isdigit(*av[i+2])) {
				printf("Неправильно введен параметр y.\n");
				exit(1);
			}
			else
				*y=strtol(av[i+2], NULL, 10);
		i+=2;
		}
	return;
}
	
void print_help() {
	printf(
		"Синтаксис:\n"
		"\t./programm [параметры] [имя файла] [x] [y]\n"
		"Параметры:\n"
		"\t-r\tСгенерировать случайную матрицу инцидентности.\n"
		"\t-q\tЗапустить программу без вывода матриц на экран.\n"
		"\t-h\tВывести эту информацию.\n"
		"Описание:\n"
		"\tПрограмма преобразует матрицу инцидентности размерностью \"x\" вершин на \"y\" дуг в матрицу связности. При задании имени файла вывод матриц происходит в файлы <имя_файла>.im  и <имя_файла>.am, иначе имя файла заменяется стандартным именем.\n"
	);
	return;
}
