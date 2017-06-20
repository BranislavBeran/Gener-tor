#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#define ohranicenie 20

typedef struct{
	unsigned char d;
	float *p;
}POSTUPNOST;																		//struktura pre postupnosti

void generuj_postupnost(POSTUPNOST *A){
	int i;

	A->d=rand()%11+10;
	printf("%d ",A->d);
	A->p=malloc((int)A->d*sizeof(float));
    for (i=0;i<(int)A->d;i++){
    	A->p[i]= rand()/(float)(RAND_MAX)* ohranicenie; 	
		printf("%f ",A->p[i]);
	}
}																					//generuje naodne postupnosti a uklada ich do pola struktur

void vytvorsubor(char fileName[],int n){    
	int f;
	int i,j;
	POSTUPNOST *A;
	
	f =  open(fileName,O_WRONLY| O_BINARY | O_CREAT,S_IWUSR);
	
	A=malloc(n*sizeof(POSTUPNOST));
	
	for(i=0;i<n;i++){
		generuj_postupnost(&A[i]);
	}
	
	for(i=0;i<n;i++){	
		write(f,&A[i].d,sizeof(unsigned char));
		printf("%d ",A[i].d);
		
		for(j=0;j<(int)A[i].d;j++){
		
			write(f,&A[i].p[j],sizeof(float));
			printf("%f ",A[i].p[j]);
		}
		printf("\n");														//zapise do suboru 
	}
	free(A);
}
	
int main(int argc,char* argv[]){
	int i,n;

	srand(time(NULL));
	
	n=atoi(argv[2]);
	
	if (argc!=3){
		printf("zle zadane argumenty");
		return 0;
	}
	
	vytvorsubor(argv[1],n);
}
