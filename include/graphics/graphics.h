#pragma once

/**
 * Library for simple graphics
 */

#define G_BLACK    0xff000000
#define G_WHITE    0xffffffff
#define G_RED      0xff0000ff
#define G_GREEN    0xff00ff00
#define G_BLUE     0xffff0000
#define G_YELLOW   0xff00ffff
#define G_CYAN     0xffffff00
#define G_MAGENTA  0xffff00ff

#define G_ALPHA(c) (((int)(0xff*c)<<24)|0x00ffffff)

typedef struct GImage
{
	unsigned int _id;
	int width, height;
} 
GImage;

typedef struct GContext GContext;

#ifdef __cplusplus
extern "C" {
#endif

GContext *gCreateContext();
void gDestroyContext(GContext *context);
void gSetInitCallback(GContext *context, void (*callback)(void *), void *data);

/* Initializes graphics subsystem */
int gInit(GContext *context);

/* Safely disposes graphics subsystem */
int gDispose(GContext *ctx);

/* Performs resizing of window */
void gResize(GContext *ctx, int width, int height);

/* Transform */
void gTranslate(GContext *ctx, const float vector[2]);
void gTransform(GContext *ctx, const float matrix[4]);

/* Color */
void gSetColorInt(GContext *ctx, unsigned color);
void gSetColor(GContext *ctx, const float color[4]);

/* Fill */
void gClear(GContext *ctx);
void gFill(GContext *ctx);

/* Geometry */
void gDrawQuad(GContext *ctx);
void gDrawCircle(GContext *ctx);
void gDrawRing(GContext *ctx, float in);
/*
void gDrawCircleSegment(GContext *ctx, float angle);
void gDrawRingSegment(GContext *ctx, float in, float angle);
*/

/* Images */
GImage *gGenImage(GContext *ctx, int width, int height, void *data);
void gFreeImage(GContext *ctx, GImage *image);
void gDrawImage(GContext *ctx, GImage *image);

#ifdef __cplusplus
}
#endif
