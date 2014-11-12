/**
 * Library for simple graphics
 *
 * You need to have SDL2 and GLEW libraries
 * Link -lSDL2 -lGLEW -lGL
 */

int createWindow(int width, int height);
int destroyWindow();

/* Implementation */
#include<SDL2/SDL.h>
#include<GL/glew.h>

#include<stdio.h>

struct
{
		int width, height;
		SDL_Window *window;
		SDL_GLContext context;
}__global_context;

int createWindow(int width, int height)
{
	__global_context.width = width;
	__global_context.height = height;

	__global_context.window =
		SDL_CreateWindow(
			"Graphics application",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL
		);

	__global_context.context =
		SDL_GL_CreateContext(__global_context.window);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
	SDL_GL_SetSwapInterval(1);

	GLenum glew_status = glewInit();
	if(GLEW_OK != glew_status)
	{
		printf("%s\n",glewGetErrorString(glew_status));
		return -1;
	}
	if(!GLEW_VERSION_2_0)
	{
		printf("%s\n","No support for OpenGL 2.0 found");
		return -2;
	}

	glClearColor(0, 0, 0, 0);
	glViewport(0,0,width,width);
}

int destroyWindow()
{
	SDL_GL_DeleteContext(__global_context.context);
	SDL_DestroyWindow(__global_context.window);
	return 0;

}
