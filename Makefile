CC = gcc
CFLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors -lm
OBJS = utils.o symnmfImp.o sym.o ddg.o symnmf.o nsm.o readData.o

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

symnmf.o: symnmf.c symnmf.h readData.h
	$(CC) $(CFLAGS) -c symnmf.c

nsm.o: nsm.c ncm.h ddg.h
	$(CC) $(CFLAGS) -c nsm.c

readData.o: readData.c readData.h
	$(CC) $(CFLAGS) -c readData.c

clean:
	rm -f $(OBJS) program
