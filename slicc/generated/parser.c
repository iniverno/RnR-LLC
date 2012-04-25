/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     STRING = 259,
     NUMBER = 260,
     FLOATNUMBER = 261,
     LIT_BOOL = 262,
     VOID = 263,
     IMBED = 264,
     IMBED_TYPE = 265,
     CHIP = 266,
     THIS = 267,
     ASSIGN = 268,
     DOUBLE_COLON = 269,
     DOT = 270,
     SEMICOLON = 271,
     COLON = 272,
     GLOBAL_DECL = 273,
     MACHINE_DECL = 274,
     IN_PORT_DECL = 275,
     OUT_PORT_DECL = 276,
     PEEK = 277,
     ENQUEUE = 278,
     COPY_HEAD = 279,
     CHECK_ALLOCATE = 280,
     CHECK_STOP_SLOTS = 281,
     DEBUG_EXPR_TOKEN = 282,
     DEBUG_MSG_TOKEN = 283,
     ACTION_DECL = 284,
     TRANSITION_DECL = 285,
     TYPE_DECL = 286,
     STRUCT_DECL = 287,
     EXTERN_TYPE_DECL = 288,
     ENUM_DECL = 289,
     TYPE_FIELD = 290,
     OTHER = 291,
     IF = 292,
     ELSE = 293,
     RETURN = 294,
     EQ = 295,
     NE = 296,
     LE = 297,
     GE = 298,
     NOT = 299,
     AND = 300,
     OR = 301,
     PLUS = 302,
     DASH = 303,
     STAR = 304,
     SLASH = 305,
     RIGHTSHIFT = 306,
     LEFTSHIFT = 307
   };
#endif
/* Tokens.  */
#define IDENT 258
#define STRING 259
#define NUMBER 260
#define FLOATNUMBER 261
#define LIT_BOOL 262
#define VOID 263
#define IMBED 264
#define IMBED_TYPE 265
#define CHIP 266
#define THIS 267
#define ASSIGN 268
#define DOUBLE_COLON 269
#define DOT 270
#define SEMICOLON 271
#define COLON 272
#define GLOBAL_DECL 273
#define MACHINE_DECL 274
#define IN_PORT_DECL 275
#define OUT_PORT_DECL 276
#define PEEK 277
#define ENQUEUE 278
#define COPY_HEAD 279
#define CHECK_ALLOCATE 280
#define CHECK_STOP_SLOTS 281
#define DEBUG_EXPR_TOKEN 282
#define DEBUG_MSG_TOKEN 283
#define ACTION_DECL 284
#define TRANSITION_DECL 285
#define TYPE_DECL 286
#define STRUCT_DECL 287
#define EXTERN_TYPE_DECL 288
#define ENUM_DECL 289
#define TYPE_FIELD 290
#define OTHER 291
#define IF 292
#define ELSE 293
#define RETURN 294
#define EQ 295
#define NE 296
#define LE 297
#define GE 298
#define NOT 299
#define AND 300
#define OR 301
#define PLUS 302
#define DASH 303
#define STAR 304
#define SLASH 305
#define RIGHTSHIFT 306
#define LEFTSHIFT 307




/* Copy the first part of user declarations.  */
#line 61 "parser/parser.y"

#include <string>
#include <stdio.h>
#include <assert.h>
#include "ASTs.h"

#define YYMAXDEPTH 100000
#define YYERROR_VERBOSE

extern char* yytext;

