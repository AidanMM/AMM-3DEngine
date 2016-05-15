/*----------------------------------------------
Adapted from http://www.swiftless.com/tutorials/opengl4/1-opengl-window.html
into a class Date: 2015/06
----------------------------------------------*/

#ifndef __GLSystemSingleton_H_
#define __GLSystemSingleton_H_

#include "RE\system\WindowClass.h"

#include <GL\glew.h>
#include <GL\wglew.h>

namespace ReEng
{

class ReEngDLL GLSystemSingleton
{
	//--Members
	HDC   m_hDC = NULL;		// Private GDI Device Context
	HGLRC m_hRC = NULL;		// Permanent Rendering Context
	float m_fGLVersion = 0.0f; // OpenGL version
	bool m_bForceOldGL = false;	// Forces OpenGL 2.1 to be initialized
public:
	//--Methods

	/*
	HRESULT InitGLDevice(HWND g_hWnd);
		Initializes the OpenGL Device Context
	ARGUMENTS:
		HWND g_hWnd -> Window Handler
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	HRESULT InitGLDevice(HWND g_hWnd);

	/*
	int DrawOldGLScene(GLvoid);
		Draws a demo scene using OpenGL 2.1 Context, used only if
		failed to initialize 3.x+ in the system
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int DrawOldGLScene(GLvoid);
	
	/*
	static GLSystemSingleton* GetInstance(void);
		Singleton Accessor, returns the singleton of this class
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	static GLSystemSingleton* GetInstance(void);

	
	/*
	void ReleaseInstance(void);
		Releases the singleton of this class
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	
	/*
	HDC GetDeviceContext(GLvoid);
		Returns the OpenGL rendering context device
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	HDC GetDeviceContext(GLvoid);

	/*
	float GetGLVersion(void);
		Returns the OpenGL Version the program is RE_RUNNING
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetGLVersion(void);

	/*
	bool IsNewOpenGLRE_RUNNING(void);
		Returns whether OpenGL3.x or newer is RE_RUNNING
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsNewOpenGLRunning(void);

	/*
	void ForceOldOpenGL(bool input = true);
		Forces OpenGL 2.1 to be used for the rendering context
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void ForceOldOpenGL(bool a_bInput = true);

	/*
	void GLSwapBuffers(void);
		SwapsvOpenGL buffer
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void GLSwapBuffers(void);

private:
	//--Methods
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLSystemSingleton(void); // Constructor
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLSystemSingleton(GLSystemSingleton const& other); //Copy Constructor
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLSystemSingleton& operator=(GLSystemSingleton const& other); // Copy Assignment Operator
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~GLSystemSingleton(void); // Destructor

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void); // Release Memory
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void); // Initialize variables
	
	static GLSystemSingleton* m_pInstance; // Singleton
};

}

#include "ShaderCompiler.h"

#endif /*__GLSystemSingleton_H__*/