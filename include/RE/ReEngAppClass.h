/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/05 (Last Modified on 2015/11)
----------------------------------------------*/
#ifndef __REENGAPPCLASS_H_
#define __REENGAPPCLASS_H_
#pragma warning(disable:4251)
#include "RE\ReEng.h"
#include <locale>
#include <codecvt>
#include <string>

#ifndef FBXSDK_SHARED
#define FBXSDK_SHARED
#endif

/* Winapi callback for the window */
ReEngDLL LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ReEng
{

	class ReEngDLL ReEngAppClass
	{
	protected:
		bool m_bUsingConsole = false;//Using console flag
		bool m_bFPC = false;// First Person Camera flag
		bool m_bArcBall = false;// Arcball flag

		float m_dMinDelta = 0.0166f;//Minimum reason of change

		std::pair<int, int> m_selection = std::pair<int, int>(-1, -1); //Selection in the scene

		int m_nCmdShow;	// Number of starting commands on startup
		HINSTANCE m_hInstance; // Windows application Instance
		LPWSTR m_lpCmdLine; // Command line arguments

		//Standard variables
		SystemSingleton* m_pSystem = nullptr;// Singleton of the system

		WindowClass* m_pWindow = nullptr;// Window class
		GLSystemSingleton* m_pGLSystem = nullptr;// Singleton of the OpenGL rendering context

		LightManagerSingleton* m_pLightMngr = nullptr;// Singleton for the Light Manager
		MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager
		CameraManagerSingleton* m_pCameraMngr = nullptr; // Singleton for the camera that represents our scene

		vector4 m_v4ClearColor; //Color of the scene
		quaternion m_qArcBall; //ArcBall quaternion

	public:

		static ReEngAppClass* m_pSelfPointer; //Used for callbacks
		/*
		USAGE: Initializes the object
		ARGUMENTS: ReEngAppClass
		- HINSTANCE hInstance -> Instance of the window
		- LPWSTR lpCmdLine -> Command line
		- int nCmdShow -> Number or arguments
		- bool a_bConsole = false -> create command window flag
		OUTPUT: instance object
		*/
		ReEngAppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bConsole = false) : m_hInstance(hInstance), m_lpCmdLine(lpCmdLine), m_nCmdShow(nCmdShow), m_bUsingConsole(a_bConsole){}
		/*
		USAGE: Destroys instance
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~ReEngAppClass(void){Release();}
		/*
		USAGE: Runs the main loop of this class DO NOT OVERRIDE
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void Run(void) final
		{
			//Initialize the system with the fields recollected by the constructor
			Init(m_hInstance, m_lpCmdLine, m_nCmdShow, m_bUsingConsole);

			//Run the main loop until the exit message is sent
			MSG msg = { 0 };
			DWORD dCumulative = 0;
			DWORD dLastTime = GetTickCount();
			while (WM_QUIT != msg.message)
			{
				//Peek the message send by windows and do something dispatch it
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else //If no message was sent continue the regular fields
				{
					DWORD dCurrentTime = GetTickCount();//Current time in the clock
					DWORD dDeltaTime = dCurrentTime - dLastTime; //Calculate the dif between calls
					dLastTime = dCurrentTime; //Set the last time the method was call
			
					dCumulative += dDeltaTime;//Calculate the cumulative time
					if (static_cast<float>(dCumulative/1000.0f) >= m_dMinDelta) //if more than the minimum delta time has passed
					{
						if (GetFocus() != NULL) //If the window is focused...
						{
							ProcessKeyboard(); //Check for keyboard input
							ProcessMouse(); //Check for mouse input
							ProcessJoystick(); //Check for Joystick input
						}
						Update(); //Update the scene
						Display(); //Display the changes on the scene

						dCumulative = dDeltaTime; //reset cumulative time
					}

					
				}
				Idle(); //Every cycle execute idle code.
			}
		}
		/*
		USAGE: This will process windows messages received from the Windows callback
		ARGUMENTS:
		- HWND hwnd -> Window handle
		- UINT msg -> message
		- WPARAM wParam ->  wParam
		- LPARAM lParam -> lParam
		OUTPUT:
		*/
		virtual LRESULT ProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			//Callbacks for winapi 
			switch (msg)
			{
			case WM_SIZE: //if the windows changed size
				if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED) //if it was either maximized or minimized
				{
					Reshape(); //Resize the viewport
				}
				break;
			case WM_EXITSIZEMOVE: //if the window is RE_DONE resized by the edges
				Reshape(); //resize the viewport
				break;
			case WM_CLOSE: // if the close message was sent
				DestroyWindow(hwnd); //destroy the window
				break;
			case WM_DESTROY:// if the destroy message was sent
				PostQuitMessage(0); //post the quit message to the message manager
				break;
			}
			return 0; //end the program
		}
		/*
		USAGE: Clears the OpenGL screen by the specified color
		ARGUMENTS:
		- vector4 a_v4ClearColor = vector4(-1.0f) -> the color of the clear window, if vec4 of -1s
		will use the initial color without changing it
		OUTPUT: ---
		*/
		void ClearScreen(vector4 a_v4ClearColor = vector4(-1.0f))
		{
			if (a_v4ClearColor != vector4(-1.0f))
			{
				m_v4ClearColor = a_v4ClearColor;
				glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
		}

	private:
		/*
		USAGE: Can't be defined
		ARGUMENTS:
		- ReEngAppClass const& input -> object to instance
		OUTPUT: instance
		*/
		ReEngAppClass(ReEngAppClass const& input);
		/*
		USAGE: Cant be defined
		ARGUMENTS:
		- ReEngAppClass const& input -> object to copy
		OUTPUT: ---
		*/
		ReEngAppClass& operator=(ReEngAppClass const& input);
		/*
		USAGE: Resizes the window DO NOT OVERRIDE
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void Reshape(void) final
		{
			m_pWindow->CalculateWindowSize(); //Ask WinApi for the window size and store it in System
			int nWidth = m_pWindow->GetWidth(); //Get the width of the window
			int nHeight = m_pWindow->GetHeight();//Get the height of the window
			printf("Window size: [%d, %d]\n", nWidth, nHeight);//inform the new window size
			glViewport(0, 0, nWidth, nHeight);//resize the viewport
		}
		/*
		USAGE: Initializes the ReEng window and rendering context DO NOT OVERRIDE
		ARGUMENTS:
		- HINSTANCE hInstance -> Window instance
		- LPWSTR lpCmdLine -> command arguments
		- int nCmdShow -> number or arguments
		- bool a_bUsingConsole -> console window creation flag
		OUTPUT: ---
		*/
		virtual void Init(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole) final
		{
			// Get the system singleton
			m_pSystem = SystemSingleton::GetInstance();

			SetMaxFramerate(60.0f);

			m_pSystem->SetUsingConsole(a_bUsingConsole);
			// Is this RE_RUNNING within Visual Studio?
			if (IsDebuggerPresent())
			{
				system("cmd.exe /C xcopy \"../include/RE/Shaders\" \"Shaders\" /y /q");//copy the shader to the right folder
				m_pSystem->SetUsingConsole(true); //set the console creation flag to true
			}
			if (m_pSystem->GetUsingConsole()) //If using the window
			{
				m_pWindow->CreateConsoleWindow();//create a new console window
			}

			m_pSelfPointer = this; //make the shared pointer of the class object point to this object

			//Light manager
			m_pLightMngr = LightManagerSingleton::GetInstance();

			// Init the App System
			InitWindow("Rendering Engine");

			// Read the configuration file
			ReadConfig();

#pragma region Window Construction and Context setup
			// Create a new window and set its properties
			m_pWindow = new WindowClass(hInstance, nCmdShow, WndProc);
			m_pWindow->SetFullscreen(m_pSystem->IsWindowFullscreen());//set the window to fullscreen?
			m_pWindow->SetBorderless(m_pSystem->IsWindowBorderless());//Set the window to borderless?

			// Make the Window name a wide string
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wide = converter.from_bytes(m_pSystem->GetWindowName());

			// Create a window in the window class
			m_pWindow->CreateMEWindow(wide.c_str(), m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight());

			// Get the instance of the class
			m_pGLSystem = GLSystemSingleton::GetInstance();

			// Set OPENGL 3.x Context
			m_pSystem->m_RenderingContext = OPENGL3X;

			// Create context
			m_pGLSystem->InitGLDevice(m_pWindow->GetHandler());

			// Verify what is the OpenGL rendering context and save it to system (3.x might fail, in which case exit)
			if (m_pGLSystem->IsNewOpenGLRunning() == false)
				exit(0);
#pragma endregion			
			//Ambient light (Ambient Light is always the first light, or light[0])
			m_pLightMngr->SetPosition(glm::vec3(0, 0, 0), 0);
			m_pLightMngr->SetIntensity(0.75f, 0);
			m_pLightMngr->SetColor(glm::vec3(1, 1, 1), 0);

			//Point Light (light[1])
			m_pLightMngr->SetPosition(glm::vec3(0, 0, 10), 1);
			m_pLightMngr->SetIntensity(5.00f, 1);
			m_pLightMngr->SetColor(glm::vec3(1, 1, 1), 1);

			// Initializing the Mesh manager
			m_pMeshMngr = MeshManagerSingleton::GetInstance();
			
			// Setting the camera position.
			m_pCameraMngr = CameraManagerSingleton::GetInstance();
			m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 10.0f));

			// Initialize the App Variables
			InitVariables();

			//Color of the window
			if (m_pSystem->m_RenderingContext == OPENGL3X)
				glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);

			//Start the clock
			m_pSystem->StartClock();

			printf("\n");
		}

	protected:
		/*
		USAGE: Process the arcball of the scene, rotating an object in the center of it	a_fSensitivity is
		a factor of change DO NOT OVERRIDE
		ARGUMENTS:
		- float a_fSensitivity = 0.1f -> indicates how fast the arcball is going to change
		OUTPUT: ---
		*/
		virtual void ArcBall(float a_fSensitivity = 0.1f) final
		{
			//If the arcball is not enabled return
			if (!m_bArcBall)
				return;

			//static quaternion qArcBall;
			UINT	MouseX, MouseY;		// Coordinates for the mouse
			UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

			//Initialize the position of the pointer to the middle of the screen
			CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
			CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;
			
			//Calculate the position of the mouse and store it
			POINT pt;
			GetCursorPos(&pt); 
			MouseX = pt.x;
			MouseY = pt.y;

			//Calculate the difference in position and update the quaternion orientation based on it
			float DeltaMouse;
			if (MouseX < CenterX)
			{
				DeltaMouse = static_cast<float>(CenterX - MouseX);
				m_qArcBall = quaternion(vector3(0.0f, glm::radians(a_fSensitivity * DeltaMouse), 0.0f)) * m_qArcBall;
			}
			else if (MouseX > CenterX)
			{
				DeltaMouse = static_cast<float>(MouseX - CenterX);
				m_qArcBall = quaternion(vector3(0.0f, glm::radians(-a_fSensitivity * DeltaMouse), 0.0f)) * m_qArcBall;
			}

			if (MouseY < CenterY)
			{
				DeltaMouse = static_cast<float>(CenterY - MouseY);
				m_qArcBall = quaternion(vector3(glm::radians(-a_fSensitivity * DeltaMouse), 0.0f, 0.0f)) * m_qArcBall;
			}
			else if (MouseY > CenterY)
			{
				DeltaMouse = static_cast<float>(MouseY - CenterY);
				m_qArcBall = quaternion(vector3(glm::radians(a_fSensitivity * DeltaMouse), 0.0f, 0.0f)) * m_qArcBall;
			}

			SetCursorPos(CenterX, CenterY);//Position the mouse in the center
			//return qArcBall; // return the new quaternion orientation
		}
		/*
		USAGE: Manages the rotation of the camera a_fSpeed is a factor of change DO NOT OVERRIDE
		ARGUMENTS:
		- float a_fSpeed = 0.005f
		OUTPUT: ---
		*/
		virtual void CameraRotation(float a_fSpeed = 0.005f) final
		{
			UINT	MouseX, MouseY;		// Coordinates for the mouse
			UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

			//Initialize the position of the pointer to the middle of the screen
			CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
			CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

			//Calculate the position of the mouse and store it
			POINT pt;
			GetCursorPos(&pt);
			MouseX = pt.x;
			MouseY = pt.y;

			//Calculate the difference in view with the angle
			float fAngleX = 0.0f;
			float fAngleY = 0.0f;
			float fDeltaMouse = 0.0f;
			if (MouseX < CenterX)
			{
				fDeltaMouse = static_cast<float>(CenterX - MouseX);
				fAngleY += fDeltaMouse * a_fSpeed;
			}
			else if (MouseX > CenterX)
			{
				fDeltaMouse = static_cast<float>(MouseX - CenterX);
				fAngleY -= fDeltaMouse * a_fSpeed;
			}

			if (MouseY < CenterY)
			{
				fDeltaMouse = static_cast<float>(CenterY - MouseY);
				fAngleX -= fDeltaMouse * a_fSpeed;
			}
			else if (MouseY > CenterY)
			{
				fDeltaMouse = static_cast<float>(MouseY - CenterY);
				fAngleX += fDeltaMouse * a_fSpeed;
			}
			//Change the Yaw and the Pitch of the camera
			m_pCameraMngr->ChangeYaw(fAngleY * 3.0f);
			m_pCameraMngr->ChangePitch(-fAngleX * 3.0f);
			SetCursorPos(CenterX, CenterY);//Position the mouse in the center
		}
		/*
		USAGE: Initialize ReEng variables necessary to create the window
		ARGUMENTS:
		- String a_sWindowName = "ReEng" -> Window name
		OUTPUT: ---
		*/
		virtual void InitWindow(String a_sWindowName = "ReEng")
		{
			//These are the default values for the windows construction but they will
			//not have any effect if the .cfg file is present next to the binary folder
			//(the .cfg will be created if not existent using these values, but once
			//created its values will have priority over these)

			// Indicate window properties
			m_pSystem->SetWindowName(a_sWindowName);
			m_pSystem->SetWindowWidth(1080);
			m_pSystem->SetWindowHeight(720);
			m_pSystem->SetWindowFullscreen(false);
			m_pSystem->SetWindowBorderless(false);

			// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
			//if this line is in Init Window it will depend on the .cfg file, if it
			//is on the InitVariables it will always force it regardless of the .cfg
			m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
		}
		/*
		USAGE: Reads the configuration of the application to a file
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void ReadConfig(void)
		{
			//If we are reading the changes the changes, know what file to open
			String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
			String App = m_pSystem->GetAppName();
			App = sRoot + App + ".cfg";

			FileReaderClass reader;
			//If the file doesnt exist, create it and exit this method
			if (reader.ReadFile(App.c_str()) == REERRORS::RERROR_FILE_MISSING)
			{
				WriteConfig();
				return;
			}

			//read the file for startup values
			reader.Rewind();
			while (reader.ReadNextLine() == RE_RUNNING)
			{
				String sWord = reader.GetFirstWord();

				int nLenght = reader.m_sLine.length();
				char* zsTemp = new char[nLenght];

				if (sWord == "Fullscreen:")
				{
					int nValue;
					sscanf_s(reader.m_sLine.c_str(), "Fullscreen: %d", &nValue);
					if (nValue == 0)
						m_pSystem->SetWindowFullscreen(false);
					else
						m_pSystem->SetWindowFullscreen(true);
				}
				else if (sWord == "Borderless:")
				{
					int nValue;
					sscanf_s(reader.m_sLine.c_str(), "Borderless: %d", &nValue);
					if (nValue == 0)
						m_pSystem->SetWindowBorderless(false);
					else
						m_pSystem->SetWindowBorderless(true);
				}
				else if (sWord == "Resolution:")
				{
					int nValue1;
					int nValue2;
					sscanf_s(reader.m_sLine.c_str(), "Resolution: [ %d x %d ]", &nValue1, &nValue2);
					m_pSystem->SetWindowWidth(nValue1);
					m_pSystem->SetWindowHeight(nValue2);
				}
				else if (sWord == "Ambient:")
				{
					float fValueX;
					float fValueY;
					float fValueZ;
					sscanf_s(reader.m_sLine.c_str(), "Ambient: [%f,%f,%f]", &fValueX, &fValueY, &fValueZ);
					m_pLightMngr->SetColor(vector3(fValueX, fValueY, fValueZ), 0);
				}
				else if (sWord == "Background:")
				{
					float fValueX;
					float fValueY;
					float fValueZ;
					float fValueW;
					sscanf_s(reader.m_sLine.c_str(), "Background: [%f,%f,%f,%f]", &fValueX, &fValueY, &fValueZ, &fValueW);
					m_v4ClearColor = vector4(fValueX, fValueY, fValueZ, fValueW);
				}
				else if (sWord == "AmbientPower:")
				{
					float fValue;
					sscanf_s(reader.m_sLine.c_str(), "AmbientPower: %f", &fValue);
					m_pLightMngr->SetIntensity(fValue, 0);
				}
				else if (sWord == "Data:")
				{
					sscanf_s(reader.m_sLine.c_str(), "Data: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderData(zsTemp);
				}
				else if (sWord == "3DS:")
				{
					sscanf_s(reader.m_sLine.c_str(), "3DS: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderM3DS(zsTemp);
				}
				else if (sWord == "BTO:")
				{
					sscanf_s(reader.m_sLine.c_str(), "BTO: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderMBTO(zsTemp);
				}
				else if (sWord == "FBX:")
				{
					sscanf_s(reader.m_sLine.c_str(), "FBX: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderMFBX(zsTemp);
				}
				else if (sWord == "OBJ:")
				{
					sscanf_s(reader.m_sLine.c_str(), "OBJ: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderMOBJ(zsTemp);
				}
				else if (sWord == "POM:")
				{
					sscanf_s(reader.m_sLine.c_str(), "POM: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderMPOM(zsTemp);
				}
				else if (sWord == "Level:")
				{
					sscanf_s(reader.m_sLine.c_str(), "Level: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderLVL(zsTemp);
				}
				else if (sWord == "Textures:")
				{
					sscanf_s(reader.m_sLine.c_str(), "Textures: %s", zsTemp, nLenght);
					m_pSystem->m_pFolder->SetFolderTextures(zsTemp);
				}

				delete[] zsTemp;
				zsTemp = nullptr;
			}
			reader.CloseFile();
		}
		/*
		USAGE: Writes the configuration of the application to a file
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void WriteConfig(void)
		{
			// Write the configuration for this application
			String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
			String App = m_pSystem->GetAppName();
			App = sRoot + App + ".cfg";

			FILE *pFile;
			fopen_s(&pFile, App.c_str(), "w");
			if (!pFile)	//If we couldn't create the file we exit without changes.
				return;

			//Save default values for a config file
			rewind(pFile);
			fprintf(pFile, "# Configuration file for the program: %s", m_pSystem->GetAppName().c_str());

			fprintf(pFile, "\n\nFullscreen: ");
			if (m_pSystem->IsWindowFullscreen())
				fprintf(pFile, "1");
			else
				fprintf(pFile, "0");

			fprintf(pFile, "\nBorderless: ");
			if (m_pSystem->IsWindowBorderless())
				fprintf(pFile, "1");
			else
				fprintf(pFile, "0");

			fprintf(pFile, "\nContext: OPENGL3X"); //Only openGL3X context is supported ATM

			fprintf(pFile, "\n\n# Resolution: [ 640 x 480 ]");
			fprintf(pFile, "\n# Resolution: [ 1280 x 720 ]");
			fprintf(pFile, "\n# Resolution: [ 1680 x 1050 ]");
			fprintf(pFile, "\n# Resolution: [ 1920 x 1080 ]");
			fprintf(pFile, "\n# Resolution: [ 2650 x 1440 ]");
			fprintf(pFile, "\nResolution: [ %d x %d ]", m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight());

			fprintf(pFile, "\n\nAmbient: [%.2f,%.2f,%.2f]",
				m_pLightMngr->GetColor(0).r, m_pLightMngr->GetColor(0).g, m_pLightMngr->GetColor(0).b);
			fprintf(pFile, "\nAmbientPower: %.2f", m_pLightMngr->GetIntensity(0));

			fprintf(pFile, "\n\nBackground: [%.3f,%.3f,%.3f,%.3f]",
				m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);

			fprintf(pFile, "\n\n# Folders:");

			fprintf(pFile, "\nData:		%s", m_pSystem->m_pFolder->GetFolderData().c_str());
			fprintf(pFile, "\n3DS:		%s", m_pSystem->m_pFolder->GetFolderM3DS().c_str());
			fprintf(pFile, "\nBTO:		%s", m_pSystem->m_pFolder->GetFolderMBTO().c_str());
			fprintf(pFile, "\nFBX:		%s", m_pSystem->m_pFolder->GetFolderMFBX().c_str());
			fprintf(pFile, "\nOBJ:		%s", m_pSystem->m_pFolder->GetFolderMOBJ().c_str());
			fprintf(pFile, "\nLevel:		%s", m_pSystem->m_pFolder->GetFolderLVL().c_str());
			fprintf(pFile, "\nTextures:	%s", m_pSystem->m_pFolder->GetFolderTextures().c_str());

			fclose(pFile);
		}
		/*
		USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
		the purpose of this member function is to initialize member variables specific for this lesson.
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void InitVariables(void){}
		/*
		USAGE:	Will initialize the maximum frame rate and the max delta frame 
		ARGUMENTS: 
		- float a_fMaxFrameRate -> maximum frame rate the system can execute
		OUTPUT: ---
		*/
		virtual void SetMaxFramerate(float a_fFrameRateLimit) final { m_dMinDelta = 1.0f / a_fFrameRateLimit; }
		/*
		USAGE: Releases the application
		IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void Release(void)
		{
			SafeDelete(m_pWindow); // destroy the allocated window
			// Release all the singletons used in the dll
			ReleaseAllSingletons();
		}
		/*
		USAGE: Updates the scene
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void Update(void)
		{
			//Update the system so it knows how much time has passed since the last call
			m_pSystem->UpdateTime();
			//Update the information on the Mesh manager I will not check for collision detection so the argument is false
			m_pMeshMngr->Update();
			//Add the sphere to the render queue
			m_pMeshMngr->AddTorusToQueue(glm::rotate(IDENTITY_M4, 90.0f, vector3(90.0f, 0.0f, 0.0f)) * ToMatrix4(m_qArcBall), RERED, SOLID | WIRE);

			//Is the arcball active?
			ArcBall();

			//Is the first person camera active?
			if (m_bFPC == true)
				CameraRotation();
			
			//Indicate the FPS
			int nFPS = m_pSystem->GetFPS();
			//print info into the console
			printf("FPS: %d            \r", nFPS);//print the Frames per Second
			//Print info on the screen
			m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
			m_pMeshMngr->Print("FPS:");
			m_pMeshMngr->Print(std::to_string(nFPS), RERED);
		}
		/*
		USAGE: Displays the scene
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void Display(void)
		{
			//clear the screen
			ClearScreen();

			//Render the grid based on the camera's mode:
			switch (m_pCameraMngr->GetCameraMode())
			{
			default: //Perspective
				m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
				break;
			case CAMERAMODE::CAMROTHOX:
				m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
				break;
			case CAMERAMODE::CAMROTHOY:
				m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
				break;
			case CAMERAMODE::CAMROTHOZ:
				m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
				break;
			}

			m_pMeshMngr->Render(); //Renders everything set up in the render queue

			m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
		}
		/*
		USAGE: Runs faster than the update
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void Idle(void) {}
		/*
		USAGE: Manage the response of key presses
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void ProcessKeyboard(void){}
		/*
		USAGE: Manage the response of key presses and mouse position
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void ProcessMouse(void){}
		/*
		USAGE: Manage the response of gamepad controllers
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		virtual void ProcessJoystick(void){}
	};

}
#endif //__REENGAPPCLASS_H_