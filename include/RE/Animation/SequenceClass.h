/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SEQUENCECLASS_H_
#define __SEQUENCECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL SequenceClass
{
	bool m_bDirectAnimation = true;//Secuence going from a low to a high frame number?
	uint m_uID = 0;					//Secuence Identifier
	int m_nFirstFrame = 0;			//First frame of the secuence;
	int m_nLastFrame = 0;			//Last frame of the secuence;
	uint m_uFrameRate = 0;			//How many frames a secuence is playing
	uint m_uFrameCount = 0;			//Number of frames in this sequence;
	String m_sName = "NULL";		//Secuence Name
	
public:
	/*
	 Sequenceclass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	SequenceClass();	//Constructor
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	SequenceClass(String a_sName, int a_nID, int a_nFirstFrame, int a_nLastFrame, int a_nFrameRate);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	SequenceClass(const SequenceClass& other);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	SequenceClass& operator=(const SequenceClass& other);;
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	~SequenceClass();	//Destructor

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Init();		//Initialices variable values
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Release();		//Releases the memory and deallocate space.
	
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetID(int a_nID);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int getID(void);
	//__declspec(property(put = SetID, get = GetID)) int ID;

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetName(String a_sName);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetName(void);
	//__declspec(property(put = SetName, get = GetName)) String Name;

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetFirstFrame(int a_nFirstFrame);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetFirstFrame(void);
	//__declspec(property(put = SetFirstFrame, get = GetFirstFrame)) int FirstFrame;

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetLastFrame(int a_nLastFrame);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetLastFrame(void);
	//__declspec(property(put = SetLastFrame, get = GetLastFrame)) int LastFrame;

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetDirectAnimation(bool a_bDirectAnimation);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsDirectAnimation(void);
	//__declspec(property(put = SetDirectAnimation, get = IsDirectAnimation)) bool DirectAnimation;

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void setFrameRate(int a_nFrameRate);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetFrameRate(void);
	//__declspec(property(put = SetFrameRate, get = GetFrameRate)) int FrameRate;

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetFrameCount(void);

private:
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Swap(SequenceClass& other);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<SequenceClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<SequenceClass*>;

}
#endif //__SEQUENCECLASS_H__