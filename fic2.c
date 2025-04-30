////////////////////////// lire un fichier texte quelconque LIGNE par LIGNE
// quelconque signifie : sans format spécifique

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_LIGNES_MAX_DU_POEME 200
#define TAILLEMAX_LIGNE 200 //
typedef char T_chaine[TAILLEMAX_LIGNE];
/*******************************************************************/
/*    fonction : lireUnFichierTXTQuelconque 	                  */
/*    description  : lire 'importe quel fichier txt		  */
/*    paramètre : aucun						   */
/*    retourne : RIEN					           */
/*    condition : le fichier poeme.txt doit exister 		   */
/*    auteur : kub						   */
/*    date : 29/3/20						   */
/*******************************************************************/

int lireUnFichierTXTQuelconque(T_chaine *Tab_lignes) 
{

T_chaine ligne;
int numLigne=1;
FILE *fic=NULL;

	fic=fopen("poeme.txt","rt");//mode rt = "read" et "text"
	if (fic!=NULL)
		{ // le fichier txt existe
		do
		{

		//fgets(ligne,TAILLEMAX_LIGNE,fic);//pas de fscanf ici sinon vous ne lirez jamais toute la ligne (mais simplement son premier mot
		//ou bien pour lire commandeXXXX.txt
        //int ref;
        //int qtt;
        T_Produit P;

        //
        // fscanf(fic, "%i %s  %f", &(P.reference)  , P.libelle, &(P.prixU)  ); 
        //plus besoin de atoi

        
        ligne[strlen(ligne)-1]='\0';
		if (!(feof(fic)))		
		{
			strcpy(Tab_lignes[numLigne],ligne);
			numLigne++;
			printf("\n>%s<",ligne);
		}
		}while(!(feof(fic)));
		fclose(fic);
		
		}
return numLigne-1;
}


/**************************************************************************/
/*        prepa au TP10 : lire et ecrire dans des fichiers txt        */
/**************************************************************************/
int main()
{
int j;
T_chaine leTableauDesLignes[NB_LIGNES_MAX_DU_POEME+1];

	int nbLignesDansLePoeme= lireUnFichierTXTQuelconque(leTableauDesLignes);
	getchar();
	for(j=1;j<=nbLignesDansLePoeme;j++)
		printf("\n-->%s<--",leTableauDesLignes[j]);
	printf("\n-->il y a %d lignes dans ce fichier.",nbLignesDansLePoeme);


	return 0;
}
