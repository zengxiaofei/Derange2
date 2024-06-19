/* Programme utilitaire pour le tri de permutation par inversion, transposition et transversion

   Trouve les mouvements succeptibles d'enlever 1,2,3 cassures
 Par Mathieu Blanchette, sous la direction de David Sankoff.
 Centre de Recherches Mathematiques, Universite de Montreal.
 Dernieres modifications : 14/06/95

*/

#include "transpo.h"

L* push(L* pile,int gauche, int droite, int nouveau, int type,int gain);
extern int size;
extern int forme;
extern int signature;

short signe1(int a)
{
if (a<0) return -1;
if (a>0) return 1;
return 0;
}

short adjacent(int *perm,int point, int code)

/* Code 0 : adj gauche et droite
			 -1 : adj gauche
				1 : adj droite
				2 : adj gauche ou droite*/


{

if (signature==UNSIGNED)
{
        if (forme==CIRCULAR && code==-1 && point==1) return abs(perm[1]-perm[size]);
	if (forme==CIRCULAR && code==1 && point==size) return abs(perm[1]-perm[size]);
	
if (code==-1) return abs(perm[point]-perm[point-1])==1;
	else
	if (code==1) return abs(perm[point]-perm[point+1])==1;
	else
	if (code==0) return abs(perm[point]-perm[point+1])==1 && abs(perm[point]-perm[point-1])==1;
	else
	if (code==2) return abs(perm[point]-perm[point+1])==1 || abs(perm[point]-perm[point-1])==1;
	return 0;
}
if (signature==SIGNED)
{  
	if (forme==CIRCULAR && code==-1 && point==1) return perm[1]-perm[size]==1;
	if (forme==CIRCULAR && code==1 && point==size) return perm[1]-perm[size]==1;
	
	if (code==-1) return perm[point]-perm[point-1]==1;
	else
	if (code==1) return perm[point+1]-perm[point]==1;
	return 0;
}




}

L* inversion2(L* pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	/*
		 Trouve les inversions qui enlevent deux cassures. Retourne la pile des
		 mouvements possibles
	*/

	 register int i,k, j;

if (signature==UNSIGNED)
{
	 for (k=1;k<=points;k++)
	 {
	 i=breakpoints[k];
		 j=inverse[perm[i]+1];
		 if (j>i && j<=size && abs(perm[i+1]-perm[j+1])==1
				 && !adjacent(perm,j,1))
		 {
		 pile=push(pile,i+1,j,0,0,2);if (p==1) return pile;

		 }
		 if (i!=0)
		 {
			j=inverse[perm[i]-1];
		 if (j>i && j<=size && abs(perm[i+1]-perm[j+1])==1
				 && !adjacent(perm,j,1))
		 {
		 pile=push(pile,i+1,j,0,0,2);if (p==1) return pile;

		 }
		 }

	 }
	 return pile;
}

if (signature==SIGNED)
{ 
for (k=1;k<=points;k++)
	 {
	 i=breakpoints[k];
		 j=inverse[abs(perm[i]+1)];
		 if (signe(perm[i])!=signe(perm[j]) && i<j && j<=size && (perm[j+1]+perm[i+1])==1
				 && !adjacent(perm,j,1))
		 {
			pile=push(pile,i+1,j,0,0,2);if (p==1) return pile;
		 }
	 }
	 return pile;
}
}

L* inversion1(L* pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	/*
		 Trouve les inversions qui enlevent deux cassures. Retourne la pile des
		 mouvements possibles
	*/

	 register int i,k, j;

if (signature==UNSIGNED)
{
	 for (k=1;k<=points;k++)
	 {
	 i=breakpoints[k];
		 j=inverse[perm[i]+1];
		 if (j>i && j<=size && !xor(abs(perm[i+1]-perm[j+1])==1,adjacent(perm,j,1)))

		 {
		 pile=push(pile,i+1,j,0,0,2);if (p==1) return pile;

		 }
		 if (i!=0)
		 {
			j=inverse[perm[i]-1];
		 if (j>i && j<=size && !xor(abs(perm[i+1]-perm[j+1])==1,adjacent(perm,j,1)))
		 {
		 pile=push(pile,i+1,j,0,0,2);if (p==1) return pile;

		 }
		 }
		 i=breakpoints[k]+1;
		 j=inverse[perm[i]+1];
		 if (j<i && i<=size && !xor(abs(perm[i-1]-perm[j-1])==1,adjacent(perm,j,-1)))

		 {
		 pile=push(pile,j,i-1,0,0,2);if (p==1) return pile;

		 }
		 if (i!=0 && perm[i]-1>0)
		 {
			j=inverse[perm[i]-1];
		 if (j<i && i<=size && !xor(abs(perm[i-1]-perm[j-1])==1,adjacent(perm,j,-1)))
		 {

		 pile=push(pile,j,i-1,0,0,2);if (p==1) return pile;

		 }
		 }

	 }
	 return pile;
}

if (signature==SIGNED)
{
 for (k=1;k<=points;k++)
	 {
	 i=breakpoints[k];
		 j=inverse[abs(perm[i]+1)];
		 if (signe(perm[i])!=signe(perm[j]) && j>i && j<=size && !xor(perm[j+1]+perm[i+1]==1,adjacent(perm,j,1)))
		 {
		 pile=push(pile,i+1,j,0,0,2);if (p==1) return pile;
		 }

		 i=breakpoints[k]+1;
		 if (perm[i]-1>0)
		 {
		 j=inverse[abs(perm[i]-1)];
		 if (signe(perm[i])!=signe(perm[j]) && j<i && i<=size && !xor(perm[i-1]+perm[j-1]==-1,adjacent(perm,j,-1)))
		 {

		 pile=push(pile,j,i-1,0,0,2);if (p==1) return pile;

		 }
		 }
		 }
	 return pile;
}

}


