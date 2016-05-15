/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __RENDERINGENGINE_H_
#define __RENDERINGENGINE_H_

#pragma warning( disable : 4251 )

#include "RE\system\REDefinitions.h" //ReEng basic Definitions
#include "RE\system\SystemSingleton.h" //System related methods

#include "RE\system\WindowClass.h" //WinAPI encapsulated methods
#include "RE\system\FileReaderClass.h" //Reads an object and returns lines as strings
#include "RE\system\FolderSingleton.h" //Sets the working directory
#include "RE\system\GLSystemSingleton.h" //OpenGL 2.0 and 3.0 initialization

#include "RE\system\ShaderManagerSingleton.h" //Shader Manager, loads and manages different shader files
#include "RE\system\ShaderCompiler.h" //Compiles the shader objects

#include "RE\light\LightManagerSingleton.h" //Manages the light sources of the world

#include "RE\materials\MaterialManagerSingleton.h" //Manages the materials
#include "RE\materials\TextureManagerSingleton.h" //Manages the Textures, loads, display and release

#include "RE\Animation\AnimationClass.h" //Manages the animations in a model
#include "RE\Animation\FrameClass.h" //Manages the transformations of a model in a frame of time
#include "RE\Animation\SequenceClass.h" //Manages the starting and ending point of an animation
#include "RE\Animation\StateClass.h" //Manages the current state of the model

#include "RE\Mesh\MeshDrawerSingleton.h" //Singleton for drawing Meshes
#include "RE\Mesh\TextSingleton.h" //Singleton for drawing Text on the screen
#include "RE\Mesh\MeshManagerSingleton.h" //Singleton for drawing Meshes
#include "RE\Mesh\PrimitiveManagerSingleton.h" //Creates and manages the Primitive objects
#include "RE\Mesh\ModelManagerSingleton.h" //Manages models and instances

#include "RE\Physics\OctantClass.h"//Manages the octants

#include "RE\Camera\CameraManagerSingleton.h" //Creates and manages the camera object for the world

/*
 MapValue
USAGE: Will map a value from an original scale to a new scale
ARGUMENTS:
	T valueToMap -> input value
	T originalScale_min ->  Start of the original scale
	T originalScale_max -> End of the original scale
	T mappedScale_min -> Start of the new scale
	T mappedScale_max -> end of the new scale
OUTPUT: returns the mapped value
*/
template <class T>
static T MapValue(T valueToMap, T originalScale_min, T originalScale_max, T mappedScale_min, T mappedScale_max)
{
	return (valueToMap - originalScale_min) * (mappedScale_max - mappedScale_min) / (originalScale_max - originalScale_min) + mappedScale_min;
}
/*
 MapVector
USAGE: Will return a vector mapped in the mappedScale range from a value vectorToMap in the OriginalScale range
ARGUMENTS:
	vector3 vectorToMap -> input vector
	vector3 originalScaleVectorMin -> Start of the original vector
	vector3 originalScaleVectorMax -> End of the original vector
	vector3 mappedScaleVectorMin -> Start of the new vector
	vector3 mappedScaleVectorMax -> End of the new vector
OUTPUT: returns the mapped vector
*/
static vector3 MapVector(vector3 vectorToMap, vector3 originalScaleVectorMin, vector3 originalScaleVectorMax,
	vector3 mappedScaleVectorMin, vector3 mappedScaleVectorMax)
{
	vector3 v3Output;
	v3Output.x = MapValue(vectorToMap.x, originalScaleVectorMin.x, originalScaleVectorMax.x, mappedScaleVectorMin.x, mappedScaleVectorMax.x);
	v3Output.y = MapValue(vectorToMap.y, originalScaleVectorMin.y, originalScaleVectorMax.y, mappedScaleVectorMin.y, mappedScaleVectorMax.y);
	v3Output.z = MapValue(vectorToMap.z, originalScaleVectorMin.z, originalScaleVectorMax.z, mappedScaleVectorMin.z, mappedScaleVectorMax.z);
	return v3Output;
}
/*
 ToMatrix4
USAGE: Will take a glm::quat and return a glm::mat4 wrapping glm::mat4_cast
ARGUMENTS: 
	quaternion a_qInput -> quaternion to translate from
OUTPUT: matrix4 conversion of a_qInput
*/
static matrix4 ToMatrix4(quaternion a_qInput)
{
	return glm::mat4_cast(a_qInput);
}

/*
 ReleaseAllSingletons
USAGE: Releases all ReEngine Singletons
ARGUMENTS: ---
OUTPUT: ---
*/
static void ReleaseAllSingletons(void)
{
	LightManagerSingleton::ReleaseInstance();
	MaterialManagerSingleton::ReleaseInstance();
	TextureManagerSingleton::ReleaseInstance();
	ModelManagerSingleton::ReleaseInstance();
	CameraManagerSingleton::ReleaseInstance();
	FolderSingleton::ReleaseInstance();
	GLSystemSingleton::ReleaseInstance();
	ShaderManagerSingleton::ReleaseInstance();
	SystemSingleton::ReleaseInstance();
	PrimitiveManagerSingleton::ReleaseInstance();
	MeshManagerSingleton::ReleaseInstance();
	TextSingleton::ReleaseInstance();
	MeshDrawerSingleton::ReleaseInstance();
}
#endif //__RENDERINGENGINE_H__