extern "C" void yyerror(char*);
extern "C" int yylex();



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 77 "parser/parser.y"
{
  string* str_ptr;
  Vector<string>* string_vector_ptr; 

  // Decls
  DeclAST* decl_ptr;
  DeclListAST* decl_list_ptr;
  Vector<DeclAST*>* decl_vector_ptr; 
  
  // TypeField
  TypeFieldAST* type_field_ptr;
  Vector<TypeFieldAST*>* type_field_vector_ptr;
  
  // Type
  TypeAST* type_ptr;
  Vector<TypeAST*>* type_vector_ptr;

  // Formal Params
  FormalParamAST* formal_param_ptr;
  Vector<FormalParamAST*>* formal_param_vector_ptr;

  // Statements
  StatementAST* statement_ptr;
  StatementListAST* statement_list_ptr;
  Vector<StatementAST*>* statement_vector_ptr; 

  // Pairs
  PairAST* pair_ptr;
  PairListAST* pair_list_ptr;

  // Expressions
  VarExprAST* var_expr_ptr;
  ExprAST* expr_ptr;
  Vector<ExprAST*>* expr_vector_ptr; 
}
/* Line 193 of yacc.c.  */
#line 252 "generated/parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 265 "generated/parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   710

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  316

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      56,    57,     2,     2,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,     2,
      41,    61,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    42,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    11,    20,    27,    38,
      49,    60,    69,    76,    85,    94,   103,   112,   117,   125,
     133,   141,   149,   152,   153,   158,   164,   167,   168,   176,
     179,   180,   184,   186,   187,   191,   193,   195,   197,   199,
     201,   203,   204,   208,   210,   213,   215,   219,   221,   225,
     229,   232,   233,   236,   237,   241,   243,   247,   251,   253,
     257,   260,   261,   265,   267,   268,   271,   276,   285,   293,
     302,   308,   318,   320,   324,   332,   338,   346,   348,   350,
     352,   357,   371,   382,   399,   413,   417,   424,   431,   436,
     440,   444,   448,   452,   456,   460,   464,   468,   472,   476,
     480,   484,   488,   492,   496,   498,   500,   502,   504,   508,
     510
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      65,     0,    -1,    66,    -1,    67,    -1,    68,    67,    -1,
      -1,    19,    56,    83,    86,    57,    58,    66,    59,    -1,
      29,    56,    83,    86,    57,    89,    -1,    20,    56,    83,
      60,    77,    60,    97,    86,    57,    89,    -1,    21,    56,
      83,    60,    77,    60,    97,    86,    57,    16,    -1,    30,
      56,    84,    60,    84,    60,    83,    86,    57,    84,    -1,
      30,    56,    84,    60,    84,    86,    57,    84,    -1,    33,
      56,    77,    86,    57,    16,    -1,    33,    56,    77,    86,
      57,    58,    71,    59,    -1,    18,    56,    77,    86,    57,
      58,    69,    59,    -1,    32,    56,    77,    86,    57,    58,
      69,    59,    -1,    34,    56,    77,    86,    57,    58,    73,
      59,    -1,    77,    83,    86,    16,    -1,    77,    83,    56,
      80,    57,    86,    16,    -1,    78,    83,    56,    80,    57,
      86,    16,    -1,    77,    83,    56,    80,    57,    86,    89,
      -1,    78,    83,    56,    80,    57,    86,    89,    -1,    70,
      69,    -1,    -1,    77,    83,    86,    16,    -1,    77,    83,
      13,    94,    16,    -1,    72,    71,    -1,    -1,    79,    83,
      56,    75,    57,    86,    16,    -1,    74,    73,    -1,    -1,
      83,    86,    16,    -1,    76,    -1,    -1,    77,    60,    76,
      -1,    77,    -1,    83,    -1,     8,    -1,    77,    -1,    78,
      -1,    81,    -1,    -1,    82,    60,    81,    -1,    82,    -1,
      77,    83,    -1,     3,    -1,    58,    85,    59,    -1,    83,
      -1,    83,    16,    85,    -1,    83,    60,    85,    -1,    83,
      85,    -1,    -1,    60,    87,    -1,    -1,    88,    60,    87,
      -1,    88,    -1,    83,    61,     4,    -1,    83,    61,    83,
      -1,     4,    -1,    58,    90,    59,    -1,    92,    90,    -1,
      -1,    94,    60,    91,    -1,    94,    -1,    -1,    94,    16,
      -1,    94,    13,    94,    16,    -1,    23,    56,    97,    60,
      77,    86,    57,    89,    -1,    22,    56,    97,    60,    77,
      57,    89,    -1,    24,    56,    97,    60,    97,    86,    57,
      16,    -1,    25,    56,    97,    57,    16,    -1,    26,    56,
      97,    60,     4,    60,     4,    57,    16,    -1,    93,    -1,
      39,    94,    16,    -1,    37,    56,    94,    57,    89,    38,
      89,    -1,    37,    56,    94,    57,    89,    -1,    37,    56,
      94,    57,    89,    38,    93,    -1,    97,    -1,    95,    -1,
      96,    -1,    83,    56,    91,    57,    -1,    12,    15,    97,
      55,    94,    62,    15,    97,    15,    83,    56,    91,    57,
      -1,    12,    15,    97,    55,    94,    62,    15,    97,    15,
      98,    -1,    11,    55,    94,    62,    15,    97,    55,    94,
      62,    15,    97,    15,    83,    56,    91,    57,    -1,    11,
      55,    94,    62,    15,    97,    55,    94,    62,    15,    97,
      15,    98,    -1,    94,    15,    98,    -1,    94,    15,    83,
      56,    91,    57,    -1,    77,    14,    83,    56,    91,    57,
      -1,    94,    55,    91,    62,    -1,    94,    51,    94,    -1,
      94,    52,    94,    -1,    94,    49,    94,    -1,    94,    50,
      94,    -1,    94,    41,    94,    -1,    94,    43,    94,    -1,
      94,    44,    94,    -1,    94,    45,    94,    -1,    94,    40,
      94,    -1,    94,    42,    94,    -1,    94,    47,    94,    -1,
      94,    48,    94,    -1,    94,    53,    94,    -1,    94,    54,
      94,    -1,    56,    94,    57,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,    83,    63,    83,    -1,    83,    -1,
      83,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   165,   165,   167,   169,   170,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   193,   194,   197,   198,   202,   203,   206,   210,
     211,   214,   218,   219,   222,   223,   226,   229,   232,   233,
     237,   238,   241,   242,   245,   249,   251,   252,   255,   256,
     257,   258,   262,   263,   265,   266,   269,   270,   271,   276,
     279,   280,   283,   284,   285,   288,   289,   290,   291,   293,
     294,   295,   296,   297,   300,   301,   302,   305,   306,   307,
     308,   312,   314,   316,   318,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   341,   344,   345,   346,   347,   350,   353,
     356
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "STRING", "NUMBER",
  "FLOATNUMBER", "LIT_BOOL", "VOID", "IMBED", "IMBED_TYPE", "CHIP", "THIS",
  "ASSIGN", "DOUBLE_COLON", "DOT", "SEMICOLON", "COLON", "GLOBAL_DECL",
  "MACHINE_DECL", "IN_PORT_DECL", "OUT_PORT_DECL", "PEEK", "ENQUEUE",
  "COPY_HEAD", "CHECK_ALLOCATE", "CHECK_STOP_SLOTS", "DEBUG_EXPR_TOKEN",
  "DEBUG_MSG_TOKEN", "ACTION_DECL", "TRANSITION_DECL", "TYPE_DECL",
  "STRUCT_DECL", "EXTERN_TYPE_DECL", "ENUM_DECL", "TYPE_FIELD", "OTHER",
  "IF", "ELSE", "RETURN", "EQ", "'<'", "NE", "'>'", "LE", "GE", "NOT",
  "AND", "OR", "PLUS", "DASH", "STAR", "SLASH", "RIGHTSHIFT", "LEFTSHIFT",
  "'['", "'('", "')'", "'{'", "'}'", "','", "'='", "']'", "':'", "$accept",
  "file", "decl_list", "decls", "decl", "type_members", "type_member",
  "type_methods", "type_method", "type_enums", "type_enum", "type_list",
  "types", "type", "void", "type_or_void", "formal_param_list",
  "formal_params", "formal_param", "ident", "ident_list", "idents",
  "pair_list", "pairs", "pair", "statement_list", "statements",
  "expr_list", "statement", "if_statement", "expr", "literal",
  "enumeration", "var", "field", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    60,   296,    62,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,    91,    40,    41,   123,   125,
      44,    61,    93,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    71,    72,    73,
      73,    74,    75,    75,    76,    76,    77,    78,    79,    79,
      80,    80,    81,    81,    82,    83,    84,    84,    85,    85,
      85,    85,    86,    86,    87,    87,    88,    88,    88,    89,
      90,    90,    91,    91,    91,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    95,    95,    95,    95,    96,    97,
      98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     8,     6,    10,    10,
      10,     8,     6,     8,     8,     8,     8,     4,     7,     7,
       7,     7,     2,     0,     4,     5,     2,     0,     7,     2,
       0,     3,     1,     0,     3,     1,     1,     1,     1,     1,
       1,     0,     3,     1,     2,     1,     3,     1,     3,     3,
       2,     0,     2,     0,     3,     1,     3,     3,     1,     3,
       2,     0,     3,     1,     0,     2,     4,     8,     7,     8,
       5,     9,     1,     3,     7,     5,     7,     1,     1,     1,
       4,    13,    10,    16,    13,     3,     6,     6,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     3,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,    45,    37,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     5,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     4,
      53,     0,    53,    53,     0,     0,    53,    51,    47,     0,
      53,    53,    53,    41,     0,     0,    41,     0,     0,     0,
       0,     0,    51,     0,     0,     0,     0,     0,     0,     0,
      40,    43,    58,     0,    52,    55,    17,     0,     0,     0,
       0,     0,     0,    51,    51,    50,    46,    53,     0,     0,
       0,    44,    53,     0,     0,     0,    53,    23,     5,     0,
       0,    61,     7,    48,    49,     0,     0,    23,    12,    27,
      30,     0,    42,    56,    57,    54,     0,     0,    23,     0,
       0,   109,    53,    53,   104,   105,   106,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   109,
       0,    61,    72,     0,    78,    79,    77,    53,     0,     0,
       0,    27,    38,    39,     0,     0,    30,    53,    18,    20,
      19,    21,    14,    22,    53,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    59,    60,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,    11,    15,    13,    26,     0,    16,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,   103,     0,     0,    63,   108,     0,   110,
      85,    97,    93,    98,    94,    95,    96,    99,   100,    91,
      92,    89,    90,   101,   102,     0,     0,    33,    31,     0,
      24,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    80,    64,    66,    64,    88,    10,     0,    32,
      35,    25,     0,     0,     0,    53,    53,    70,     0,    75,
       0,    62,     0,    53,     0,     0,     0,     0,     0,     0,
       0,     0,    87,    86,     0,    34,     0,     0,    68,     0,
       0,     0,    74,    76,    28,     0,     0,    67,    69,     0,
       0,     0,    71,     0,   110,    82,     0,    64,     0,     0,
     110,    84,    81,    64,     0,    83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,   107,   108,   140,   141,   145,
     146,   258,   259,   128,    17,   144,    59,    60,    61,   129,
      39,    53,    45,    64,    65,    92,   130,   215,   131,   132,
     216,   134,   135,   136,   220
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -270
static const yytype_int16 yypact[] =
{
     250,  -270,  -270,   -46,   -43,   -21,   -18,    -8,    11,    13,
      16,    20,     7,  -270,  -270,   250,    91,    91,  -270,    91,
      91,    91,    91,    91,     1,    91,    91,    91,  -270,  -270,
       5,    40,    41,    41,    56,    59,    41,    91,  -270,    62,
      41,    41,    41,    91,    26,    82,    91,    63,    66,    91,
      91,    68,    15,    67,     1,    73,    74,    75,    91,    76,
    -270,    77,  -270,    78,  -270,    80,  -270,    79,    84,    85,
      87,    89,    92,    91,    91,  -270,  -270,    93,    96,   -13,
      98,  -270,    41,    91,   100,    26,    41,    91,   250,    91,
      91,   331,  -270,  -270,  -270,    26,   101,    91,  -270,    60,
      91,   -11,  -270,  -270,  -270,  -270,    -7,   106,    91,    91,
     107,  -270,    41,    41,  -270,  -270,  -270,  -270,   112,   119,
     113,   117,   120,   121,   122,   127,   200,   200,   143,    14,
     128,   331,  -270,   469,  -270,  -270,  -270,    45,     1,   129,
     132,    60,  -270,  -270,    91,   134,    91,    41,  -270,  -270,
    -270,  -270,  -270,  -270,    -5,  -270,   135,   138,   200,    91,
      91,    91,    91,    91,    91,   200,   532,   489,    91,   200,
      91,  -270,  -270,   200,    91,  -270,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   140,  -270,  -270,  -270,  -270,   144,  -270,  -270,   180,
     200,   186,    92,   192,   348,   154,   155,   157,   158,   162,
     160,   510,  -270,  -270,   166,   169,   448,  -270,   553,   167,
    -270,   635,   330,   635,   330,   330,   330,   655,   614,    27,
      27,    38,    38,   594,   594,   152,     1,    91,  -270,   573,
    -270,  -270,  -270,   212,   200,    91,    91,    91,   213,   131,
      92,   200,  -270,   200,  -270,   200,  -270,  -270,   171,  -270,
     170,  -270,    91,   391,   174,    41,    41,  -270,   172,   195,
     177,  -270,   178,    41,    91,   184,   225,    92,   185,   187,
     237,    -1,  -270,  -270,   232,  -270,   200,    91,  -270,    92,
     233,   193,  -270,  -270,  -270,   407,   240,  -270,  -270,   241,
     246,    91,  -270,    91,   207,  -270,   251,   200,    91,   208,
     211,  -270,  -270,   200,   215,  -270
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -270,  -270,   189,   258,  -270,   -37,  -270,   137,  -270,   142,
    -270,  -270,    18,   102,   -85,  -270,   229,   198,  -270,     0,
     -52,   -40,   139,   204,  -270,   -95,   159,  -189,  -270,     4,
     133,  -270,  -270,   -49,  -269
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -37
static const yytype_int16 yytable[] =
{
      18,   235,    77,    98,     1,   148,   149,    28,   200,   150,
      19,   151,    75,    20,   143,    18,    30,    31,     1,    18,
      33,    34,    35,    36,    38,    18,    18,    18,   -36,     1,
      62,    73,   305,    93,    94,    21,   125,    52,    22,   311,
     112,   113,   174,    18,    63,    99,    18,    91,    23,    18,
      18,    91,    52,   174,    38,    44,   143,    91,    81,    37,
     139,    43,   270,     1,   271,    44,   272,    24,     2,    25,
     169,   153,    26,    52,    52,    74,    27,   170,   186,   187,
     188,   189,   190,    18,   104,    63,   192,    18,    18,   111,
     111,   188,   189,   190,     1,   137,    46,    18,    66,    18,
     147,    44,    16,     1,   103,    44,    84,   241,    18,   154,
     205,   206,   207,   208,   209,   210,    49,    16,   309,    50,
      68,    32,    54,    69,   314,    72,    76,    40,    41,    42,
      78,    79,    80,    82,   159,   268,    86,    83,    38,    84,
      85,    18,    87,    88,   196,    58,   147,    89,    58,    90,
      91,    70,    71,    95,    97,   269,   100,   168,   138,   111,
     111,   111,   111,   111,   111,   152,   155,   158,   214,   160,
     217,    47,    48,   161,   219,    51,   162,   163,   164,    55,
      56,    57,   288,   165,   257,    58,   292,   171,   193,   109,
      16,   194,   202,   197,   297,   203,   238,   236,   266,   109,
     237,   142,   240,     1,   114,   115,   116,   117,   242,   244,
     109,   118,   119,   275,   256,   245,    96,   246,   247,   248,
     249,   101,   251,   255,   133,   106,   252,   262,   273,   267,
     274,   277,   280,   281,   282,   283,    38,    18,   296,   286,
     287,   291,   289,   142,   290,    18,    18,   111,   294,   298,
     299,   156,   157,     1,   306,   301,   127,   302,     2,   166,
     167,   303,   111,   307,   133,   312,   308,   313,     3,     4,
       5,     6,   315,    29,    18,    67,   191,   110,   195,     7,
       8,   102,     9,    10,    11,   293,   199,   111,   198,   105,
     172,   204,   285,   201,     0,     0,     0,     0,   211,     0,
       0,   304,     0,   111,     0,     0,   218,     0,   310,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   239,     1,   114,   115,   116,   117,   260,
       0,     0,   118,   119,     0,   174,     0,   264,   265,     0,
       0,     0,     0,   120,   121,   122,   123,   124,     0,     0,
       0,     0,     0,   174,     0,     0,     0,     0,   125,     0,
     126,   -37,     0,   -37,   -37,   -37,   260,   263,     0,   184,
     185,   186,   187,   188,   189,   190,     0,   127,   176,   177,
     178,   179,   180,   181,     0,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   278,   279,   174,     0,     0,     0,
     243,     0,   284,     0,     0,     0,     0,     0,     0,   295,
       0,     0,   174,     0,     0,     0,     0,     0,     0,     0,
       0,   176,   177,   178,   179,   180,   181,     0,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   176,   177,   178,
     179,   180,   181,   276,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   174,     0,     0,     0,     0,     0,   300,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,     0,   174,   175,     0,     0,   176,   177,
     178,   179,   180,   181,     0,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   174,     0,     0,     0,   253,   176,
     177,   178,   179,   180,   181,     0,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   174,     0,     0,     0,   176,
     177,   178,   179,   180,   181,     0,   182,   183,   184,   185,
     186,   187,   188,   189,   190,     0,   213,   174,   212,     0,
     176,   177,   178,   179,   180,   181,     0,   182,   183,   184,
     185,   186,   187,   188,   189,   190,     0,   250,   174,   254,
       0,     0,   176,   177,   178,   179,   180,   181,     0,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   174,   261,
       0,     0,     0,   176,   177,   178,   179,   180,   181,     0,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   174,
       0,     0,     0,   176,   177,   178,   179,   180,   181,     0,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   174,
       0,     0,     0,     0,   176,   177,   178,   179,   180,   181,
       0,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     174,     0,     0,     0,   176,   177,   178,   179,   180,   181,
       0,   182,     0,   184,   185,   186,   187,   188,   189,   190,
     174,     0,     0,     0,     0,   -37,   177,   -37,   179,   180,
     181,     0,     0,     0,   184,   185,   186,   187,   188,   189,
     190,     0,     0,     0,     0,   176,   177,   178,   179,   180,
     181,     0,     0,     0,   184,   185,   186,   187,   188,   189,
     190
};

static const yytype_int16 yycheck[] =
{
       0,   190,    54,    16,     3,    16,   101,     0,    13,    16,
      56,   106,    52,    56,    99,    15,    16,    17,     3,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    14,     3,
       4,    16,   301,    73,    74,    56,    37,    37,    56,   308,
      89,    90,    15,    43,    44,    58,    46,    58,    56,    49,
      50,    58,    52,    15,    54,    60,   141,    58,    58,    58,
      97,    56,   251,     3,   253,    60,   255,    56,     8,    56,
      56,   108,    56,    73,    74,    60,    56,    63,    51,    52,
      53,    54,    55,    83,    84,    85,   138,    87,    88,    89,
      90,    53,    54,    55,     3,    95,    56,    97,    16,    99,
     100,    60,     0,     3,     4,    60,    61,   202,   108,   109,
     159,   160,   161,   162,   163,   164,    60,    15,   307,    60,
      57,    19,    60,    57,   313,    57,    59,    25,    26,    27,
      57,    57,    57,    57,    15,     4,    57,    60,   138,    61,
      60,   141,    58,    58,   144,    43,   146,    60,    46,    60,
      58,    49,    50,    60,    58,   250,    58,    14,    57,   159,
     160,   161,   162,   163,   164,    59,    59,    55,   168,    56,
     170,    32,    33,    56,   174,    36,    56,    56,    56,    40,
      41,    42,   277,    56,   236,    83,   281,    59,    59,    87,
      88,    59,    57,    59,   289,    57,    16,    57,   247,    97,
      56,    99,    16,     3,     4,     5,     6,     7,    16,    55,
     108,    11,    12,   262,    62,    60,    77,    60,    60,    57,
      60,    82,    56,    56,    91,    86,    57,    15,    57,    16,
      60,    57,    60,    38,    57,    57,   236,   237,   287,    55,
      15,     4,    57,   141,    57,   245,   246,   247,    16,    16,
      57,   112,   113,     3,   303,    15,    56,    16,     8,   126,
     127,    15,   262,    56,   131,    57,    15,    56,    18,    19,
      20,    21,    57,    15,   274,    46,   137,    88,   141,    29,
      30,    83,    32,    33,    34,   281,   147,   287,   146,    85,
     131,   158,   274,   154,    -1,    -1,    -1,    -1,   165,    -1,
      -1,   301,    -1,   303,    -1,    -1,   173,    -1,   308,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,     3,     4,     5,     6,     7,   237,
      -1,    -1,    11,    12,    -1,    15,    -1,   245,   246,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    37,    -1,
      39,    41,    -1,    43,    44,    45,   274,   244,    -1,    49,
      50,    51,    52,    53,    54,    55,    -1,    56,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,   265,   266,    15,    -1,    -1,    -1,
      62,    -1,   273,    -1,    -1,    -1,    -1,    -1,    -1,   286,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    40,    41,    42,
      43,    44,    45,    62,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    15,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    13,    -1,    15,    16,    -1,    -1,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    15,    -1,    -1,    -1,    60,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    15,    -1,    -1,    -1,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    57,    15,    16,    -1,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    57,    15,    16,
      -1,    -1,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    15,    16,
      -1,    -1,    -1,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    15,
      -1,    -1,    -1,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    15,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      15,    -1,    -1,    -1,    40,    41,    42,    43,    44,    45,
      -1,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      15,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,    18,    19,    20,    21,    29,    30,    32,
      33,    34,    65,    66,    67,    68,    77,    78,    83,    56,
      56,    56,    56,    56,    56,    56,    56,    56,     0,    67,
      83,    83,    77,    83,    83,    83,    83,    58,    83,    84,
      77,    77,    77,    56,    60,    86,    56,    86,    86,    60,
      60,    86,    83,    85,    60,    86,    86,    86,    77,    80,
      81,    82,     4,    83,    87,    88,    16,    80,    57,    57,
      77,    77,    57,    16,    60,    85,    59,    84,    57,    57,
      57,    83,    57,    60,    61,    60,    57,    58,    58,    60,
      60,    58,    89,    85,    85,    60,    86,    58,    16,    58,
      58,    86,    81,     4,    83,    87,    86,    69,    70,    77,
      66,    83,    97,    97,     4,     5,     6,     7,    11,    12,
      22,    23,    24,    25,    26,    37,    39,    56,    77,    83,
      90,    92,    93,    94,    95,    96,    97,    83,    57,    69,
      71,    72,    77,    78,    79,    73,    74,    83,    16,    89,
      16,    89,    59,    69,    83,    59,    86,    86,    55,    15,
      56,    56,    56,    56,    56,    56,    94,    94,    14,    56,
      63,    59,    90,    13,    15,    16,    40,    41,    42,    43,
      44,    45,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    86,    84,    59,    59,    71,    83,    59,    73,    86,
      13,    86,    57,    57,    94,    97,    97,    97,    97,    97,
      97,    94,    16,    57,    83,    91,    94,    83,    94,    83,
      98,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    91,    57,    56,    16,    94,
      16,    89,    16,    62,    55,    60,    60,    60,    57,    60,
      57,    56,    57,    60,    16,    56,    62,    84,    75,    76,
      77,    16,    15,    94,    77,    77,    97,    16,     4,    89,
      91,    91,    91,    57,    60,    97,    62,    57,    86,    86,
      60,    38,    57,    57,    86,    76,    55,    15,    89,    57,
      57,     4,    89,    93,    16,    94,    97,    89,    16,    57,
      62,    15,    16,    15,    83,    98,    97,    56,    15,    91,
      83,    98,    57,    56,    91,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 165 "parser/parser.y"
    { g_decl_list_ptr = (yyvsp[(1) - (1)].decl_list_ptr); ;}
    break;

  case 3:
#line 167 "parser/parser.y"
    { (yyval.decl_list_ptr) = new DeclListAST((yyvsp[(1) - (1)].decl_vector_ptr)); ;}
    break;

  case 4:
#line 169 "parser/parser.y"
    { (yyvsp[(2) - (2)].decl_vector_ptr)->insertAtTop((yyvsp[(1) - (2)].decl_ptr)); (yyval.decl_vector_ptr) = (yyvsp[(2) - (2)].decl_vector_ptr); ;}
    break;

  case 5:
#line 170 "parser/parser.y"
    { (yyval.decl_vector_ptr) = new Vector<DeclAST*>; ;}
    break;

  case 6:
#line 173 "parser/parser.y"
    { (yyval.decl_ptr) = new MachineAST((yyvsp[(3) - (8)].str_ptr), (yyvsp[(4) - (8)].pair_list_ptr), (yyvsp[(7) - (8)].decl_list_ptr)); ;}
    break;

  case 7:
#line 174 "parser/parser.y"
    { (yyval.decl_ptr) = new ActionDeclAST((yyvsp[(3) - (6)].str_ptr), (yyvsp[(4) - (6)].pair_list_ptr), (yyvsp[(6) - (6)].statement_list_ptr)); ;}
    break;

  case 8:
#line 175 "parser/parser.y"
    { (yyval.decl_ptr) = new InPortDeclAST((yyvsp[(3) - (10)].str_ptr), (yyvsp[(5) - (10)].type_ptr), (yyvsp[(7) - (10)].var_expr_ptr), (yyvsp[(8) - (10)].pair_list_ptr), (yyvsp[(10) - (10)].statement_list_ptr)); ;}
    break;

  case 9:
#line 176 "parser/parser.y"
    { (yyval.decl_ptr) = new OutPortDeclAST((yyvsp[(3) - (10)].str_ptr), (yyvsp[(5) - (10)].type_ptr), (yyvsp[(7) - (10)].var_expr_ptr), (yyvsp[(8) - (10)].pair_list_ptr)); ;}
    break;

  case 10:
#line 177 "parser/parser.y"
    { (yyval.decl_ptr) = new TransitionDeclAST((yyvsp[(3) - (10)].string_vector_ptr), (yyvsp[(5) - (10)].string_vector_ptr), (yyvsp[(7) - (10)].str_ptr), (yyvsp[(8) - (10)].pair_list_ptr), (yyvsp[(10) - (10)].string_vector_ptr)); ;}
    break;

  case 11:
#line 178 "parser/parser.y"
    { (yyval.decl_ptr) = new TransitionDeclAST((yyvsp[(3) - (8)].string_vector_ptr), (yyvsp[(5) - (8)].string_vector_ptr), NULL, (yyvsp[(6) - (8)].pair_list_ptr), (yyvsp[(8) - (8)].string_vector_ptr)); ;}
    break;

  case 12:
#line 179 "parser/parser.y"
    { (yyvsp[(4) - (6)].pair_list_ptr)->addPair(new PairAST("external", "yes")); (yyval.decl_ptr) = new TypeDeclAST((yyvsp[(3) - (6)].type_ptr), (yyvsp[(4) - (6)].pair_list_ptr), NULL); ;}
    break;

  case 13:
#line 180 "parser/parser.y"
    { (yyvsp[(4) - (8)].pair_list_ptr)->addPair(new PairAST("external", "yes")); (yyval.decl_ptr) = new TypeDeclAST((yyvsp[(3) - (8)].type_ptr), (yyvsp[(4) - (8)].pair_list_ptr), (yyvsp[(7) - (8)].type_field_vector_ptr)); ;}
    break;

  case 14:
#line 181 "parser/parser.y"
    { (yyvsp[(4) - (8)].pair_list_ptr)->addPair(new PairAST("global", "yes"));(yyval.decl_ptr) = new TypeDeclAST((yyvsp[(3) - (8)].type_ptr), (yyvsp[(4) - (8)].pair_list_ptr), (yyvsp[(7) - (8)].type_field_vector_ptr)); ;}
    break;

  case 15:
#line 182 "parser/parser.y"
    { (yyval.decl_ptr) = new TypeDeclAST((yyvsp[(3) - (8)].type_ptr), (yyvsp[(4) - (8)].pair_list_ptr), (yyvsp[(7) - (8)].type_field_vector_ptr)); ;}
    break;

  case 16:
#line 183 "parser/parser.y"
    { (yyvsp[(4) - (8)].pair_list_ptr)->addPair(new PairAST("enumeration", "yes")); (yyval.decl_ptr) = new EnumDeclAST((yyvsp[(3) - (8)].type_ptr), (yyvsp[(4) - (8)].pair_list_ptr), (yyvsp[(7) - (8)].type_field_vector_ptr)); ;}
    break;

  case 17:
#line 184 "parser/parser.y"
    { (yyval.decl_ptr) = new ObjDeclAST((yyvsp[(1) - (4)].type_ptr), (yyvsp[(2) - (4)].str_ptr), (yyvsp[(3) - (4)].pair_list_ptr)); ;}
    break;

  case 18:
#line 185 "parser/parser.y"
    { (yyval.decl_ptr) = new FuncDeclAST((yyvsp[(1) - (7)].type_ptr), (yyvsp[(2) - (7)].str_ptr), (yyvsp[(4) - (7)].formal_param_vector_ptr), (yyvsp[(6) - (7)].pair_list_ptr), NULL); ;}
    break;

  case 19:
#line 186 "parser/parser.y"
    { (yyval.decl_ptr) = new FuncDeclAST((yyvsp[(1) - (7)].type_ptr), (yyvsp[(2) - (7)].str_ptr), (yyvsp[(4) - (7)].formal_param_vector_ptr), (yyvsp[(6) - (7)].pair_list_ptr), NULL); ;}
    break;

  case 20:
#line 187 "parser/parser.y"
    { (yyval.decl_ptr) = new FuncDeclAST((yyvsp[(1) - (7)].type_ptr), (yyvsp[(2) - (7)].str_ptr), (yyvsp[(4) - (7)].formal_param_vector_ptr), (yyvsp[(6) - (7)].pair_list_ptr), (yyvsp[(7) - (7)].statement_list_ptr)); ;}
    break;

  case 21:
#line 188 "parser/parser.y"
    { (yyval.decl_ptr) = new FuncDeclAST((yyvsp[(1) - (7)].type_ptr), (yyvsp[(2) - (7)].str_ptr), (yyvsp[(4) - (7)].formal_param_vector_ptr), (yyvsp[(6) - (7)].pair_list_ptr), (yyvsp[(7) - (7)].statement_list_ptr)); ;}
    break;

  case 22:
#line 193 "parser/parser.y"
    { (yyvsp[(2) - (2)].type_field_vector_ptr)->insertAtTop((yyvsp[(1) - (2)].type_field_ptr)); (yyval.type_field_vector_ptr) = (yyvsp[(2) - (2)].type_field_vector_ptr); ;}
    break;

  case 23:
#line 194 "parser/parser.y"
    { (yyval.type_field_vector_ptr) = new Vector<TypeFieldAST*>; ;}
    break;

  case 24:
#line 197 "parser/parser.y"
    { (yyval.type_field_ptr) = new TypeFieldMemberAST((yyvsp[(1) - (4)].type_ptr), (yyvsp[(2) - (4)].str_ptr), (yyvsp[(3) - (4)].pair_list_ptr), NULL); ;}
    break;

  case 25:
#line 198 "parser/parser.y"
    { (yyval.type_field_ptr) = new TypeFieldMemberAST((yyvsp[(1) - (5)].type_ptr), (yyvsp[(2) - (5)].str_ptr), new PairListAST(), (yyvsp[(4) - (5)].expr_ptr)); ;}
    break;

  case 26:
#line 202 "parser/parser.y"
    { (yyvsp[(2) - (2)].type_field_vector_ptr)->insertAtTop((yyvsp[(1) - (2)].type_field_ptr)); (yyval.type_field_vector_ptr) = (yyvsp[(2) - (2)].type_field_vector_ptr); ;}
    break;

  case 27:
#line 203 "parser/parser.y"
    { (yyval.type_field_vector_ptr) = new Vector<TypeFieldAST*>; ;}
    break;

  case 28:
#line 206 "parser/parser.y"
    { (yyval.type_field_ptr) = new TypeFieldMethodAST((yyvsp[(1) - (7)].type_ptr), (yyvsp[(2) - (7)].str_ptr), (yyvsp[(4) - (7)].type_vector_ptr), (yyvsp[(6) - (7)].pair_list_ptr)); ;}
    break;

  case 29:
#line 210 "parser/parser.y"
    { (yyvsp[(2) - (2)].type_field_vector_ptr)->insertAtTop((yyvsp[(1) - (2)].type_field_ptr)); (yyval.type_field_vector_ptr) = (yyvsp[(2) - (2)].type_field_vector_ptr); ;}
    break;

  case 30:
#line 211 "parser/parser.y"
    { (yyval.type_field_vector_ptr) = new Vector<TypeFieldAST*>; ;}
    break;

  case 31:
#line 214 "parser/parser.y"
    { (yyval.type_field_ptr) = new TypeFieldEnumAST((yyvsp[(1) - (3)].str_ptr), (yyvsp[(2) - (3)].pair_list_ptr)); ;}
    break;

  case 32:
#line 218 "parser/parser.y"
    { (yyval.type_vector_ptr) = (yyvsp[(1) - (1)].type_vector_ptr); ;}
    break;

  case 33:
#line 219 "parser/parser.y"
    { (yyval.type_vector_ptr) = new Vector<TypeAST*>; ;}
    break;

  case 34:
#line 222 "parser/parser.y"
    { (yyvsp[(3) - (3)].type_vector_ptr)->insertAtTop((yyvsp[(1) - (3)].type_ptr)); (yyval.type_vector_ptr) = (yyvsp[(3) - (3)].type_vector_ptr); ;}
    break;

  case 35:
#line 223 "parser/parser.y"
    { (yyval.type_vector_ptr) = new Vector<TypeAST*>; (yyval.type_vector_ptr)->insertAtTop((yyvsp[(1) - (1)].type_ptr)); ;}
    break;

  case 36:
#line 226 "parser/parser.y"
    { (yyval.type_ptr) = new TypeAST((yyvsp[(1) - (1)].str_ptr)); ;}
    break;

  case 37:
#line 229 "parser/parser.y"
    { (yyval.type_ptr) = new TypeAST((yyvsp[(1) - (1)].str_ptr)); ;}
    break;

  case 38:
#line 232 "parser/parser.y"
    { (yyval.type_ptr) = (yyvsp[(1) - (1)].type_ptr); ;}
    break;

  case 39:
#line 233 "parser/parser.y"
    { (yyval.type_ptr) = (yyvsp[(1) - (1)].type_ptr); ;}
    break;

  case 40:
#line 237 "parser/parser.y"
    { (yyval.formal_param_vector_ptr) = (yyvsp[(1) - (1)].formal_param_vector_ptr); ;}
    break;

  case 41:
#line 238 "parser/parser.y"
    { (yyval.formal_param_vector_ptr) = new Vector<FormalParamAST*>; ;}
    break;

  case 42:
#line 241 "parser/parser.y"
    { (yyvsp[(3) - (3)].formal_param_vector_ptr)->insertAtTop((yyvsp[(1) - (3)].formal_param_ptr)); (yyval.formal_param_vector_ptr) = (yyvsp[(3) - (3)].formal_param_vector_ptr); ;}
    break;

  case 43:
#line 242 "parser/parser.y"
    { (yyval.formal_param_vector_ptr) = new Vector<FormalParamAST*>; (yyval.formal_param_vector_ptr)->insertAtTop((yyvsp[(1) - (1)].formal_param_ptr)); ;}
    break;

  case 44:
#line 245 "parser/parser.y"
    { (yyval.formal_param_ptr) = new FormalParamAST((yyvsp[(1) - (2)].type_ptr), (yyvsp[(2) - (2)].str_ptr)); ;}
    break;

  case 45:
#line 249 "parser/parser.y"
    { (yyval.str_ptr) = (yyvsp[(1) - (1)].str_ptr); ;}
    break;

  case 46:
#line 251 "parser/parser.y"
    { (yyval.string_vector_ptr) = (yyvsp[(2) - (3)].string_vector_ptr); ;}
    break;

  case 47:
#line 252 "parser/parser.y"
    { (yyval.string_vector_ptr) = new Vector<string>; (yyval.string_vector_ptr)->insertAtTop(*((yyvsp[(1) - (1)].str_ptr))); delete (yyvsp[(1) - (1)].str_ptr); ;}
    break;

  case 48:
#line 255 "parser/parser.y"
    { (yyvsp[(3) - (3)].string_vector_ptr)->insertAtTop(*((yyvsp[(1) - (3)].str_ptr))); (yyval.string_vector_ptr) = (yyvsp[(3) - (3)].string_vector_ptr); delete (yyvsp[(1) - (3)].str_ptr); ;}
    break;

  case 49:
#line 256 "parser/parser.y"
    { (yyvsp[(3) - (3)].string_vector_ptr)->insertAtTop(*((yyvsp[(1) - (3)].str_ptr))); (yyval.string_vector_ptr) = (yyvsp[(3) - (3)].string_vector_ptr); delete (yyvsp[(1) - (3)].str_ptr); ;}
    break;

  case 50:
#line 257 "parser/parser.y"
    { (yyvsp[(2) - (2)].string_vector_ptr)->insertAtTop(*((yyvsp[(1) - (2)].str_ptr))); (yyval.string_vector_ptr) = (yyvsp[(2) - (2)].string_vector_ptr); delete (yyvsp[(1) - (2)].str_ptr); ;}
    break;

  case 51:
#line 258 "parser/parser.y"
    { (yyval.string_vector_ptr) = new Vector<string>; ;}
    break;

  case 52:
#line 262 "parser/parser.y"
    { (yyval.pair_list_ptr) = (yyvsp[(2) - (2)].pair_list_ptr); ;}
    break;

  case 53:
#line 263 "parser/parser.y"
    { (yyval.pair_list_ptr) = new PairListAST(); ;}
    break;

  case 54:
#line 265 "parser/parser.y"
    { (yyvsp[(3) - (3)].pair_list_ptr)->addPair((yyvsp[(1) - (3)].pair_ptr)); (yyval.pair_list_ptr) = (yyvsp[(3) - (3)].pair_list_ptr); ;}
    break;

  case 55:
#line 266 "parser/parser.y"
    { (yyval.pair_list_ptr) = new PairListAST(); (yyval.pair_list_ptr)->addPair((yyvsp[(1) - (1)].pair_ptr)); ;}
    break;

  case 56:
#line 269 "parser/parser.y"
    { (yyval.pair_ptr) = new PairAST((yyvsp[(1) - (3)].str_ptr), (yyvsp[(3) - (3)].str_ptr)); ;}
    break;

  case 57:
#line 270 "parser/parser.y"
    { (yyval.pair_ptr) = new PairAST((yyvsp[(1) - (3)].str_ptr), (yyvsp[(3) - (3)].str_ptr)); ;}
    break;

  case 58:
#line 271 "parser/parser.y"
    { (yyval.pair_ptr) = new PairAST(new string("short"), (yyvsp[(1) - (1)].str_ptr)); ;}
    break;

  case 59:
#line 276 "parser/parser.y"
    { (yyval.statement_list_ptr) = new StatementListAST((yyvsp[(2) - (3)].statement_vector_ptr)); ;}
    break;

  case 60:
#line 279 "parser/parser.y"
    { (yyvsp[(2) - (2)].statement_vector_ptr)->insertAtTop((yyvsp[(1) - (2)].statement_ptr)); (yyval.statement_vector_ptr) = (yyvsp[(2) - (2)].statement_vector_ptr); ;}
    break;

  case 61:
#line 280 "parser/parser.y"
    { (yyval.statement_vector_ptr) = new Vector<StatementAST*>; ;}
    break;

  case 62:
#line 283 "parser/parser.y"
    { (yyvsp[(3) - (3)].expr_vector_ptr)->insertAtTop((yyvsp[(1) - (3)].expr_ptr)); (yyval.expr_vector_ptr) = (yyvsp[(3) - (3)].expr_vector_ptr); ;}
    break;

  case 63:
#line 284 "parser/parser.y"
    { (yyval.expr_vector_ptr) = new Vector<ExprAST*>; (yyval.expr_vector_ptr)->insertAtTop((yyvsp[(1) - (1)].expr_ptr)); ;}
    break;

  case 64:
#line 285 "parser/parser.y"
    { (yyval.expr_vector_ptr) = new Vector<ExprAST*>; ;}
    break;

  case 65:
#line 288 "parser/parser.y"
    { (yyval.statement_ptr) = new ExprStatementAST((yyvsp[(1) - (2)].expr_ptr)); ;}
    break;

  case 66:
#line 289 "parser/parser.y"
    { (yyval.statement_ptr) = new AssignStatementAST((yyvsp[(1) - (4)].expr_ptr), (yyvsp[(3) - (4)].expr_ptr)); ;}
    break;

  case 67:
#line 290 "parser/parser.y"
    { (yyval.statement_ptr) = new EnqueueStatementAST((yyvsp[(3) - (8)].var_expr_ptr), (yyvsp[(5) - (8)].type_ptr), (yyvsp[(6) - (8)].pair_list_ptr), (yyvsp[(8) - (8)].statement_list_ptr)); ;}
    break;

  case 68:
#line 291 "parser/parser.y"
    { (yyval.statement_ptr) = new PeekStatementAST((yyvsp[(3) - (7)].var_expr_ptr), (yyvsp[(5) - (7)].type_ptr), (yyvsp[(7) - (7)].statement_list_ptr), "peek"); ;}
    break;

  case 69:
#line 293 "parser/parser.y"
    { (yyval.statement_ptr) = new CopyHeadStatementAST((yyvsp[(3) - (8)].var_expr_ptr), (yyvsp[(5) - (8)].var_expr_ptr), (yyvsp[(6) - (8)].pair_list_ptr)); ;}
    break;

  case 70:
#line 294 "parser/parser.y"
    { (yyval.statement_ptr) = new CheckAllocateStatementAST((yyvsp[(3) - (5)].var_expr_ptr)); ;}
    break;

  case 71:
#line 295 "parser/parser.y"
    { (yyval.statement_ptr) = new CheckStopSlotsStatementAST((yyvsp[(3) - (9)].var_expr_ptr), (yyvsp[(5) - (9)].str_ptr), (yyvsp[(7) - (9)].str_ptr)); ;}
    break;

  case 72:
#line 296 "parser/parser.y"
    { (yyval.statement_ptr) = (yyvsp[(1) - (1)].statement_ptr); ;}
    break;

  case 73:
#line 297 "parser/parser.y"
    { (yyval.statement_ptr) = new ReturnStatementAST((yyvsp[(2) - (3)].expr_ptr)); ;}
    break;

  case 74:
#line 300 "parser/parser.y"
    { (yyval.statement_ptr) = new IfStatementAST((yyvsp[(3) - (7)].expr_ptr), (yyvsp[(5) - (7)].statement_list_ptr), (yyvsp[(7) - (7)].statement_list_ptr)); ;}
    break;

  case 75:
#line 301 "parser/parser.y"
    { (yyval.statement_ptr) = new IfStatementAST((yyvsp[(3) - (5)].expr_ptr), (yyvsp[(5) - (5)].statement_list_ptr), NULL); ;}
    break;

  case 76:
#line 302 "parser/parser.y"
    { (yyval.statement_ptr) = new IfStatementAST((yyvsp[(3) - (7)].expr_ptr), (yyvsp[(5) - (7)].statement_list_ptr), new StatementListAST((yyvsp[(7) - (7)].statement_ptr))); ;}
    break;

  case 77:
#line 305 "parser/parser.y"
    { (yyval.expr_ptr) = (yyvsp[(1) - (1)].var_expr_ptr); ;}
    break;

  case 78:
#line 306 "parser/parser.y"
    { (yyval.expr_ptr) = (yyvsp[(1) - (1)].expr_ptr); ;}
    break;

  case 79:
#line 307 "parser/parser.y"
    { (yyval.expr_ptr) = (yyvsp[(1) - (1)].expr_ptr); ;}
    break;

  case 80:
#line 308 "parser/parser.y"
    { (yyval.expr_ptr) = new FuncCallExprAST((yyvsp[(1) - (4)].str_ptr), (yyvsp[(3) - (4)].expr_vector_ptr)); ;}
    break;

  case 81:
#line 312 "parser/parser.y"
    { (yyval.expr_ptr) = new ChipComponentAccessAST((yyvsp[(3) - (13)].var_expr_ptr), (yyvsp[(5) - (13)].expr_ptr), (yyvsp[(8) - (13)].var_expr_ptr), (yyvsp[(10) - (13)].str_ptr), (yyvsp[(12) - (13)].expr_vector_ptr) ); ;}
    break;

  case 82:
#line 314 "parser/parser.y"
    { (yyval.expr_ptr) = new ChipComponentAccessAST((yyvsp[(3) - (10)].var_expr_ptr), (yyvsp[(5) - (10)].expr_ptr), (yyvsp[(8) - (10)].var_expr_ptr), (yyvsp[(10) - (10)].str_ptr) ); ;}
    break;

  case 83:
#line 316 "parser/parser.y"
    { (yyval.expr_ptr) = new ChipComponentAccessAST((yyvsp[(3) - (16)].expr_ptr), (yyvsp[(6) - (16)].var_expr_ptr), (yyvsp[(8) - (16)].expr_ptr), (yyvsp[(11) - (16)].var_expr_ptr), (yyvsp[(13) - (16)].str_ptr), (yyvsp[(15) - (16)].expr_vector_ptr) ); ;}
    break;

  case 84:
#line 318 "parser/parser.y"
    { (yyval.expr_ptr) = new ChipComponentAccessAST((yyvsp[(3) - (13)].expr_ptr), (yyvsp[(6) - (13)].var_expr_ptr), (yyvsp[(8) - (13)].expr_ptr), (yyvsp[(11) - (13)].var_expr_ptr), (yyvsp[(13) - (13)].str_ptr) ); ;}
    break;

  case 85:
#line 321 "parser/parser.y"
    { (yyval.expr_ptr) = new MemberExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(3) - (3)].str_ptr)); ;}
    break;

  case 86:
