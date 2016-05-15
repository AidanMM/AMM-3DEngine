/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SHADERCLASS_H_
#define __SHADERCLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\system\ShaderCompiler.h"

namespace ReEng
{

class ReEngDLL ShaderClass
{
	String m_sProgramName = "NULL";
	String m_sVertexShaderName = "NULL";
	String m_sFragmentShaderName = "NULL";
	GLuint m_nProgram = 0;
public:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	ShaderClass(void);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ShaderClass(const ShaderClass& other);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ShaderClass& operator=(const ShaderClass& other);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ShaderClass(void);
	
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(ShaderClass& other);

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	//Attributes
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetProgramName(void);
	//__declspec(property(get = GetProgramName)) String Name;

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetVertexShaderName(void);
	//__declspec(property(get = GetVertexShaderName)) String VertexShader;

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFragmentShaderName(void);
	//__declspec(property(get = GetFragmentShaderName)) String FragmentShader;

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetProgramID(void);
	//__declspec(property(get = GetProgramID)) int ProgramID;

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

protected:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<ShaderClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<ShaderClass*>;

}

#endif //__SHADERCLASS_H__