SRC = graphics/graphics.c graphics/shader.c
OBJ = $(SRC:graphics/%.c=obj/%.o)

lib/libgraphics.so: $(OBJ)
	mkdir -p lib
	gcc -shared $^ -o lib/libgraphics.so

obj/%.o: graphics/%.c
	mkdir -p obj
	gcc -c -Wall -Werror -fpic $< -o $@
