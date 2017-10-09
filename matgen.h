#include <stdio.h>
#include <stdlib.h>

int create_inc_matr(char *file, int x, int y);
int rm_repeat_str(int **buff, int y, int x);
int arr_cmp(int size, int *a, int *b);

int create_inc_matr(char *file, int x, int y) {
	int i,j,one_pos,two_pos;
	int *buff[y];
	FILE *in=fopen(file, "w");
	for(i=0;i<y;i++) {
		buff[i]=calloc(x,sizeof(int));
		for(j=0;j<x;j++)
			buff[i][j]=0;
	}
/*Генерация матрицы*/
	for(i=0;i<y;i++) {
		one_pos=rand()%x;
		while((two_pos=rand()%x)==one_pos)
			two_pos=rand()%x;
		buff[i][one_pos]=1;
		buff[i][two_pos]=2;
	}
/*Удаление в матрице повторяющихся строк*/
	y=rm_repeat_str(buff, y, x);
/*Запись матрицы в файл*/
	fprintf(in, "%d %d\n", y, x);
	for(i=0;i<y;i++) {
		for(j=0;j<x;j++)
			fprintf(in, "%d", buff[i][j]);
		fprintf(in, "\n");
	}
	for(i=0;i<4;i++)
		free(buff[i]);
	//fclose(in);
	return 0;
}

int rm_repeat_str(int **buff, int y, int x) {	
	int i, j, k;
	for(i=0;i<y;i++)
		for(j=i+1;j<y;j++)
			if(arr_cmp(x, buff[i], buff[j])) {
				for(k=j;k<y-1;k++)
					buff[k]=buff[k+1];
				y--;
			}
	return y;
}

int arr_cmp(int size, int *a, int *b) {
	int i;
	for(i=0;i<size;i++)
		if (a[i]!=b[i])
			return 0;
	return 1;
}
