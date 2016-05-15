#pragma once

#include <windows.h>
#include <XInput.h>
#include <math.h>;

#pragma comment(lib, "XInput.lib")

class XboxControls
{
private:
	XINPUT_STATE m_controllerState;
	int m_controllerNum;
public:
	XboxControls(int playerNumber); // Constructor
	XINPUT_STATE GetState();		// Returns the state of the controler (what buttons are being pressed);
	bool IsConnected();				// returns if the controller is connected
	void Vibrate(int leftVal = 0, int rightVal = 0);	// vibrates the controller
};