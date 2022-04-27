#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <GL/gl.h>

typedef GLubyte Pixel[5];

GLuint load_texture(char* filename);

#endif // TEXTURE_H_INCLUDED
