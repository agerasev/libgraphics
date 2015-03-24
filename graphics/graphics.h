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

#define G_ALPHA(c) (((int)(255.0f*c)<<24)|0x00ffffff)

#define G_BLEND_ADDITION   0x01
#define G_BLEND_OVERLAY    0x02

typedef struct GImage
{
	unsigned int _id;
	int width, height;
} 
GImage;

#ifdef __cplusplus
extern "C" {
#endif

/* Initializes graphics subsystem */
int gInit();

/* Safely disposes graphics subsystem */
int gDispose();

/* Performs resizing of window */
void gResize(int width, int height);

/* Transform */
void gTranslate(const float vector[2]);
void gTransform(const float matrix[4]);

/* Color */
void gSetColorInt(unsigned color);
void gSetColor(const float color[4]);
void gSetBlendMode(unsigned mode);

/* Fill */
void gClear();
void gFill();

/* Geometry */
void gDrawQuad();
void gDrawCircle();
void gDrawRing(float in);
/*
void gDrawCircleSegment(float angle);
void gDrawRingSegment(float in, float angle);
*/

/* Images */
GImage *gGenImage(int width, int height, void *data);
void gFreeImage(GImage *image);
void gDrawImage(GImage *image);

#ifdef __cplusplus
}
#endif
