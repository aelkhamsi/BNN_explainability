
BIN = tree_struc

CC ?= cc
CFLAGS = -Wall -Wextra -std=c99 -g
# LDFLAGS =

.PHONY: all test build clean

all: build test

build: ${BIN}

test: build
	@for e in ${BIN}; do \
	echo "\e[46m Test $${e} \e[49m"; ./$${e}; \
	done

clean:
	rm -f *.o ${BIN}



#tree
tree.o: tree.c tree.h
	${CC} ${CFLAGS} tree.c -c

test_tree_struc.o: test_tree_struc.c tree.h
	${CC} ${CFLAGS} test_tree_struc.c -c

tree_struc: test_tree_struc.o tree.o
	${CC} test_tree_struc.o tree.o -o $@ ${LDFLAGS}
