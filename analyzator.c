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


typedef struct{
	unsigned char d;
	float *p;
}POSTUPNOST;																	//struktura kde d je pocet floatov branych do uvahy pri dalsich vypoctoch

void analyzator(char fileName[]){
	int f,i,j,n=0,pocet_bajtov;
	unsigned char c,g;
	float priemer,*priemer_floatov,total_priemer;
	POSTUPNOST *A;
	
	f = open(fileName,O_RDONLY| O_BINARY,S_IWUSR);								

	pocet_bajtov=lseek(f,0,SEEK_END);											// zistenie dlzky suboru

	lseek(f,0,SEEK_SET);														//navrat file pointera na zaciatok

	for(i=0;i<pocet_bajtov;i++){
	
		read(f,&c,sizeof(unsigned char));
		i = lseek(f,(int)c*(sizeof(float)), SEEK_CUR);
		n++;
						
	}																			//vypocet poctu postupnosti
		
	printf("pocet postupnosti =%d \n",n);
	
	lseek(f, 0, SEEK_SET);
	
	A=malloc(n*sizeof(POSTUPNOST));
	
	for(i=0;i<n;i++){

		read(f,&A[i].d,sizeof(unsigned char));
		A[i].p=malloc((int)A[i].d*sizeof(float));
		
		for(j=0;j<(int)A[i].d;j++){	
			read(f,&A[i].p[j],sizeof(float));
		}
	}														//nacitanie postupnosti do struktur
								
	priemer_floatov=malloc(n*sizeof(float));
	for(i=0;i<n;i++){
		
		for(j=0;j<(int)A[i].d;j++){
			priemer+=A[i].p[j];
			
		}
		priemer_floatov[i]=priemer/((int)A[i].d);
		printf("priemer v %d.postupnosti je= %f\n",i+1,priemer_floatov[i]);
		priemer=0;
	}																		//ulozenie priemerov v jednotlivych postupnostiach
	
	for(i=0;i<n;i++){
		total_priemer+=priemer_floatov[i];
	}																		//vypocet uplneho priemeru
	total_priemer=total_priemer/n;
	printf("priemer priemerov postupnosti je= %f\n",total_priemer);
	
	for(i=0;i<n;i++){		
		for(j=0;j<(int)A[i].d;j++){
			printf("%f  ",A[i].p[j]);
		}
		printf("\n");
	}																		//vypis postupnosti
	
	for(i=0;i<n;i++){
		free(A[i].p);
		
	}																		//uvolnenie pamate
	free(A);	
}
int main(int argc,char *argv[]){
	
	if (argc!=2){
		printf("zle zadane argumenty");
		return 0;
	}
	analyzator(argv[1]);
}
