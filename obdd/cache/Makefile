CAH_DIR = cache
LNK_DIR = link

BIN = link_struc cache_struc

CC ?= cc
CPPFLAGS = -I ${CAH_DIR} -I ${LNK_DIR}
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



#link
link.o: ${LNK_DIR}/link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/link.c -c

test_link_struc.o: ${LNK_DIR}/test_link_struc.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link_struc.c -c

link_struc: test_link_struc.o link.o
	${CC} test_link_struc.o link.o -o $@ ${LDFLAGS}


#cache
cache.o: ${CAH_DIR}/cache.c ${CAH_DIR}/cache.h ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${CAH_DIR}/cache.c -c

test_cache_struc.o: ${CAH_DIR}/test_cache_struc.c ${CAH_DIR}/cache.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${CAH_DIR}/test_cache_struc.c -c

cache_struc: test_cache_struc.o cache.o link.o
	${CC} test_cache_struc.o cache.o link.o -o $@ ${LDFLAGS}
