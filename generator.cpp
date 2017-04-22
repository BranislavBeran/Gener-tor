#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>


typedef struct{
	unsigned char d;
	float p[20];
}POSTUPNOST;

void generuj_postupnost(POSTUPNOST *A){
	
	int i;
	
	A->d=rand()%10+11;
	
	printf(" %d \n",A->d);
	
    for (i=0;i<A->d;i++){
    	A->p[i]= rand()/(float)(RAND_MAX)* 20;
    	
	}
}

void vytvorsubor(char fileName[],int n){    
	FILE *f;
	int i,j;
	POSTUPNOST A[n];
	
	f = fopen(fileName, "w");
	if(f == NULL){
		printf("%s", strerror(errno));
		return;
	}
	
	for(i=0;i<n;i++){
		generuj_postupnost(&A[i]);
	}
//	
//	for(i=0;i<n;i++){
//		write(f,A[i].d,sizeof(unsigned char));		
//		write(f,A[i].p,A[i].d*sizeof(float));
//	}
	

	
	if(fclose(f) == EOF){
		printf("Unable to close file\n");
		return;
	}
}
	
main(){
	srand(time(NULL));
	

	int i;
	char meno[20];
	int n;
	
	scanf("%s",&meno);
	scanf("%d",&n);
	

	vytvorsubor(meno,n);

//	subor = (int*)malloc (()*sizeof(unsigned char));
	
}
