/* Program solving a given permutation by calling the "meilleur" procedure
   iteratively until the identity permutation is found.
   
   By Mathieu Blanchette, directed by David Sankoff.
   Centre de Recherches Mathematiques, Universite de Montreal
  
*/


#include "transpo.h"

extern unsigned long noeud;
extern long trans,inver,transver;
extern float poids_transpo,poids_inversion,poids_transver;
extern FILE *fic;
extern int size,forme;
float best;
L mouv[20];
float distance(int *perm1,int *perm2,int look_ahead,int follow_trough);
void meilleur(int *perm,int profondeur,float cout,int *t);
void inverser_signe(int *perm,int *inverse);
float effectuer(int *perm, int follow);

float solutionner_1bout(int *perm,int look_ahead,int follow_trough)
{
	float compte;
	int j,trouve;
	int inve[MAX_LENGTH];
	long t1,i1,tv1;
	t1=trans;
	i1=inver;
	tv1=transver;
	compte=0;
	if (forme==CIRCULAR && perm[1]!=1) replacer(perm);
	while (!IsIdentity(perm))
	{
		if (forme==CIRCULAR && perm[1]!=1) replacer(perm);
		best=30000;
		for (j=0;j<=11;j++) {mouv[j].gauche=0;mouv[j].droite=0;mouv[j].nouveau=0;mouv[j].gain=0;mouv[j].type=0;}					
		meilleur(perm,look_ahead,compte,&trouve);	
		compte+=effectuer(perm,follow_trough);
	}
	fprintf(fic,"Total cost: %f\n",compte);
	fprintf(fic,"%5.0f moves : %5.0f inversions, %5.0f transpositions and %5.0f transversions",(double)(inver+trans+transver-i1-t1-tv1),(double)(inver-i1),(double)(trans-t1),(double)(transver-tv1));
	return (double)(inver+trans+transver-i1-t1-tv1);
}

