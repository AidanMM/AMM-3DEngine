/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __ANIMATIONCLASS_H_
#define __ANIMATIONCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Animation\FrameClass.h"

namespace ReEng
{

class ReEngDLL AnimationClass
{
public:
	/*
	 AnimationClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	AnimationClass(void);
	/*
	 AnimationClass
	USAGE: Copy Constructor
	ARGUMENTS: other instance
	OUTPUT: class object
	*/
	AnimationClass(const AnimationClass& other);
	/*
	 operator=
	USAGE: copy assignment operator
	ARGUMENTS: other instance
	OUTPUT: ---
	*/
	AnimationClass& operator=(const AnimationClass& other);
	/*
	 ~AnimationClass
	USAGE: destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AnimationClass(void);
	/*
	 Init
	USAGE: Initializes the variable members
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	 Release
	USAGE: Deinitializes the variable members
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	 Swap
	USAGE: swaps the values of the member fields of incoming object for self's
	ARGUMENTS: other instance
	OUTPUT: ---
	*/
	void Swap(AnimationClass& other);
	/*
	 AnimationClass
	USAGE: constructor, will create a number of frames
	ARGUMENTS:
		FrameClass *a_pFrame -> pointer to a frame class object 
		int a_nFrames -> number of frames to create
	OUTPUT: class object
	*/
	AnimationClass(FrameClass *a_pFrame, int a_nFrames);
	/*
	 CheckInterpolation const;
	USAGE: Checks the interpolation of the frames
	ARGUMENTS:
		FrameClass *a_pFrame -> pointer to frame object
		int a_nFrames
	OUTPUT: ---
	*/
	void CheckInterpolation(FrameClass *a_pFrame, int a_nFrames) const;
private:
	/*
	 Interpolation const;
	USAGE: Interpolates the frames from the first to the last frame
	ARGUMENTS:
		FrameClass *a_pFrame -> frame pointer
		int a_nFirstKeyFrame -> First frame to interpolate
		int a_nLastKeyFrame -> Last frame to interpolate
	OUTPUT: ---
	*/
	void Interpolation(FrameClass *a_pFrame, int a_nFirstKeyFrame, int a_nLastKeyFrame) const;
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<AnimationClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<AnimationClass*>;

}
#endif //__ANIMATIONCLASS_H__