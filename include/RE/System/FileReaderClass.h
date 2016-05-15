/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FILEREADERCLASS_H_
#define __FILEREADERCLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL FileReaderClass
{
	SystemSingleton* m_pSystem = nullptr; //System pointer
	FILE* m_pFile; //File pointer
	std::ifstream m_iStream;
	std::ofstream m_oStream;

public:
	String m_sLine = ""; //Line of file
	String m_sFirstWord = "";

	/* constructor */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	FileReaderClass(void);
	/* Copy constructor */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	FileReaderClass(const FileReaderClass& other);
	/* Copy assignment operator */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	FileReaderClass& operator=(const FileReaderClass& other);
	/* Destructor */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~FileReaderClass(void);
	
	/* Deallocate object from memory */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/* Rewinds the file */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Rewind(void) const;

	/* Reads Files and allocates it on the string */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS ReadFile(String a_sFileName);

	/* Saves a file with the specified name and location */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS SaveFile(String a_sFileName);

	/* Saves a file in binary mode */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS SaveBinaryFile(String a_sFileName);

	/* Reads Binary Files */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS ReadBinaryFile(String a_sFileName);

	/* closes the file */
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CloseFile(void);

	/* writes a line of the file and saves it in the string */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS WriteLine(String a_sStringInput);

	/* writes a line of the file and saves it in the char array */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS WriteLine(const char * _Format, ...);
	
	/* writes on the same line of the file and saves it in the string */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS Write(String a_sStringInput);

	/* writes on the same line of the file and saves it in the char array */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS Write(const char * _Format, ...);

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteInt(int input);

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteFloat(float input);

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteBool(bool input);

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteString(String input);


	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int ReadInt(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float ReadFloat(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool ReadBool(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String ReadString(void);

	/* Removes all tabs from the string (it makes regular spaces)*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS RemoveTabs(String* a_sInput);

	/* reads a line of the file and saves it in the string */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS ReadNextLine(bool a_bSkipComments = true);
	/* 
	Removes the blank spaces of the line
		Modified by AndrewWilkinson88@gmail.com
	*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS RemoveBlanks(char** a_szInput);

	/*Removes the blank spaces of the line and returns a new copy*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS RemoveBlanks(char* a_szInput);

	/*Removes the blank spaces of the line and returns a new copy*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS RemoveBlanks(String* a_sInput);

	/* Gets the first word of the line */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	String GetFirstWord(bool a_bToUpper = false);

	/*Gets a file name from a explorer window*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	String RetriveFileNameFromExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	/*Tells a file name from explorer window*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	String IndicateFileNameOnExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	/*Gets the filename with extension from the name */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetFileNameAndExtension(String a_sFileName);

	/*Gets the filename from the name */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetFileName(String a_sFileName);

	/*Gets the extension from the filename*/
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetExtension(String a_sFileName);

	/* Gets the absolute route from a file name */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetAbsoluteRoute(String a_sFileName);

	/* Returns the string in uppercase */
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static String ToUpper(String a_sInput);

private:
	/* Initializates the variables of the object*/
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass*>;

}
#endif //_EMPTY_H