#line 322 "parser/parser.y"
    { (yyval.expr_ptr) = new MethodCallExprAST((yyvsp[(1) - (6)].expr_ptr), (yyvsp[(3) - (6)].str_ptr), (yyvsp[(5) - (6)].expr_vector_ptr)); ;}
    break;

  case 87:
#line 323 "parser/parser.y"
    { (yyval.expr_ptr) = new MethodCallExprAST((yyvsp[(1) - (6)].type_ptr), (yyvsp[(3) - (6)].str_ptr), (yyvsp[(5) - (6)].expr_vector_ptr)); ;}
    break;

  case 88:
#line 324 "parser/parser.y"
    { (yyval.expr_ptr) = new MethodCallExprAST((yyvsp[(1) - (4)].expr_ptr), new string("lookup"), (yyvsp[(3) - (4)].expr_vector_ptr)); ;}
    break;

  case 89:
#line 325 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 90:
#line 326 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 91:
#line 327 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 92:
#line 328 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 93:
#line 329 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 94:
#line 330 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 95:
#line 331 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 96:
#line 332 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 97:
#line 333 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 98:
#line 334 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 99:
#line 335 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 100:
#line 336 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 101:
#line 337 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 102:
#line 338 "parser/parser.y"
    { (yyval.expr_ptr) = new InfixOperatorExprAST((yyvsp[(1) - (3)].expr_ptr), (yyvsp[(2) - (3)].str_ptr), (yyvsp[(3) - (3)].expr_ptr)); ;}
    break;

  case 103:
