lib/libgraphics.so: obj/graphics.o obj/shader.o
	mkdir -p lib
	gcc -shared $^ -o lib/libgraphics.so

obj/graphics.o: graphics/graphics.c graphics/graphics.h graphics/shader.h
	mkdir -p obj
	gcc -c -Wall -Werror -fpic $< -o $@

obj/shader.o: graphics/shader.c graphics/shader.h graphics/shader_source.h
	mkdir -p obj
	gcc -c -Wall -Werror -fpic $< -o $@