L* transposition3(L *pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	/*
		 Trouve les transversion qui enlevent trois cassures. Retourne la pile des
		 mouvements possibles
	*/
	register int m,it,nga,ndr;

if (signature==UNSIGNED)
{
	for (m=1; m<=points;++m)
	{
		it=breakpoints[m];

			if (it>0)
			{
			nga=inverse[perm[it]-1];
			ndr=inverse[perm[it+1]-1];

			if (ndr<it && nga>0 && ndr<=size && nga<=ndr && abs(perm[nga-1]-perm[ndr+1])==1 && signe1(nga-it)==signe1(ndr-it) && !adjacent(perm,ndr,1) && !adjacent(perm,nga,-1))
			{

			pile=push(pile,nga,ndr,it,1,3);if (p==1) return pile;
			}
			}
			nga=inverse[perm[it]+1];
			ndr=inverse[perm[it+1]-1];
				if (ndr<it && nga>0 && ndr<=size && nga<=ndr && abs(perm[nga-1]-perm[ndr+1])==1 && signe1(nga-it)==signe1(ndr-it) && !adjacent(perm,ndr,1) && !adjacent(perm,nga,-1))
			{

			pile=push(pile,nga,ndr,it,1,3);if (p==1) return pile;
			}


			if (it<size)
			{
			if (it>0)
			{
			nga=inverse[perm[it]-1];
			ndr=inverse[perm[it+1]+1];

				if (ndr<it && nga>0 && ndr<=size && nga<=ndr && abs(perm[nga-1]-perm[ndr+1])==1 && signe1(nga-it)==signe1(ndr-it) && !adjacent(perm,ndr,1) && !adjacent(perm,nga,-1))
			{

			pile=push(pile,nga,ndr,it,1,3);if (p==1) return pile;
			}
			}

						nga=inverse[perm[it]+1];
			ndr=inverse[perm[it+1]+1];

				if (ndr<it && nga >0 && ndr<=size && nga<=ndr && abs(perm[nga-1]-perm[ndr+1])==1 && signe1(nga-it)==signe1(ndr-it) && !adjacent(perm,ndr,1) && !adjacent(perm,nga,-1))
			{

			pile=push(pile,nga,ndr,it,1,3);if (p==1) return pile;
			}

			}
		}
		return pile;
}

if (signature==SIGNED)
{
for (m=1; m<=points;++m)
	{
		it=breakpoints[m];

			if (it>0)
			{
			nga=inverse[abs(perm[it]+1)];
			ndr=inverse[abs(perm[it+1]-1)];

			if (signe(perm[nga])==signe(perm[it]) && signe(perm[ndr])==signe(perm[it+1]) && ndr<it && nga>0 && ndr<=size && nga<=ndr && perm[ndr+1]-perm[nga-1]==1 && signe(nga-it)==signe(ndr-it) && !adjacent(perm,ndr,1) && !adjacent(perm,nga,-1))
			{

			pile=push(pile,nga,ndr,it,1,3);if (p==1) return pile;
			}
			}

		}
		return pile;
}



}



