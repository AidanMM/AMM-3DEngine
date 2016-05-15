/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __STATECLASS_H_
#define __STATECLASS_H_

#include "RE\system\SystemSingleton.h"
#include <vector>

namespace ReEng
{

class ReEngDLL StateClass
{
	
	bool m_bTransitionState = false;//Is this a transition state
	bool m_bRepeatSequence	= true;	//Does the sequence repeats
	bool m_bBreakableState = true;	//Can I break out of this state without finishing the animation?
	int m_nSequence = 0;			//Sequence being played
	uint m_uExitCount = 0;				//Number of exits of this state
	
	std::vector<StateClass*> m_lExit;//Exits of the state

	String m_sName;
public:
	/*
	 Stateclass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	StateClass();	//Constructor
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	StateClass(String a_sName, int a_nSequence = 0, bool a_bBreakableState = false, bool a_bTransitionState = false, bool a_bRepeatSequence = false);
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	StateClass(const StateClass& other);
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	StateClass& operator=(const StateClass& other);
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	~StateClass();	//Destructor

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
	void SetSequence(int a_nSequence);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetSequence(void);
	//__declspec(property(put = SetSequence, get = GetSequence)) int Sequence;

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetBreakable(bool a_bRepeatSequence);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetBreakable(void);

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetRepeatSequence(bool a_bRepeatSequence);
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetRepeatSequence(void);
	//__declspec(property(put = SetRepeatSequence, get = GetRepeatSequence)) bool RepeatSequence;

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetNumberOfExits(void);
	//__declspec(property(get = GetNumberOfExists)) int Exits;

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int AddExit(StateClass* a_pState);

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int GetExitIndex(StateClass* a_pState);

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsTransitionState(void);

	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	StateClass* GetAutoExit(void);

	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	StateClass* GetExit(uint a_uIndex);

private:
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Swap(StateClass& other);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<StateClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<StateClass*>;

}

#endif //__STATECLASS_H__