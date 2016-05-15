/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
	Provides a fullscreen mode and icon to 
	http://www.winprog.org/tutorial/simple_window.html 
	Adapted into a class.
Date: 2014/05
----------------------------------------------*/
#ifndef __WINDOWCLASS_H_
#define __WINDOWCLASS_H_

#include <windows.h>
#include "Resource.h"
#include "RE\system\REDefinitions.h" //ReEng basic Definitions
#include "RE\System\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL WindowClass
{
	bool m_bFullscreen = false; //Run in fullscreen mode?
	bool m_bBorderless = false; //Run with borders?
	bool m_bWindowCrated = false; //Window has been created

	int m_nCommandShow = 0; //Number of arguments

	LPCWSTR m_sWindowName; //Name of the window
	HWND m_hWindowHandler; //Window handler

	HINSTANCE m_hInstance; //Window Instance
	WNDPROC m_Callback; //Associated Callback for this window

	SystemSingleton* m_pSystem; //System singleton for ReEngine
	
public:
	/*
	Constructor
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	WindowClass(void);
	/*
	Constructor
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	WindowClass(HINSTANCE a_hInstance, int a_nCmdShow, WNDPROC a_WndProc);

	/*
	void CalculateWindowSize(void);
	Gets the window size.
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateWindowSize(void);

	/*
	void SetWindowInstance(HINSTANCE hInstance);
		Sets the window Instance
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowInstance(HINSTANCE a_hInstance);

	/*
	void SetWindowCallback(WNDPROC WndProc);
		Sets the window callback
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowCallback(WNDPROC a_WndProc);

	/*
	void SetIncomingArguments(int nCmdShow);
		Sets the number of incoming arguments
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetIncomingArguments(int a_nCmdShow);

	/*
	CreateMEWindow
		Creates window with the provided arguments
	ARGUMENTS:
		LPCWSTR windowName = L"Window" -> Name of the window
		int width = 1280 -> width of the window
		int height = 720 -> height of the window
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int CreateMEWindow(LPCWSTR a_windowName = L"Window", int a_nWidth = 1280, int a_nHeight = 720);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetWidth(void);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetHeight(void);

	/*
	GetHandler
		Returns the window handler
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	HWND GetHandler(void);

	/*
	SetFullscreen(bool input = true)
		Sets whether or not the program will run in fullscreen
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFullscreen(bool a_bInput = true);

	/*
	SetBorderless(bool input = true)
		Sets whether or not the window will be borderless
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetBorderless(bool a_bInput = true);

	/*
	void CreateConsoleWindow(void)
		Allocates a console window for output
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CreateConsoleWindow(void);

private:
	/*
	Copy Constructor
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	WindowClass(const WindowClass& other);

	/*
	Copy Assignment Operator
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	WindowClass& operator=(const WindowClass& other);

	/*
	void Init(void);
		Initializes the member variables
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}

#endif /*__WINDOWCLASS_H__*/