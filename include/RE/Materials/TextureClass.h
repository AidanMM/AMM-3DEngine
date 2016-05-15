/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTURECLASS_H_
#define __TEXTURECLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\system\filereaderclass.h"
#include "FreeImage\FreeImage.h"

namespace ReEng
{

class ReEngDLL TextureClass
{
	GLuint m_nTextureID = 0;
	SystemSingleton* m_pSystem = nullptr;
	String m_sName = "NULL";
	String m_sFileName = "NULL";

public:
	/*
	 TextureClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	TextureClass(void); //Constructor
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	TextureClass(const TextureClass& other); //Copy Constructor
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	TextureClass& operator=(const TextureClass& other); //Copy Assignment Operator
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
	~TextureClass(void); //Destructor

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void LoadTexture(String a_sFileName);
//Accessors
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetGLTextureID(void); //Returns the OpenGL Identifier
	//__declspec(property(get = GetGLTextureID)) GLuint GLTextureID;
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetTextureName(void); //Returns the name of the texture
	//__declspec(property(get = GetTextureName)) String TextureName;
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetTextureFileName(void); //Returns the filename of the texture
	//__declspec(property(get = GetTextureFileName)) String TextureFileName;

private:
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void); //Initializes the variables
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<TextureClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<TextureClass*>;

}
#endif //_TEXTURECLASS_H