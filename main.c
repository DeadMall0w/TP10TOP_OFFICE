////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"
#include "math.h"


struct Achat {   // Structure declaration
	int id;           // Member (int variable)
	int qtt;       // Member (char variable)
}typedef Achat;



int SIZE(int nb){
	return floor(log10(abs(nb)))+1;
}
double rechercheProduit(int* pRef, char  *lib)
{
	int laRef; double prix;
	FILE *fp = NULL;
	fp = fopen("produits.txt","r");
	if ( fp!=NULL ) 
	{
		do {
			fscanf( fp,"%d %s %lf",&laRef,lib,&prix);
			if (laRef==*pRef) {
				fclose(fp);
				return prix;
			}
		}
		while(!feof(fp));
	}
	return prix;
}

void UpdateStockFSEEK(Achat achat, int nbAchat){
	FILE *file = fopen("stock.txt", "r+");
   if (file == NULL) {
       perror("Error opening file");
   }

   fseek(file, 0, SEEK_SET);  // aller au début du fichier

   int flag = 0; // 0 reading ref, 1 reading space, 2 reading qtt
   char refAchat[11] = "";
   
   sprintf(refAchat, "%d", achat.id);
   printf("%s\n", refAchat);
   char tmp[3] = "";
   char ref[11] = "";
 
   char ch;
    do
	{
		char ch = fgetc(file); // on recup le prochain caractère
		if(flag == 0){ // On lit l'id du produit
			if (ch == ' '){ // Si c'est un espace c'est qu'on a fini de lire
				// fgetc(file);
				if (strcmp(refAchat, ref) == 0){
					printf("FOUND ! \n");
					int nb = achat.qtt;
					char toWrite[8] = "";
					sprintf(toWrite, "%d", nb);
					int taille = SIZE(nb);
					for (int i = taille; i < 8; i++)
					{
						strcat(toWrite, " ");
					}
					
					fwrite(toWrite, 1, 8, file);
					flag = 10; 
				}

				flag = 1;
				continue;
			}
			tmp[0] = ch;
			tmp[1] = '\0';
			strcat(ref, tmp);
		}
		
		if(ch == '\n'){
			// printf("reset %s \n", ref);
			strcpy(ref, "");
			flag = 0;
		}
		// printf("%c",ch);
	} while (!feof(file));





   fclose(file);
//    return 0;

}

void LireCommande(FILE * fc, char * suf){
	char nomFichier[100] = "factures/facture";
	char libelle[50];
	double pu, TOTAL = 0;
	strcat(nomFichier, suf);
	strcat(nomFichier, ".txt");
	FILE *facture=fopen(nomFichier,"w");

	char nomClient[50];
	int ref, qtt;
	
	// écriture du nom du client
	fscanf(fc, "%s\n", nomClient);
	
	fprintf(facture, "Client %s\n", nomClient);
	do{
		fscanf(fc, "%d %d", &ref, &qtt);
		printf("\n %d-%d", ref, qtt);
		pu = rechercheProduit(&ref, libelle);
		fprintf(facture, "%d - %s - (PU = %.2lf) :: %.2lf\n", qtt, libelle, pu, qtt*pu);
		TOTAL += qtt*pu;
	} while (!feof(fc));
	fprintf(facture, "\t\t\t\tTOTAL = %.2lf €\n", TOTAL);
}



int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
	FILE *f;
	int N;
	f=fopen("nextFact","r");
	fread(&N,sizeof(int),1,f);
	fclose(f);
	//printf("\n--->lu N=%d",N);
	return N;
}


void EcrireCommande(){

}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
int m,c,d,u;
char cm,cc,cd,cu;
m=N/1000;cm=48+m;
N%=1000;
c=N/100;cc=48+c;
N%=100;
d=N/10;cd=48+d;
u=N%10;
cu=48+u;
N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}


void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
FILE *ficCommande=NULL;
int FINI=0;
int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
char NNNN[5];
char nomCommande[29];

do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
	{
	strcpy(nomCommande,"./commandes/commande");
	convertirNenChaine4(N,NNNN); 
	//printf("\n==>%s<==",NNNN);
	ficCommande=NULL;
	strcat(nomCommande,NNNN);
	strcat(nomCommande,".txt");
	
	//printf("\n traitement de  %s",nomCommande);
	
	ficCommande=fopen(nomCommande,"rt");
	if (ficCommande!=NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present",nomCommande);
			LireCommande(ficCommande, NNNN); // à vous de coder cette fonction lors de ce TP9
			fclose(ficCommande);
		}
	else
		{
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
			// pour 
			fwrite(&N,1,sizeof(int),f);
			fclose(f);
			FINI=1;			
		}

	N++;
	}while(FINI==0);		

}



int main()
{
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	FILE *f;int N=1;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);

	Achat achat;
	achat.id = 231698547;
	achat.qtt = 10;

 	
	UpdateStockFSEEK(achat, 2);

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	

	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	

	return 0;
}