L* transversion3(L *pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	/*
		 Trouve les transversion qui enlevent trois cassures. Retourne la pile des
		 mouvements possibles
	*/
	register int m,it,nga,ndr;

if (signature==UNSIGNED)
{
	for (m=1; m<=points;++m)
	{
		it=breakpoints[m];

			if (it>0)
			{
			nga=inverse[perm[it]-1];
			ndr=inverse[perm[it+1]-1];

			if (nga<it && ndr>0 && nga<=size && ndr<nga && abs(perm[ndr-1]-perm[nga+1])==1 && signe1(ndr-it)==signe1(nga-it) && !adjacent(perm,nga,1) && !adjacent(perm,ndr,-1))
			{

			pile=push(pile,ndr,nga,it,2,3);if (p==1) return pile;
			}
			}
			nga=inverse[perm[it]+1];
			ndr=inverse[perm[it+1]-1];

			if (nga<it && ndr>0 && nga<=size && ndr<nga && abs(perm[ndr-1]-perm[nga+1])==1 && signe1(ndr-it)==signe1(nga-it) && !adjacent(perm,nga,1) && !adjacent(perm,ndr,-1))
			{

			pile=push(pile,ndr,nga,it,2,3);if (p==1) return pile;
			}
			if (it<size)
			{
			if (it>0)
			{
			nga=inverse[perm[it]-1];
			ndr=inverse[perm[it+1]+1];

			if (nga<it && ndr>0 && nga<=size && ndr<nga && abs(perm[ndr-1]-perm[nga+1])==1 && signe1(ndr-it)==signe1(nga-it) && !adjacent(perm,nga,1) && !adjacent(perm,ndr,-1))
			{

			pile=push(pile,ndr,nga,it,2,3);if (p==1) return pile;
			}
			}
			nga=inverse[perm[it]+1];
			ndr=inverse[perm[it+1]+1];

			if (nga<it && ndr>0 && nga<=size &&  ndr<nga && abs(perm[ndr-1]-perm[nga+1])==1 && signe1(ndr-it)==signe1(nga-it) && !adjacent(perm,nga,1) && !adjacent(perm,ndr,-1))
			{

			pile=push(pile,ndr,nga,it,2,3);if (p==1) return pile;
			}
			}
		}
		return pile;
}

if (signature==SIGNED)
{
	for (m=1; m<=points;++m)
	{
		it=breakpoints[m];

			if (it>0)
			{
			nga=inverse[abs(perm[it]+1)];
			ndr=inverse[abs(perm[it+1]-1)];

			if (signe(perm[nga])!=signe(perm[it]) && signe(perm[ndr])!=signe(perm[it+1]) && nga<it && ndr>0 && nga<=size && nga>=ndr && perm[nga+1]-perm[ndr-1]==1 && signe(nga-it)==signe(ndr-it) && !adjacent(perm,ndr,-1) && !adjacent(perm,nga,1))
			{

			pile=push(pile,ndr,nga,it,2,3);if (p==1) return pile;
			}
			}

		}
		return pile;
}

}






#define verif()   \
{\
if ((ndr<i && 0<nga && nga<=ndr && ndr<size && signe1(nga-i)==signe1(ndr-i))\
	&&\
	((xor(adjacent(perm,nga,-1),adjacent(perm,ndr,1)) && (abs(perm[nga-1]-perm[ndr+1])==1))\
	 ||\
	 (!adjacent(perm,nga,-1) && !adjacent(perm,ndr,1) && abs(perm[nga-1]-perm[ndr+1])!=1)\
	)\
	)\
{pile=push(pile,nga,ndr,i,1,2);if (p==1) return pile;}\
}\



short condition(int *perm,int i,int suiv,int nga)
{
if (signature==UNSIGNED)
{
return (suiv>0 && suiv<size && nga>0 && suiv<=nga && nga<size+1 && (signe1(nga-suiv)==signe1(nga-i)) &&
			 (!adjacent(perm,i,1) && !adjacent(perm,suiv,-1)) &&
						((!adjacent(perm,nga,1) && xor(abs(perm[nga]-perm[i+1])==1,abs(perm[nga+1]-perm[suiv-1])==1)
						 ||
						 adjacent(perm,nga,1) && abs(perm[nga]-perm[i+1])==1 && abs(perm[nga+1]-perm[suiv-1]==1))));
}
if (signature==SIGNED)
{
return (suiv>0 && suiv<size && nga>0 && suiv<nga && nga<size+1 && (signe(nga-suiv)==signe(nga-i)) &&
			 (!adjacent(perm,i,1) && !adjacent(perm,suiv,-1)) &&
						((!adjacent(perm,nga,1) && xor((perm[i+1]-perm[nga])==1,(perm[nga+1]-perm[suiv-1])==1)
						 ||
						 adjacent(perm,nga,1) && (perm[i+1]-perm[nga])==1 && (perm[nga+1]-perm[suiv-1]==1))));
}
}

