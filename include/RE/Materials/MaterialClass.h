/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MATERIALCLASS_H_
#define __MATERIALCLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\materials\TextureManagerSingleton.h"

namespace ReEng
{

class ReEngDLL MaterialClass
{
	SystemSingleton* m_pSystem = nullptr;
	TextureManagerSingleton* m_pTextureMngr = nullptr;

	GLuint m_nMapDiffuse = 0;
	GLuint m_nMapNormal = 0;
	GLuint m_nMapSpecular = 0;

	vector3 m_vKd;

	String m_sName = "NULL";
	String m_sMapDiffuse = "NULL";
	String m_sMapNormal = "NULL";
	String m_sMapSpecular = "NULL";
	
public:
	/*
	 MaterialClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MaterialClass(String a_sName);
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialClass(const MaterialClass& other);
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialClass& operator=(const MaterialClass& other);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MaterialClass(void);
	
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetName(String a_sName);
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	String	GetName(void);
	//__declspec(property(put = SetName, get = GetName)) String Name;

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetDiffuseMapName(String a_sFileName);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String	GetDiffuseMapName(void);
	//__declspec(property(put = SetDiffuseMapName, get = GetDiffuseMapName)) String DiffuseMapName;

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetNormalMapName(String a_sFileName);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String	GetNormalMapName(void);
	//__declspec(property(put = SetNormalMapName, get = GetNormalMapName)) String NormalMapName;

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetSpecularMapName(String a_sFileName);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String	GetSpecularMapName(void);
	//__declspec(property(put = SetSpecularMapName, get = GetSpecularMapName)) String SpecularMapName;

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint	GetDiffuseMap(void);
	//__declspec(property(get = GetDiffuseMap)) GLuint DiffuseMap;

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint	GetNormalMap(void);
	//__declspec(property(get = GetNormalMap)) GLuint NormalMap;

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint	GetSpecularMap(void);
	//__declspec(property(get = GetSpecularMap)) GLuint SpecularMap;

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetDiffuse(vector3 a_Kd);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3	GetDiffuse(void);
	//__declspec(property(put = SetDiffuse, get = GetDiffuse)) vector3 Kd;

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadDiffuse(String a_sFileName);

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadNormal(String a_sFileName);

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadSpecular(String a_sFilename);

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	REERRORS LoadMaps(void);
private:
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}
#endif //_EMPTY_H