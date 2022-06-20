CC = gcc
MAIN = main.c
AUXFILES = maze.c display.c file_routines.c
EXECNAME = resolvedor_de_labirintos

target:
	${CC} -o ${EXECNAME} ${AUXFILES} ${MAIN}

remove:
	rm ${EXECNAME}
