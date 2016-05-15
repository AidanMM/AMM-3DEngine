/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SystemSingleton_H_
#define __SystemSingleton_H_

#include "RE\System\FolderSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL SystemSingleton
{
	bool m_bWindowFullscreen = false; // Window Fullscreen
	bool m_bWindowBorderless = false; // Window Borderless
	bool m_bMultithreaded = false; // Experimental: mutithreaded system
	bool m_bConsoleWindow = false; // Experimental: Console window init

	int m_nWindowWidth = 1280; // Window width
	int m_nWindowHeight = 720; // Window height
	int m_nWindowX = 0; // Window Position X
	int m_nWindowY = 0; // Window Position Y

	int m_nFPS = 60; //Frames per Second
	uint m_uFrameCount = 0; //Frames Passed

	static SystemSingleton* m_pInstance; // Singleton

	String m_sWindowName = "ReEng"; // Window Name
	String m_sAppName = "Application";//Name of the Application

	DWORD m_dTimerStart = 0; //Start time of the program
	DWORD m_dStartingTime = 0; //Start time of the program
	DWORD m_dLastFPS = 0; //Last time the time was called

	std::vector<DWORD> m_lClock;//clocks list
	
public:
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static SystemSingleton* GetInstance(); // Singleton accessor
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void); //Singleton Release

	// Application Name Property
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetAppName(void);
	//__declspec(property(get = GetAppName)) String ApplicationName;

	// Window Borderless Property
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowBorderless(bool a_bBorderless = true);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsWindowBorderless(void);
	//__declspec(property(get = IsWindowBorderless, put = SetWindowBorderless)) bool WindowBorderless;

	// Window Fullscreen Property
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowFullscreen(bool a_bFullscreen = true);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsWindowFullscreen(void);
	//__declspec(property(get = IsWindowFullscreen, put = SetWindowFullscreen)) bool WindowFullscreen;
	
	// Window Width Property
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowWidth(int a_nWidth);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetWindowWidth(void);
	//__declspec(property(get = GetWindowWidth, put = SetWindowWidth)) int WindowWidth;

	// Window Height Property
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowHeight(int a_nHeight);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetWindowHeight(void);
	//__declspec(property(get = GetWindowHeight, put = SetWindowHeight)) int WindowHeight;

	// WindowX Property
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowX(int a_nX);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetWindowX(void);
	//__declspec(property(get = GetWindowX, put = SetWindowX)) int WindowX;

	// WindowY Property
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowY(int a_nY);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetWindowY(void);
	//__declspec(property(get = GetWindowY, put = SetWindowY)) int WindowY;
	
	// Window Name Property
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetWindowName(String a_sWindowName);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetWindowName(void);
	//__declspec(property(get = GetWindowName, put = SetWindowName)) String WindowName;

	// Window Name Property
	/* Sets the system to be multi-threaded <<<EXPERIMENTAL>>>*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetThreaded(bool a_bMultithreaded);
	/* Asks the system if its multi-threaded*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetThreaded(void);
	//__declspec(property(get = GetThreaded, put = SetThreaded)) bool Multithreaded;


	// Asks for the value of m_bConsole
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetUsingConsole(void);

	// Asks for the value of m_bConsole
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetUsingConsole(bool a_bUsing);

	/*
	float GetWindowRatio(void);
		This will return the proportions of the window size in the system, from bottom to top of the window the value is 1,
		from left to right the value is the output of this function.
	*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetWindowRatio(void);

	// WindowX Property
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetFPS(void);
	//__declspec(property(get = GetFPS)) int FPS;

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void UpdateTime(void);//Updates the current time
	//float LapClock(void);//Checks the time difference between startclock and current call
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void StartClock(unsigned int a_nClock = 0);//Starts a time count for the specified clock
	/*
	 LapClock
	USAGE: Gets the time difference between the last time this method was called for this particular clock
	ARGUMENTS:
	OUTPUT:
	*/
	double LapClock(unsigned int a_nClock = 0);

	/*
	 AddClock
	USAGE: Adds a clock to the list and return said clock's index
	ARGUMENTS: ---
	OUTPUT: uint -> index of the new clock;
	*/
	uint AddClock(void);


	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool CountDown(float a_fTime, bool a_bRepeat = false);//counts down on the specified clock, returns true when the count is up

	FolderSingleton* m_pFolder;
	REOptions m_RenderingContext;

private:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	SystemSingleton(void); // Constructor
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	SystemSingleton(SystemSingleton const& other); //Copy Constructor
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	SystemSingleton& operator=(SystemSingleton const& other); // Copy Assignment Operator
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~SystemSingleton(void); // Destructor

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
};

}
#include "RE\System\GLSystemSingleton.h"

#endif //__SystemSingleton_H__