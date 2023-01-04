# Writen by: Oscar Bergström
# https://github.com/OSCARJFB

# Compile code.
main: game_of_life.c  
	cc game_of_life.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o GameOfLife

# Remove all object files.
clean:
	rm -rf GameOfLife