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
	unsigned char *d;
	float *p[20];
}POSTUPNOST;																	//struktura kde d je pocet floatov branych do uvahy pri dalsich vypoctoch

void analyzator(char fileName[]){
	int f,i,j,n,pocet_bitov;
	unsigned char c,p,g;

	f = open(fileName,O_RDONLY| O_BINARY,S_IWUSR);								


	pocet_bitov=lseek(f,0,SEEK_END);											// zistenie dlzky suboru

	lseek(f,0, SEEK_SET);														//navrat file pointera na zaciatok

		
		
		
	for(i=0;i<pocet_bitov;i++){
	
		read(f,&c,sizeof(unsigned char));
		i = lseek(f,(int)c*(sizeof(float)), SEEK_CUR);
		n++;
						
	}																			//vypocet poctu postupnosti
	
	printf("pocet postupnosti =%d \n",n);
	
	lseek(f, 0, SEEK_SET);
	
	POSTUPNOST A[n];


	for(i=0;i<n;i++){
	
		A[i].d= (unsigned char *)malloc (sizeof(unsigned char));
		read(f,A[i].d,sizeof(unsigned char));
		
		for(j=0;j<(int)*A[i].d;j++){
			A[i].p[j]= (float*)malloc (sizeof(float));
				read(f,A[i].p[j],sizeof(float));
		}		
	}																		//nacitanie postupnosti do struktur
	float priemer,priemer_floatov[n],total_priemer;							//deklaracia premennych na vypocet priemerov


	for(i=0;i<n;i++){
		
		for(j=0;j<(int)*A[i].d;j++){
			priemer+=*A[i].p[j];
		}
		priemer_floatov[i]=priemer/(*A[i].d);
		printf("priemer v %d.postupnosti je= %f\n",i,priemer_floatov[i]);
		priemer=0;
	}																		//ulozenie priemerov v jednotlivych postupnostiach
	
	for(i=0;i<n;i++){
		total_priemer+=priemer_floatov[i];
	}																		//vypocet uplneho priemeru
	total_priemer=total_priemer/n;
	printf("priemer priemerov postupnosti je= %f\n",total_priemer);
	
	for(i=0;i<n;i++){		
		for(j=0;j<(int)*A[i].d;j++){
			printf("    %f",*A[i].p[j]);
		}
		printf("\n");
	}																		//vypis postupnosti
	
	for(i=0;i<n;i++){	
		
		for(j=0;j<(int)*A[i].d;j++){
			
			free(A[i].p[j]);
	
		}
		free(A[i].d);
	}																		//uvolnenie pamate
	
	
}
int main(int argc,char *argv[]){
	
	analyzator(argv[1]);
	
	if (argc!=2){
		printf("zle zadane argumenty");
		return 0;
	}
	
}
