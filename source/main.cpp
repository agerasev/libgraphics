#include <media/media.hpp>
#include <graphics/graphics.h>

class GraphicsHandler : public media::Graphics::Handler {
private:
	int mx, my;
	
public:
	GraphicsHandler() = default;
	virtual ~GraphicsHandler() = default;
	
	virtual void create() override {
		logMessage("graphics created");
		gInit();
	}
	
	virtual void destroy() override {
		logMessage("graphics destroyed");
		gDispose();
	}
	
	virtual void resize(int w, int h) override {
		logMessage("graphics resized %d %d", w, h);
		gResize(w, h);
	}
	
	virtual void draw(double dt) override {
		// logMessage("frame redrawed dt = %lf", dt);
		float s = 100.0;
		float matrix[4] = {s,0,0,s};
		float vector[2] = {(float) mx, (float) my};
		gClear();
		gTransform(matrix);
		gTranslate(vector);
		gSetColorInt(G_RED);
		gDrawRing(0.5);
	}
	
	void setm(int x, int y) {
		mx = x;
		my = y;
	}
};

class PointerHandler : public media::Pointer::Handler {
public:
	GraphicsHandler *g;
	PointerHandler(GraphicsHandler *gh) : g(gh) {}
	virtual ~PointerHandler() = default;
	
	virtual void move(int buttons, ivec2 from, ivec2 to) override {
		/*
		logMessage(
		      "pointer moved from {%d, %d} to {%d, %d}, buttons: %d",
		      from.x(), from.y(), to.x(), to.y(), buttons
		      );
		*/
		g->setm(to.x(), to.y());
	}
	
	virtual void up(int button, ivec2 pos, int index) override {
		logMessage(
		      "pointer upped. button: %d, pos: {%d, %d}, index: %d",
		      button, pos.x(), pos.y(), index
		      );
	}
	
	virtual void down(int button, ivec2 pos, int index) override {
		logMessage(
		      "pointer downed. button: %d, pos: {%d, %d}, index: %d",
		      button, pos.x(), pos.y(), index
		      );
	}
	
	virtual void click(int button, ivec2 pos, int index) override {
		logMessage(
		      "pointer clicked. button: %d, pos: {%d, %d}, index: %d",
		      button, pos.x(), pos.y(), index
		      );
	}
	
	virtual void scroll(ivec2 pos, ivec2 val) override {
		logMessage(
		      "pointer scroll. pos: {%d, %d}, value: {%d, %d}",
		      pos.x(), pos.y(), val.x(), val.y()
		      );
	}
};

class AppHandler : public media::App::Handler {
public:
	virtual void create() override {
		GraphicsHandler *gh = new GraphicsHandler;
		PointerHandler *ph = new PointerHandler(gh);
		super->getGraphics()->setHandler(gh);
		super->getPointer()->setHandler(ph);
		logMessage("app created");
	}
	
	virtual void destroy() override {
		delete super->getGraphics()->getHandler();
		delete super->getPointer()->getHandler();
		logMessage("app destroyed");
	}
};

MEDIA_SET_APP_HANDLER(AppHandler)
