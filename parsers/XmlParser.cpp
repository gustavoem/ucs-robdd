
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */


/* Line 311 of lalr1.cc  */
#line 41 "parsers/XmlParser.cpp"


#include "XmlParser.hpp"

/* User implementation prologue.  */


/* Line 317 of lalr1.cc  */
#line 50 "parsers/XmlParser.cpp"
/* Unqualified %code blocks.  */

/* Line 318 of lalr1.cc  */
#line 53 "parsers/XmlParser.yy"

#include "XmlParserDriver.h"
std::stringstream out;
pair<map<string, float>::iterator,bool> ret;



/* Line 318 of lalr1.cc  */
#line 63 "parsers/XmlParser.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace yy {

/* Line 380 of lalr1.cc  */
#line 132 "parsers/XmlParser.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  XmlParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  XmlParser::XmlParser (XmlParserDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  XmlParser::~XmlParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  XmlParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
        case 3: /* "\"open ElementSet\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 209 "parsers/XmlParser.cpp"
	break;
      case 4: /* "\"close ElementSet\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 218 "parsers/XmlParser.cpp"
	break;
      case 5: /* "\"open SetName\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 227 "parsers/XmlParser.cpp"
	break;
      case 6: /* "\"close SetName\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 236 "parsers/XmlParser.cpp"
	break;
      case 7: /* "\"open NumberOfElements\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 245 "parsers/XmlParser.cpp"
	break;
      case 8: /* "\"close NumberOfElements\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 254 "parsers/XmlParser.cpp"
	break;
      case 9: /* "\"open MaxNumberOfElementValues\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 263 "parsers/XmlParser.cpp"
	break;
      case 10: /* "\"close MaxNumberOfElementValues\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 272 "parsers/XmlParser.cpp"
	break;
      case 11: /* "\"open Element\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 281 "parsers/XmlParser.cpp"
	break;
      case 12: /* "\"close Element\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 290 "parsers/XmlParser.cpp"
	break;
      case 13: /* "\"open Cost\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 299 "parsers/XmlParser.cpp"
	break;
      case 14: /* "\"close Cost\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 308 "parsers/XmlParser.cpp"
	break;
      case 15: /* "\"open name\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 317 "parsers/XmlParser.cpp"
	break;
      case 16: /* "\"close name\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 326 "parsers/XmlParser.cpp"
	break;
      case 17: /* "\"open value\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 335 "parsers/XmlParser.cpp"
	break;
      case 18: /* "\"close value\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 344 "parsers/XmlParser.cpp"
	break;
      case 19: /* "\"XML header\"" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 353 "parsers/XmlParser.cpp"
	break;
      case 20: /* "\"string value\"" */

/* Line 449 of lalr1.cc  */
#line 85 "parsers/XmlParser.yy"
	{ debug_stream () << *(yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 362 "parsers/XmlParser.cpp"
	break;
      case 25: /* "set" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 371 "parsers/XmlParser.cpp"
	break;
      case 26: /* "element" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 380 "parsers/XmlParser.cpp"
	break;
      case 28: /* "value" */

/* Line 449 of lalr1.cc  */
#line 87 "parsers/XmlParser.yy"
	{ debug_stream () << (yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 389 "parsers/XmlParser.cpp"
	break;
       default:
	  break;
      }
  }


  void
  XmlParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  XmlParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 20: /* "\"string value\"" */

/* Line 480 of lalr1.cc  */
#line 86 "parsers/XmlParser.yy"
	{ delete (yyvaluep->sval); };

/* Line 480 of lalr1.cc  */
#line 428 "parsers/XmlParser.cpp"
	break;

	default:
	  break;
      }
  }

  void
  XmlParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  XmlParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  XmlParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  XmlParser::debug_level_type
  XmlParser::debug_level () const
  {
    return yydebug_;
  }

  void
  XmlParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  XmlParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 36 "parsers/XmlParser.yy"
{
  // Initialize the initial location.
  yylloc.begin.filename = yylloc.end.filename = &driver.file;
}

/* Line 553 of lalr1.cc  */
#line 514 "parsers/XmlParser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 9:

