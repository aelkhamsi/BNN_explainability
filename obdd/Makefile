CAH_DIR = cache
LNK_DIR = link
TREE_DIR = tree
LST_DIR = list

CPPFLAGS = -I ${CAH_DIR} -I ${LNK_DIR} -I ${TREE_DIR} -I .
BIN = link_struc list_struc cache_struc tree_struc

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
main.o: main.c ${CAH_DIR}/cache.h ${TREE_DIR}/tree.h utils.h
	${CC} ${CPPFLAGS} ${CFLAGS} main.c -c

main: main.o cache.o tree.o link.o utils.o
	${CC} main.o cache.o tree.o link.o utils.o -o $@ ${LDFLAGS}

#print
utils.o: utils.c utils.h ${TREE_DIR}/tree.h cst.h
	${CC} ${CPPFLAGS} ${CFLAGS} utils.c -c



#link
link.o: ${LNK_DIR}/link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/link.c -c

test_link_struc.o: ${LNK_DIR}/test_link_struc.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link_struc.c -c

link_struc: test_link_struc.o link.o
	${CC} test_link_struc.o link.o -o $@ ${LDFLAGS}


#cache
cache.o: ${CAH_DIR}/cache.c ${CAH_DIR}/cache.h ${LNK_DIR}/link.h ${TREE_DIR}/tree.h cst.h
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


#list
list.o: ${LST_DIR}/list.c ${LST_DIR}/list.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LST_DIR}/list.c -c

test_list_struc.o: ${LST_DIR}/test_list_struc.c ${LST_DIR}/list.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LST_DIR}/test_list_struc.c -c

list_struc: test_list_struc.o list.o
	${CC} test_list_struc.o list.o -o $@ ${LDFLAGS}
