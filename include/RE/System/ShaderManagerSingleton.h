/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SHADERMANAGERSINGLETON_H_
#define __SHADERMANAGERSINGLETON_H_

#include "RE\system\ShaderClass.h"
#include <vector>
#include <assert.h>
#include <map>
namespace ReEng
{

//System Class
class ReEngDLL ShaderManagerSingleton
{
	uint m_uShaderCount = 0; //Number of shaders

	static ShaderManagerSingleton* m_pInstance; // Singleton
	
	std::vector<ShaderClass> m_vShader; //vector of shaders
	std::map<String, int> m_map;//Indexer of Shaders

public:
	/* Singleton accessor */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static ShaderManagerSingleton* GetInstance();

	/* Singleton Release */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	
	/* Compiles a shader program and returns the OpenGL identifier */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	/* Asks the manager for the OpenGL identifier for the specified name*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint GetShaderID(String a_sName);

	/* Asks the manager for the OpenGL identifier for the specified index*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint GetShaderID(uint a_nIndex);

	/* Ask for the Index in the vector of the specified shader name*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyShader(String a_sName);

private:
	/* Constructor */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	ShaderManagerSingleton(void);

	/* Copy Constructor */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ShaderManagerSingleton(ShaderManagerSingleton const& other);

	/* Copy Assignment Operator */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ShaderManagerSingleton& operator=(ShaderManagerSingleton const& other);

	/* Destructor */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ShaderManagerSingleton(void);

	/* Release Memory */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/* Initialize variables */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}
#endif //__SHADERMANAGERSINGLETON_H_