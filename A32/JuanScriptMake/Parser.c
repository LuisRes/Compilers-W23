/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Antonio Campos
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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
juan_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
juan_void matchToken(juan_int tokenCode, juan_int tokenAttribute) {
	juan_int matchFlag = 1;
	printf("\nToken code: %d", tokenCode);
	printf(" Token attribute: %d\n", tokenAttribute);
	printf("Lookahead code: %d", lookahead.code);
	printf(" Lookahead attribute code: %d\n", lookahead.attribute.codeType);
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
juan_void syncErrorHandler(juan_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
} /*DONE*/

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
juan_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
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
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> <?JUAN <opt_statements> JUAN?>
 * FIRST(<program>)= {OPT_T (<?JUAN)}.
 ***********************************************************
 */
juan_void program() {
	switch (lookahead.code) {
	case COM_T:
		commentStatement();
	case OPT_T:
		matchToken(OPT_T, NO_ATTR);
		codeSession();
		matchToken(CLT_T, NO_ATTR);
		break;
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
juan_void codeSession() {
	optionalStatements();
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
juan_void optionalStatements() {
	switch (lookahead.code) {
	case KW_T:
		statements();
		break;
	case MNID_T:
		statements();
		break;
	case VAR_T:
		statements();
		break;
	case COM_T:
		statements();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
juan_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
juan_void statementsPrime() {
	switch (lookahead.code) {
	case MNID_T:
		statements();
		break;
	case VAR_T:
		statements();
		break;
	case KW_T:
		statements();
		break;
	case COM_T:
		statements();
		break;
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Function Definition
 ***********************************************************
 */
juan_void functionDefinition(){
	//Parse function and then reuse statements
	matchToken(MNID_T, NO_ATTR);
	matchToken(VAR_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	if (lookahead.code==RPR_T) {
		matchToken(RPR_T, NO_ATTR);
	}
	else {
		parameters();
		matchToken(RPR_T, NO_ATTR);
	}
	matchToken(LBR_T, NO_ATTR);
	statements();
	matchToken(RBR_T, NO_ATTR);
}

/*
 ************************************************************
 * Parameters
 ***********************************************************
 */
juan_void parameters() {
	parameter();
	parametersPrime();
	printf("%s%s\n", STR_LANGNAME, ": Parameters parsed");
}

/*
 ************************************************************
 * Single Parameter
 ***********************************************************
 */
juan_void parameter() {
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_const:
			matchToken(KW_T, KW_const);
			break;
		case KW_var:
			matchToken(KW_T, KW_var);
			break;
		default:
			;
		}
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case CMS_T:
		matchToken(CMS_T, NO_ATTR);
		break;
	default:
		;
	}
}

/*
 ************************************************************
 * Parameters Prime
 ***********************************************************
 */
juan_void parametersPrime() {
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_const:
			parameters();
		case KW_var:
			parameters();
			break;
		case CMS_T:
			parameters();
			break;
		default:
			break;
		}
		break;
	default:
		;
	}
}

/*
 ************************************************************
 * Function Call
 ***********************************************************
 */
juan_void functionCall() {
	matchToken(LPR_T, NO_ATTR);
	if (lookahead.code != RPR_T) {
		callParameters();
	}
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Function Call parsed");
}

juan_void callParameters() {
	matchToken(VAR_T, NO_ATTR);
	if (lookahead.code == CMS_T) {
		callParameters();
	}
	printf("%s%s\n", STR_LANGNAME, ": Function Call Parameters parsed");
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
juan_void statement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_const:
			matchToken(KW_T, KW_const);
			definitionStatement();
			break;
		case KW_var:
			matchToken(KW_T, KW_var);;
			definitionStatement();
			break;
		case KW_prin:
			outputStatement();
			break;
		case KW_scan:
			inputStatement();
			break;
		case KW_while:
			iterationStatement();
			break;
		case KW_if:
			conditionalStatement();
			break;
		case KW_elif:
			conditionalStatement();
			break;
		case KW_else:
			conditionalStatement();
			break;
		case KW_return:
			returnStatement();
			break;
		default:
			printError();
		}
		break;
	case MNID_T:
		functionDefinition();
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		if (lookahead.code == LPR_T) {
			functionCall();
		}
		else if (lookahead.code == ASS_T) {
			assignmentStatement();
		}
		break;
	case COM_T:
		commentStatement();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Comment Statement
 ***********************************************************
 */
juan_void commentStatement() {
	matchToken(COM_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * Return Statement
 ***********************************************************
 */
juan_void returnStatement() {
	matchToken(KW_T, KW_return);
	switch (lookahead.code)
	{
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	if (lookahead.code == EOS_T) {
		matchToken(EOS_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Return Statement parsed");
}

/*
 ************************************************************
 * Definition Statement
 ***********************************************************
 */
juan_void definitionStatement() {
	switch (lookahead.code)
	{
	case ASS_T:
		assignmentStatement();
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		definitionStatement();
		break;
	case CMS_T:
		matchToken(CMS_T, NO_ATTR);
		definitionStatement();
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		;
	}
}

/*
 ************************************************************
 * Assignment Statement
 ***********************************************************
 */
juan_void assignmentStatement() {
	matchToken(ASS_T, NO_ATTR);
	switch (lookahead.code){
	case STR_T:
		stringConcatenation();
		break;
	case VAR_T:
		arithmeticExpression();
		break;
	case FPL_T:
		arithmeticExpression();
		break;
	case INL_T:
		arithmeticExpression();
		break;
	default:
		;
	}
	if (lookahead.code == CMS_T) {
		matchToken(CMS_T, NO_ATTR);
		assignmentStatement();
	}
	else if(lookahead.code == EOS_T){
		matchToken(EOS_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Assignment Statement parsed");
}

/*
 ************************************************************
 * String Assingment
 ***********************************************************
 */
juan_void stringAssignment() {
	matchToken(STR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": String Assignment parsed");
}

/*
 ************************************************************
 * String Concatenation
 ***********************************************************
 */
juan_void stringConcatenation() {
	switch (lookahead.code)
	{
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		stringConcatenation();
		break;
	case ART_OP_T:
		matchToken(ART_OP_T, NO_ATTR);
		stringConcatenation();
		break;
	case STR_T:
		stringAssignment();
		break;
	default:
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Assignment Statement parsed");
}

/*
 ************************************************************
 * Simple Arithmethic Expression
 ***********************************************************
 */
juan_void arithmeticExpression()
{
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		if (lookahead.code == LPR_T) {
			functionCall();
		}
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	default:
		;
	}
	if (lookahead.code == ART_OP_T) {
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_ADD:
			matchToken(ART_OP_T, NO_ATTR);
			break;
		case OP_SUB:
			matchToken(ART_OP_T, NO_ATTR);
			break;
		case OP_MUL:
			matchToken(ART_OP_T, NO_ATTR);
			break;
		case OP_DIV:
			matchToken(ART_OP_T, NO_ATTR);
			break;
		default:
			;
		}
		if (lookahead.code == EOS_T) {
			matchToken(EOS_T, NO_ATTR);
		}
		else if (lookahead.code == LPR_T) {
			groupedArithmeticExpression();
		}
		else {
			arithmeticExpression();
		}
	}
	else if (lookahead.code == LPR_T) {
		groupedArithmeticExpression();
	}
	else if (lookahead.code == EOS_T) {
		matchToken(EOS_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Simple arithmetic expression parsed");
}

/*
 ************************************************************
 * Grouped Arithmethic Expression
 ***********************************************************
 */
juan_void groupedArithmeticExpression() {
	matchToken(LPR_T, NO_ATTR);
	if (lookahead.code != RPR_T) {
		arithmeticExpression();
	}
	if(lookahead.code == RPR_T){
		matchToken(RPR_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Grouped arithmetic expression parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
juan_void outputStatement() {
	matchToken(KW_T, KW_prin);
	outputVariableList();
	if (lookahead.code == EOS_T) {
		matchToken(EOS_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
juan_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		if (lookahead.code == ART_OP_T && lookahead.attribute.arithmeticOperator == OP_ADD) {
			stringConcatenation();
		}
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * Input Statement
 ***********************************************************
 */
juan_void inputStatement() {
	matchToken(KW_T, KW_scan);
	matchToken(LPR_T, NO_ATTR);
	matchToken(VAR_T, NO_ATTR);
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

/*
 ************************************************************
 * Conditional Statement
 ***********************************************************
 */
juan_void conditionalStatement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_if:
			matchToken(KW_T, KW_if);
			matchToken(LPR_T, NO_ATTR);
			conditionalExpression();
			matchToken(RPR_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			statements();
			matchToken(RBR_T, NO_ATTR);
			break;
		case KW_elif:
			matchToken(KW_T, KW_elif);
			matchToken(LPR_T, NO_ATTR);
			conditionalExpression();
			matchToken(RPR_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			statements();
			matchToken(RBR_T, NO_ATTR);
			break;
		case KW_else:
			matchToken(KW_T, KW_else);
			matchToken(LBR_T, NO_ATTR);
			statements();
			matchToken(RBR_T, NO_ATTR);
			break;
		default:
			;
		}
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Conditional statement parsed");
}

/*
 ************************************************************
 * Conditional Expression
 ***********************************************************
 */
juan_void conditionalExpression() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	default:
		;
	}
	switch (lookahead.code)
	{
	case ART_OP_T:
		arithmeticExpression();
		break;
	case LOG_OP_T:
		logicalExpression();
		break;

	case REL_OP_T:
		relationalExpression();
		break;
	default:
		break;
	}
}

/*
 ************************************************************
 * Logical Expression
 ***********************************************************
 */
juan_void logicalExpression() {
	switch (lookahead.code){
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		logicalExpression();
		break;
	case ART_OP_T:
		arithmeticExpression();
	case LOG_OP_T:
		switch (lookahead.attribute.logicalOperator)
		{
		case OP_AND:
			matchToken(LOG_OP_T, NO_ATTR);
			logicalExpression();
			break;
		case OP_OR:
			matchToken(LOG_OP_T, NO_ATTR);
			logicalExpression();
			break;
		case OP_NOT:
			matchToken(LOG_OP_T, NO_ATTR);
			logicalExpression();
			break;
		default:
			;
		}
	case REL_OP_T:
		relationalExpression();
		break;
	default:
		;
	}
}

/*
 ************************************************************
 * Relational Expression
 ***********************************************************
 */
juan_void relationalExpression() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		logicalExpression();
		break;
	case ART_OP_T:
		arithmeticExpression();
	case REL_OP_T:
		switch (lookahead.attribute.relationalOperator)
		{
		case OP_LT:
			matchToken(REL_OP_T, NO_ATTR);
			relationalExpression();
			break;
		case OP_LE:
			matchToken(REL_OP_T, NO_ATTR);
			relationalExpression();
			break;
		case OP_EQ:
			matchToken(REL_OP_T, NO_ATTR);
			relationalExpression();
			break;
		case OP_NE:
			matchToken(REL_OP_T, NO_ATTR);
			relationalExpression();
			break;
		case OP_GT:
			matchToken(REL_OP_T, NO_ATTR);
			relationalExpression();
			break;
		case OP_GE:
			matchToken(REL_OP_T, NO_ATTR);
			relationalExpression();
			break;
		default:
			;
		}
	case LOG_OP_T:
		logicalExpression();
		break;
	default:
		;
	}
}

/*
 ************************************************************
 * Iteration Statement
 ***********************************************************
 */
juan_void iterationStatement() {
	matchToken(KW_T, KW_while);
	matchToken(LPR_T, NO_ATTR);
	conditionalExpression();
	matchToken(RPR_T, NO_ATTR);
	matchToken(LBR_T, NO_ATTR);
	statements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Iteration statement parsed");
}