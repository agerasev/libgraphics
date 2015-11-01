#include <media/media.hpp>
#include <graphics/graphics.h>

class GraphicsHandler : public media::Graphics::Handler {
private:
	int color = 0xff000000;
	
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
	
	virtual void draw() override {
		// logMessage("frame redrawed");
		gClear();
		gSetColorInt(G_ALPHA(1) & color++);
		gFill();
	}
};

class PointerHandler : public media::Pointer::Handler {
public:
	PointerHandler() = default;
	virtual ~PointerHandler() = default;
	
	virtual void move(int buttons, ivec2 from, ivec2 to) override {
		/*
		logMessage(
		      "pointer moved from {%d, %d} to {%d, %d}, buttons: %d",
		      from.x(), from.y(), to.x(), to.y(), buttons
		      );
		*/
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
		super->getGraphics()->setHandler(new GraphicsHandler);
		super->getPointer()->setHandler(new PointerHandler);
		logMessage("app created");
	}
	
	virtual void destroy() override {
		delete super->getGraphics()->getHandler();
		delete super->getPointer()->getHandler();
		logMessage("app destroyed");
	}
};

MEDIA_SET_APP_HANDLER(AppHandler)
