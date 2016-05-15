/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __ExampleSingleton_H_
#define __ExampleSingleton_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL ExampleSingleton
{
	uint m_uDataCount = 0; //number of elements in the list
	static ExampleSingleton* m_pInstance; // Singleton pointer
	std::vector<int> m_lData; //list of elements
public:
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static ExampleSingleton* GetInstance();
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetData(void);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetData(int a_nData = 1);
	/* Property GetData/SetData */
	//__declspec(property(get = GetData, put = SetData)) int Data;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetDataOnVector(int a_nData);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int& GetDataOnVector(int a_nIndex);

private:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	ExampleSingleton(void);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ExampleSingleton(ExampleSingleton const& other);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ExampleSingleton& operator=(ExampleSingleton const& other);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ExampleSingleton(void);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}

#endif //__EXAMPLECLASS_H__