L* transposition2(L* pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	register m,l,k,i,it,suiv,nga,ndr;

if (signature==UNSIGNED)
{
	/* Cas (-1,-1) ou on cherche un bloc qui entre bien */
	for (k=1; k<=points;k++)
	{
		i=breakpoints[k];
			nga=inverse[perm[i]+1];
			ndr=inverse[perm[i+1]-1];
			verif();
			if (i<size)
			{
				nga=inverse[perm[i]+1];
				ndr=inverse[perm[i+1]+1];
				verif();
			}

						if (i>0)
			{
				nga=inverse[perm[i]-1];
				ndr=inverse[perm[i+1]-1];
				verif();
				if (i<size)
				{
					nga=inverse[perm[i]-1];
						ndr=inverse[perm[i+1]+1];
						verif();
							}
			}

	}
		/* Cas (-2,0) ou on enleve le bloc de trop */
	for (k=1; k<=points;k++)
	{
		it=i=breakpoints[k];

		for (l=0;l<=1;l++)
		{

		if (l==0) m=-1; else m=1;
		if (!(l==0 && it==0))
		{
		suiv=inverse[perm[it]+m];
		if (suiv>=i)
		{
				/*   Cas 6 (2 _ _ 4) 7 1 > 5      */
			nga=inverse[perm[it+1]-1];
			if (condition(perm,it,suiv,nga)) {pile=push(pile,it+1,suiv-1,nga,1,2);if (p==1) return pile;}

				/* Cas 6 (2 _ _ 4) 7 3 > 3    */
			nga=inverse[perm[it+1]+1];


			if (condition(perm,it,suiv,nga)) {pile=push(pile,it+1,suiv-1,nga,1,2);if (p==1) return pile;}

					/*Cas 6 (2 _ _ 4) 7 1 > 3 */
			ndr=inverse[perm[suiv-1]-1];

			if (!adjacent(perm,ndr,-1) && condition(perm,it,suiv,ndr-1)) {pile=push(pile,it+1,suiv-1,ndr-1,1,2);if (p==1) return pile;}

				/*Cas 6 (2 _ _ 4) 7 3 > 5*/
			ndr=inverse[perm[suiv-1]+1];
			if (!adjacent(perm,ndr,-1) && condition(perm,it,suiv,ndr-1)) {pile=push(pile,it+1,suiv-1,ndr-1,1,2);if (p==1) return pile;}

			}
		}
		}
		}


	return pile;
}
if (signature==SIGNED)
{
	/* Cas (-1,-1) ou on cherche un bloc qui entre bien */
	for (k=1; k<=points;k++)
	{
		i=breakpoints[k];
			nga=inverse[abs(perm[i]+1)];
			ndr=inverse[abs(perm[i+1]-1)];
	 if ((perm[nga]-perm[i]==1 && perm[ndr]-perm[i+1]==-1 && ndr<i && 0<nga && nga<=ndr && ndr<size && signe(nga-i)==signe(ndr-i))
	&&
	(xor(adjacent(perm,nga,-1),adjacent(perm,ndr,1)) && (perm[ndr+1]-perm[nga-1])==1
	 ||
	 ((!adjacent(perm,nga,-1) && !adjacent(perm,ndr,1) && (perm[ndr+1]-perm[nga-1])!=1))
	)
	)
{pile=push(pile,nga,ndr,i,1,2);if (p==1) return pile;}
 }
		/* Cas (-2,0) ou on enleve le bloc de trop */
	for (k=1; k<=points;k++)
	{
		it=i=breakpoints[k];

		suiv=inverse[abs(perm[it]+1)];
		if (suiv>=i && signe(perm[it])==signe(perm[suiv]))
		{

			nga=inverse[abs(perm[it+1]-1)];
			if (signe(perm[nga])==signe(perm[it+1]) && condition(perm,it,suiv,nga)) {pile=push(pile,it+1,suiv-1,nga,1,2);if (p==1) return pile;}



			ndr=inverse[abs(perm[suiv-1]+1)];
			if (signe(perm[ndr])==signe(perm[suiv-1]) &&condition(perm,it,suiv,ndr-1)) {pile=push(pile,it+1,suiv-1,ndr-1,1,2);if (p==1) return pile;}



	 }
	 }
	return pile;
}


}

#define verifrev()   \
{\
if ((0<ndr && nga>ndr && nga<size && signe1(nga-i)==signe1(ndr-i))\
&&\
	((xor(adjacent(perm,nga,1),adjacent(perm,ndr,-1)) && (abs(perm[nga+1]-perm[ndr-1])==1))\
	 ||\
	 (!adjacent(perm,nga,1) && !adjacent(perm,ndr,-1) && abs(perm[nga+1]-perm[ndr-1])!=1)\
	)\
	)\
{pile=push(pile,ndr,nga,i,2,2);if (p==1) return pile;}\
}\



short conditionrev(int *perm,int i,int suiv,int nga)
{
if (signature==UNSIGNED)
{
return (suiv>0 && nga>0 && nga<size+1 && (signe1(nga-suiv)==signe1(nga-i)) &&
			 (!adjacent(perm,i,1) && !adjacent(perm,suiv,-1)) &&
						((!adjacent(perm,nga,-1) && xor(abs(perm[nga]-perm[i+1])==1,abs(perm[nga-1]-perm[suiv-1])==1)
						 ||
						 adjacent(perm,nga,-1) && abs(perm[nga]-perm[i+1])==1 && abs(perm[nga-1]-perm[suiv-1]==1))));
}
if (signature==SIGNED)
{
return (i>0 && suiv<size && nga>0 && suiv<size+1 && (signe(nga-suiv)==signe(nga-i)) &&
			 (!adjacent(perm,i,1) && !adjacent(perm,suiv,-1)) &&
						((!adjacent(perm,nga,1) && xor((perm[suiv-1]+perm[nga])==-1,(perm[nga+1]+perm[i+1])==1)
						 ||
						 adjacent(perm,nga,1) && (perm[suiv-1]+perm[nga])==1 && (perm[nga+1]+perm[i+1]==1))));
}
}



/* Attention, lors des permuitations signe1es, il faut permettre les mouv
 du type 3 3 6 car il sont differents */

