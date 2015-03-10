#pragma once

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#else
#include <GL/glew.h>
#endif

#define ARRAY_SIZE(array) \
	(sizeof(array)/sizeof(array[0]))

#ifdef __ANDROID__
#define GLSL_PRECISION "precision mediump float;\n"
#else
#define GLSL_PRECISION ""
#endif

/* Uniforms */
#define U_TRANSLATION "uTranslation"
#define U_PROJECTION  "uProjection"
#define U_MODELVIEW   "uModelview"

/* Attributes */
#define A_COORD       "aCoord"

/* Varyings */
#define V_POSITION    "vPosition"

static const GLchar *ATTR_VERT[] = {A_COORD};
static const GLchar *UNIF_VERT[] = {U_TRANSLATION, U_PROJECTION, U_MODELVIEW};
static const GLchar *SRC_VERT = 
	GLSL_PRECISION
	"uniform vec2 "U_TRANSLATION";\n"
	"uniform mat2 "U_PROJECTION";\n"
	"uniform mat2 "U_MODELVIEW";\n"
	"attribute vec2 "A_COORD";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		V_POSITION" = "A_COORD";\n"
		"gl_Position = vec4("U_PROJECTION"*("U_MODELVIEW"*"A_COORD" + "U_TRANSLATION"),0.0,1.0);\n"
	"}\n";

/* Uniforms */
#define U_COLOR       "uColor"

static const GLchar *UNIF_FRAG_FILL[] = {U_COLOR};
static const GLchar *SRC_FRAG_FILL =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"gl_FragColor = "U_COLOR";\n"
	"}\n";

static const GLchar *UNIF_FRAG_QUAD[] = {U_COLOR,U_MODELVIEW};
static const GLchar *SRC_FRAG_QUAD =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"uniform mat2 "U_MODELVIEW";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"vec2 lBounds = vec2(length("U_MODELVIEW"*vec2(1.0,0.0)),length("U_MODELVIEW"*vec2(0.0,1.0)));\n"
		"gl_FragColor = "U_COLOR"*(clamp(0.5*min(\n"
		"  lBounds.x*min(1.0 - "V_POSITION".x, 1.0 + "V_POSITION".x),\n"
		"  lBounds.y*min(1.0 - "V_POSITION".y, 1.0 + "V_POSITION".y)\n"
		"),-0.5,0.5) + 0.5);\n"
	"}\n";

static const GLchar *UNIF_FRAG_CIRCLE[] = {U_COLOR,U_MODELVIEW};
static const GLchar *SRC_FRAG_CIRCLE =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"uniform mat2 "U_MODELVIEW";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"float lLen = length("V_POSITION");\n"
		"vec2 lNorm = "V_POSITION"/lLen;\n"
		"float lEllipseLen = length("U_MODELVIEW"*lNorm);\n"
		"gl_FragColor = "U_COLOR"*(clamp(0.5*(1.0 - lLen)*lEllipseLen,-0.5,0.5) + 0.5);\n"
	"}\n";

#define U_INNER_MUL "uInnerMul"

static const GLchar *UNIF_FRAG_RING[] = {U_COLOR,U_MODELVIEW,U_INNER_MUL};
static const GLchar *SRC_FRAG_RING =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"uniform mat2 "U_MODELVIEW";\n"
  "uniform float "U_INNER_MUL";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"float lLen = length("V_POSITION");\n"
		"vec2 lNorm = "V_POSITION"/lLen;\n"
		"float lEllipseLen = length("U_MODELVIEW"*lNorm);\n"
		"gl_FragColor = "U_COLOR"*(clamp(min(\n"
      "0.5*(1.0 - lLen)*lEllipseLen,\n"
      "0.5*(lLen - "U_INNER_MUL")*lEllipseLen\n"
    "),-0.5,0.5) + 0.5);\n"
	"}\n";
