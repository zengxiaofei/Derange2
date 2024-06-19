/* Finds the best sequence of moves to reduce the number of breakpoints of a
   permutation.
   
   By Mathieu Blanchette, directed by David Sankoff.
   Centre de Recherches Mathematiques, Universite de Montreal
   
   e-mail : blanchet@hans.crm.umontreal.ca
*/

#include "transpo.h"

void inverser(int *perm,  int *inverse);
int     Compute_Break_Points(int seq[MAX_LENGTH],int b[MAX_LENGTH]);
L* transposition3(L* pile,int *perm,int *inverse,int o,int *b,int p);
L* transposition2(L* pile,int *perm,int *inverse,int o,int *b,int p);
L* transposition1(L* pile,int *perm,int *inverse,int o,int *b,int p);
L* transversion1(L* pile,int *perm,int *inverse,int o,int *b,int p);
L* transversion2(L* pile,int *perm,int *inverse,int o,int *b,int p);
L* transversion3(L *pile,int *perm,int *inverse,int o,int *b,int p);
L* inversion1(L* pile,int *perm,int *inverse,int o,int *b,int p);
L* inversion2(L* pile,int *perm,int *inverse,int o,int *b,int p);
void    Block_Move(int *seq,int i,int j,int k,int code);
void Reverse(register int *Perm, int i, int j);
short IsIdentity(int *perm);

extern unsigned long noeud;  /* Number of nodes explored */
extern float best;           /* Score of the best solutions found */
extern L mouv[20];           /* array of the best sequence of moves found */
extern long trans,inver,transver;    /* Counts the number of transpositions, inversions and transversion */
extern float poids_transpo,poids_inversion,poids_transver;   /* Weight for ... */
extern FILE *fic;            /* File for the output */
extern int size;
extern int signature;
extern int forme;

/* Macros for procedure meilleur */

#define garder()\
{\
	mouv[10-profondeur+1].gauche=pile->gauche;\
	mouv[10-profondeur+1].droite=pile->droite;\
	mouv[10-profondeur+1].nouveau=pile->nouveau;\
	mouv[10-profondeur+1].type=pile->type;\
	flag=1;\
	*t=1;\
}\

#define passer();\
{\
	piletmp=pile;\
	pile=pile->prochain;\
	free(piletmp);\
}\


void meilleur(int *perm,int profondeur,float cout,int *t)

/* Finds the best sequence of (profondeur) moves. The best score found
   is contained in best and the sequence of moves corresponding to this
   score is stored in the array mouv[]. */


