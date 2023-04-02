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
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

#define NDEBUG        //to suppress assert() call 
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern ReaderPointer stringLiteralTable;	/* String literal table */
juan_int line;								/* Current line number of the source code */
extern juan_int errorNumber;				/* Defined in platy_st.c - run-time error number */

extern juan_int stateType[];
extern juan_char* keywordTable[];
extern PTR_ACCFUN finalStateTable[];
extern juan_int transitionTable[][TABLE_COLUMNS];

/* Local(file) global objects - variables */
static ReaderPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static ReaderPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */
juan_int startScanner(ReaderPointer psc_buf) {
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */
Token tokenizer(juan_void) {
	/* TO_DO: Follow the standard and adjust datatypes */
	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	juan_char c;	/* input symbol */
	juan_int state = 0;		/* initial state of the FSM */
	juan_int lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	juan_int lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	juan_int lexLength;		/* token length */
	juan_int i;				/* counter */
	juan_char newc;			/* new char */
	
	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case ' ':
		case '\t':
		case '\f':
			break;
		case '\n':
			line++;
			break;

		/* Cases for symbols */
		case ';':
			currentToken.code = EOS_T;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			return currentToken;
		/*case '*':
			currentToken.code = currentToken.attribute.arithmeticOperator;
			return currentToken;
		case '+':
			currentToken.code = OP_ADD;
			return currentToken;
		case '-':
			currentToken.code = OP_SUB;*/
		/* Comments */
		case '/':
			// check if the next character is an asterisk
			newc = readerGetChar(sourceBuffer);
			if (newc == '*') {
				readerGetChar(sourceBuffer); // consume the asterisk
				do {
					c = readerGetChar(sourceBuffer);
					if (c == '\n') {
						line++;
					}
					else if (c == '*') {
						newc = readerGetChar(sourceBuffer); // consume the closing slash
						if (newc == '/') {
							break;
						}
					}
				} while (1);
			}
			else {
				currentToken.code = OP_DIV;
				return currentToken;
			}
		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;
		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
			readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((juan_int)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer);
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */
juan_int nextState(juan_int state, juan_char c) {
	juan_int col;
	juan_int next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}
/* DONE */

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */


juan_int nextClass(juan_char c) {
	juan_int val = -1;
		switch (c) {
		case CHRCOL3:
			val = 3;
			break;
		case CHRCOL4:
			val = 4;
			break;
		case CHRCOL5:
			val = 5;
			break;
		case CHRCOL6:
			val = 6;
			break;
		case CHRCOL7:
			val = 7;
			break;
		case CHRCOL8:
			val = 8;
			break;
		case CHARSEOF0:
			val = 9;
			break;
		case CHARSEOF255:
			val = 9;
			break;
		default:
			if (isalpha(c)) {
				if (islower(c))
					val = 0;
				else
					val = 1;
			}
			else if (isdigit(c)) {
				val = 2;
				break;
			}
			else {
				val = 10;
				break;
			}
		}
		return val;
}
/* DONE */


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */
Token funcIL(juan_char lexeme[]) {
	Token currentToken = { 0 };
	juan_long tlong;
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			currentToken.attribute.intValue = (juan_int)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}
/* DONE */

/*
  ************************************************************
  * Acceptance State Function FP
  *		Function responsible to identify FP (Floating Point literals).
  * - It is necessary respect the limit.
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for FP */
Token funcFP(juan_char lexeme[])
{
	Token currentToken = { 0 };
	juan_doub tdouble;
	if (lexeme[0] != '\0' && strlen(lexeme) > FLT_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tdouble = atof(lexeme);
		if (tdouble >= 0 && tdouble <= FLT_MAX) {
			currentToken.code = FPL_T;
			currentToken.attribute.floatValue = (juan_float)tdouble;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}
/* DONE */

/*
 ************************************************************
 * Acceptance State Method ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */
Token funcFID(juan_char lexeme[])
{
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	juan_int isFUNC = JUAN_FALSE;
	if (lexeme[0] == MNIDPREFIX) {
		currentToken.code = MNID_T;
		isFUNC = JUAN_TRUE;
	}
	else {
		currentToken = funcKEY(lexeme);
	}
	if (isFUNC == JUAN_TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	return currentToken;
}
/* DONE */

/*
 ************************************************************
 * Acceptance State Method OpTag
 *		In this function, the pattern for opening tags must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with <?JUAN from language.
 ***********************************************************
 */
Token funcOpTag(juan_char lexeme[])
{
	Token currentToken = { 0 };
	if (strncmp(lexeme, "<?JUAN", TAG_LEN) == 0) {
		currentToken.code = OPT_T;
		strncpy(currentToken.attribute.tagType, lexeme, TAG_LEN);
		currentToken.attribute.idLexeme[TAG_LEN] = CHARSEOF0;
	}
	else {
		funcErr(lexeme);
	}
	return currentToken;
}
/* DONE */

/*
 ************************************************************
 * Acceptance State Method OpTag
 *		In this function, the pattern for opening tags must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with <?JUAN from language.
 ***********************************************************
 */
Token funcClTag(juan_char lexeme[])
{
	Token currentToken = { 0 };
	if (strncmp(lexeme, "JUAN?>", TAG_LEN) == 0) {
		currentToken.code = CLT_T;
		strncpy(currentToken.attribute.tagType, lexeme, TAG_LEN);
		currentToken.attribute.idLexeme[TAG_LEN] = CHARSEOF0;
	}
	else {
		funcErr(lexeme);
	}
	return currentToken;
}
/* DONE */

/*
 ************************************************************
 * Acceptance State Variable ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */
Token funcVID(juan_char lexeme[]) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	juan_int isVar = JUAN_FALSE;
	juan_int i = 0;

	// Check if the lexeme matches the pattern for variable names
	for (i = 0; i < length-1; i++) {
		if (lexeme[i] < 0 || lexeme[i] >= 255) {
			isVar = JUAN_FALSE;
			break;
		}
		isVar = JUAN_TRUE;
	}

	if (isVar == JUAN_TRUE) {
		currentToken.code = VAR_T;
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	else {
		currentToken = funcErr(lexeme);
	}

	return currentToken;
}
/* DONE */

/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table
 *   (stringLiteralTable). You need to include the literals in
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for SL */
Token funcSL(juan_char lexeme[]) {
	Token currentToken = { 0 };
	juan_int i = 0, len = (juan_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n') {
			line++;
		}
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */
Token funcKEY(juan_char lexeme[]) {
	Token currentToken = { 0 };
	juan_int kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++) {
		if (!strcmp(lexeme, keywordTable[j])) {
			kwindex = j;
			break;
		}
	}
	if (kwindex != -1) {
		currentToken.code = KW_T;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		currentToken = funcErr(lexeme);
	}
	return currentToken;
}
/* DONE */

/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */
Token funcErr(juan_char lexeme[]) {
	Token currentToken = { 0 };
	juan_int i = 0, len = (juan_int)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	return currentToken;
}
/* DONE */

/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

juan_void printToken(Token t) {

	/* External variables */
	extern juan_char* keywordTable[]; /* link to keyword table in */
	extern numScannerErrors;			/* link to number of errors (defined in Scanner.h) */

	switch (t.code) {
	case RTE_T:
		numScannerErrors++;
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case OPT_T:
		printf("OPT_T\t\t%s\t\n", t.attribute.tagType);
		break;
	case CLT_T:
		printf("CLT_T\t\t%s\t\n", t.attribute.tagType);
		break;
	case ERR_T:
		numScannerErrors++;
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T\t\t%d\t ", (juan_int)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (juan_int)t.attribute.codeType));
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case EOS_T:
		printf("EOS_T\n");
		break;
	case INL_T:
		printf("INL_T\t\t%d\t\n", t.attribute.intValue);
		break;
	case FPL_T:
		printf("FPL_T\t\t%f\t\n", t.attribute.floatValue);
		break;
	default:
		//numScannerErrors++;
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
