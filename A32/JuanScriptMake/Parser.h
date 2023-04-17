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
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern juan_int line;
extern Token tokenizer();
extern juan_char* keywordTable[];
juan_int syntaxErrorNumber = 0;

#define STR_LANGNAME	"JUANSCRIPT"
#define LANG_WRTE		"JUANFULLHD"
#define LANG_READ		"JUANBALCONY"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants 
	"NAUJ", /*Constants //0
"JUAN", /*Variables //1
"JUANFULLHD", /*Output function //2
"JUANBALCONY", /*Input function //3
"JUANPQ", /*Loop(While) function //4
"IFJUAN", /*Start if function //5
"JUANPRIMERO", /*Else if function //6
"JUANSEGUNDO", /*Else function //7
"RETURNJUAN" /*Return Tag //8
*/
enum KEYWORDS {
	NO_ATTR = -1,
	KW_const, //NAUJ
	KW_var, //JUAN
	KW_prin,
	KW_scan,
	KW_while, //JUANPQ
	KW_if, //IFJUAN
	KW_elif, //JUANPRIMERO
	KW_else, //JUANSEGUNDO
	KW_return //RETURNJUAN
};

/* Function definitions */
juan_void startParser();
juan_void matchToken(juan_int, juan_int);
juan_void syncErrorHandler(juan_int);
juan_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
juan_void codeSession();
juan_void optionalStatements();
juan_void outputStatement();
juan_void outputVariableList();
juan_void program();
juan_void statement();
juan_void statements();
juan_void statementsPrime();
juan_void functionDefinition();
juan_void parameters();
juan_void parameter();
juan_void parametersPrime();
juan_void functionCall();
juan_void assignmentStatement();
juan_void arithmeticExpression();
juan_void logicalExpression();
juan_void conditionalExpression();
juan_void inputStatement();
juan_void conditionalStatement();
juan_void returnStatement();
juan_void groupedArithmeticExpression();
juan_void relationalExpression();
juan_void stringAssignment();
juan_void stringConcatenation();
juan_void callParameters();
juan_void commentStatement();
juan_void iterationStatement();
juan_void definitionStatement();

#endif