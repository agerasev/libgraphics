#include <graphics/graphics.h>

#include <emscripten.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EVAL_SIZE 0x40

void eval(const char *script) {
	emscripten_run_script(script);
}

struct GContext {
	int w, h;
	float tf[4];
	float tl[2];
	float c[4];
	
	static void (*callback)(void *) = NULL;
	static void *callback_data = NULL;
};

static GContext *global_context = NULL;

GContext *gCreateContext() {
	GContext *context = malloc(sizeof(GContext));
	context->callback = NULL;
	global_context = context;
	return context;
}

void gDestroyContext(GContext *context) {
	global_context = NULL;
	free(context);
}

void gSetInitCallback(GContext *context, void (*callback)(void *), void *data) {
	context->callback = callback;
	context->callback_data = data;
}

void gfx_script_loaded() {
	eval("__gfxInit(__libmedia_canvas);");
	if(global_context->callback != NULL)
		global_context->callback(global_context->callback_data);
}

/* Initializes graphics subsystem */
int gInit(GContext *ctx)
{
	eval(
	  "__loadScript('graphics.js', function(){Module.ccall('gfx_script_loaded',null,[],[]);});"
	  );
	return 0;
}

/* Safely disposes graphics subsystem */
int gDispose(GContext *ctx)
{
	eval("__gfxDispose();");
	return 0;
}

/* Performs resizing of window */
void gResize(GContext *ctx, int width, int height)
{
	ctx->w = width;
	ctx->h = height;
}

void gTranslate(GContext *ctx, const float vector[2])
{
	char str[EVAL_SIZE];
	memcpy(ctx->tl, vector, sizeof(float)*2);
	sprintf(str, "__gfxTranslate(%f,%f);", vector[0], vector[1]);
	eval(str);
}

void gTransform(GContext *ctx, const float matrix[4])
{
	char str[EVAL_SIZE];
	memcpy(ctx->tf, matrix, sizeof(float)*4);
	sprintf(
	  str, "__gfxTransform(%f,%f,%f,%f);", 
	  matrix[0], matrix[1], matrix[2], matrix[3]
	  );
	eval(str);
}

void gSetColorInt(GContext *ctx, unsigned color)
{
	float c[4];
	c[0] = (float) ((color >>  0) & 0xff)/0xff;
	c[1] = (float) ((color >>  8) & 0xff)/0xff;
	c[2] = (float) ((color >> 16) & 0xff)/0xff;
	c[3] = (float) ((color >> 24) & 0xff)/0xff;
	gSetColor(ctx, c);
}

void gSetColor(GContext *ctx, const float color[4])
{
	char str[EVAL_SIZE];
	memcpy(ctx->c, color, sizeof(float)*4);
	sprintf(
	  str, "__gfx_ctx->fillStyle = 'rgba(%d,%d,%d,%f)';", 
	  (int) (color[0]*0xff), (int) (color[1]*0xff), (int) (color[2]*0xff), color[3]
	  );
	eval(str);
}

void gClear(GContext *ctx)
{
	eval("__gfxClear();");
}

void gFill(GContext *ctx)
{
	eval("__gfxFill();");
}

void gDrawQuad(GContext *ctx) 
{
	eval("__gfxDrawQuad();");
}

void gDrawCircle(GContext *ctx)
{
	eval("__gfxDrawCircle();");
}

void gDrawRing(GContext *ctx, float in)
{
	char str[EVAL_SIZE];
	sprintf(str, "__gfxDrawRing(%f);", in);
	eval(str);
}

GImage *gGenImage(GContext *ctx, int width, int height, void *data)
{
	return NULL;
}

void gFreeImage(GContext *ctx, GImage *image)
{
	
}

void gDrawImage(GContext *ctx, GImage *image)
{
	
}
