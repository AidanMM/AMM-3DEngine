/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __EXAMPLECLASS_H_
#define __EXAMPLECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL ExampleClass
{
	uint m_uDataCount = 0; //Number of elements in the list of elements
	std::vector<int> m_lData; //list of elements

public:
	/*
	 ExampleClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	ExampleClass(void);
	/*
	 ExampleClass
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	ExampleClass(ExampleClass const& other);
	/*
	 operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	ExampleClass& operator=(ExampleClass const& other);
	/*
	 ~ExampleClass
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ExampleClass(void);

	/*
	 Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(ExampleClass& other);

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
	/* Property */
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
	 Release
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	 Init
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<ExampleClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<ExampleClass*>;

}

#endif //__EXAMPLECLASS_H__