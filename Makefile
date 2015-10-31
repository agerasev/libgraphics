.phony: all desktop web

D_CC=gcc
D_CXX=g++

W_CC=emcc
W_CXX=em++

AR=ar

SOURCE=source/main.cpp
HEADERS=

D_OBJ_DIR=build/desktop/obj
D_APP_DIR=build/desktop

W_OBJ_DIR=build/web/obj
W_APP_DIR=build/web

MEDIA_DIR=libmedia
include $(MEDIA_DIR)/Makefile

GFX_DIR=libgraphics
include $(GFX_DIR)/Makefile

D_SOURCE=$(SOURCE)

D_HEADERS=$(HEADERS) $(MEDIA_HEADERS) $(MEDIA_D_HEADERS) $(GFX_HEADERS) $(GFX_D_HEADERS)

D_INCLUDES=$(MEDIA_INCLUDES) $(MEDIA_D_INCLUDES) $(GFX_INCLUDES) $(GFX_D_INCLUDES)

D_LIBS=$(MEDIA_D_LIB) $(MEDIA_D_LINK_LIBS) $(GFX_D_LIB) $(GFX_D_LINK_LIBS)
D_LIB_DIRS=$(MEDIA_D_LIB_DIR) $(GFX_D_LIB_DIR)

D_CFLAGS=$(MEDIA_CFLAGS) $(MEDIA_D_CFLAGS) -Wall
D_LFLAGS=$(MEDIA_LFLAGS) $(MEDIA_D_LFLAGS)

W_SOURCE=$(SOURCE)

W_HEADERS=$(HEADERS) $(MEDIA_HEADERS) $(MEDIA_W_HEADERS)

W_INCLUDES=$(MEDIA_INCLUDES) $(MEDIA_W_INCLUDES)

W_LIBS=$(MEDIA_W_LIB) $(MEDIA_W_LINK_LIBS)
W_LIB_DIRS=$(MEDIA_W_LIB_DIR)

W_CFLAGS=$(MEDIA_CFLAGS) $(MEDIA_W_CFLAGS) -Wall
W_LFLAGS=$(MEDIA_LFLAGS) $(MEDIA_W_LFLAGS)

all: build desktop web

desktop: build/desktop libmedia_desktop libgraphics_desktop build/desktop/app

web: build/web libmedia_web libgraphics_web build/web/app.js

build:
	mkdir -p build

build/desktop:
	mkdir -p build/desktop

build/desktop/app: $(D_SOURCE) $(D_HEADERS) $(MEDIA_D_LIB_FILE) $(GFX_D_LIB_FILE)
	$(D_CXX) $(D_CFLAGS) $(D_LFLAGS) $(D_INCLUDES:%=-I%) $(D_LIB_DIRS:%=-L%) $(D_LIBS:%=-l%) $< -o $@

build/web:
	mkdir -p build/web

build/web/app.js: $(W_SOURCE) $(W_HEADERS) $(MEDIA_W_LIB_FILE)
	$(W_CXX) $(W_CFLAGS) $(W_LFLAGS) $(W_INCLUDES:%=-I%) $(W_LIB_DIRS:%=-L%) $(W_LIBS:%=-l%) $< -o $@
