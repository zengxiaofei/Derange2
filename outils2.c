
/* Some useful procedures for Derange2 */
/* By Mathieu Blanchette, with some codes from Gopal Sundaram and John Kececioglu*/

#include "transpo.h"
extern unsigned long noeud;
extern float best;
extern L mouv[20];
extern long trans,inver,transver;
extern float poids_transpo,poids_inversion,poids_transver,coeff_trans,coeff_inver,coeff_transver;
extern FILE *fic;
extern int size;
extern int signature;
extern int forme;
void generer_permutation(int *perm);
void	Block_Move(int *seq,int i,int j,int k,int code);
void Reverse(register int *Perm, int i, int j);

int verifier_integrite(int *perm)
{
        /*Verify that the permutation is complete*/
        char a[MAX_LENGTH];
        int i;
        for (i=0;i<=size+1;i++) a[i]=0;
        for (i=0;i<=size+1;i++) a[abs(perm[i])]=1;
        for (i=1;i<=size;i++) if (a[i]==0) return 1;
        return 0;
}

short IsIdentity(int *perm)
{
	register i,t;
	t=1;
	for (i=1;i<=size;i++) t=t && perm[i]==i;
	return t;
}
void inverser(int *perm,int *inverse)
{
	int i;
	for (i=0; i<=size+1;i++)
		{
			inverse[abs(perm[i])]=i;
		}
}
void inverser_signe(int *perm,int *inverse)
{
	int i;
	for (i=0; i<=size+1;i++)
		{
			inverse[abs(perm[i])]=signe(perm[i])*i;
		}
}


void replacer(int *perm)
{
int b[MAX_LENGTH];
int r[MAX_LENGTH];
int i,j,k;
i=1;
if (perm[1]!=1)
{
while (abs(perm[i])!=1) {++i;}
k=perm[i];
forme=LINEAR;
if (k==-1) {Reverse(perm,1,size);
Block_Move(perm,size-i+1,size,0,1);}
else Block_Move(perm,i,size,0,1);
forme=CIRCULAR;
}

}


/*
        Code from John Kececioglu, modified by Mathieu Blanchette.
	Move the block i...j to position AFTER k in seq[seq_length]
*/

void	Block_Move(int *seq,int i,int j,int k,int code)

{
	int	l,m;
	int	block[MAX_LENGTH];

	if ((k > i) && (k < j))
	{
		fprintf(stderr, "Illegal Parameters for Block_Move %d,%d,%d\n",i,j,k);
		exit(1);
	}

	
	if (code==2)
	{
	if (signature==SIGNED)
	for (l=i; l<= j; ++l) block[l] = -seq[j-l+i];
	else
	for (l=i; l<= j; l++) block[l] = seq[j-l+i];
	}
	else
	{for (l=i; l<= j; l++)
		block[l] = seq[l];
		}
	if (k > j){	/* ....i...j.....k */

		for (l=i; l< i+ (k-j); ++l)
			seq[l] = seq[l+(j-i)+1];

		m = i;
		for (l=i+(k-j); l<= k; ++l){
			seq[l] = block[m];
			++m;
		}
	}
	else{		/* ....k......i.....j */

		for (l=j; l>=(k+2+(j-i)); --l)
			seq[l] = seq[l - (j-i+1)];

		m = i;
		for (l=k+1; l<= (k+1+(j-i)); ++l){
			seq[l] = block[m];
			m++;
		}
	}
if (forme==CIRCULAR) replacer(seq);
	}
/*    Code from John Kececioglu, modified by Mathieu Blanchette.
 * Reverse -- Reverse `Perm[i] Perm[i+1] ... Perm[j]'
 *
 */
void Reverse(register int *Perm, int i, int j)

{
	 register int p, q, x,k;
	 k=((signature==SIGNED) ? (-1):(1));
	
	 for (p = i, q = j; p <= q; p++, q--)
	 {
			x = Perm[p];
			Perm[p] = k*Perm[q];
			Perm[q] = k*x;
	 }
if (forme==CIRCULAR) replacer(Perm);
}



/*    Code from John Kececioglu, modified by Mathieu Blanchette.
	Computes the number of break-points in the array
*/

int	Compute_Break_Points(int *seq,int *b)

