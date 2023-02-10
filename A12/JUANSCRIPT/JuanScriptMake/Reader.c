/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Luis Resendiz
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Reader (.c)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/************************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
**************************************************************/
ReaderPointer readerCreate(juan_int size, juan_int increment, juan_int mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the values according to parameters */
	/*Case of invalid size or no size*/
	if (size <= 0 || size == NULL) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	/*Case of invalid increment*/
	if (increment <= 0) {
		increment = READER_DEFAULT_INCREMENT;
	}
	/*Case of no increment*/
	else if (increment == NULL) {
		mode = MODE_FIXED;
	}
	/*Case of invalid mode*/
	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI) {
		return NULL;
	}
	/*Creation of reader*/
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return NULL;
	}
	readerPointer->content = (juan_char*)malloc(size);
	if (!readerPointer->content) {
		free(readerPointer);
		return NULL;
	}
	/* TO_DO: Defensive programming */
	/* TO_DO: Initialize the histogram */
	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	readerPointer->flags = RST_EMP_BIT;
	return readerPointer;
} /************DONE*****************/


/************************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
ReaderPointer readerAddChar(ReaderPointer const readerPointer, juan_char ch) {
	juan_char* tempReader = NULL;
	juan_int newSize = 0;
	/* TO_DO: Defensive programming: check buffer and valid char (increment numReaderErrors) */
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	/* Check if the buffer reader is not null and if the input char is valid */
	if (!readerPointer) {
		return NULL;
	}
	if (ch < 0 || ch >= CHAR_MAX) {
		readerPointer->numReaderErrors++;
	}
	if (readerPointer->position.wrte * (juan_int)sizeof(juan_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags = CHK_FULL_BIT;
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags = (RST_FULL_BIT);
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			/* TO_DO: Defensive programming */
			newSize = readerPointer->size + readerPointer->increment;
			if (newSize >= READER_MAX_SIZE || newSize<0) {
				newSize = READER_MAX_SIZE - 1;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			/* TO_DO: Defensive programming */
			newSize = readerPointer->size * readerPointer->increment;
			if (newSize >= READER_MAX_SIZE || newSize < 0) {
				newSize = READER_MAX_SIZE - 1;
			}
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		/* TO_DO: Defensive programming */
		/* TO_DO: Check Relocation */
		tempReader = (juan_char*)realloc(readerPointer->content, newSize * sizeof(juan_char));
		if (!tempReader) {
			/* Increment the number of reader errors */
			//readerPointer->numReaderErrors++;
			readerPointer->flags = SET_FULL_BIT;
			return NULL;
		}
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		if (!readerPointer->content) {
			//readerPointer->numReaderErrors++;
			return NULL;
		}
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte] = ch;
	readerPointer->position.wrte++;
	/* TO_DO: Update histogram*/
	if (ch >= 0 && ch < CHAR_MAX) {
		readerPointer->histogram[ch]++;
	}
	return readerPointer;
}/****************** DONE **********************/

/************************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
/********************* DONE ********************/
juan_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust flags original */
	if (!readerPointer) {
		return JUAN_FALSE;
	}
	else {
		readerPointer->flags = RST_EMP_BIT;
		readerPointer->position.wrte = 0;
		readerPointer->position.read = 0;
		readerPointer->position.mark = 0;
		return JUAN_TRUE;
	}
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return JUAN_FALSE;
	}
	else {
		/* TO_DO: Free pointers */
		if (readerPointer->content) {
			free(readerPointer->content);
		}
		free(readerPointer);
		return JUAN_TRUE;
	}
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags == CHK_FULL_BIT) {
		return JUAN_TRUE;
	}
	else {
		return JUAN_FALSE;
	}
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags == CHK_EMP_BIT) {
		return JUAN_TRUE;
	}
	else {
		return JUAN_FALSE;
	}
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_boln readerSetMark(ReaderPointer const readerPointer, juan_int mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte)
		return JUAN_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return JUAN_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerPrint(ReaderPointer const readerPointer) {
	juan_int count = 0;
	juan_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (count < readerPointer->position.wrte) {
		count++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return count;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	juan_int size = 0;
	juan_char c;

	/* defensive programming */
	if (readerPointer == NULL || fileDescriptor == NULL) {
		return READER_ERROR;
	}

	c = (juan_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}

	/* defensive programming */
	if (ferror(fileDescriptor)) {
		return READER_ERROR;
	}

	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Recover positions */
	if (!readerPointer) {
		return JUAN_FALSE;
	}
	else {
		readerPointer->position.read = readerPointer->position.mark;
		return JUAN_TRUE;
	}
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Retract (return 1 pos read) */
	if (!readerPointer || readerPointer->position.wrte <= 0) {
		return JUAN_FALSE;
	}
	else {
		readerPointer->position.wrte--;
		return JUAN_TRUE;
	}
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Restore positions (read/mark) */
	if (!readerPointer) {
		return JUAN_FALSE;
	}
	else {
		readerPointer->position.read = 0;
		readerPointer->position.mark = 0;
		return JUAN_TRUE;
	}
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	if (!readerPointer) {
		return 0;
	}

	/* Check if read position is within buffer bounds */
	if (readerPointer->position.read >= readerPointer->size) {
		readerPointer->flags = SET_END_BIT;
		return readerPointer->content[readerPointer->position.read];
	}

	/* Reset EOB flag */
	readerPointer->flags = RST_END_BIT;

	/* Return the character */
	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_char* readerGetContent(ReaderPointer const readerPointer, juan_int pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return NULL;
	}
	
	/* TO_DO: Check boundary conditions */
	if (pos >= readerPointer->position.wrte|| pos < 0) {
		return NULL;
	}

	/* TO_DO: Return content (string) */
	return &readerPointer->content[pos];
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return read */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->position.read;
	}
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return wrte */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->position.wrte;
	}
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->position.mark;
	}
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return size */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->size;
	}
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return increment */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->increment;
	}
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->mode;
	}
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return flags */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->flags;
	}
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
	if (!readerPointer) {
		return 0;
	}
	else {
		int stat = 0;
		for (int i = 0; i < CHAR_MAX; i++) {
			if (readerPointer->histogram[i] > 0) {
				stat++;
			}
		}
		return stat;
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juan_int readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
	if (!readerPointer) {
		return 0;
	}
	else {
		return readerPointer->numReaderErrors;
	}
}
