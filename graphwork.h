#include <stdio.h>
#include <stdlib.h>

#define ZERO 0x0
#define ONE 0x1 
#define M_ONE 0x2

typedef struct bit_matrix {
	int x;
	int y;
	int *a;
}matr;

matr read_mi(char *file_in);
matr get_ms(matr *mi);
int write_matr(matr *in, char *file_out);
int check_file(char *fname, char m_type, int x);

matr read_mi(char *file_in) {
	FILE *in=fopen(file_in, "r");
	matr mi;
	char x=0, y=0;
	char *buff;
	int i, j, s;
	if (!in) {
		printf("Входной файл не найден: %s\n", file_in);
		exit(1);
	}
	/*Получение размеров матрицы из файла*/
		fscanf(in, "%d %d\n", &mi.y, &mi.x);
		y=mi.y;
		x=mi.x;
		if(x>16) {
			printf("Количество обрабатываемых вершин не может быть больше 16\n");
			exit(1);
		}
	/*Выделение пространства на матрицу*/
		mi.a=calloc(y,sizeof(int)); 
		for(i=0; i<y;i++) 
			mi.a[i]=0;
	/*Заполнение матрицы*/
		buff=malloc(x*sizeof(char));
		for(i=0; i<y;i++) {
			fgets(buff,x+2,in);
			s=0;
			for(j=x-1;j>=0;j--) {
				switch(buff[j]) {
					case '0':
						mi.a[i]|=ZERO<<(2*s); 
					break;
					case '1':
						mi.a[i]|=ONE<<(2*s); 
					break;
					case '2':
						mi.a[i]|=M_ONE<<(2*s); 
					break;
				}
				s++;
			}
		}
	fclose(in);
	/* Обязательно освободить память.
	Иначе следующая ошибка: malloc(): memory corruption. 
	ХЗ почему*/
	free(buff);  
	return mi;
}

matr get_ms(matr *mi) {
	int i,j, ji;
	int y=mi->y;
	int x=mi->x;
	int pos_1, pos_2;
	char is_ONE=0, is_M_ONE=0;
	int dbl;
	matr ms;
	ms.a=calloc(x,sizeof(char));
	for(i=0;i<y;i++)
		ms.a[i]=0;
	ms.x=ms.y=mi->x;
	for(i=0;i<y;i++) {
		for(j=0, ji=x-1;j<x;j++, ji--) {
			dbl=mi->a[i]&(0x3<<j*2);
			dbl>>=j*2;
			if(dbl==ONE) {
				is_ONE=1;
				pos_1=ji;
				int jj;
				int dbl;
				for(jj=0;jj<x;jj++) {
					dbl=mi->a[i]&(0x3<<jj*2);
					dbl>>=jj*2;
					if(dbl==M_ONE) {
						is_M_ONE=1;
						pos_2=jj;
						ms.a[pos_1]|=1<<pos_2;
					}
					dbl=0;
				}
				if(!is_M_ONE) {
					printf("Ошибка в матрице инцидентности: отсутствует конец дуги. Строка %d\n", i+1);
					exit(1);
				}
			}
		}
		is_M_ONE=0;
		if(!is_ONE) {
			printf("Ошибка в матрице инцидентности: отсутствует начало дуги. Строка %d\n", i+1);
			exit(1);
		}
		is_ONE=0;
	}
	return ms;
}

int write_matr(matr *in, char *file_out) {
	FILE *out=fopen(file_out, "wb");
	fwrite(in->a,sizeof(int),in->y,out);
	fclose(out);
	return 0;
}

int check_file(char *fname, char m_type, int x) {
	FILE *in=fopen(fname, "rb");
	int buff, i, j;
	printf("  ");
	for(i=1;i<x+1;i++)
		printf(" %02d",i);
	printf("\n");
	for(i=1;i<x+1;i++)
		printf("---");
	printf("--");
	printf("\n");
	j=1;
	while (fread(&buff, sizeof(int), 1, in)) {
		printf("%02d|", j);
		for(i=x-1;i>=0;i--)
			if (m_type=='a')
				printf("%d  ", (buff&(1<<i))>>i);
			else
				printf("%d  ", (buff&(3<<i*2))>>i*2);
		printf("[0x%x]", buff);
		printf("\n");
		j++;
	}
	fclose(in);
	return 0;
}
