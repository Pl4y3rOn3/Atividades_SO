#include <stdio.h>
#include<stdlib.h>
#include <conio.h>

struct pstruct{
	int fno; //frame onde a pagina é alocada
	int pbit; //bit de presenca
}ptable[10];

typedef struct process{
	int psize;
	int npaginas;
	int pid;
	char pname[30];
}process;

typedef struct block{
	int bid;
}block;

int pmsize, lmsize, psize, frame, page, ftable[20], frameno;
//pmsize = tamanho memoria fisica; lmsize = tamanho memoria virtual;
//psize = tamanho da particao; frame = quantidade de frames ; page= quantidade de paginas;

void info(){
	psize = 0;
	printf("\n\nEnter the Size of Physical memory: ");
	scanf("%d",&pmsize);
	
	printf("\n\nEnter the size of Logical memory: ");
	scanf("%d",&lmsize);
	
	printf("\n\nEnter the partition size: ");
	scanf("%d",&psize);
	
	frame = (int) pmsize/psize;
	page = (int) lmsize/psize;
	
	printf("\nThe physical memory is divided into %d no.of frames\n",frame);
	printf("\nThe Logical memory is divided into %d no.of pages",page);
	
}

void assign(){
	int i;
	
	for (i=0;i<page;i++){
		ptable[i].fno = -1;
		ptable[i].pbit= -1;
	}
	for(i=0; i<frame;i++)
		ftable[i] = 32555;
	for (i=0;i<page;i++){
		printf("\n\nEnter the Frame number where page %d must be placed: ",i);
		scanf("%d",&frameno);
		ftable[frameno] = i;
		if(ptable[i].pbit == -1){
			ptable[i].fno = frameno;
			ptable[i].pbit = 1;
		}
	}
	
	getch();
	
	printf("\n\nPAGE TABLE\n\n");
	printf("PageAddress FrameNo. PresenceBit\n\n");
	
	for (i=0;i<page;i++)
		printf("%d\t\t%d\t\t%d\n",i,ptable[i].fno,ptable[i].pbit);
		printf("\n\n\n\tFRAME TABLE\n\n");
		printf("FrameAddress PageNo\n\n");
	for(i=0;i<frame;i++)
		printf("%d\t\t%d\n",i,ftable[i]);
}

void fifo(){
	
	int i,j,n,k,m,r,t,pagef;
	int contsize, contpage, npage, in_frag;
	
	process p[100];
	block b[100];
	
	k=0,pagef=0;
	
	n = page;
	m = frame;
	
	for(i=0;i<m;i++) //blocos são preenchidos com -1
		b[i].bid=-1;
	
	contpage = 0;
	in_frag = 0;
	for(i=0;i<n;i++){
		printf("enter the process id [%d]: ", i);
		scanf("%d",&p[i].pid);
		printf("enter the process name [%d]: ", i);
		scanf("%s",&p[i].pname);
		printf("enter the process size [%d]: ", i);
		scanf("%d",&p[i].psize);
		printf("\n");
		
		contsize = psize;
		npage = 1;
		if(p[i].psize <= psize){
			p[i].npaginas = npage;
			in_frag = in_frag + (psize - p[i].psize);
			//printf("\n\tnpage = %d\n", p[i].npaginas);
		}
		else{
			while(p[i].psize > contsize){
				contsize = contsize + psize;
				npage = npage + 1;
				if(p[i].psize <= contsize){
					p[i].npaginas = npage;
					in_frag = in_frag + (contsize - p[i].psize);
					//printf("\n\tnpage = %d\n", p[i].npaginas);
				}
			}
		}
		contpage = contpage + npage;
		if(contpage > page){
			printf("\nLimite de Paginas atingido\n");
			break;
		}
	}
	
	printf("\n-----------------------------------------\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(b[j].bid==p[i].pid){
				printf("the page %d is already present in main memory\n",p[i].pid);
				break;
			}
		}
		if(j==m){
			
			for(t=0;t<p[i].npaginas;t++){
			b[k].bid = p[i].pid;
			k++;
			
			if(k==m)
				k=0;
			
			for(r=0;r<m;r++)
				printf("\t %d ",b[r].bid);
			
			printf("\n");
			}
			pagef++;
		}
	}
	printf("\n-----------------------------------------\n");
	printf("\nnumber of page faults: %d", pagef);
	printf("\ntotal internal fragmentation: %d", in_frag);
	
	getch(); 
}

int main()
{
	int ch;
	do{
		printf("\n\n ------------------------------------------------------");
		printf("\n\n Options:");
		printf("\n 0. Info");
		printf("\n 1. PTable");
		printf("\n 2. FIFO");
		printf("\n 5. Exit");
		printf("\n Select : ");
		scanf("%d",&ch);
		
		switch(ch){
			case 0:
				info();
				break;
			case 1:
				assign();
				break;
			case 2:
				fifo();
				break;
			case 5: exit(0);
			default:
				printf("\n Invalid selection.");
		}
	}while(ch != 5);
	getch();
}
