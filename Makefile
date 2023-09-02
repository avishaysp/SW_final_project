CC = gcc
CFLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
OBJS = utils.o symnmfImp.o sym.o ddg.o

program: $(OBJS)
	$(CC) $(CFLAGS) -o program $(OBJS)

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

symnmfImp.o: symnmfImp.c symnmfImp.h ncm.h
	$(CC) $(CFLAGS) -c symnmfImp.c

sym.o: sym.c sym.h utils.h
	$(CC) $(CFLAGS) -c sym.c

ddg.o: ddg.c ddg.h sym.h
	$(CC) $(CFLAGS) -c ddg.c

clean:
	rm -f $(OBJS) program
