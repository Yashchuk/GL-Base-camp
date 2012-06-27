#ifndef _STACK_H
#define _STACK_H

#define DllExport __declspec(dllexport)

/**
  * @brief		Clear stack
  * @return		void
  */
extern "C" void DllExport clearStack();

/**
  * @brief		Check if stack is empty
  * @return		Boolean value
  */
extern "C" bool DllExport isEmpty();

/**
  * @brief		Push charcter into stack
  * @param		[in] c Character to push
  * @return		False if stack is full
  */
extern "C" bool DllExport pushCharacter(char c);

/**
  * @brief		Pop charcter from stack
  * @return		Character or 0 if stack was empty
  */
extern "C" char DllExport popCharacter();

/**
  * @brief		Get charcter from the top of stack
  * @return		Character or 0 if stack was empty
  */
extern "C" char DllExport peekCharacter();

#endif /* _STACK_H */