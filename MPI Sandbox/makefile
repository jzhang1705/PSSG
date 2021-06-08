EXECS=helloworld ring reduction
MPICC?=mpicc

all: ${EXECS}

helloworld: helloworld.c
	${MPICC} -o helloworld helloworld.c

ring: ring.c
	${MPICC} -o ring ring.c

reduction: reduction.c
	${MPICC} -o reduction reduction.c


clean:
	rm -f ${EXECS}