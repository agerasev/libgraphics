#pragma once

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#else
#include <GL/glew.h>
#endif

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

#define ATTR_VERT_HARD_SIZE 1
#define UNIF_VERT_HARD_SIZE 3
static const GLchar *ATTR_VERT_HARD[ATTR_VERT_HARD_SIZE] = {A_COORD};
static const GLchar *UNIF_VERT_HARD[UNIF_VERT_HARD_SIZE] = {U_TRANSLATION, U_PROJECTION, U_MODELVIEW};
static const GLchar *SRC_VERT_HARD = 
	GLSL_PRECISION
	"uniform vec2 "U_TRANSLATION";\n"
	"uniform mat2 "U_PROJECTION";\n"
	"uniform mat2 "U_MODELVIEW";\n"
	"attribute vec2 "A_COORD";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		V_POSITION" = "A_COORD";\n"
		"gl_Position = vec4("U_PROJECTION"*("U_MODELVIEW"*"V_POSITION" + "U_TRANSLATION"),0.0,1.0);\n"
	"}\n";

#define ATTR_VERT_SMOOTH_SIZE 1
#define UNIF_VERT_SMOOTH_SIZE 3
static const GLchar *ATTR_VERT_SMOOTH[ATTR_VERT_SMOOTH_SIZE] = {A_COORD};
static const GLchar *UNIF_VERT_SMOOTH[UNIF_VERT_SMOOTH_SIZE] = {U_TRANSLATION, U_PROJECTION, U_MODELVIEW};
static const GLchar *SRC_VERT_SMOOTH = 
	GLSL_PRECISION
	"uniform vec2 "U_TRANSLATION";\n"
	"uniform mat2 "U_PROJECTION";\n"
	"uniform mat2 "U_MODELVIEW";\n"
	"attribute vec2 "A_COORD";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		V_POSITION" = "A_COORD" + "A_COORD"*"U_PROJECTION";\n"
		"gl_Position = vec4("U_PROJECTION"*("U_MODELVIEW"*"V_POSITION" + "U_TRANSLATION"),0.0,1.0);\n"
	"}\n";

/* Uniforms */
#define U_COLOR       "uColor"
#define U_TEXTURE     "uTexture"

#define UNIF_FRAG_FILL_SIZE 1
static const GLchar *UNIF_FRAG_FILL[UNIF_FRAG_FILL_SIZE] = {U_COLOR};
static const GLchar *SRC_FRAG_FILL =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"gl_FragColor = "U_COLOR";\n"
	"}\n";

#define UNIF_FRAG_TEX_SIZE 2
static const GLchar *UNIF_FRAG_TEX[UNIF_FRAG_TEX_SIZE] = {U_COLOR,U_TEXTURE};
static const GLchar *SRC_FRAG_TEX =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"uniform sampler2D "U_TEXTURE";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"gl_FragColor = "U_COLOR"*texture2D("U_TEXTURE",vec2(0.5,-0.5)*"V_POSITION" + vec2(0.5,0.5));\n"
	"}\n";

#define UNIF_FRAG_QUAD_SIZE 2
static const GLchar *UNIF_FRAG_QUAD[UNIF_FRAG_QUAD_SIZE] = {U_COLOR,U_MODELVIEW};
static const GLchar *SRC_FRAG_QUAD =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"uniform mat2 "U_MODELVIEW";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"vec2 lBounds = vec2(length("U_MODELVIEW"*vec2(1.0,0.0)),length("U_MODELVIEW"*vec2(0.0,1.0)));\n"
		"gl_FragColor = "U_COLOR"*vec4(1.0,1.0,1.0,clamp(min(\n"
		"  lBounds.x*min(1.0 - "V_POSITION".x, 1.0 + "V_POSITION".x),\n"
		"  lBounds.y*min(1.0 - "V_POSITION".y, 1.0 + "V_POSITION".y)\n"
		"),-0.5,0.5) + 0.5);\n"
	"}\n";

#define UNIF_FRAG_CIRCLE_SIZE 2
static const GLchar *UNIF_FRAG_CIRCLE[UNIF_FRAG_CIRCLE_SIZE] = {U_COLOR,U_MODELVIEW};
static const GLchar *SRC_FRAG_CIRCLE =
	GLSL_PRECISION
	"uniform vec4 "U_COLOR";\n"
	"uniform mat2 "U_MODELVIEW";\n"
	"varying vec2 "V_POSITION";\n"
	"void main(void) {\n"
		"float lLen = length("V_POSITION");\n"
		"vec2 lNorm = "V_POSITION"/lLen;\n"
		"float lEllipseLen = length("U_MODELVIEW"*lNorm);\n"
		"gl_FragColor = "U_COLOR"*vec4(1.0,1.0,1.0,clamp((1.0 - lLen)*lEllipseLen,-0.5,0.5) + 0.5);\n"
	"}\n";

#define U_INNER_MUL "uInnerMul"

#define UNIF_FRAG_RING_SIZE 3
static const GLchar *UNIF_FRAG_RING[UNIF_FRAG_RING_SIZE] = {U_COLOR,U_MODELVIEW,U_INNER_MUL};
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
		"gl_FragColor = "U_COLOR"*vec4(1.0,1.0,1.0,clamp(min(\n"
      "(1.0 - lLen),\n"
      "(lLen - "U_INNER_MUL")\n"
    ")*lEllipseLen,-0.5,0.5) + 0.5);\n"
	"}\n";
