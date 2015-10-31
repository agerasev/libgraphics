###########
# Desktop #
###########

# Requires:
#  GFX_DIR
#  GFX_D_OBJ_DIR

# Provides:
#  GFX_HEADERS
#  GFX_INCLUDES
#  GFX_D_LIB
#	 GFX_D_LIB_DIR
#  GFX_D_LIB_FILE
#  GFX_D_LINK_LIBS

_GFX_HEADERS= \
	graphics.h \
	graphics.hpp
GFX_HEADERS=$(_GFX_HEADERS:%=$(GFX_DIR)/include/graphics/%)

GFX_D_OBJ_DIR=$(D_OBJ_DIR)/graphics

GFX_D_LIB='graphics'
GFX_D_LIB_DIR=$(GFX_D_OBJ_DIR)
GFX_D_LIB_FILE=$(GFX_D_LIB_DIR)/libgraphics.a
GFX_D_LINK_LIBS=GL GLEW

GFX_INCLUDES=$(GFX_DIR)/include

GFX_SOURCE_DIR=$(GFX_DIR)/source

_GFX_LOCAL_HEADERS= \
	shader.h \
	shader_source.h
GFX_LOCAL_HEADERS=$(_GFX_LOCAL_HEADERS:%=$(GFX_SOURCE_DIR)/%)

GFX_SOURCE= \
	graphics.c \
	shader.c

_GFX_D_OBJS= \
	graphics.o \
	shader.o
GFX_D_OBJS=$(_GFX_D_OBJS:%=$(GFX_D_OBJ_DIR)/%)

GFX_ALL_HEADERS=$(GFX_HEADERS) $(GFX_LOCAL_HEADERS)
GFX_ALL_INCLUDES=$(GFX_INCLUDES)

.phony: libgraphics_desktop

libgraphics_desktop: $(GFX_D_OBJ_DIR) $(GFX_D_LIB_FILE)

$(GFX_D_OBJ_DIR):
	mkdir -p $@

$(GFX_D_LIB_FILE): $(GFX_D_OBJS)
	$(AR) rcs $@ $^

$(GFX_D_OBJ_DIR)/graphics.o: $(GFX_SOURCE_DIR)/graphics.c $(GFX_ALL_HEADERS)
	$(D_CC) -c -Wall $(GFX_ALL_INCLUDES:%=-I%) $< -o $@

$(GFX_D_OBJ_DIR)/shader.o: $(GFX_SOURCE_DIR)/shader.c $(GFX_ALL_HEADERS)
	$(D_CC) -c -Wall $(GFX_ALL_INCLUDES:%=-I%) $< -o $@
