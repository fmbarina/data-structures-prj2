CC=gcc
CC_FLAGS=-g -Wall -Wextra -pedantic #-ansi 
CC_LIBS=-lm
CC_HEADERS=-I ./headers

COMMON=tree.c assertr.c bits.c bytes.c compfile.c counter.c encoding.c treelist.c pathman.c reglfile.c rwbin.c

.PHONY: all compile clean compacta descompacta reset

compile: all

all: compacta.out descompacta.out

compacta: compacta.out

descompacta: descompacta

compacta.out:
	$(CC) $(CC_FLAGS) $(addprefix ./src/,$(COMMON)) ./src/compacta.c -o compacta.out $(CC_HEADERS) $(CC_LIBS)

descompacta.out:
	$(CC) $(CC_FLAGS) $(addprefix ./src/,$(COMMON)) ./src/descompacta.c -o descompacta.out $(CC_HEADERS) $(CC_LIBS)

clean:
	@ rm -rf ./*.o ./*.out

reset:
	@ rm -rf ./*.o ./*.out

# Em caso de dúvida...
# https://www.gnu.org/software/make/manual/html_node/index.html
