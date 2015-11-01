#include <graphics/graphics.h>

#include <emscripten.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EVAL_SIZE 0x40

void eval(const char *script) {
	emscripten_run_script(script);
}

static struct {
	int w, h;
	float tf[4];
	float tl[2];
	float c[4];
} ctx;

/* Initializes graphics subsystem */
int gInit()
{
	eval("__gfx_ctx = __libmedia_canvas.getContext('2d');");
	return 0;
}

/* Safely disposes graphics subsystem */
int gDispose()
{
	eval("__gfx_ctx = undefined;");
	return 0;
}

/* Performs resizing of window */
void gResize(int width, int height)
{
	ctx.w = width;
	ctx.h = height;
}

void gTranslate(const float vector[2])
{
	memcpy(ctx.tl, vector, sizeof(float)*2);
}

void gTransform(const float matrix[4])
{
	memcpy(ctx.tf, matrix, sizeof(float)*4);
}

void gSetColorInt(unsigned color)
{
	float c[4];
	c[0] = (float) ((color >>  0) & 0xff)/0xff;
	c[1] = (float) ((color >>  8) & 0xff)/0xff;
	c[2] = (float) ((color >> 16) & 0xff)/0xff;
	c[3] = (float) ((color >> 24) & 0xff)/0xff;
	gSetColor(c);
}

void gSetColor(const float color[4])
{
	char str[EVAL_SIZE];
	memcpy(ctx.c, color, sizeof(float)*4);
	sprintf(
	      str, "__gfx_ctx.fillStyle = 'rgba(%d,%d,%d,%f)';", 
	      (int) (color[0]*0xff), (int) (color[1]*0xff), (int) (color[2]*0xff), color[3]
	    );
	eval(str);
}

void gSetBlendMode(unsigned mode)
{
	fprintf(stderr, "gSetBlendMode not implemented for canvas yet\n");
}

void gClear()
{
	char str[EVAL_SIZE];
	sprintf(str, "__gfx_ctx.clearRect(0,0,%d,%d);", ctx.w, ctx.h);
	eval(str);
}

void gFill()
{
	char str[EVAL_SIZE];
	sprintf(str, "__gfx_ctx.fillRect(0,0,%d,%d);", ctx.w, ctx.h);
	eval(str);
}

void gDrawCircle()
{
	
}

void gDrawRing(float in)
{
	
}

GImage *gGenImage(int width, int height, void *data)
{
	return NULL;
}

void gFreeImage(GImage *image)
{
	
}

void gDrawImage(GImage *image)
{
	
}
