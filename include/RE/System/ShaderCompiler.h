/*----------------------------------------------
From: http://www.opengl-tutorial.org/
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/

#ifndef __SHADERCOMPILER_H_
#define __SHADERCOMPILER_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include "RE\system\REDefinitions.h" //ReEng basic Definitions

/*

USAGE:
ARGUMENTS:
OUTPUT:
*/
ReEngDLL GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);


#endif //__SHADER_H__
