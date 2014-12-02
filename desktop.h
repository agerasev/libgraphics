#pragma once

/**
 * Desktop implementation of graphics library
 * 
 * You need to have SDL2 and GLEW libraries
 * Link -lSDL2 -lGLEW -lGL when building
 */

struct __Context
{
	SDL_Window *window;
	SDL_GLContext context;
}
__platform__context;

#ifdef DEBUG

void __printShaderCompilationErrors(GLuint id)
{
	int   infologLen   = 0;
	int   charsWritten = 0;
	char *infoLog;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLen);
	if(infologLen > 1)
	{
		infoLog = malloc(sizeof(char)*infologLen);
		glGetShaderInfoLog(id, infologLen, &charsWritten, infoLog);
		printf(infoLog);
		free(infoLog);
	}
}

void __printProgramLinkingErrors(GLuint id)
{
	int link_ok;
	glGetProgramiv(id, GL_LINK_STATUS, &link_ok);
	if(!link_ok) {
		printf("Linking error\n");
	}
}

#endif

int initGraphics(int width, int height)
{
	__context.width = width;
	__context.height = height;

	__platform__context.window =
		SDL_CreateWindow(
			"Graphics application",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			__context.width,
			__context.height,
			SDL_WINDOW_OPENGL
		);

	__platform__context.context =
		SDL_GL_CreateContext(__platform__context.window);

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0,0,0,0);
	glViewport(0,0,width,height);
	glClear(GL_COLOR_BUFFER_BIT);

	__loadShaders(&(__context.shaders));
	__loadBuffers(&(__context.buffers));

	__context.projection_matrix[0] = (float)height/width;
	__context.projection_matrix[1] = 0.0f;
	__context.projection_matrix[2] = 0.0f;
	__context.projection_matrix[3] = 1.0f;

	return 0;
}

int disposeGraphics()
{
	__deleteBuffers(&(__context.buffers));
	__deleteShaders(&(__context.shaders));

	SDL_GL_DeleteContext(__platform__context.context);
	SDL_DestroyWindow(__platform__context.window);
	return 0;
}

void __flip()
{
	SDL_GL_SwapWindow(__platform__context.window);
}

int handleEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			return 1;
		}
	}
	return 0;
}

void startLoop(void(*draw)(void*), void *data)
{
	while(!handleEvents())
	{
		draw(data);
		__flip();
	}
}
