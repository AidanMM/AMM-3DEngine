/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __LIGHTMANAGERSINGLETON_H_
#define __LIGHTMANAGERSINGLETON_H_

#include "RE\light\LightClass.h"
#include <vector>
#include <assert.h>

namespace ReEng
{

//System Class
class ReEngDLL LightManagerSingleton
{
	//Private Fields
	uint m_uLightCount = 0;		//Number of Lights
	float m_fAmbient = 0.0f;	//Ambient power
	static LightManagerSingleton* m_pInstance; // Singleton
	std::vector<LightClass*> m_lLight; //vector of lights

public:
	//Public Accessors
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static LightManagerSingleton* GetInstance();
	/*
	USAGE: Releases the singleton pointer
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Adds a light to the list of lights
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddLight(	vector3 a_v4Position = vector3(0.0f),
					vector3 a_v3Color = vector3(1.0f),
					float a_vIntensity = 1.0f);
	/*
	USAGE: Gets the address of a light in the list of lights
	ARGUMENTS:
	- int a_nLightIndex = 1 -> Index of the light (0 for ambient)
	OUTPUT:
	*/
	LightClass* GetLight(uint a_nLightIndex = 1);
	/*
	USAGE: Sets the position of a light in the list of lights
	ARGUMENTS:
	- vector3 a_v4Position -> spatial location of the light
	- int a_nLightIndex = 1 -> Index of the light (0 for ambient)
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v4Position, uint a_nLightIndex = 1);
	/*
	USAGE: Gets the position of a light in the list of lights
	ARGUMENTS:
	- int a_nLightIndex = 1 -> Index of the light (0 for ambient)
	OUTPUT: light position
	*/
	vector3 GetPosition(uint a_nLightIndex = 1);
	/*
	USAGE: Sets the color of a light in the list of lights
	ARGUMENTS:
	- vector3 a_v3Color -> color of the light
	- int a_nLightIndex = 1 -> Index of the light (0 for ambient)
	OUTPUT: ---
	*/
	void SetColor(vector3 a_v3Color, uint a_nLightIndex = 1);
	/*
	USAGE: Gets the color of a light in the list of lights
	ARGUMENTS:
	- int a_nLightIndex = 1 -> Index of the light (0 for ambient)
	OUTPUT: light color
	*/
	vector3 GetColor(uint a_nLightIndex = 1);
	/*
	USAGE: Sets the intensity of a light in the list of lights
	ARGUMENTS:
	- float a_fIntensity -> Intensity of the light
	- int a_nLightIndex = 1 -> Index of the light (0 for ambient)
	OUTPUT: ---
	*/
	void SetIntensity(float a_fIntensity, uint a_nLightIndex = 1);
	/*
	USAGE: Gets the intensity of a light in the list of lights
	ARGUMENTS:
	- int a_nLightIndex = 1 -> Index of the light (0 for ambient)
	OUTPUT: light intensity
	*/
	float GetIntensity(uint a_nLightIndex = 1);

private:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	LightManagerSingleton(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	LightManagerSingleton(LightManagerSingleton const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	LightManagerSingleton& operator=(LightManagerSingleton const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~LightManagerSingleton(void);
	/*
	USAGE: Releases Memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Initialize variables
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}
#endif //__LIGHTMANAGERSINGLETON_H__