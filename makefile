OBJS = ./obj/main.o ./obj/myoled.o ./obj/getSystem.o
SRC1 = ./src/main.c
SRC2 = ./src/myoled.c
SRC3 = ./src/getSystem.c
LINKA = -lwiringPi
LINKB = -I ./include/

main:${OBJS}
	gcc $^ -o $@ ${LINKA} ${LINKB}

./obj/myoled.o:${SRC2}
	gcc -c $^ -o $@ ${LINKA} ${LINKB}

./obj/getSystem.o:${SRC3}
	gcc -c $^ -o $@ ${LINKB}

./obj/main.o:${SRC1}
	gcc -c $^ -o $@ ${LINKA} ${LINKB}