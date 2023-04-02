:: COMPILERS COURSE - SCRIPT ---------------------------------------------
:: SCRIPT A22 - CST8152 - Winter 2023

CLS
SET COMPILER=JUANCompiler.exe

SET FILE0=a
SET FILE1=charTest
SET FILE2=EMPTY
SET FILE3=INPUT2
SET FILE4=README
SET FILE5=xd
SET FILE6=INPUT6_Err1Reader
SET FILE9=INPUT9_Big

SET ASSIGNMENT=A12
SET EXTENSION=juan
SET OUTPUT=out
SET ERROR=err

SET PARAM=S

:: ---------------------------------------------------------------------
:: Begin of Tests (A22 - W22) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "                                                                       "
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "@@@@                                                               @@@@"
ECHO "@@          /       ==============================        /          @@"
ECHO "@         ////           @@       @@ #@                  ////         @"
ECHO "@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @"
ECHO "@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @"
ECHO "@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @"
ECHO "@     (((((/)))((    ------------------------------    ((((./////*    @"
ECHO "@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @"
ECHO "@    ///// / /////   ==============================  * ////* / ////   @"
ECHO "@     ///// ///// ((                               (( ///// /////     @"
ECHO "@    ((((   / , (((((                             (((((  //   /(((    @"
ECHO "@    (((((((/ . (((((                          (((((* / (((((((       @"
ECHO "@      (((((( //((((/((((                    *((((/((((/( (((((/      @"
ECHO "@       .//,   * /   (((((                   (((((  ///    .//.       @"
ECHO "@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @"
ECHO "@         //////// ,// ((( /////,     ////// ((( //  /////// *        @"
ECHO "@            (((((((((,// * /////     /////   (//(((((((((            @"
ECHO "@            ((((((((((((/////         //.///  (((((((((((.           @"
ECHO "@                   (///////// //(   (//.//////////                   @"
ECHO "@                  (/////////             //////////                  @"
ECHO "@                                                                     @"
ECHO "@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@"
ECHO "@@@@                                                               @@@@"
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "                                                                       "
ECHO "[SCANNER SCRIPT ......................................................]"
ECHO "                                                                       "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A22 - W22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A22 - W22) --------------------------------------------
:: ---------------------------------------------------------------------
