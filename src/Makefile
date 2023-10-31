#	Writen by: Oscar Bergström
#  	https://github.com/OSCARJFB
#	
#	MIT License
#	Copyright (c) 2023 Oscar Bergström

cc = gcc
cflags = -Wall -Wextra -Werror -pedantic
rel = -o3 -march=native -mtune=native -flto -fomit-frame-pointer
link = -lraylib -lm

main: 
	$(cc) main.c gameOfLife.c $(link) $(cflags) -o main.o

release:
	$(cc) main.c gameOfLife.c $(link) $(rel) -o GameOfLife

clean:
	rm *.o
