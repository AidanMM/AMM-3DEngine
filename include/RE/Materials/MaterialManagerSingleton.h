/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MATERIALMANAGERSINGLETON_H_
#define __MATERIALMANAGERSINGLETON_H_

#include "RE\system\SystemSingleton.h"
#include "RE\materials\MaterialClass.h"
#include <map>


namespace ReEng
{

class ReEngDLL MaterialManagerSingleton
{
	/* 
		The material vector is public for accessing speed reasons its more secure to have it as private
		and provide the right accessors for it, but its call so often that it creates overhead the other way
	*/
	std::map<String,int> m_map; //Map of the materials
	SystemSingleton* m_pSystem; //System class Pointer
	static MaterialManagerSingleton* m_pInstance; // Singleton Pointer

public:
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<MaterialClass*> m_lMaterial; //Materials Vector
	

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static MaterialManagerSingleton* GetInstance(); // Singleton Accessor
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);	//Singleton Destructor

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyMaterial(String a_sName); //Identifies the material, if found return its index -1 otherwise

	//returns the index number of the material if it created a new one, otherwise it returns the index
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int AddMaterial(String a_sName);
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int AddMaterial(MaterialClass a_InputMaterial);

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetMaterialCount(void); //Return the number of materials in the vector

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReloadMaps(void); //Tries to load all the textures for all of the materials

	/* Gets a copy of the material specified by name */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialClass GetMaterialCopy(String a_sName);

	/* Returns the memory location containing the material specified by the name */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialClass* GetMaterial(String a_sName);

	/* Returns the memory location containing the material specified by the index */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialClass* GetMaterial(uint a_nIndex);

private:
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	MaterialManagerSingleton(void); // Constructor
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialManagerSingleton(MaterialManagerSingleton const& other); //Copy Constructor
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialManagerSingleton& operator=(MaterialManagerSingleton const& other); // Copy Assignment Operator
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MaterialManagerSingleton(void); // Destructor

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void); // Release Memory
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void); // Initialize variables
};

}
#endif //_MATERIALMANAGERSINGLETON_H