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
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

#pragma warning(error:4001)	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 35  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */
#define FLT_LEN 7
#define TAG_LEN 7

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (begins: ?) */
	VAR_T,		/*  2: Variable identifier token*/
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	CMS_T,		/*  8: Comma separator token*/
	KW_T,		/*  9: Keyword token */
	EOS_T,		/* 10: End of statement (semicolon) */
	RTE_T,		/* 11: Run-time error token */
	INL_T,		/* 12: Integer Literal token */
	FPL_T,		/* 13: Float Literal token*/
	OPT_T,		/* 14: Open Tag Token*/
	CLT_T,		/* 15: Closing Tag Token*/
	ART_OP_T,	/* 16: Arithmetic opeator token*/
	REL_OP_T,	/* 17: Relational operator token*/
	LOG_OP_T,	/* 18: Logical operator token*/
	ASS_T,		/* 19: Assignment operator token*/
	COM_T,		/* 20: Comment Token*/
	SEOF_T		/* 21: Source end-of-file token */
};
/* DONE */

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT, OP_GE, OP_LE } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;
/*DONE*/

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	juan_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	juan_int intValue;						/* integer literal attribute (value) */
	juan_int keywordIndex;					/* keyword index in the keyword table */
	juan_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	juan_float floatValue;					/* floating-point literal attribute (value) */
	juan_char idLexeme[VID_LEN + 1];		/* method identifier token attribute */
	juan_char tagType[TAG_LEN + 1];
	juan_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;
/* DONE */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	juan_byte flags;			/* Flags information */
	union {
		juan_int intValue;				/* Integer value */
		juan_float floatValue;			/* Float value */
		juan_char* stringContent;		/* String value */
	} values;
} IdAttibutes;
/* DONE */