{
	int inverse[MAX_LENGTH];
	int bis[MAX_LENGTH];
	int breakpoints[MAX_LENGTH];   /* Array for the position of the 1st, 2nd, 3rd ... breakpoints */
	int i,flag;
        int res;    /* Number of breakpoints in the permutation */
        int avarice;
                   /* When avarice<=1, all the moves that remove at least a breakpoint are consider.
                      when avarice=2, the moves that remove 1 bp are not considered, unless no better moves have been found.
		      when avarice=3, the moves thatt remove 2 bp or less are not considered, unless ...
                      when avarice=4, the first move found is the only one that is considered.
		  
		      A proper use of avarice can reduce the number of nodes explored without affecting too much the quality of the solution found.
                      For example, with a look ahead (named profondeur) of 4 the following lines might be added:

		      if (profondeur==4) avarice=1;
                      if (profondeur==3) avarice=2;
                      if (profondeur==2) avarice=3;
                      if (profondeur==1) avarice=4;
		  */

	float mi;       /* An upper bound for the score the permutation can get */
	L* pile=NULL;   /* The stack of the moves found that remove x bp */
	L* piletmp;
	int trouve;    

	*t=0;
	trouve=0;
	avarice=0;
	res=Compute_Break_Points(perm,breakpoints);

	if (res-3*profondeur>=0) mi=mini(mini(poids_transpo,poids_transver)*profondeur+res-3*profondeur,poids_inversion*profondeur+res-2*profondeur);
	else mi=mini(mini(poids_transver,poids_transpo)*(ceil(res/3)),poids_inversion*(ceil(res/2)));

	if (cout+mi<best)
	{
		if (profondeur<=0)
		{
			best=cout+res;
			*t=1; 
			for (i=1;i<=10;i++) 
			{
				mouv[i].gauche=mouv[i].droite=mouv[i].nouveau=mouv[i].gain=mouv[i].type=0;
			}
			
		}
		else
		{
			if (IsIdentity(perm))
			{
				if (best>cout+res) 
				{
					best=cout+res;
					*t=1; 
					for (i=1;i<=10;i++) 
					{
						mouv[i].gauche=mouv[i].droite=mouv[i].nouveau=mouv[i].gain=mouv[i].type=0;
					}
				}
			}
			else
			{
				inverser(perm,inverse);
				flag=0;
				if ((res-3)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-3-3*(profondeur-1),poids_inversion*(profondeur-1)+res-3-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-3)/3)),poids_inversion*(ceil((res-3)/2)));
				mi+=poids_transpo;
				if (cout+mi<best)
				{
					
					/* Search for transpositions that removes 3 bp */
					pile=NULL;
					pile=transposition3(pile,perm,inverse,res,breakpoints,(avarice>3) ? 1:0);			
					while (pile!=NULL)
					{
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Block_Move(bis,pile->gauche,pile->droite,pile->nouveau,1);
					
						meilleur(bis,profondeur-1,cout+poids_transpo,&trouve);
						if (trouve) garder();
						passer();
					}
				}
				if (flag==1 && avarice>3) goto sortie;

				if ((res-3)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-3-3*(profondeur-1),poids_inversion*(profondeur-1)+res-3-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-3)/3)),poids_inversion*(ceil((res-3)/2)));
				mi+=poids_transver;
				if (cout+mi<best)
				{
					/* Search for transversions that removes 3 bp */
					pile=NULL;
					pile=transversion3(pile,perm,inverse,res,breakpoints,(avarice>3) ? 1:0);
					while (pile!=NULL)
					{
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Block_Move(bis,pile->gauche,pile->droite,pile->nouveau,2);
						meilleur(bis,profondeur-1,cout+poids_transver,&trouve);
						if (trouve) garder();
		 				passer();
					}
				}
				if (flag==1 && avarice>=3) goto sortie;
				flag=0;

				if ((res-2)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-2-3*(profondeur-1),poids_inversion*(profondeur-1)+res-2-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-2)/3)),poids_inversion*(ceil((res-2)/2)));
				mi=mi+poids_inversion;
				if (cout+mi<best)
				{
					/* Search for inversions that removes 2 bp */
					pile=NULL;
					pile=inversion2(pile,perm,inverse,res,breakpoints,(avarice>2) ? 1:0);
					while (pile!=NULL)
					{
						
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Reverse(bis,pile->gauche,pile->droite);
						meilleur(bis,profondeur-1,cout+poids_inversion,&trouve);
						if (trouve) garder();
						passer();
					}
				}
				if (flag==1 && avarice>2) goto sortie;

				if ((res-2)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-2-3*(profondeur-1),poids_inversion*(profondeur-1)+res-2-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-2)/3)),poids_inversion*(ceil((res-2)/2)));
				mi=mi+poids_transpo;
				if (cout+mi<best)
				{
					/* Search for transpositions that removes 2  bp*/
					pile=NULL;
					pile=transposition2(pile,perm,inverse,res,breakpoints,(avarice>2) ? 1:0);
					while (pile!=NULL)
					{
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Block_Move(bis,pile->gauche,pile->droite,pile->nouveau,1);
						meilleur(bis,profondeur-1,cout+poids_transpo,&trouve);
						if (trouve) garder();
						passer();
					}
				}
				if (flag==1 && avarice>2) goto sortie;

				if ((res-2)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-2-3*(profondeur-1),poids_inversion*(profondeur-1)+res-2-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-2)/3)),poids_inversion*(ceil((res-2)/2)));
				mi=mi+poids_transver;

				if (cout+mi<best)
				{
					/* Search for transversions that removes 2 bp */
					pile=NULL;
					pile=transversion2(pile,perm,inverse,res,breakpoints,(avarice>2) ? 1:0);
					while (pile!=NULL)
					{
						
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Block_Move(bis,pile->gauche,pile->droite,pile->nouveau,2);
						meilleur(bis,profondeur-1,cout+poids_transver,&trouve);
						if (trouve) garder();
						passer();
					}
				}
				if (flag==1 && avarice>=2) goto sortie;
				flag=0;

				if ((res-1)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-1-3*(profondeur-1),poids_inversion*(profondeur-1)+res-1-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-1)/3)),poids_inversion*(ceil((res-1)/2)));
				mi=mi+poids_inversion;

				if (cout+mi<best)
				{
					/* Search for inversions that removes 1 bp */
					pile=NULL;
					pile=inversion1(pile,perm,inverse,res,breakpoints,(avarice>1) ? 1:0);
					while (pile!=NULL)
					{
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Reverse(bis,pile->gauche,pile->droite);
						meilleur(bis,profondeur-1,cout+poids_inversion,&trouve);
						if (trouve) garder();
						passer();
					}
				}
				if (flag==1 && avarice>1) goto sortie;

				if ((res-1)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-1-3*(profondeur-1),poids_inversion*(profondeur-1)+res-1-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-1)/3)),poids_inversion*(ceil((res-1)/2)));
				mi=mi+poids_transpo;
				if (cout+mi<best)
				{
					/* Search for transpositions that removes 1 bp */
					pile=NULL;
					pile=transposition1(pile,perm,inverse,res,breakpoints,(avarice>1) ? 1:0);
					while (pile!=NULL)
					{
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Block_Move(bis,pile->gauche,pile->droite,pile->nouveau,1);
						meilleur(bis,profondeur-1,cout+poids_transpo,&trouve);
						if (trouve) garder();
						passer();
					}
				}
				if (flag==1 && avarice>1) goto sortie;

				if ((res-1)-3*(profondeur-1)>=0) mi=mini(mini(poids_transver,poids_transpo)*(profondeur-1)+res-1-3*(profondeur-1),poids_inversion*(profondeur-1)+res-1-2*(profondeur-1));
				else mi=mini(mini(poids_transver,poids_transpo)*(ceil((res-1)/3)),poids_inversion*(ceil((res-1)/2)));
				mi=mi+poids_transver;
				if (cout+mi<best)
				{
					/* Search for transversions that removes 1 bp */
					pile=NULL;
					pile=transversion1(pile,perm,inverse,res,breakpoints,(avarice>1) ? 1:0);
					while (pile!=NULL)
					{
						for (i=0;i<=size+1;i++) bis[i]=perm[i];
						Block_Move(bis,pile->gauche,pile->droite,pile->nouveau,2);
						meilleur(bis,profondeur-1,cout+poids_transver,&trouve);
						if (trouve) garder();
						passer();
					}
				}
			}
			sortie:;
		}
	}
}
