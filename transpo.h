/* Declarations for Derange2 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define		MAX_LENGTH	5000

#define		LINEAR		0
#define		CIRCULAR	1

#define         SIGNED          0
#define         UNSIGNED        1

typedef struct liste_de_mouv L;
struct liste_de_mouv
{
	short type;    /* inversion=0, transposition=1 */
	int gauche;
	int droite;
	int nouveau;
	struct liste_de_mouv *prochain;
        int gain;

};

#define xor(a,b) ((a || b) && !(a && b))

#define mini(a,b) ((a<b) ? a : b)

#define signe(a) ((a<0) ? -1:1)
