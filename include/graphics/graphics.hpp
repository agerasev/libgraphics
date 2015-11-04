#pragma once

/**
 * Library for simple graphics
 */

#include "graphics.h"

#include <la/vec.hpp>
#include <la/mat.hpp>

namespace gfx {
static const int BLACK   = G_BLACK;
static const int WHITE   = G_WHITE;
static const int RED     = G_RED;
static const int GREEN   = G_GREEN;
static const int BLUE    = G_BLUE;
static const int YELLOW  = G_YELLOW;
static const int CYAN    = G_CYAN;
static const int MAGENTA = G_MAGENTA;

inline int ALPHA(float c) {
	return G_ALPHA(c);
}

class Image {
public:
	
};

class Context;

class Handler {
public:
	Context *super;
	virtual void init() {}
	virtual void dispose() {}
	virtual void draw(double) {}
};

class Shape {
public:
	Shape() = default;
	virtual ~Shape() = default;
	virtual void _draw() const = 0;
};

class Colored {
private:
	float color[4];
	
public:
	Colored() = default;
	virtual ~Colored() = default;
	void setColor(const float c[4]);
	void setColor(const fvec4 &c);
	void setColor(int c);
};

class Quad : public Shape {
public:
	Quad() = default;
	virtual ~Quad() = default;
	virtual void _draw() const override;
};

class Circle : public Shape {
public:
	Circle() = default;
	virtual ~Circle() = default;
	virtual void _draw() const override;
};

class Ring : public Shape {
public:
	float in = 0.5f;
	
	Ring() = default;
	Ring(float inm) : in(inm) {}
	virtual ~Ring() = default;
	virtual void _draw() const override;
};

class Context {
private:
	GContext *context;
	Handler *handler;
	
	bool inited = false;
	static void callback(void *data);
	
public:
	/* Initializes graphics subsystem */
	Context(Handler *h = nullptr);
	
	/* Safely disposes graphics subsystem */
	virtual ~Context();
	
	/* Performs resizing of window */
	void resize(int w, int h);
	
	/* Transform */
	void translate(const float v[2]);
	void translate(const fvec2 &v);
	void transform(const float m[4]);
	void transform(const fmat2 &m);
	
	/* Fill */
	void clear();
	void fill(const float c[4]);
	void fill(const fvec4 &c);
	void fill(int color);
	
	/* Geometry */
	void draw(const Shape *s);
	
	Handler *getHandler();
};


/*
void gDrawCircleSegment(float angle);
void gDrawRingSegment(float in, float angle);
*/

/* Images */
GImage *gGenImage(int width, int height, void *data);
void gFreeImage(GImage *image);
void gDrawImage(GImage *image);

}
