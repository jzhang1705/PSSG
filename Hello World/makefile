EXECS=helloworld
MPICC?=mpicc

all: ${EXECS}

mpi_hello_world: helloworld.c
	${MPICC} -o helloworld helloworld.c

clean:
	rm -f ${EXECS}