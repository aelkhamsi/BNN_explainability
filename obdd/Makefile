CAH_DIR = cache/cache
LNK_DIR = cache/link
TREE_DIR = tree

CPPFLAGS = -I ${CAH_DIR} -I ${LNK_DIR} -I ${TREE_DIR}
BIN = link_struc cache_struc tree_struc

CC ?= cc
CFLAGS = -Wall -Wextra -std=c99 -g
# LDFLAGS =

.PHONY: all test build clean

all: build test main

build: ${BIN}

test: build
	@for e in ${BIN}; do \
	echo "\e[46m Test $${e} \e[49m"; ./$${e}; \
	done

clean:
	rm -f *.o ${BIN};
	rm main


#main
main.o: main.c ${CAH_DIR}/cache.h ${TREE_DIR}/tree.h #utils.h
	${CC} ${CPPFLAGS} ${CFLAGS} main.c -c

main: main.o cache.o tree.o link.o #utils.o
	${CC} main.o cache.o tree.o link.o -o $@ ${LDFLAGS}

#print
# utils.o: utils.c utils.h ${TREE_DIR}/tree.h
# 	${CC} ${CPPFLAGS} ${CFLAGS} utils.c -c



#link
link.o: ${LNK_DIR}/link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/link.c -c

test_link_struc.o: ${LNK_DIR}/test_link_struc.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link_struc.c -c

link_struc: test_link_struc.o link.o
	${CC} test_link_struc.o link.o -o $@ ${LDFLAGS}


#cache
cache.o: ${CAH_DIR}/cache.c ${CAH_DIR}/cache.h ${LNK_DIR}/link.h ${TREE_DIR}/tree.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${CAH_DIR}/cache.c -c

test_cache_struc.o: ${CAH_DIR}/test_cache_struc.c ${CAH_DIR}/cache.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${CAH_DIR}/test_cache_struc.c -c

cache_struc: test_cache_struc.o cache.o link.o tree.o
	${CC} test_cache_struc.o cache.o link.o tree.o -o $@ ${LDFLAGS}


#tree
tree.o: ${TREE_DIR}/tree.c ${TREE_DIR}/tree.h
	${CC} ${CFLAGS} ${TREE_DIR}/tree.c -c

test_tree_struc.o: ${TREE_DIR}/test_tree_struc.c ${TREE_DIR}/tree.h
	${CC} ${CFLAGS} ${TREE_DIR}/test_tree_struc.c -c

tree_struc: test_tree_struc.o tree.o
	${CC} test_tree_struc.o tree.o -o $@ ${LDFLAGS}