/* Token declaration */
typedef struct Token {
	juan_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF
#define NL '\n'

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL3 '?'
#define CHRCOL4 '\''
#define CHRCOL5 '\"'
#define CHRCOL6 '.'
#define CHRCOL7 '<'
#define CHRCOL8 '>'
/* DONE */


/* These constants will be used on VID / MID function */
#define MNIDPREFIX '?'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	22		/* Error state with no retract */
#define ESWR	23		/* Error state with retract */
 /*DONE*/

 /* TO_DO: State transition table definition */
#define STATE_ROWS 24
#define TABLE_COLUMNS 11
 /*DONE*/

/* TO_DO: Transition table - type of states defined in separate table */
static juan_int transitionTable[STATE_ROWS][TABLE_COLUMNS] = {
    /*[a-z],[ A-Z],[0-9],  [?],  ['],  ["],  [.],  [<],   [>],  SEOF,  Other
	  LL(0), UL(1), D(2),QM(3),SQ(4),DQ(5), P(6),LA(7), RA(8),  E(9),  O(10) */
	{	 16,	16,   8	,    6,   13,	15,   10,	 1,	 ESNR,	ESNR,  ESNR}, // S0:  NOAS
	{  ESNR,  ESNR, ESNR,	 2, ESWR, ESWR, ESNR, ESNR,  ESNR,  ESWR,  ESNR}, // S1:  NOAS
	{  ESNR,	 3,	ESNR, ESNR,	ESWR, ESWR,	ESNR, ESNR,	 ESNR,	ESWR,  ESNR}, // S2:  NOAS
	{     4,	 3,	   4,	 4,	   4,	 4,	   4,	 4,	    4,	ESWR,	  4}, // S3:  NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S4:  ASWR(OPEN TAG)
	{  ESNR,	 6,	ESNR, ESNR,	ESWR, ESWR,	ESNR, ESNR,	 ESNR,	ESWR,  ESNR}, // S5:  NOAS
	{     7,     6,	   7,	 7,	ESWR, ESWR,	   7,	 7,	    7,	ESWR,	  7}, // S6:  NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S7:  ASWR(METHOD)
	{     9,	 9,	   8,	 9,	ESWR, ESWR,	  10,	 9,	    9,	ESWR,	  9}, // S8:  NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S9:  ASWR(INT)
	{    10,	10,	  11,	10,	ESWR, ESWR,	  10,	10,	   10,	ESWR,	 10}, // S10: NOAS
	{    12,	12,   11,	12,	ESWR, ESWR,	  12,	12,	   12,	ESWR,  	 12}, // S11: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S12: ASWR(FLOAT)
	{    13,	13,	  13,	13,	  14,	13,	  13,	13,	   13,	ESWR,	 13}, // S13: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S14: ASNR(STRING)
	{    15,	15,	  15,	15,	  15,	14,	  15,	15,	   15,	ESWR,	 15}, // S15: NOAS
	{    16,	18,	  17,	20,	ESWR, ESWR,	  17,	17,	   17,	ESWR,	 17}, // S16: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S17: ASWR(ID)
	{    16,	18,	  19,	20,	ESWR, ESWR,	  19,	19,	   19,	ESWR,	 19}, // S18: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S19: ASWR(KEY)
	{  ESNR,  ESNR,	ESNR, ESNR,	ESWR, ESWR,	ESNR, ESNR,	   21,	ESWR,  ESNR}, // S20: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S21: ASNR(CLOSE TAG)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}, // S22: ASNR(ERROR NO RETRACT)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,    FS}  // S23: ASWR(ERROR WITH RETRACT)
};
 /*DONE*/

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static juan_int stateType[STATE_ROWS] = {
	NOFS, //S0
	NOFS, //S1
	NOFS, //S2
	NOFS, //S3
	FSWR, //S4 (OPEN TAG)
	NOFS, //S5
	NOFS, //S6
	FSWR, //S7 (METHOD)
	NOFS, //S8
	FSWR, //S9 (INT)
	NOFS, //S10
	NOFS, //S11
	FSWR, //S12(FLOAT)
	NOFS, //S13
	FSNR, //S14 (STRING)
	NOFS, //S15
	NOFS, //S16
	FSWR, //S17 (ID)
	NOFS, //S18
	FSWR, //S19 (KEY)
	NOFS, //S20
	FSNR, //S21 (CLOSE TAG)
	FSNR, //S22 (ENR)
	FSWR  //S23 (EWR)
};
/*DONE*/

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
juan_int startScanner(ReaderPointer psc_buf);
Token tokenizer(juan_void);
static juan_int nextClass(juan_char c);				/* character class function */
static juan_int nextState(juan_int, juan_char);		/* state machine function */
juan_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(juan_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(juan_char lexeme[]); /*DONE*/
Token funcVID	(juan_char lexeme[]); /*DONE*/
Token funcKEY	(juan_char lexeme[]); /*DONE*/
Token funcErr	(juan_char lexeme[]); /*DONE*/
Token funcIL	(juan_char lexeme[]); /*DONE*/
Token funcFP	(juan_char lexeme[]); /*DONE*/
Token funcFID	(juan_char lexeme[]); /*DONE*/
Token funcOpTag	(juan_char lexeme[]); /*DONE*/
Token funcClTag (juan_char lexeme[]); /*DONE*/

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[STATE_ROWS] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	NULL,		/* -    [02] */
	NULL,		/* -    [03] */
	funcOpTag,	/* OPT	[04] - Opening Tag */
	NULL,		/* -	[05] */
	NULL,		/* -	[06] */
	funcFID,	/* MID	[07] - Method Identifier*/
	NULL,		/* -	[08] */
	funcIL,		/* ITL	[09] - Integer Literals*/
	NULL,		/* -	[10] */
	NULL,		/* -	[11] */
	funcFP,		/* FPL	[12] - Float Literal*/
	NULL,		/* -    [13] */
	funcSL,		/* SL	[14] - String Literal*/
	NULL,		/* -	[15] */
	NULL,		/* -    [16] */
	funcVID,	/* VID	[17] - Variable Identifier*/
	NULL,		/* -    [18] */
	funcKEY,	/* KEY  [19] - Keywords */
	NULL,		/* -    [20] */
	funcClTag,	/* CLT  [21] - Closing Tag */
	funcErr,	/* ERR1 [22] - No retract */
	funcErr		/* ERR2 [23] - Retract */
};
/* DONE */

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 9

/* TO_DO: Define the list of keywords */
static juan_char* keywordTable[KWT_SIZE] = {
	"NAUJ", /*Constants*/ //0
	"JUAN", /*Variables*/ //1
	"JUANFULLHD", /*Output function*/ //2
	"JUANBALCONY", /*Input function*/ //3
	"JUANPQ", /*Loop(While) function*/ //4
	"IFJUAN", /*Start if function*/ //5
	"JUANPRIMERO", /*Else if function*/ //6
	"JUANSEGUNDO", /*Else function*/ //7
	"RETURNJUAN" /*Return Tag*/ //8
};
/* DONE */

/*	NOT USING INDENTATION	*/

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data)
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	juan_char indentationCharType;
	juan_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;
/*DONE KIND OF*/

/* Number of errors */
juan_int numScannerErrors;

#endif
