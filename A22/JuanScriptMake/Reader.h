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
* Purpose: This file is the main header for Reader (.h)
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
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (JUAN) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for JUAN */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 7: FUL = Full */
#define SET_FULL_BIT 0x80
#define RST_FULL_BIT 0x7F
#define CHK_FULL_BIT 0x80
/* TO_DO: BIT 6: EMP: Empty */
#define SET_EMP_BIT  0x40
#define RST_EMP_BIT  0xBF
#define CHK_EMP_BIT  0x40
/* TO_DO: BIT 5: REL = Relocation */
#define SET_REL_BIT  0x20
#define RST_REL_BIT  0xDF
#define CHK_REL_BIT  0x20
/* TO_DO: BIT 4: END = EndOfBuffer */
#define SET_END_BIT  0x10
#define RST_END_BIT  0xEF
#define CHK_END_BIT  0x10

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (JUAN) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	juan_int mark;			/* the offset to the mark position (in chars) */
	juan_int read;			/* the offset to the get a char position (in chars) */
	juan_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	juan_char*	    content;			/* pointer to the beginning of character array (character buffer) */
	juan_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	juan_int		increment;			/* character array increment factor */
	juan_int		mode;				/* operational mode indicator */
	juan_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	juan_int		histogram[NCHAR];	/* Statistics of chars */
	juan_int		numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(juan_int, juan_int, juan_int);
ReaderPointer	readerAddChar		(ReaderPointer const, juan_char);
juan_boln	readerClear		    (ReaderPointer const);
juan_boln	readerFree		    (ReaderPointer const);
juan_boln	readerIsFull		(ReaderPointer const);
juan_boln	readerIsEmpty		(ReaderPointer const);
juan_boln	readerSetMark		(ReaderPointer const, juan_int);
juan_int		readerPrint		    (ReaderPointer const);
juan_int		readerLoad			(ReaderPointer const, FILE* const);
juan_boln	readerRecover		(ReaderPointer const);
juan_boln	readerRetract		(ReaderPointer const);
juan_boln	readerRestore		(ReaderPointer const);
/* Getters */
juan_char		readerGetChar		(ReaderPointer const);
juan_char*	readerGetContent	(ReaderPointer const, juan_int);
juan_int		readerGetPosRead	(ReaderPointer const);
juan_int		readerGetPosWrte	(ReaderPointer const);
juan_int		readerGetPosMark	(ReaderPointer const);
juan_int		readerGetSize		(ReaderPointer const);
juan_int		readerGetInc		(ReaderPointer const);
juan_int		readerGetMode		(ReaderPointer const);
juan_byte		readerGetFlags		(ReaderPointer const);
juan_int		readerShowStat		(ReaderPointer const);
juan_int		readerNumErrors		(ReaderPointer const);

#endif
