/*
 XmlScanner.ll -- a Flex scanner for a XML Parser.

    This file is part of the featsel program
    Copyright (C) 2010  Marcelo S. Reis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


%{                                            /* -*- C++ -*- */
# include <cstdlib>
# include <cfloat>
# include <errno.h>
# include <limits.h>
# include <string>
# include "XmlParserDriver.h"
# include "XmlParser.hpp"

/* Work around an incompatibility in flex (at least versions
   2.5.31 through 2.5.33): it generates code that does
   not conform to C89.  See Debian bug 333231
   <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.  */
# undef yywrap
# define yywrap() 1

/* By default yylex returns int, we use token_type.
   Unfortunately yyterminate by default returns 0, which is
   not of token_type.  */
#define yyterminate() return token::END
%}

%option noyywrap nounput batch debug

int   -?[0-9]+
str   [a-zA-Z_0-9]+
blank [ \t]
xml   \<\?[xX][mM][lL].*\?\>
float -?[0-9]+\.[0-9]+

%{
# define YY_USER_ACTION  yylloc->columns (yyleng);
%}

%%

%{
  yylloc->step ();
%}

{blank}+   yylloc->step ();

[\n]+      yylloc->lines (yyleng); yylloc->step ();

%{
  typedef yy::XmlParser::token token;
%}

{xml}                         return token::XML_HEADER;
"<ElementSet>"                return token::OPEN_ELEM_SET;
"</ElementSet>"               return token::CLOSE_ELEM_SET;
"<SetName>"                   return token::OPEN_SET_NAME;
"</SetName>"                  return token::CLOSE_SET_NAME;
"<NumberOfElements>"          return token::OPEN_NUM_ELEM;
"</NumberOfElements>"         return token::CLOSE_NUM_ELEM;
"<MaxNumberOfElementValues>"  return token::OPEN_MAX_NUM_VAL;
"</MaxNumberOfElementValues>" return token::CLOSE_MAX_NUM_VAL;
"<Element>"                   return token::OPEN_ELEM;
"</Element>"                  return token::CLOSE_ELEM;
"<Cost>"                      return token::OPEN_COST;
"</Cost>"                     return token::CLOSE_COST;
"<name>"                      return token::OPEN_NAME;
"</name>"                     return token::CLOSE_NAME;
"<value>"                     return token::OPEN_VALUE;
"</value>"                    return token::CLOSE_VALUE;

         /* Convert ints to the actual type of tokens.  */
{int}      {
  errno = 0;
  long n = strtol (yytext, NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    driver.error (*yylloc, "integer is out of range");
  yylval->ival = n;
  return token::NUM_VALUE;
}

{str}       yylval->sval = new std::string (yytext); return token::STR_VALUE;

.          driver.error (*yylloc, "invalid character");


         /* Convert floats to the actual type of tokens.  */
{float}      {
  errno = 0;
  double d = strtod (yytext, NULL);
  /* verification DBL_MIN <= d is not working... why?! :-( */
  if (! (d <= DBL_MAX && errno != ERANGE))
    driver.error (*yylloc, "float is out of range");
  yylval->dval = d;
  return token::COST_VALUE;
}


%%


void XmlParserDriver::scan_begin (){
  yy_flex_debug = trace_scanning;
  if (file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error (std::string ("cannot open ") + file);
      exit (1);
    }
}

void XmlParserDriver::scan_end (){
  fclose (yyin);
}
