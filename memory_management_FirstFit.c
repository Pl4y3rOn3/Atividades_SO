#include<stdio.h>
#include<stdlib.h>
#include <conio.h>

#define MEM_MAX 256

typedef struct process{
	char pname[20];
	int psize;
	int pid;
	int pflag;
}process;

typedef struct block{
	int bid;
	int bsize;
	int bflag;
}block;

int cont;

void accept(process p[],block b[],int *n,int *m){
	
	int i,j,k;
	cont = 0;
	
	printf("\n Enter no. of blocks : ");
	scanf("%d",m);
	for(i=0;i<*m;i++){
		if(cont <= MEM_MAX){
			printf(" Enter size of block[%d] : ",i);
			scanf("%d",&k);
			cont = cont + k;
		}
		if(cont <= MEM_MAX){
			b[i].bsize = k;
		}
		else{
			printf(" Limite de memoria atingido, bloco %d nao registrado",i);
			*m = *m-1;
		}
		b[i].bid = i;
	}

	printf("\n Enter no. of processes : ");
	scanf("%d",n);
	for(i=0;i<*n;i++){
		printf(" Enter name of process[%d] : ",i);
		scanf("%s",&p[i].pname);
		printf(" Enter size of process[%d] : ",i);
		scanf("%d",&p[i].psize);
		printf("\n");
		p[i].pid = i;
	}

}

void re_init(process p[],block b[],int n,int m){
	int i;
	for(i=0;i<n;i++)
		p[i].pflag=0;
	for(i=0;i<m;i++)
		b[i].bflag=0;
}

void first_fit(process p[],block b[],int n,int m){

	int i,j,in_frag=0,ex_frag=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(p[i].psize <= b[j].bsize && b[j].bflag == 0 && p[i].pflag == 0){
				b[j].bflag = p[i].pflag = 1;
				in_frag += b[j].bsize - p[i].psize;
				printf("\n P: id: %d | name: %s | size: %d \t - \t B: id: %d | size: %d \t - \t Frag interna: %d",p[i].pid,p[i].pname,p[i].psize, b[j].bid, b[j].bsize, (b[j].bsize - p[i].psize));
				break;
			}
			
		}
		if(p[i].pflag == 0)
			printf("\n P: id: %d | name: %s | size: %d \t - \t Unsigned",p[i].pid,p[i].pname,p[i].psize);
	}
	printf("\n");
	for(j=0;j<m;j++){
		if(b[j].bflag == 0){
			printf("\n Bloco de memoria livre: id: %d | size: %d",b[j].bid, b[j].bsize);
			ex_frag+=b[j].bsize;
		}
	}
	
	printf("\n\n Total internal fragmentation : %d",in_frag );
	printf("\n Total external fragmentation : %d",ex_frag );
	printf("\n Memoria livre : %d", MEM_MAX - cont);
}

int main(){

	int ch,n=0,m=0;
	process p[10];
	block b[10];
	do{
		printf("\n\n ----------------------------------------------------------- ");
		printf("\n\n Options:");
		printf("\n 0. Accept");
		printf("\n 1. First Fit");
		printf("\n 5. Exit");
		printf("\n Select : ");
		scanf("%d",&ch);
		switch(ch){
			case 0:
				accept(p,b,&n,&m);
				break;
			case 1:
				re_init(p,b,n,m);
				first_fit(p,b,n,m);
				break;
			case 5:exit(0);
			default:
				printf("\n Invalid selection.");
		}
	}while(ch != 5);
	getch();
	return 0;
}