L* transversion2(L* pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	register m,l,k,i,it,suiv,nga,ndr;
if (signature==UNSIGNED)
{
	/* Cas (-1,-1) ou on cherche un bloc qui entre bien */
	for (k=1; k<=points;k++)
	{
		i=breakpoints[k];
			nga=inverse[perm[i]+1];
			ndr=inverse[perm[i+1]-1];
			verifrev();
			if (i<size)
			{
				nga=inverse[perm[i]+1];
				ndr=inverse[perm[i+1]+1];
				verifrev();
			}

						if (i>0)
			{
				nga=inverse[perm[i]-1];
				ndr=inverse[perm[i+1]-1];
				verifrev();
				if (i<size)
				{
					nga=inverse[perm[i]-1];
						ndr=inverse[perm[i+1]+1];
						verifrev();
							}
			}

	}
		/* Cas (-2,0) ou on enleve le bloc de trop*/
	for (k=1; k<=points;k++)
	{
		it=i=breakpoints[k];
	
		for (l=0;l<=1;l++)
		{
		if (l==0) m=-1; else m=1;
		if (!(l==0 && it==0))
		{
		suiv=inverse[perm[it]+m];
		if (suiv>=i)
		{

			nga=inverse[perm[it+1]-1];
			if (conditionrev(perm,it,suiv,nga)) {pile=push(pile,it+1,suiv-1,nga-1,2,2);if (p==1) return pile;}


			nga=inverse[perm[it+1]+1];

			if (conditionrev(perm,it,suiv,nga)) {pile=push(pile,it+1,suiv-1,nga-1,2,2);if (p==1) return pile;}


			ndr=inverse[perm[suiv-1]-1];

			if (!adjacent(perm,ndr,1) && conditionrev(perm,it,suiv,ndr+1)) {pile=push(pile,it+1,suiv-1,ndr,2,2);if (p==1) return pile;}


			ndr=inverse[perm[suiv-1]+1];
			if (!adjacent(perm,ndr,1) && conditionrev(perm,it,suiv,ndr+1)) {pile=push(pile,it+1,suiv-1,ndr,2,2);if (p==1) return pile;}

			}
		}
		}
		}

	return pile;
}

if (signature==SIGNED)
{
	/* Cas (-1,-1) ou on cherche un bloc qui entre bien*/
	for (k=1; k<=points;k++)
	{
		i=breakpoints[k];
			nga=inverse[abs(perm[i]+1)];
			ndr=inverse[abs(perm[i+1]-1)];
	 if ((perm[nga]+perm[i]==-1 && perm[ndr]+perm[i+1]==1 && 0<ndr && nga>=ndr && nga<size && signe(nga-i)==signe(ndr-i) && nga!=i && ndr!=i)
	&&
	(xor(adjacent(perm,ndr,-1),adjacent(perm,nga,1)) && (perm[ndr-1]-perm[nga+1])==-1
	 ||
	 ((!adjacent(perm,ndr,-1) && !adjacent(perm,nga,1) && (perm[ndr-1]-perm[nga+1])!=-1))
	)
	)
{pile=push(pile,ndr,nga,i,2,2);if (p==1) return pile;}
 }
		/* Cas (-2,0) ou on enleve le bloc de trop */
	for (k=1; k<=points;k++)
	{
		it=i=breakpoints[k];

		suiv=inverse[abs(perm[it]+1)];
		if (suiv>0 && suiv>=i && signe(perm[it])==signe(perm[suiv]))
		{

			nga=inverse[abs(perm[suiv-1]+1)];
			if (nga<=size && signe(perm[nga])==-signe(perm[suiv-1]) && conditionrev(perm,it,suiv,nga)) {pile=push(pile,it+1,suiv-1,nga,2,2);if (p==1) return pile;}


			if (it<size)
			{
			ndr=inverse[abs(perm[it+1]-1)];
			if (ndr<=size+1 && signe(perm[ndr])==-signe(perm[it+1]) &&conditionrev(perm,it,suiv,ndr-1)) {pile=push(pile,it+1,suiv-1,ndr-1,2,2);if (p==1) return pile;}
			}


	 }
	 }
	return pile;
}
}



#define verif1()\
{\
if (signature==UNSIGNED)\
{\
if (ndr<i && 0<nga && nga<=ndr && ndr<=size && signe1(nga-i)==signe1(ndr-i))\
{\
if (adjacent(perm,nga,-1) || adjacent(perm,ndr,1)) \
 {\
 if (adjacent(perm,nga,-1) && adjacent(perm,ndr,1)) \
 {\
	if (abs(perm[nga-1]-perm[ndr+1]==1)) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;} \
 }\
 else \
 if (abs(perm[nga-1]-perm[ndr+1])!=1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;} \
 }\
}\
}\
if (signature==SIGNED)\
{\
if (signe(perm[nga])==signe(perm[i]) && signe(perm[ndr])==signe(perm[i+1]) && ndr<i && 0<nga && nga<=ndr && ndr<=size && signe(nga-i)==signe(ndr-i))\
{\
if (adjacent(perm,nga,-1) || adjacent(perm,ndr,1)) \
 {\
 if (adjacent(perm,nga,-1) && adjacent(perm,ndr,1)) \
 {\
	if ((perm[nga-1]-perm[ndr+1]==-1)) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;} \
 }\
 else \
 if ((perm[nga-1]-perm[ndr+1])!=-1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;} \
 }\
}\
}\
}\

