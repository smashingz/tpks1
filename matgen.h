#include <stdio.h>
#include <stdlib.h>

int create_inc_matr(char *file, int x, int y);

int create_inc_matr(char *file, int x, int y) {
	int i,j,one_pos,two_pos;
	int *buff;
	FILE *in=fopen(file, "w");
	buff=calloc(x,sizeof(int));
	for(i=0;i<x;i++)
		buff[i]=0;
	fprintf(in, "%d %d\n",y,x);
	for(i=0;i<y;i++) {
		one_pos=rand()%x;
		while((two_pos=rand()%x)==one_pos)
			two_pos=rand()%x;
		buff[one_pos]=1;
		buff[two_pos]=2;
		for(j=0;j<x;j++)
			fprintf(in, "%d", buff[j]);
		fprintf(in, "\n");
		buff[one_pos]=buff[two_pos]=0;
	}
	free(buff);
	fclose(in);
	return 0;
}
