/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FOLDERSINGLETON_H_
#define __FOLDERSINGLETON_H_

#include <string>
#include <Windows.h>

#include "RE\system\REDefinitions.h" //ReEng basic Definitions

namespace ReEng
{

typedef std::string String;
class ReEngDLL FolderSingleton
{
	String m_sRoot = "";
	String m_sData = "";
	String m_s3DS = "";
	String m_sBTO = "";
	String m_sPOM = "";
	String m_sFBX = "";
	String m_sOBJ = "";
	String m_sLVL = "";
	String m_sTextures = "";
	String m_sShaders = "";
	String m_sAddOn = "";

	static FolderSingleton* m_pInstance;
public:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	static FolderSingleton* GetInstance(void);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	static void ReleaseInstance();	//Singleton Destructor
	
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderRoot(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderRoot(void);
	//__declspec(property(put = SetFolderRoot, get = GetFolderRoot)) String Root;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderData(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderData(void);
	//__declspec(property(put = SetFolderData, get = GetFolderData)) String Data;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderM3DS(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderM3DS(void);
	//__declspec(property(put = SetFolderM3DS, get = GetFolderM3DS)) String M3DS;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMBTO(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMBTO(void);
	//__declspec(property(put = SetFolderMBTO, get = GetFolderMBTO)) String MBTO;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMPOM(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMPOM(void);
	//__declspec(property(put = SetFolderMPOM, get = GetFolderMPOM)) String MPOM;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMFBX(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMFBX(void);
	//__declspec(property(put = SetFolderMFBX, get = GetFolderMFBX)) String MFBX;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMOBJ(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMOBJ(void);
	//__declspec(property(put = SetFolderMOBJ, get = GetFolderMOBJ)) String MOBJ;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderLVL(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderLVL(void);
	//__declspec(property(put = SetFolderLVL, get = GetFolderLVL)) String LVL;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderTextures(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderTextures(void);
	//__declspec(property(put = SetFolderTextures, get = GetFolderTextures)) String Textures;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderShaders(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderShaders(void);
	//__declspec(property(put = SetFolderShaders, get = GetFolderShaders)) String Shaders;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderAddOn(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderAddOn(void);
	//__declspec(property(put = SetFolderAddOn, get = GetFolderAddOn)) String AddOn;

private:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	FolderSingleton(void);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	FolderSingleton(const FolderSingleton& other);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	FolderSingleton& operator=(const FolderSingleton& other);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~FolderSingleton(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetRealProgramPath(void);
};

}

#endif //__FOLDERSINGLETON_H_