/* Line 678 of lalr1.cc  */
#line 110 "parsers/XmlParser.yy"
    {
          								                   driver.set_name = *(yysemantic_stack_[(3) - (2)].sval);  
                                                           delete (yysemantic_stack_[(3) - (2)].sval); 
                                                          }
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 115 "parsers/XmlParser.yy"
    {
              											   out << (yysemantic_stack_[(3) - (2)].ival);
          								                   driver.set_name = out.str ();
          								                   out.clear ();  
														   out.str (std::string ());
                                                           }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 122 "parsers/XmlParser.yy"
    {
                driver.number_of_elements = (yysemantic_stack_[(3) - (2)].ival);
                driver.list_of_elements = new Element*[(yysemantic_stack_[(3) - (2)].ival)];
                if (driver.list_of_elements == 0)
			        std::cout << "Error: could not allocate memory for ElementSet elements!" << std::endl;
               }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 129 "parsers/XmlParser.yy"
    { 
                                                           driver.number_of_values = (yysemantic_stack_[(3) - (2)].ival);
                                                          }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 137 "parsers/XmlParser.yy"
    { 
				ret = driver.explicit_cost.insert (pair<string, float> (*(yysemantic_stack_[(6) - (2)].sval), (yysemantic_stack_[(6) - (5)].dval)));
				if (!ret.second)
					std::cout << "Error adding explicit cost function element " << (yysemantic_stack_[(6) - (2)].sval) << std::endl;
	            delete (yysemantic_stack_[(6) - (2)].sval);   
             }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 147 "parsers/XmlParser.yy"
    { 
              driver.current_element++;
              driver.list_of_elements[driver.current_element-1] = 
                  new Element(driver.number_of_values, "elem");
              if (driver.list_of_elements[driver.current_element-1] == 0)
			      std::cout << "Error: could not allocate memory for current Element!" << std::endl;
              driver.list_of_elements[driver.current_element-1]->set_element_name (*(yysemantic_stack_[(3) - (2)].sval)); 
              delete (yysemantic_stack_[(3) - (2)].sval);   
             }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 157 "parsers/XmlParser.yy"
    { 
              out << (yysemantic_stack_[(3) - (2)].ival);
              driver.current_element++;
              driver.list_of_elements[driver.current_element-1] = 
                  new Element(driver.number_of_values, "elem");
              if (driver.list_of_elements[driver.current_element-1] == 0)
			      std::cout << "Error: could not allocate memory for current Element!" << std::endl;
              driver.list_of_elements[driver.current_element-1]->set_element_name (out.str());
          								                   out.clear ();  
														   out.str (std::string ());
             }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 169 "parsers/XmlParser.yy"
    { 
              driver.list_of_elements[driver.current_element-1]->add_element_value ((yysemantic_stack_[(4) - (3)].ival));
             }
    break;



