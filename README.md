# A modified version of Derange2 (DERANGE II) used in the HapHiC study

## Modification

> The original version of Derange2: ftp://ftp.ebi.ac.uk/pub/software/unix/derange2.tar.Z

> Citation: Blanchette, M., Kunisawa, T. & Sankoff, D. Parametric genome rearrangement. Gene 172, GC11-GC17 (1996).

Modification: `MAX_LENGTH` in `transpo.h` was set to 5000 to support more contigs.

## HapHiC

> Xiaofei Zeng, Zili Yi, Xingtan Zhang, Yuhui Du, Yu Li, Zhiqing Zhou, Sijie Chen, Huijie Zhao, Sai Yang, Yibin Wang, Guoan Chen. Chromosome-level scaffolding of haplotype-resolved assemblies using Hi-C data without reference genomes. *Nature Plants*. doi: https://doi.org/10.1038/s41477-024-01755-3

## Documentation

```
Documentation about Derange2

********************************************************************************
***                                                                          ***
***                        Documentation about Derange2                      ***
***                                                                          ***
***   By Mathieu Blanchette (e-mail : blanchet@hans.crm.umontreal.ca)        ***
***   directed by David Sankoff.                                             ***
***                                                                          ***
********************************************************************************

General informations :

Derange2 is a computer program (written in C) designed to sort a given
permutation to the identity permutation by using inversions, transpositions
and inverted transpositions. It allows the user to specify a weight associated
to each kind of moves, in order to influence the overall proportion of each
kind of moves in the final solution.

Compiling Derange2 :

Derange2 has been used on several kind of computers, such as SGI and Sun.
A makefile is provided with the package, so that compilation is automatically
done by typing : make derange2
The program also works on PC, although the Makefile is no longer valid, since
it uses cc compiler, which should be replaced by your own compiler.

The inputs :

Derange2 takes 8 parameters as input. The first one is used to choose the
kind of permutation (choose -S for a signed or -U for unsigned permutations).
The second selects if the permutation is linear (-L) or circular (-C).
Then comes the input file, containing the permutations to sort. See below for
the format of this file. The fourth parameter is the look ahead used in the 
research (a look ahead between 2 and 4 gives very reliable results, although
it is possible to set it up to 10). The three next parameters are weights for
inversions, transpositions and inverted transpositions respectively. It is
usual to set the inversion weight to 1 and to vary the two other weights, but
any set of (positive) weights can be used. Finally, you need to supply the name
of a file where the results will be written.

For example, the command : derange2 -S -L Perm_file 3 1 2 2 Out_file
would be acceptable.

The input file :

The input file contains the permutation(s) you want to sort. It has the
following format : Each element of the permutation to sort is listed, separated
by a space (' '). After each permutation, use 0 (zero) to indicate the end
of the current permutation. Note that many permutations can be in a same file,
as long as each one is on its one line and terminated by zero.
For example, a file may look like :

5 3 6 -2 1 -4 0
6 9 -3 -1 2 10 7 -4 8 -5 0

The output file :

Derange2 generates a file containing its results. This file contains:
- A resume of the permutation solved and of the parameters used.
- The list of moves sorting the permutation:
  inverted segments are shown between [  ]
  transposed segments are shown between ( ) and insert at @
  inverted-transposed segments are shown between < > and are insert at @
- A resume of the total number of moves and of the number of moves of each
  kind.

IMPORTANT : Derange2 is an EXPERIMENTAL program which may still contain a few bugs.
            The authors don't any responsibility about the results (correct or not)
            it may give or about eventual corrections that may be needed.
            However, feel free to contact the authors if you have questions
            or comments about Derange2.
```
