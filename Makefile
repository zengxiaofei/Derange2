# Makefile pour derange2 et derange2_lang
CFLAGS =-O
LIBS = -lm -lc
HEADERS = transpo.h
SOURCES = derange2.c outils2.c moves2.c approches.c meilleur.c
OBJS = derange2.o outils2.o moves2.o approches.o meilleur.o 

derange2 : derange2.o ${OBJS} 
		${CC} ${CFLAGS} -o derange2  ${OBJS} ${LIBS}
