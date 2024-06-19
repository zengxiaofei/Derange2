/* Permutation solver using inversions, transpositions
   and transversions (a transposition on which the moved segments
   is inverted). Uses a depht-first exploration of the available solutions.
   
   Created by Mathieu Blanchette, directed by David Sankoff.
   Centre de Recherches Mathematiques, Universite de Montreal
  		      
   Last modifications on 29/11/95
		      
   For more informations, comments or suggestions :
		      
   e-mail : blanchet@hans.crm.umontreal.ca
		      
		      */

#include "transpo.h"

void generer_permutation(int *perm);
float solutionner_1bout(int *perm,int look_ahead,int follow_trough);

unsigned long noeud;  /* Number of nodes explored */
long trans,inver,transver;    /* Counts the number of transpositions, inversions and transversion */
float coeff_inver,coeff_trans,coeff_transver;    /* Lenght coefficient for inversions, transpositions and transversions */
float poids_transpo,poids_inversion,poids_transver;   /* Weight for ... */
FILE *fic;            /* File for the output */
int size;
int signature;
int forme;



void usage()
{
  printf("USAGE : \n");
  printf("derange2 -[L(inear), C(ircular)] -[S(igned), U(nsigned)] Input_File Look_ahead Inversion_weight Transposition_weight Transversion_weight Output_file\n");
  exit(1);
}


void main(int argc, char *argv[])
{
  int perm[MAX_LENGTH];
  int temp;
  int j;
  float compte;
  int follow_trough;
  int look_ahead;
  FILE *fic_perm;
  signature=SIGNED;
  forme=CIRCULAR;
        

  if (argc!=9) usage();

  if (*argv[1]!='-') usage();
  ++argv[1];
  switch(*argv[1])
{
 case 'S' : signature=SIGNED;break;
 case 'U' : signature=UNSIGNED;break;
 case 'C' : forme=CIRCULAR;break;
 case 'L' : forme=LINEAR;break;
 default  : usage();
}

  if (*argv[2]!='-') usage();
  ++argv[2];
  switch(*argv[2])
{
 case 'S' : signature=SIGNED;break;
 case 'U' : signature=UNSIGNED;break;
 case 'C' : forme=CIRCULAR;break;
 case 'L' : forme=LINEAR;break;
 default  : usage();
}


  fic_perm=fopen(argv[3],"r");look_ahead=atoi(argv[4]);
  poids_inversion=atof(argv[5]);
  poids_transpo=atof(argv[6]);
  poids_transver=atof(argv[7]);
  fic=fopen(argv[8],"a");
  compte=trans=inver=transver=0;
  temp=0;	
  while (temp!=EOF)
{

  size=0;	
  while ((temp=fscanf(fic_perm,"%d ",&perm[++size]))!=EOF && perm[size]!=0);
  size--;
  if (size!=0)
{	
  perm[0]=0;perm[size+1]=size+1;
  if (verifier_integrite(perm)) {printf("Incomplete permutation!\n");exit(0);}	
  fprintf(fic,"\n\nPermutation : ");
  for (j=1;j<=size;j++) fprintf(fic,"%d ",perm[j]);
  fprintf(fic,"\nLook ahead : %d\n",look_ahead);
  fprintf(fic,"Inversion weight : %f\n",poids_inversion);
  fprintf(fic,"Transposition weight : %f\n",poids_transpo);
  fprintf(fic,"Transversion weight : %f\n",poids_transver);
  fprintf(fic,"Inversion lenght coefficient : %f\n",coeff_inver);
  fprintf(fic,"Transposition lenght coefficient : %f\n",coeff_trans);
  fprintf(fic,"Transversion lenght coefficient : %f\n",coeff_transver);

  compte=solutionner_1bout(perm,look_ahead,1);
  fprintf(fic,"\n\n");
}
}

}