L* transposition1(L* pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	register i,j,k,l,nga,ndr,it;
	/* Cas (-1,0) */
if (signature==UNSIGNED)
{
	for (k=1;k<=points;k++)
	{
	i=breakpoints[k];

			nga=inverse[perm[i]+1];
			ndr=inverse[perm[i+1]-1];
			verif1();
			if (i<size)
			{
				nga=inverse[perm[i]+1];
				ndr=inverse[perm[i+1]+1];
				verif1();
				nga=inverse[perm[i]-1];
						ndr=inverse[perm[i+1]+1];
						verif1();
			}
			nga=inverse[perm[i]-1];
			ndr=inverse[perm[i+1]-1];
			verif1()
	}

	/* Cas (0,-1) le bloc enleve enleve 1 bp et le bloc ajoute cree 0bp */
	for (i=0;i<=size;i++)
	{

		if (adjacent(perm,i,1) && i!=0)
		{
			nga=inverse[perm[i]+perm[i]-perm[i+1]];
			ndr=inverse[perm[i+1]+perm[i+1]-perm[i]];
			if (ndr<i && nga>=1 && ndr<=size && nga<=ndr && signe1(nga-i)==signe1(ndr-i))
			{
				if (!adjacent(perm,nga,-1) && !adjacent(perm,ndr,1) && abs(perm[nga-1]-perm[ndr+1])!=1)
					{pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
				if (xor(adjacent(perm,nga,-1),adjacent(perm,ndr,1)) && abs(perm[nga-1]-perm[ndr+1])==1)
					{pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
			}
		}
		else
		{
			for (j=0;j<=1;j++)
			{
				k=0;
				if (j==0 && i!=0) k=-1;
				if (j==1 && perm[i]!=size) k=1;
				if (k!=0)
				{
					nga=inverse[perm[i]+k];
					if (nga>=1 && nga<i)
					{
						for (ndr=nga;ndr<i;ndr++)
						{
							if (abs(perm[ndr]-perm[i+1])!=1 && (!adjacent(perm,nga,-1) || !adjacent(perm,ndr,1)))
							if (!adjacent(perm,nga,-1) && !adjacent(perm,ndr,1))
							{
								if (abs(perm[nga-1]-perm[ndr+1])!=1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
							}
							else
							if (abs(perm[nga-1]-perm[ndr+1])==1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
						}
					}


					ndr=inverse[perm[i+1]+k];
					if (ndr<i && ndr>=1)
					{
						for (nga=1;nga<=ndr;nga++)
						{
							if (abs(perm[nga]-perm[i])!=1 && (!adjacent(perm,nga,-1) || !adjacent(perm,ndr,1)))
							if (!adjacent(perm,nga,-1) && !adjacent(perm,ndr,1))
							{
								if (abs(perm[nga-1]-perm[ndr+1])!=1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
							}
							else
							if (abs(perm[nga-1]-perm[ndr+1])==1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
						}
					}

				}

			}

			/*Cas (1,-2)*/ 
			if (i>0)
			{
				nga=i;
				ndr=inverse[perm[i-1]+k]-1;
				if (nga<=ndr && ndr<=size && !adjacent(perm,nga,-1) && !adjacent(perm,ndr,1))
				{
					for (l=ndr+1;l<=size;l++)
					{
						if (adjacent(perm,l,1) && xor(abs(perm[nga]-perm[l])==1, abs(perm[ndr]-perm[l+1])==1))
							{pile=push(pile,nga,ndr,l,1,1);if (p==1) return pile;}
						if (!adjacent(perm,l,1) && abs(perm[nga]-perm[l])!=1 && abs(perm[ndr]-perm[l+1])!=1)
							{pile=push(pile,nga,ndr,l,1,1);if (p==1) return pile;}
					}
				}
			}
		}

	}
	 return pile;
}
if (signature==SIGNED)
{
	/* Cas (0,-1) le bloc enleve enleve 1 bp et le bloc ajoute cree 0bp */
	for (it=1;it<=points;it++)
	{
i=breakpoints[it];

nga=inverse[abs(perm[i]+1)];
if (signe(perm[i])==signe(perm[nga]) && nga>=1 && nga<i)
{
	for (ndr=nga;ndr<i;ndr++)
	{
	if ((perm[ndr]-perm[i+1])!=-1 && (!adjacent(perm,nga,-1) || !adjacent(perm,ndr,1)))
							if (!adjacent(perm,nga,-1) && !adjacent(perm,ndr,1))
							{
								if ((perm[nga-1]-perm[ndr+1])!=-1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
							}
							else
							if ((perm[nga-1]-perm[ndr+1])==-1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
						}
					}


					ndr=inverse[abs(perm[i+1]-1)];
					if (signe(perm[i+1])==signe(perm[ndr]) && ndr<i && ndr>=1)
					{
						for (nga=1;nga<=ndr;nga++)
						{
							if ((perm[nga]-perm[i])!=1 && (!adjacent(perm,nga,-1) || !adjacent(perm,ndr,1)))
							if (!adjacent(perm,nga,-1) && !adjacent(perm,ndr,1))
							{
								if ((perm[nga-1]-perm[ndr+1])!=-1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
							}
							else
							if ((perm[nga-1]-perm[ndr+1])==-1) {pile=push(pile,nga,ndr,i,1,1);if (p==1) return pile;}
						}
				

			}
}

for (k=1;k<=points;k++)
{
nga=breakpoints[k]+1;			
if (nga>1)
{
ndr=inverse[abs(perm[nga-1]+1)]-1;
				
				if (ndr>0 && !adjacent(perm,ndr,1) && signe(perm[nga-1])== signe(perm[ndr+1]) && ndr>=nga && ndr<=size)
				{
					
					for (l=ndr+1;l<=size;l++)
					{
						if (adjacent(perm,l,1) && xor((perm[nga]-perm[l])==1, (perm[ndr]-perm[l+1])==-1))
							{pile=push(pile,nga,ndr,l,1,1);if (p==1) return pile;}
						if (!adjacent(perm,l,1) && (perm[nga]-perm[l])!=1 && (perm[ndr]-perm[l+1])!=-1)
							{pile=push(pile,nga,ndr,l,1,1);if (p==1) return pile;}
					}
				}
			
}
}

	 return pile;
}
}



#define verif1rev()\
{\
if (signature==UNSIGNED)\
{\
if (0<ndr && ndr<nga && nga<=size && nga!=i && ndr!=i && signe1(nga-i)==signe1(ndr-i))\
{\
if (adjacent(perm,ndr,-1) || adjacent(perm,nga,1)) \
 {\
 if (adjacent(perm,ndr,-1) && adjacent(perm,nga,1)) \
 {\
	if (abs(perm[ndr-1]-perm[nga+1]==1)) {{pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}} \
 }\
 else \
 if (abs(perm[ndr-1]-perm[nga+1])!=1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;} \
 }\
 }\
}\
if (signature==SIGNED)\
{\
if (signe(perm[nga])!=signe(perm[i]) && signe(perm[ndr])!=signe(perm[i+1]) && 0<ndr && ndr<nga && nga<=size && signe(nga-i)==signe(ndr-i))\
{\
if (adjacent(perm,ndr,-1) || adjacent(perm,nga,1)) \
 {\
 if (adjacent(perm,ndr,-1) && adjacent(perm,nga,1)) \
 {\
	if ((perm[ndr-1]-perm[nga+1]==-1)) {{pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}} \
 }\
 else \
 if ((perm[ndr-1]-perm[nga+1])!=-1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;} \
 }\
 }\
}\
}\


L* transversion1(L* pile,int *perm,int *inverse,int points,int *breakpoints,int p)
{
	register i,j,k,l,nga,ndr,it;
if (signature==UNSIGNED)
{
	/* Cas (-1,0)*/
	for (k=1;k<=points;k++)
	{
	i=breakpoints[k];
			nga=inverse[perm[i]+1];
			ndr=inverse[perm[i+1]-1];
			verif1rev();

			if (i<size)
			{
				nga=inverse[perm[i]+1];
				ndr=inverse[perm[i+1]+1];
				verif1rev();
			if (i>0)
			{
				nga=inverse[perm[i]-1];
				ndr=inverse[perm[i+1]+1];
				verif1rev();
				}
			}
if (i>0)
{
			nga=inverse[perm[i]-1];
			ndr=inverse[perm[i+1]-1];
			verif1rev();
			}
		}


	/* Cas (0,-1) */
	for (i=0;i<=size;i++)
	{

		if (abs(perm[i]-perm[i+1])==1)
		{ 
			if (i<size && i>0)
			{
			nga=inverse[perm[i]+perm[i]-perm[i+1]];
			ndr=inverse[perm[i+1]+perm[i+1]-perm[i]];
			if (ndr>=1 && nga<=size && nga>ndr && nga!=i && ndr!=i && signe1(nga-i)==signe1(ndr-i))
			{
				if (!adjacent(perm,ndr,-1) && !adjacent(perm,nga,1) && abs(perm[ndr-1]-perm[nga+1])!=1)
				 {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}
				if (xor(adjacent(perm,ndr,-1),adjacent(perm,nga,1)) && abs(perm[ndr-1]-perm[nga+1])==1)
					{pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}
			}
			}

		}
		else
		{

			for (j=0;j<=1;j++)
			{
				k=0;

				if (j==0 && i!=0) k=-1;
				if (j==1 && perm[i]!=size && i!=size) k=1;
				if (k!=0)
				{
					nga=inverse[perm[i]+k];
					if (nga>=1)
					{
						for (ndr=1;ndr<nga;ndr++)
						{
						 if (abs(perm[ndr]-perm[i])!=1)
						 {

							if (abs(perm[nga]-perm[i])!=1 && (i+1)!=nga && nga!=i && ndr!=i && signe1(ndr-i)==signe1(nga-i) && (!adjacent(perm,ndr,-1) || !adjacent(perm,nga,1)))
							{
							if (!adjacent(perm,ndr,-1) && !adjacent(perm,nga,1))
							{
								if (abs(perm[ndr-1]-perm[nga+1])!=1)
								{

								pile=push(pile,ndr,nga,i,2,1);
								if (p==1) return pile;
								}
							}
							else
							if (abs(perm[ndr-1]-perm[nga+1])==1)
							{
								pile=push(pile,ndr,nga,i,2,1);
							if (p==1) return pile;
							}
						} }}
					}


					ndr=inverse[perm[i+1]+k];

					if (ndr>=1)
					{
						for (nga=ndr+1;nga<=size;nga++)
						{
						if (abs(perm[nga]-perm[i])!=1)
						 {
							if (ndr!=i && nga!=i && signe1(ndr-i)==signe1(nga-i) && abs(perm[nga]-perm[i])!=1 && (!adjacent(perm,ndr,-1) || !adjacent(perm,nga,1)))
							{
							if ( !adjacent(perm,ndr,-1) && !adjacent(perm,nga,1))
							{
								if (abs(perm[ndr-1]-perm[nga+1])!=1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}

							}
							else
							if (abs(perm[ndr-1]-perm[nga+1])==1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}
						}}
						}
					}
				}

			}

			/*Cas (1,-2)*/
			if (i>0)
			{
				ndr=i;
				nga=inverse[perm[i-1]+k]-1;
				if (nga>ndr && nga<=size && !adjacent(perm,ndr,-1) && !adjacent(perm,nga,1))
				{
					for (l=1;l<=size;l++)
					{
						if (ndr !=l+1 && nga!=l && ndr!=l && nga!=l && ndr!=l && signe1(nga-l)==signe1(ndr-l) && adjacent(perm,l,1) && xor(abs(perm[nga]-perm[l])==1, abs(perm[ndr]-perm[l+1])==1))
							{pile=push(pile,ndr,nga,l,2,1);if (p==1) return pile;}
						if (ndr !=l+1 && nga!=l && ndr!=l && signe1(nga-l)==signe1(ndr-l) && !adjacent(perm,l,1) && abs(perm[nga]-perm[l])!=1 && abs(perm[ndr]-perm[l+1])!=1)
							{pile=push(pile,ndr,nga,l,2,1);if (p==1) return pile;}
					}
				}
			}           
		}

	}
	 return pile;
}
if (signature==SIGNED)
{	/* Cas (0,-1) le bloc enleve enleve 1 bp et le bloc ajoute cree 0bp */

	for (it=1;it<=points;it++)
	{
i=breakpoints[it];

nga=inverse[abs(perm[i]+1)];
if (nga!=i && signe(perm[i])!=signe(perm[nga]) && nga>=1)
{
	for (ndr=1;ndr<=nga;ndr++)
	{
	if (signe(nga-i)==signe(ndr-i) && ndr!=i && ndr!=i+1 && perm[ndr]+perm[i+1]!=1 && (!adjacent(perm,nga,1) || !adjacent(perm,ndr,-1)))
							if (!adjacent(perm,nga,1) && !adjacent(perm,ndr,-1))
							{
								if ((perm[nga+1]-perm[ndr-1])!=1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}
							}
							else
							if ((perm[nga+1]-perm[ndr-1])==1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}
						}
					}


					ndr=inverse[abs(perm[i+1]-1)];
					if (ndr!=i && ndr!=(i+1) && signe(perm[i+1])!=signe(perm[ndr])&& ndr>=1)
					{
						for (nga=ndr;nga<=size;nga++)
						{
							if (signe(nga-i)==signe(ndr-i) && nga!=i && perm[nga]+perm[i]!=-1 && (!adjacent(perm,nga,1) || !adjacent(perm,ndr,-1)))
							{
							if (!adjacent(perm,nga,1) && !adjacent(perm,ndr,-1))
							{
								if ((perm[nga+1]-perm[ndr-1])!=1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}
							}
							else
							if ((perm[nga+1]-perm[ndr-1])==1) {pile=push(pile,ndr,nga,i,2,1);if (p==1) return pile;}
						}}
				

			}
}

for (k=1;k<=points;k++)
{
nga=breakpoints[k]+1;			
if (nga>1)
{
ndr=inverse[abs(perm[nga-1]+1)]-1;
				
				if (ndr>0 && !adjacent(perm,ndr,1) && signe(perm[nga-1])== signe(perm[ndr+1]) && ndr>=nga && ndr<=size)
				{
					for (l=0;l<nga-1;l++)
					{
						if (adjacent(perm,l,1) && xor((perm[nga]+perm[l+1])==1, (perm[ndr]+perm[l])==-1))
							{pile=push(pile,nga,ndr,l,2,1);if (p==1) return pile;}
						if (!adjacent(perm,l,1) && (perm[nga]+perm[l+1])!=1 && (perm[ndr]+perm[l])!=-1)
							{pile=push(pile,nga,ndr,l,2,1);if (p==1) return pile;}
					}
					for (l=ndr+1;l<=size;l++)
					{
						if (adjacent(perm,l,1) && xor((perm[nga]+perm[l+1])==1, (perm[ndr]+perm[l])==-1))
							{pile=push(pile,nga,ndr,l,2,1);if (p==1) return pile;}
						if (!adjacent(perm,l,1) && (perm[nga]+perm[l+1])!=1 && (perm[ndr]+perm[l])!=-1)
							{pile=push(pile,nga,ndr,l,2,1);if (p==1) return pile;}
					}
				}
			
}
	}
	 return pile;
}
}
