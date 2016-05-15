/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTUREMANAGERSINGLETON_H_
#define __TEXTUREMANAGERSINGLETON_H_

#include "RE\materials\TextureClass.h"
#include <vector>
#include <map>

namespace ReEng
{

class ReEngDLL TextureManagerSingleton
{
	std::map<String,int> m_map;//indexer

public:
	std::vector<TextureClass*> m_lTextures; //Vector of Textures

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static TextureManagerSingleton* GetInstance(); //Singleton Accessor
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	static void ReleaseInstance();	//Singleton Destructor
	
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyTexure(String sName); //Returns the ID number of the texture, -1 if it does not exist.
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int LoadTexture(String sName);	//Loads a texture and returns the ID of where its stored in the vector

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetTextureCount(void); //Returns the number of texures in the vector
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint ReturnGLIndex(uint a_nIndex); //Returns the OpenGL Buffer ID in the vector location of the provided Index
private:
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static TextureManagerSingleton* m_pInstance; //Singleton
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	TextureManagerSingleton(void); //Constructor	
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	TextureManagerSingleton(const TextureManagerSingleton& other); //Copy Constructor
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	TextureManagerSingleton& operator=(const TextureManagerSingleton& other);//Copy Assignment Operator
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~TextureManagerSingleton(void); //Destructor

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void); //Release the fields in the class
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void); //Initialize variables
};

}
#endif __TEXTUREMANAGERSINGLETON_H_