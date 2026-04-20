SRCS = src/main.c src/z11lib.c src/z11_parsing.c

all :
	gcc $(SRCS) -o z11.exe

clean :
	rm z11.exe

gdb :
	gcc $(SRCS) -o z11.exe -g