################
##   Common   ##
################

# Requires:
#  GFX_DIR
#  LIBLA_DIR
#
# Provides:
#  GFX_HEADERS
#  GFX_INCLUDES

_GFX_HEADERS= \
	graphics.h \
	graphics.hpp
GFX_HEADERS=$(_GFX_HEADERS:%=$(GFX_DIR)/include/graphics/%)
_GFX_LIBLA_HEADERS= \
	$(LIBLA_DIR)/la/vec.hpp \
	$(LIBLA_DIR)/la/mat.hpp
GFX_LOCAL_HEADERS=$(_GFX_LIBLA_HEADERS)

GFX_INCLUDES=$(GFX_DIR)/include
GFX_LOCAL_INCLUDES=$(LIBLA_DIR)

.phony: libgraphics_desktop libgraphics_web

#################
##   Desktop   ##
#################

# Requires:
#  D_OBJ_DIR
#
# Provides:
#  GFX_D_LIB
#	 GFX_D_LIB_DIR
#  GFX_D_LIB_FILE
#  GFX_D_LINK_LIBS

GFX_D_OBJ_DIR=$(D_OBJ_DIR)/graphics

GFX_D_LIB=graphics
GFX_D_LIB_DIR=$(GFX_D_OBJ_DIR)
GFX_D_LIB_FILE=$(GFX_D_LIB_DIR)/libgraphics.a
GFX_D_LINK_LIBS=GL GLEW

GFX_SOURCE_DIR=$(GFX_DIR)/source

_GFX_D_LOCAL_HEADERS= \
	gl/shader.h \
	gl/shader_source.h
GFX_D_LOCAL_HEADERS=$(_GFX_D_LOCAL_HEADERS:%=$(GFX_SOURCE_DIR)/%)

GFX_D_SOURCE= \
	gl/graphics.c \
	gl/shader.c

_GFX_D_OBJS= \
	graphics.o \
	shader.o
GFX_D_OBJS=$(_GFX_D_OBJS:%=$(GFX_D_OBJ_DIR)/%)

GFX_D_ALL_HEADERS=$(GFX_HEADERS) $(GFX_LOCAL_HEADERS) $(GFX_D_LOCAL_HEADERS)
GFX_D_ALL_INCLUDES=$(GFX_INCLUDES) $(GFX_LOCAL_INCLUDES)

libgraphics_desktop: $(GFX_D_OBJ_DIR) $(GFX_D_LIB_FILE)

$(GFX_D_OBJ_DIR):
	mkdir -p $@

$(GFX_D_LIB_FILE): $(GFX_D_OBJS)
	$(AR) rcs $@ $^

$(GFX_D_OBJ_DIR)/graphics.o: $(GFX_SOURCE_DIR)/gl/graphics.c $(GFX_D_ALL_HEADERS)
	$(D_CC) -c -g -Wall $(GFX_D_ALL_INCLUDES:%=-I%) $< -o $@

$(GFX_D_OBJ_DIR)/shader.o: $(GFX_SOURCE_DIR)/gl/shader.c $(GFX_D_ALL_HEADERS)
	$(D_CC) -c -g -Wall $(GFX_D_ALL_INCLUDES:%=-I%) $< -o $@


###############
##    Web    ##
###############

# Requires:
#  W_OBJ_DIR
#
# Provides:
#  GFX_W_LIB
#	 GFX_W_LIB_DIR
#  GFX_W_LIB_FILE
#  GFX_W_OBJS
#  GFX_W_LFLAGS

GFX_W_EXPORTED_FUNCTIONS=\
	_gfx_script_loaded

GFX_W_OBJ_DIR=$(W_OBJ_DIR)/graphics

GFX_W_LIB=graphics
GFX_W_LIB_DIR=$(GFX_W_OBJ_DIR)
GFX_W_LIB_FILE=$(GFX_W_LIB_DIR)/libgraphics.a

GFX_SOURCE_DIR=$(GFX_DIR)/source

_GFX_W_LOCAL_HEADERS=
GFX_W_LOCAL_HEADERS=$(_GFX_W_LOCAL_HEADERS:%=$(GFX_SOURCE_DIR)/%)

GFX_W_SOURCE= \
	canvas/graphics.c

_GFX_W_OBJS= \
	graphics.o
GFX_W_OBJS=$(_GFX_W_OBJS:%=$(GFX_W_OBJ_DIR)/%)

GFX_W_SCRIPT_SRC=$(GFX_DIR)/resources/graphics.js
GFX_W_SCRIPT_DST=$(W_APP_DIR)/graphics.js

GFX_W_ALL_HEADERS=$(GFX_HEADERS) $(GFX_LOCAL_HEADERS) $(GFX_W_LOCAL_HEADERS)
GFX_W_ALL_INCLUDES=$(GFX_INCLUDES) $(GFX_LOCAL_INCLUDES)

libgraphics_web: $(GFX_W_OBJ_DIR) $(GFX_W_LIB_FILE) $(GFX_W_SCRIPT_DST)

$(GFX_W_SCRIPT_DST): $(GFX_W_SCRIPT_SRC)
	cp $< $@

$(GFX_W_OBJ_DIR):
	mkdir -p $@

$(GFX_W_LIB_FILE): $(GFX_W_OBJS)
	$(AR) rcs $@ $^

$(GFX_W_OBJ_DIR)/graphics.o: $(GFX_SOURCE_DIR)/canvas/graphics.c $(GFX_W_ALL_HEADERS)
	$(W_CC) -c -Wall $(GFX_W_ALL_INCLUDES:%=-I%) $< -o $@
