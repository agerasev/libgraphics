#pragma once

/**
 * Library for simple graphics
 */

#define BLACK    0xff000000
#define WHITE    0xffffffff
#define RED      0xff0000ff
#define GREEN    0xff00ff00
#define BLUE     0xffff0000
#define YELLOW   0xff00ffff
#define CYAN     0xffffff00
#define MAGENTA  0xffff00ff

#define ALPHA(c) (((int)(255.0f*c)<<24)|0x00ffffff)

/* Initializes graphics subsystem */
int initGraphics();

/* Safely disposes graphics subsystem */
int disposeGraphics();

/* Performs resizing of window */
void resizeGraphics(int width, int height);

/* Performs rendering */
void renderGraphics();

/* Sets function invokes on resize */
void setResizeFunc(void (*resize)(int,int,void*), void *data);

/* Sets function invokes when rendering */
void setDisplayFunc(void (*display)(void*), void *data);

/* Polls events and calls user-set handlers
 * returns non-zero if application need to be exited */
int handleEvents();

/* Transform */
void translate(const float *vector);
void transform(const float *matrix);

/* Color */
void setColor(unsigned color);
void setFloatColor(const float *color);

/* Draw */
void clear();
void fill();
void quad();

/* Implementation */

#if defined(__unix__) || defined(_WIN32)
#include"desktop_headers.h"
#endif

#if defined(__ANDROID__)
#include"android_headers.h"
#endif

#include"common.h"

#if defined(__unix__) || defined(_WIN32)
#include"desktop.h"
#endif

#if defined(__ANDROID__)
#include"android.h"
#endif
