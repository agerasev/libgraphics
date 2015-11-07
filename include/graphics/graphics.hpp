#pragma once

/**
 * Library for simple graphics
 */

#include "graphics.h"

#include <la/vec.hpp>
#include <la/mat.hpp>

namespace gfx {
static const vec4 BLACK   (0, 0, 0, 1);
static const vec4 WHITE   (1, 1, 1, 1);
static const vec4 RED     (1, 0, 0, 1);
static const vec4 GREEN   (0, 1, 0, 1);
static const vec4 BLUE    (0, 0, 1, 1);
static const vec4 YELLOW  (1, 1, 0, 1);
static const vec4 CYAN    (0, 1, 1, 1);
static const vec4 MAGENTA (1, 0, 1, 1);

inline vec4 ALPHA(float c) {
	return vec4(1, 1, 1, c);
}

class Context;

class Handler {
public:
	Context *super;
	virtual void init() {}
	virtual void dispose() {}
	virtual void draw(double) {}
};

class Shape {
private:
	fmat2 tf = unifmat2;
	fvec2 tl = nullvec2;
	
public:
	Shape() = default;
	virtual ~Shape() = default;
	
	/* Transformation and translation */
	void translate(const float v[2]) {
		tl.memcopy(v);
	}
	void translate(const fvec2 &v) {
		translate(v.data());
	}
	void transform(const float m[4]) {
		tf.memcopy(m);
	}
	void transform(const fmat2 &m) {
		transform(m.data());
	}
	
	fvec2 getTranslation() const {
		return tl;
	}
	fmat2 getTransformation() const {
		return tf;
	}
	
	void _applyMapping(GContext *ctx) const {
		gTransform(ctx, tf.data());
		gTranslate(ctx, tl.data());
	}
	virtual void _draw(GContext *ctx) const = 0;
};

class Colored {
private:
	fvec4 color;
	
public:
	Colored() = default;
	virtual ~Colored() = default;
	
	void setColor(const float c[4]) {
		color.memcopy(c);
	}
	void setColor(const fvec4 &c) {
		setColor(c.data());
	}
	fvec4 getColor() const {
		return color;
	}
	
	void _applyColor(GContext *ctx) const {
		gSetColor(ctx, color.data());
	}
};

class Quad : public Shape, public Colored {
public:
	Quad() = default;
	virtual ~Quad() = default;
	
	virtual void _draw(GContext *ctx) const override {
		_applyMapping(ctx);
		_applyColor(ctx);
		gDrawQuad(ctx);
	}
};

class Circle : public Shape, public Colored {
public:
	Circle() = default;
	virtual ~Circle() = default;
	
	virtual void _draw(GContext *ctx) const override {
		_applyMapping(ctx);
		_applyColor(ctx);
		gDrawCircle(ctx);
	}
};

class Ring : public Shape, public Colored {
private:
	float in = 0.5f;
	
public:
	Ring() = default;
	Ring(float inr) : in(inr) {}
	virtual ~Ring() = default;
	
	void setInnerRadius(float inr) {
		in = inr;
	}
	float getInnerRadius() const {
		return in;
	}
	
	virtual void _draw(GContext *ctx) const override {
		_applyMapping(ctx);
		_applyColor(ctx);
		gDrawRing(ctx, in);
	}
};

/* Images */
class Image : public Shape {
private:
	GImage *image;
public:
	Image(int width, int height, void *data) {
		image = gGenImage(width, height, data);
	}
	virtual ~Image() {
		gFreeImage(image);
	}
	
	virtual void _draw(GContext *ctx) const override {
		_applyMapping(ctx);
		gDrawImage(ctx, image);
	}
};

class Context {
private:
	GContext *context;
	Handler *handler;
	
	bool inited = false;
	static void callback(void *data) {
		Context *ctx = static_cast<Context *>(data);
		ctx->inited = true;
		if(ctx->handler != nullptr) {
			ctx->handler->init();
		}
	}
	
public:
	/* Initializes graphics subsystem */
	Context(Handler *h = nullptr) {
		handler = h;
		if(handler != nullptr)
			handler->super = this;
		context = gCreateContext();
		gSetInitCallback(context, callback, static_cast<void *>(this));
		gInit(context);
	}
	
	/* Safely disposes graphics subsystem */
	virtual ~Context() {
		if(handler != nullptr) {
			handler->dispose();
		}
		gDispose(context);
		gDestroyContext(context);
	}
	
	void requestDraw(double dt) const {
		if(inited && handler != nullptr) {
			handler->draw(dt);
		}
	}
	
	/* Performs resizing of window */
	void resize(int w, int h) {
		gResize(context, w, h);
	}
	
	/* Fill */
	void clear() {
		gClear(context);
	}

	void fill(const float c[4]) {
		gSetColor(context, c);
		gFill(context);
	}

	void fill(const fvec4 &c) {
		fill(c.data());
	}
	
	/* Geometry */
	void drawShape(const Shape *s) {
		s->_draw(context);
	}
	
	Handler *getHandler() {
		return handler;
	}
};

}