#line 341 "parser/parser.y"
    { (yyval.expr_ptr) = (yyvsp[(2) - (3)].expr_ptr); ;}
    break;

  case 104:
#line 344 "parser/parser.y"
    { (yyval.expr_ptr) = new LiteralExprAST((yyvsp[(1) - (1)].str_ptr), "string"); ;}
    break;

  case 105:
#line 345 "parser/parser.y"
    { (yyval.expr_ptr) = new LiteralExprAST((yyvsp[(1) - (1)].str_ptr), "int"); ;}
    break;

  case 106:
#line 346 "parser/parser.y"
    { (yyval.expr_ptr) = new LiteralExprAST((yyvsp[(1) - (1)].str_ptr), "int"); ;}
    break;

  case 107:
#line 347 "parser/parser.y"
    { (yyval.expr_ptr) = new LiteralExprAST((yyvsp[(1) - (1)].str_ptr), "bool");  ;}
    break;

  case 108:
#line 350 "parser/parser.y"
    { (yyval.expr_ptr) = new EnumExprAST(new TypeAST((yyvsp[(1) - (3)].str_ptr)), (yyvsp[(3) - (3)].str_ptr)); ;}
    break;

  case 109:
#line 353 "parser/parser.y"
    { (yyval.var_expr_ptr) = new VarExprAST((yyvsp[(1) - (1)].str_ptr)); ;}
    break;

  case 110:
#line 356 "parser/parser.y"
    { (yyval.str_ptr) = (yyvsp[(1) - (1)].str_ptr); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2351 "generated/parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 359 "parser/parser.y"


extern FILE *yyin;

DeclListAST* parse(string filename)
{
  FILE *file;
  file = fopen(filename.c_str(), "r");
  if (!file) {
    cerr << "Error: Could not open file: " << filename << endl;
    exit(1);
  }
  g_line_number = 1;
  g_file_name = filename;
  yyin = file;
  g_decl_list_ptr = NULL;
  yyparse();
  return g_decl_list_ptr;
}

extern "C" void yyerror(char* s)
{
  fprintf(stderr, "%s:%d: %s at %s\n", g_file_name.c_str(), g_line_number, s, yytext);
  exit(1);
}


