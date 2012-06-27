#ifndef _STACK_H
#define _STACK_H

/**
  * @brief		Clear stack
  * @return		void
  */
void clearStack();

/**
  * @brief		Check if stack is empty
  * @return		Boolean value
  */
bool isEmpty();

/**
  * @brief		Push charcter into stack
  * @param		[in] c Character to push
  * @return		False if stack is full
  */
bool pushCharacter(char c);

/**
  * @brief		Pop charcter from stack
  * @return		Character or 0 if stack was empty
  */
char popCharacter();

/**
  * @brief		Get charcter from the top of stack
  * @return		Character or 0 if stack was empty
  */
char peekCharacter();

#endif /* _STACK_H */