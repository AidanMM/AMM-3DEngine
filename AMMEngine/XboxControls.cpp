#include "XboxControls.h"

XboxControls::XboxControls(int playerNumber)
{
	m_controllerNum = playerNumber - 1;	// sets the current controllerNum to 1 minus the player number (0 index)
}

XINPUT_STATE XboxControls::GetState()
{
	ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));	//zeroes the state

	// Get the state of the controller
	XInputGetState(m_controllerNum, &m_controllerState);

	return m_controllerState;
}

bool XboxControls::IsConnected()
{
	ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));	//zeroes the state

	// check to see if the controller is connected
	if (XInputGetState(m_controllerNum, &m_controllerState) == ERROR_SUCCESS)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void XboxControls::Vibrate(int leftVal, int rightVal)
{
	// create a vibration state
	XINPUT_VIBRATION vibrationState;

	// zero the vibration 
	ZeroMemory(&vibrationState, sizeof(XINPUT_VIBRATION));

	// Set the vibration values for each motor
	vibrationState.wLeftMotorSpeed = leftVal;
	vibrationState.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(m_controllerNum, &vibrationState);
}