/* Line 678 of lalr1.cc  */
#line 729 "parsers/XmlParser.cpp"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  XmlParser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char XmlParser::yypact_ninf_ = -9;
  const signed char
  XmlParser::yypact_[] =
  {
        -3,    -1,    10,    21,     7,     4,    11,     8,    16,    -2,
      -9,    -1,    -9,    27,    28,    29,    25,     9,     2,    18,
      22,    -9,    -9,    13,    -9,    -9,    -9,    -9,    23,    24,
      -9,    20,    26,    -9,    -9,    -9,    -9,    30,    32,    -9,
      31,    33,    -9
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  XmlParser::yydefact_[] =
  {
         2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     4,     6,     0,     9,    10,    11,    12,     0,     0,
       7,     0,     0,     8,     3,    14,    15,     0,     0,    16,
       0,     0,    13
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  XmlParser::yypgoto_[] =
  {
        -9,    -9,    34,    -8,    -9,    -9
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  XmlParser::yydefgoto_[] =
  {
        -1,     3,     9,    10,    20,    18
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char XmlParser::yytable_ninf_ = -1;
  const unsigned char
  XmlParser::yytable_[] =
  {
         1,    22,    21,     4,     4,     5,     5,     6,     6,     7,
       7,     8,     8,    11,    30,    22,     2,    34,     4,    31,
       5,    12,     6,    17,     7,    15,     8,    13,    14,    28,
      29,    19,    16,    24,    25,    27,    33,    26,    32,    35,
      36,    37,    38,     0,     0,    23,     0,     0,    39,    40,
       0,    42,     0,    41
  };

  /* YYCHECK.  */
  const signed char
  XmlParser::yycheck_[] =
  {
         3,     9,     4,     5,     5,     7,     7,     9,     9,    11,
      11,    13,    13,     3,    12,    23,    19,     4,     5,    17,
       7,     0,     9,    15,    11,    21,    13,    20,    21,    20,
      21,    15,    21,     6,     6,    10,    14,     8,    20,    16,
      16,    21,    16,    -1,    -1,    11,    -1,    -1,    18,    17,
      -1,    18,    -1,    22
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  XmlParser::yystos_[] =
  {
         0,     3,    19,    24,     5,     7,     9,    11,    13,    25,
      26,     3,     0,    20,    21,    21,    21,    15,    28,    15,
      27,     4,    26,    25,     6,     6,     8,    10,    20,    21,
      12,    17,    20,    14,     4,    16,    16,    21,    16,    18,
      17,    22,    18
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  XmlParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  XmlParser::yyr1_[] =
  {
         0,    23,    24,    24,    24,    25,    25,    26,    26,    26,
      26,    26,    26,    27,    28,    28,    28
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  XmlParser::yyr2_[] =
  {
         0,     2,     0,     4,     3,     1,     2,     3,     3,     3,
       3,     3,     3,     6,     3,     3,     4
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const XmlParser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"open ElementSet\"",
  "\"close ElementSet\"", "\"open SetName\"", "\"close SetName\"",
  "\"open NumberOfElements\"", "\"close NumberOfElements\"",
  "\"open MaxNumberOfElementValues\"",
  "\"close MaxNumberOfElementValues\"", "\"open Element\"",
  "\"close Element\"", "\"open Cost\"", "\"close Cost\"", "\"open name\"",
  "\"close name\"", "\"open value\"", "\"close value\"", "\"XML header\"",
  "\"string value\"", "\"numeric value\"", "\"floating point value\"",
  "$accept", "input", "set", "element", "cost", "value", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const XmlParser::rhs_number_type
  XmlParser::yyrhs_[] =
  {
        24,     0,    -1,    -1,    19,     3,    25,     4,    -1,     3,
      25,     4,    -1,    26,    -1,    25,    26,    -1,    11,    28,
      12,    -1,    13,    27,    14,    -1,     5,    20,     6,    -1,
       5,    21,     6,    -1,     7,    21,     8,    -1,     9,    21,
      10,    -1,    15,    20,    16,    17,    22,    18,    -1,    15,
      20,    16,    -1,    15,    21,    16,    -1,    28,    17,    21,
      18,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  XmlParser::yyprhs_[] =
  {
         0,     0,     3,     4,     9,    13,    15,    18,    22,    26,
      30,    34,    38,    42,    49,    53,    57
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  XmlParser::yyrline_[] =
  {
         0,    95,    95,    96,    97,   101,   102,   106,   108,   110,
     115,   122,   129,   136,   147,   157,   169
  };

  // Print the state stack on the debug stream.
  void
  XmlParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  XmlParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  XmlParser::token_number_type
  XmlParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int XmlParser::yyeof_ = 0;
  const int XmlParser::yylast_ = 53;
  const int XmlParser::yynnts_ = 6;
  const int XmlParser::yyempty_ = -2;
  const int XmlParser::yyfinal_ = 12;
  const int XmlParser::yyterror_ = 1;
  const int XmlParser::yyerrcode_ = 256;
  const int XmlParser::yyntokens_ = 23;

  const unsigned int XmlParser::yyuser_token_number_max_ = 277;
  const XmlParser::token_number_type XmlParser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // yy

/* Line 1054 of lalr1.cc  */
#line 1179 "parsers/XmlParser.cpp"


/* Line 1056 of lalr1.cc  */
#line 175 "parsers/XmlParser.yy"


void yy::XmlParser::error (const yy::XmlParser::location_type& l,
                           const std::string& m){
  driver.error (l, m);
}