{
	int	i,k;
	int	no_break_points=0;
	for (i=1; i <= size+1; i++)
	{
	k=((signature==SIGNED) ? ( (seq[i-1] - seq[i])!=-1) : (abs(seq[i-1] - seq[i])!=1));
	
		if (k)
			{++no_break_points;
			 b[no_break_points]=i-1;
			}
			}
	return(no_break_points);
}


float effectuer(int *perm, int follow)
{
	/* Computes the (follow) first moves stored in the array mouv and writes the output in the file fic.
           Returns the cost of the moves computed */

	int a,b,c,d,e,f,i,j,l;
	i=1;
	while (mouv[i].gauche==0 && i<=10) ++i;
	a=b=c=d=e=f=0;
	for (j=1;j<=follow && i<=10 && !IsIdentity(perm);i++,j++)
	{

		if (mouv[i].type==0)
		{
			for (l=1;l<=mouv[i].gauche-1;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," [ ");
			for (l=mouv[i].gauche;l<=mouv[i].droite;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," ] ");
			for (l=mouv[i].droite+1;l<=size;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic,"\n");
		}

		if (mouv[i].type==1)
		{
			for (l=1;l<=mouv[i].gauche-1;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," ( ");
			for (l=mouv[i].gauche;l<=mouv[i].droite;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," ) ");
			for (l=mouv[i].droite+1;l<=mouv[i].nouveau;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," * ");
			for (l=mouv[i].nouveau+1;l<=size;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic,"\n");
		}

		if (mouv[i].type==2 && mouv[i].nouveau<mouv[i].gauche)
		{
			for (l=1;l<=mouv[i].nouveau;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," * ");
			for (l=mouv[i].nouveau+1;l<=mouv[i].gauche-1;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," < ");
			for (l=mouv[i].gauche;l<=mouv[i].droite;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," > ");
			for (l=mouv[i].droite+1;l<=size;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic,"\n");
		}

		if (mouv[i].type==2 && mouv[i].nouveau>mouv[i].droite)
		{
			for (l=1;l<=mouv[i].gauche-1;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," < ");
			for (l=mouv[i].gauche;l<=mouv[i].droite;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," > ");
			for (l=mouv[i].droite+1;l<=mouv[i].nouveau;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic," * ");
			for (l=mouv[i].nouveau+1;l<=size;l++) fprintf(fic,"%d ",perm[l]);
			fprintf(fic,"\n");
		}

		if (mouv[i].type==1) {a++;trans++;Block_Move(perm,mouv[i].gauche,mouv[i].droite,mouv[i].nouveau,1);d+=mini(mouv[i].droite-mouv[i].gauche+1,mouv[i].nouveau-mouv[i].droite);}
		if (mouv[i].type==0) {b++;inver++;Reverse(perm,mouv[i].gauche,mouv[i].droite);e+=mouv[i].droite-mouv[i].gauche+1;}
		if (mouv[i].type==2) {c++;transver++;Block_Move(perm,mouv[i].gauche,mouv[i].droite,mouv[i].nouveau,2);f+=mouv[i].droite-mouv[i].gauche+1;}
	
	}
	return a*poids_transpo+b*poids_inversion+c*poids_transver+d*coeff_trans+e*coeff_inver+f*coeff_transver;
}

L* push(L* pile,int gauche, int droite, int nouveau, int type,int gain)
{
	/* Adds a move to the current stack. Gauche and droite are the left and right ends of the moved block,
	   nouveau is the new place to insert the moved block (in the case of inversions, nouveau=0.
           Type=0 for inversions, 1 for transpositions and 2 for transverions 
	   Gain is the number of breakpoints removed */

	L *temp;
	temp=NULL;
	if (!((forme==CIRCULAR && gauche==1 && nouveau==size) || (forme==CIRCULAR && type==2 && nouveau==0 && droite==size)))
{
	while (temp==NULL) {temp =(L*) malloc(sizeof(L));if (temp==NULL) printf("Out of memory, please use a smaller look_ahead\n");exit;}
	temp->prochain=pile;
	temp->type=type;
	temp->gauche=gauche;
	temp->droite=droite;
	temp->nouveau=nouveau;
	temp->gain=gain;
	noeud++;
	return temp;
}
else return pile;
}

