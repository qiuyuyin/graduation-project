/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  Selects selection;

  QueryAttr query_attr;
  FuncType func_type;

  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t record_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  OrderType order_type;
  int nullable;
  char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->record_length = 0;
  context->ssql->sstr.insertion.record_num = 0;
  context->nullable = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 137 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    SELECT = 264,
    DESC = 265,
    SHOW = 266,
    SYNC = 267,
    INSERT = 268,
    DELETE = 269,
    UPDATE = 270,
    LBRACE = 271,
    RBRACE = 272,
    COMMA = 273,
    TRX_BEGIN = 274,
    TRX_COMMIT = 275,
    TRX_ROLLBACK = 276,
    INT_T = 277,
    STRING_T = 278,
    FLOAT_T = 279,
    DATE_T = 280,
    TEXT_T = 281,
    HELP = 282,
    EXIT = 283,
    DOT = 284,
    INTO = 285,
    VALUES = 286,
    FROM = 287,
    WHERE = 288,
    AND = 289,
    SET = 290,
    ON = 291,
    LOAD = 292,
    DATA = 293,
    INFILE = 294,
    EQ = 295,
    LT = 296,
    GT = 297,
    LE = 298,
    GE = 299,
    NE = 300,
    MAX = 301,
    MIN = 302,
    COUNT = 303,
    AVG = 304,
    SUM = 305,
    LENGTH = 306,
    ROUND = 307,
    DATE_FORMAT = 308,
    NOT = 309,
    LIKE = 310,
    INNER = 311,
    JOIN = 312,
    UNIQUE = 313,
    NULL_T = 314,
    NULLABLE_T = 315,
    IS_T = 316,
    IN_T = 317,
    EXISTS_T = 318,
    ORDER = 319,
    BY = 320,
    ASC = 321,
    GROUP = 322,
    NUMBER = 323,
    FLOAT = 324,
    DATE_STR = 325,
    ID = 326,
    PATH = 327,
    SSS = 328,
    STAR = 329,
    STRING_V = 330
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 140 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;

#line 275 "yacc_sql.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  266

#define YYUNDEFTOK  2
#define YYMAXUTOK   330


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   167,   167,   169,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   194,   199,   204,   210,   216,   222,   228,   234,
     240,   247,   253,   262,   264,   270,   276,   283,   292,   294,
     298,   309,   322,   325,   326,   327,   328,   329,   333,   340,
     342,   345,   351,   360,   362,   366,   367,   372,   374,   379,
     382,   385,   388,   392,   398,   408,   418,   420,   424,   426,
     431,   436,   441,   447,   456,   469,   474,   476,   482,   486,
     493,   497,   501,   505,   509,   513,   517,   521,   528,   529,
     530,   531,   532,   533,   534,   535,   539,   543,   545,   548,
     552,   554,   559,   561,   566,   568,   577,   579,   584,   586,
     592,   602,   612,   624,   634,   644,   655,   668,   669,   670,
     671,   672,   673,   674,   675,   676,   677,   681,   683,   685,
     690,   692,   697,   698,   705,   714,   717,   720,   724,   726,
     731,   732,   737,   744
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "MAX", "MIN", "COUNT", "AVG", "SUM", "LENGTH", "ROUND", "DATE_FORMAT",
  "NOT", "LIKE", "INNER", "JOIN", "UNIQUE", "NULL_T", "NULLABLE_T", "IS_T",
  "IN_T", "EXISTS_T", "ORDER", "BY", "ASC", "GROUP", "NUMBER", "FLOAT",
  "DATE_STR", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "index_attr_list", "show_index", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "nullable",
  "insert", "record_list", "record", "value_list", "value", "delete",
  "update", "update_value_list", "update_value", "select", "select_attr",
  "attr_list", "attribute", "attr_value", "func_type", "select_rel",
  "relation", "rel_list", "join_list", "join_condition", "where",
  "condition_list", "condition", "comOp", "suffix_by", "order_by_list",
  "order_by_attr", "order_type", "group_by_list", "group_by_attr",
  "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330
};
# endif

#define YYPACT_NINF (-198)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -198,    13,  -198,    -2,    23,    36,   -61,    28,    17,     7,
       6,   -32,    45,    51,    52,    64,    67,    14,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,   -14,    -3,    63,
       1,     2,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,    61,  -198,  -198,    59,    74,  -198,
      77,    93,    94,    62,  -198,    27,    29,    66,  -198,  -198,
    -198,  -198,  -198,    60,    87,    92,    50,   124,   126,    68,
      81,    36,  -198,    49,  -198,  -198,    99,   131,    97,   101,
      90,   102,   103,   129,  -198,  -198,  -198,   -10,    97,    74,
     152,   172,   160,    65,   174,   138,   161,   150,  -198,   163,
      54,   166,   112,   113,   128,  -198,   -48,  -198,  -198,  -198,
      91,   168,  -198,  -198,  -198,  -198,    20,  -198,    71,   153,
    -198,    98,   101,    97,   182,   102,   173,  -198,  -198,  -198,
    -198,  -198,    -9,   118,   175,   176,   121,   130,   132,   190,
     178,   160,   195,   133,  -198,  -198,  -198,  -198,  -198,  -198,
     144,  -198,   146,    72,    78,    65,  -198,  -198,  -198,  -198,
    -198,  -198,   161,   198,   134,   163,   199,   135,   147,  -198,
    -198,   189,   137,   139,  -198,   177,   140,   141,  -198,    91,
     192,   168,  -198,    71,  -198,  -198,  -198,  -198,   185,  -198,
     153,  -198,  -198,   212,  -198,  -198,  -198,   200,  -198,   145,
     201,   189,   176,    65,   164,    -8,   203,   193,   205,   178,
    -198,  -198,    85,   148,  -198,  -198,   -45,   189,   221,   208,
    -198,   153,   169,  -198,  -198,   156,  -198,  -198,   140,  -198,
     157,   141,  -198,  -198,   202,  -198,  -198,  -198,  -198,  -198,
     226,  -198,   159,    -7,   203,  -198,   205,   162,  -198,   177,
    -198,  -198,  -198,  -198,   164,  -198
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
       0,     0,    88,    89,    90,    91,    92,    93,    94,    95,
      87,    83,    84,    85,    81,    86,    80,     0,    76,    78,
       0,     0,     0,     0,    24,     0,     0,     0,    25,    26,
      27,    23,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,    30,    29,     0,     0,   106,    68,
       0,     0,     0,     0,    28,    36,    82,    97,   106,    76,
       0,     0,    55,     0,     0,     0,    66,     0,    48,    38,
       0,     0,     0,     0,     0,    96,   127,    77,    79,    35,
       0,    53,    63,    59,    60,    61,     0,    62,     0,   108,
      64,     0,    68,   106,     0,     0,     0,    43,    44,    45,
      46,    47,    49,     0,     0,   100,     0,     0,     0,     0,
      57,    55,     0,     0,   117,   118,   119,   120,   121,   122,
       0,   123,   125,     0,     0,     0,   107,    73,    69,    70,
      71,    72,    66,     0,     0,    38,     0,     0,     0,    50,
      41,    33,     0,     0,    98,   104,   132,   140,    74,     0,
       0,    53,    52,     0,   124,   126,   112,   110,   113,   111,
     108,    67,    65,     0,    39,    37,    42,     0,    51,     0,
       0,    33,   100,     0,   102,   135,   130,   141,   138,    57,
      56,    54,     0,     0,   109,   143,    49,    33,     0,     0,
     101,   108,     0,    99,   137,     0,   136,   133,   132,   128,
       0,   140,   129,    58,     0,   114,   115,    40,    34,    31,
       0,   105,     0,   135,   130,   142,   138,     0,    32,   104,
     134,   131,   139,   116,   102,   103
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -197,  -198,  -198,  -198,    57,   100,  -198,
    -198,  -198,     8,  -198,    46,    88,    19,  -120,  -198,  -198,
      69,   104,  -198,  -198,   143,   165,   167,  -198,  -198,  -198,
      31,   -24,   -15,   -86,  -189,  -160,  -127,  -198,    -6,     9,
      -4,   -11,    10,  -198
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   210,    29,    30,    31,   136,   109,   207,
     142,   110,   180,    32,   152,   121,   190,   128,    33,    34,
     133,   106,    35,    57,    82,    58,    59,    60,    98,   115,
     184,   233,   214,   104,   166,   129,   163,   149,   239,   216,
     237,   242,   218,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     150,   164,   234,   234,    37,   200,    38,   177,   113,   178,
      61,   224,   116,     2,   229,   179,   147,     3,     4,   148,
      64,   235,     5,     6,     7,     8,     9,    10,    11,    40,
     248,    41,    12,    13,    14,    62,    63,    65,    66,    67,
      15,    16,   251,   197,   199,   178,   114,   173,    68,   153,
      17,   179,    73,   231,    69,    70,    39,    74,   236,   236,
     154,   155,   156,   157,   158,   159,   222,    71,    75,   219,
      72,    76,    77,    78,   160,   161,   137,   138,   139,   140,
     141,   162,    42,    43,    44,    45,    46,    47,    48,    49,
      79,    80,    81,    83,    86,    50,    84,    85,    87,    90,
      88,    89,   245,    91,    51,    52,    53,    54,    50,    55,
      56,   154,   155,   156,   157,   158,   159,    51,    52,    53,
      54,    93,    55,    56,   122,   160,   161,    94,    92,    95,
     103,   122,   162,   123,   124,   125,   126,   122,   127,    96,
     123,   124,   125,   196,   122,   127,   123,   124,   125,   198,
     122,   127,    97,   123,   124,   125,   244,   167,   127,   123,
     124,   125,   102,   107,   127,   112,   168,   169,   170,   118,
     101,   171,   105,   108,   111,   119,   120,   130,   131,   132,
     134,   135,   143,   144,   145,   146,   151,   165,   174,   181,
     176,   182,   185,   188,   183,   186,   189,   187,   192,   194,
     195,   202,   205,   206,   193,   203,   208,   209,   211,   220,
     212,   215,   217,   213,   223,   225,   227,   226,   228,   246,
     232,   238,   240,   241,   249,   250,   252,   253,   255,   258,
     259,   257,   204,   263,   247,   175,   172,   221,   243,   191,
     265,   201,   117,   230,   264,   262,    99,   254,   261,   260,
     100,   256
};

static const yytype_int16 yycheck[] =
{
     120,   128,    10,    10,     6,   165,     8,    16,    18,    54,
      71,   200,    98,     0,   211,    60,    64,     4,     5,    67,
       3,    29,     9,    10,    11,    12,    13,    14,    15,     6,
     227,     8,    19,    20,    21,     7,     8,    30,    32,    71,
      27,    28,   231,   163,   164,    54,    56,   133,     3,    29,
      37,    60,    38,   213,     3,     3,    58,    71,    66,    66,
      40,    41,    42,    43,    44,    45,   193,     3,    71,   189,
       3,     8,    71,    71,    54,    55,    22,    23,    24,    25,
      26,    61,    46,    47,    48,    49,    50,    51,    52,    53,
      29,    32,    18,    16,    32,    59,     3,     3,    71,    39,
      71,    35,   222,    16,    68,    69,    70,    71,    59,    73,
      74,    40,    41,    42,    43,    44,    45,    68,    69,    70,
      71,    71,    73,    74,    59,    54,    55,     3,    36,     3,
      33,    59,    61,    68,    69,    70,    71,    59,    73,    71,
      68,    69,    70,    71,    59,    73,    68,    69,    70,    71,
      59,    73,    71,    68,    69,    70,    71,    59,    73,    68,
      69,    70,    31,    73,    73,    36,    68,    69,    70,    17,
      71,    73,    71,    71,    71,     3,    16,     3,    40,    18,
      30,    18,    16,    71,    71,    57,    18,    34,     6,    71,
      17,    16,    71,     3,    18,    65,    18,    65,     3,    55,
      54,     3,     3,    68,    71,    71,    59,    18,    71,    17,
      71,    71,    71,    36,    29,     3,    71,    17,    17,    71,
      56,    18,    29,    18,     3,    17,    57,    71,    71,     3,
      71,    29,   175,    71,   226,   135,   132,   191,   219,   151,
     264,   172,    99,   212,   259,   256,    81,   238,   254,   253,
      83,   241
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    77,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    90,
      91,    92,    99,   104,   105,   108,   129,     6,     8,    58,
       6,     8,    46,    47,    48,    49,    50,    51,    52,    53,
      59,    68,    69,    70,    71,    73,    74,   109,   111,   112,
     113,    71,     7,     8,     3,    30,    32,    71,     3,     3,
       3,     3,     3,    38,    71,    71,     8,    71,    71,    29,
      32,    18,   110,    16,     3,     3,    32,    71,    71,    35,
      39,    16,    36,    71,     3,     3,    71,    71,   114,   111,
     112,    71,    31,    33,   119,    71,   107,    73,    71,    94,
      97,    71,    36,    18,    56,   115,   119,   110,    17,     3,
      16,   101,    59,    68,    69,    70,    71,    73,   103,   121,
       3,    40,    18,   106,    30,    18,    93,    22,    23,    24,
      25,    26,    96,    16,    71,    71,    57,    64,    67,   123,
     103,    18,   100,    29,    40,    41,    42,    43,    44,    45,
      54,    55,    61,   122,   122,    34,   120,    59,    68,    69,
      70,    73,   107,   119,     6,    94,    17,    16,    54,    60,
      98,    71,    16,    18,   116,    71,    65,    65,     3,    18,
     102,   101,     3,    71,    55,    54,    71,   103,    71,   103,
     121,   106,     3,    71,    93,     3,    68,    95,    59,    18,
      89,    71,    71,    36,   118,    71,   125,    71,   128,   103,
      17,   100,   122,    29,   120,     3,    17,    71,    17,    89,
     116,   121,    56,   117,    10,    29,    66,   126,    18,   124,
      29,    18,   127,   102,    71,   103,    71,    98,    89,     3,
      17,   120,    57,    71,   125,    71,   128,    29,     3,    71,
     126,   124,   127,    71,   118,   117
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    88,    89,    89,    90,    91,    92,    93,    93,
      94,    94,    95,    96,    96,    96,    96,    96,    97,    98,
      98,    98,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   103,   103,   103,   104,   105,   106,   106,   107,   107,
     107,   107,   107,   107,   108,   109,   110,   110,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   115,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   121,   121,   121,   121,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   123,   123,   123,
     124,   124,   125,   125,   125,   126,   126,   126,   127,   127,
     128,   128,   128,   129
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     0,     3,     5,     4,     8,     0,     3,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     2,     7,     0,     3,     0,     4,     0,     3,     1,
       1,     1,     1,     1,     5,     7,     0,     3,     0,     3,
       3,     3,     3,     3,     7,     2,     0,     3,     1,     4,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     3,     5,
       0,     3,     0,     5,     0,     3,     0,     3,     0,     3,
       3,     3,     3,     3,     5,     5,     7,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     0,     4,     4,
       0,     3,     0,     2,     4,     0,     1,     1,     0,     3,
       0,     1,     3,     8
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 22:
#line 194 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1658 "yacc_sql.tab.c"
    break;

  case 23:
#line 199 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1666 "yacc_sql.tab.c"
    break;

  case 24:
#line 204 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1674 "yacc_sql.tab.c"
    break;

  case 25:
#line 210 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1682 "yacc_sql.tab.c"
    break;

  case 26:
#line 216 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1690 "yacc_sql.tab.c"
    break;

  case 27:
#line 222 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1698 "yacc_sql.tab.c"
    break;

  case 28:
#line 228 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1707 "yacc_sql.tab.c"
    break;

  case 29:
#line 234 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1715 "yacc_sql.tab.c"
    break;

  case 30:
#line 240 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1724 "yacc_sql.tab.c"
    break;

  case 31:
#line 248 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string));
			create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-3].string));
		}
#line 1734 "yacc_sql.tab.c"
    break;

  case 32:
#line 254 "yacc_sql.y"
                {
			CONTEXT->ssql->sstr.create_index.unique = true;
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string));
			create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-3].string));
		}
#line 1745 "yacc_sql.tab.c"
    break;

  case 34:
#line 264 "yacc_sql.y"
                               {
		create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
	}
#line 1753 "yacc_sql.tab.c"
    break;

  case 35:
#line 270 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag=SCF_SHOW_INDEX;//"show_index";
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1762 "yacc_sql.tab.c"
    break;

  case 36:
#line 277 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1771 "yacc_sql.tab.c"
    break;

  case 37:
#line 284 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1783 "yacc_sql.tab.c"
    break;

  case 39:
#line 294 "yacc_sql.y"
                                   {    }
#line 1789 "yacc_sql.tab.c"
    break;

  case 40:
#line 299 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1804 "yacc_sql.tab.c"
    break;

  case 41:
#line 310 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1819 "yacc_sql.tab.c"
    break;

  case 42:
#line 322 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1825 "yacc_sql.tab.c"
    break;

  case 43:
#line 325 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1831 "yacc_sql.tab.c"
    break;

  case 44:
#line 326 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1837 "yacc_sql.tab.c"
    break;

  case 45:
#line 327 "yacc_sql.y"
                  { (yyval.number)=FLOATS; }
#line 1843 "yacc_sql.tab.c"
    break;

  case 46:
#line 328 "yacc_sql.y"
                 { (yyval.number)=DATES; }
#line 1849 "yacc_sql.tab.c"
    break;

  case 47:
#line 329 "yacc_sql.y"
                 { (yyval.number)=TEXTS; }
#line 1855 "yacc_sql.tab.c"
    break;

  case 48:
#line 334 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1864 "yacc_sql.tab.c"
    break;

  case 50:
#line 342 "yacc_sql.y"
                     {
		CONTEXT->nullable=1;
	}
#line 1872 "yacc_sql.tab.c"
    break;

  case 51:
#line 345 "yacc_sql.y"
                     {
		CONTEXT->nullable=0;
	}
#line 1880 "yacc_sql.tab.c"
    break;

  case 52:
#line 352 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->record_length);
			//临时变量清零
			CONTEXT->value_length=0;
			CONTEXT->record_length=0;
    }
#line 1892 "yacc_sql.tab.c"
    break;

  case 54:
#line 362 "yacc_sql.y"
                                   {

	}
#line 1900 "yacc_sql.tab.c"
    break;

  case 56:
#line 367 "yacc_sql.y"
                                         {
		inserts_record(&CONTEXT->ssql->sstr.insertion,CONTEXT->record_length++ ,CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1909 "yacc_sql.tab.c"
    break;

  case 58:
#line 374 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1917 "yacc_sql.tab.c"
    break;

  case 59:
#line 379 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1925 "yacc_sql.tab.c"
    break;

  case 60:
#line 382 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1933 "yacc_sql.tab.c"
    break;

  case 61:
#line 385 "yacc_sql.y"
                 {
		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1941 "yacc_sql.tab.c"
    break;

  case 62:
#line 388 "yacc_sql.y"
         {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
	}
#line 1950 "yacc_sql.tab.c"
    break;

  case 63:
#line 392 "yacc_sql.y"
               {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1958 "yacc_sql.tab.c"
    break;

  case 64:
#line 399 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1970 "yacc_sql.tab.c"
    break;

  case 65:
#line 409 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string),CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
			CONTEXT->value_length = 0;
		}
#line 1982 "yacc_sql.tab.c"
    break;

  case 67:
#line 420 "yacc_sql.y"
                                           {
		
	}
#line 1990 "yacc_sql.tab.c"
    break;

  case 69:
#line 426 "yacc_sql.y"
                 {
		Value value;
  		value_init_integer(&value, (yyvsp[0].number));
		updates_value_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &value);
	}
#line 2000 "yacc_sql.tab.c"
    break;

  case 70:
#line 431 "yacc_sql.y"
                {
		Value value;
  		value_init_float(&value, (yyvsp[0].floats));
		updates_value_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &value);
	}
#line 2010 "yacc_sql.tab.c"
    break;

  case 71:
#line 436 "yacc_sql.y"
                       {
		Value value;
  		value_init_date(&value, (yyvsp[0].string));
		updates_value_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &value);
	}
#line 2020 "yacc_sql.tab.c"
    break;

  case 72:
#line 441 "yacc_sql.y"
               {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		Value value;
  		value_init_string(&value, (yyvsp[0].string));
		updates_value_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &value);
	}
#line 2031 "yacc_sql.tab.c"
    break;

  case 73:
#line 447 "yacc_sql.y"
                      {
		Value value;
  		value_init_null(&value);
		updates_value_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &value);
	}
#line 2041 "yacc_sql.tab.c"
    break;

  case 74:
#line 457 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_SELECT;
		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
	}
#line 2055 "yacc_sql.tab.c"
    break;

  case 75:
#line 469 "yacc_sql.y"
                            {

	}
#line 2063 "yacc_sql.tab.c"
    break;

  case 77:
#line 476 "yacc_sql.y"
                                {
		
    }
#line 2071 "yacc_sql.tab.c"
    break;

  case 78:
#line 482 "yacc_sql.y"
                   {
		CONTEXT->query_attr.is_func = 0;
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &CONTEXT->query_attr);
	}
#line 2080 "yacc_sql.tab.c"
    break;

  case 79:
#line 486 "yacc_sql.y"
                                             {
		CONTEXT->query_attr.is_func = 1;
		CONTEXT->query_attr.func_type = CONTEXT->func_type;
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &CONTEXT->query_attr);
	}
#line 2090 "yacc_sql.tab.c"
    break;

  case 80:
#line 493 "yacc_sql.y"
             {
		CONTEXT->query_attr.is_attr = 1;
		relation_attr_init(&CONTEXT->query_attr.rel_attr, NULL, "*");
	}
#line 2099 "yacc_sql.tab.c"
    break;

  case 81:
#line 497 "yacc_sql.y"
           {
		CONTEXT->query_attr.is_attr = 1;
		relation_attr_init(&CONTEXT->query_attr.rel_attr, NULL, (yyvsp[0].string));
	}
#line 2108 "yacc_sql.tab.c"
    break;

  case 82:
#line 501 "yacc_sql.y"
                   {
		CONTEXT->query_attr.is_attr = 1;
		relation_attr_init(&CONTEXT->query_attr.rel_attr, (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 2117 "yacc_sql.tab.c"
    break;

  case 83:
#line 505 "yacc_sql.y"
                 {
		CONTEXT->query_attr.is_value = 1;
		value_init_integer(&CONTEXT->query_attr.value, (yyvsp[0].number));
	}
#line 2126 "yacc_sql.tab.c"
    break;

  case 84:
#line 509 "yacc_sql.y"
                {
		CONTEXT->query_attr.is_value = 1;
		value_init_float(&CONTEXT->query_attr.value, (yyvsp[0].floats));
	}
#line 2135 "yacc_sql.tab.c"
    break;

  case 85:
#line 513 "yacc_sql.y"
                   {
		CONTEXT->query_attr.is_value = 1;
		value_init_date(&CONTEXT->query_attr.value, (yyvsp[0].string));
	}
#line 2144 "yacc_sql.tab.c"
    break;

  case 86:
#line 517 "yacc_sql.y"
              {
		CONTEXT->query_attr.is_value = 1;
		value_init_string(&CONTEXT->query_attr.value, (yyvsp[0].string));
	}
#line 2153 "yacc_sql.tab.c"
    break;

  case 87:
#line 521 "yacc_sql.y"
                 {
		CONTEXT->query_attr.is_value = 1;
		value_init_null(&CONTEXT->query_attr.value);
	}
#line 2162 "yacc_sql.tab.c"
    break;

  case 88:
#line 528 "yacc_sql.y"
             { CONTEXT->func_type = MAX_FUNC; }
#line 2168 "yacc_sql.tab.c"
    break;

  case 89:
#line 529 "yacc_sql.y"
          { CONTEXT->func_type = MIN_FUNC; }
#line 2174 "yacc_sql.tab.c"
    break;

  case 90:
#line 530 "yacc_sql.y"
           { CONTEXT->func_type = COUNT_FUNC; }
#line 2180 "yacc_sql.tab.c"
    break;

  case 91:
#line 531 "yacc_sql.y"
          { CONTEXT->func_type = AVG_FUNC; }
#line 2186 "yacc_sql.tab.c"
    break;

  case 92:
#line 532 "yacc_sql.y"
              { CONTEXT->func_type = SUM_FUNC; }
#line 2192 "yacc_sql.tab.c"
    break;

  case 93:
#line 533 "yacc_sql.y"
                 { CONTEXT->func_type = LENGTH_FUNC; }
#line 2198 "yacc_sql.tab.c"
    break;

  case 94:
#line 534 "yacc_sql.y"
            { CONTEXT->func_type = ROUND_FUNC; }
#line 2204 "yacc_sql.tab.c"
    break;

  case 95:
#line 535 "yacc_sql.y"
                      { CONTEXT->func_type = DATE_FORMAT_FUNC; }
#line 2210 "yacc_sql.tab.c"
    break;

  case 96:
#line 539 "yacc_sql.y"
                    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
	}
#line 2218 "yacc_sql.tab.c"
    break;

  case 98:
#line 545 "yacc_sql.y"
                            {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
	}
#line 2226 "yacc_sql.tab.c"
    break;

  case 99:
#line 548 "yacc_sql.y"
                                                 {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2234 "yacc_sql.tab.c"
    break;

  case 101:
#line 554 "yacc_sql.y"
                        {	
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
	}
#line 2242 "yacc_sql.tab.c"
    break;

  case 103:
#line 561 "yacc_sql.y"
                                                {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2250 "yacc_sql.tab.c"
    break;

  case 105:
#line 568 "yacc_sql.y"
                                      {
		JoinCond join_cond;
		init_join_condition(&join_cond, CONTEXT->conditions, CONTEXT->condition_length);
		selects_append_join_conditions(&CONTEXT->ssql->sstr.selection,&join_cond);

		CONTEXT->condition_length=0;
		CONTEXT->value_length = 0;
	}
#line 2263 "yacc_sql.tab.c"
    break;

  case 107:
#line 579 "yacc_sql.y"
                                     {

	}
#line 2271 "yacc_sql.tab.c"
    break;

  case 109:
#line 586 "yacc_sql.y"
                                  {
		  
	}
#line 2279 "yacc_sql.tab.c"
    break;

  case 110:
#line 593 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2293 "yacc_sql.tab.c"
    break;

  case 111:
#line 603 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);

			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2307 "yacc_sql.tab.c"
    break;

  case 112:
#line 613 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);

			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2323 "yacc_sql.tab.c"
    break;

  case 113:
#line 625 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2337 "yacc_sql.tab.c"
    break;

  case 114:
#line 635 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2351 "yacc_sql.tab.c"
    break;

  case 115:
#line 645 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2366 "yacc_sql.tab.c"
    break;

  case 116:
#line 656 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2381 "yacc_sql.tab.c"
    break;

  case 117:
#line 668 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2387 "yacc_sql.tab.c"
    break;

  case 118:
#line 669 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2393 "yacc_sql.tab.c"
    break;

  case 119:
#line 670 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2399 "yacc_sql.tab.c"
    break;

  case 120:
#line 671 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2405 "yacc_sql.tab.c"
    break;

  case 121:
#line 672 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2411 "yacc_sql.tab.c"
    break;

  case 122:
#line 673 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2417 "yacc_sql.tab.c"
    break;

  case 123:
#line 674 "yacc_sql.y"
               { CONTEXT->comp = LIKE_TO; }
#line 2423 "yacc_sql.tab.c"
    break;

  case 124:
#line 675 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE; }
#line 2429 "yacc_sql.tab.c"
    break;

  case 125:
#line 676 "yacc_sql.y"
               { CONTEXT->comp = IS_TO; }
#line 2435 "yacc_sql.tab.c"
    break;

  case 126:
#line 677 "yacc_sql.y"
                   { CONTEXT->comp = IS_NOT; }
#line 2441 "yacc_sql.tab.c"
    break;

  case 128:
#line 683 "yacc_sql.y"
                                               {
	}
#line 2448 "yacc_sql.tab.c"
    break;

  case 129:
#line 685 "yacc_sql.y"
                                              {

	}
#line 2456 "yacc_sql.tab.c"
    break;

  case 131:
#line 692 "yacc_sql.y"
                                           {
		
	}
#line 2464 "yacc_sql.tab.c"
    break;

  case 133:
#line 698 "yacc_sql.y"
                        {
		OrderAttr order_attr;
		relation_attr_init(&order_attr.rel_attr, NULL, (yyvsp[-1].string));
		order_attr.order_type = CONTEXT->order_type;

		selects_append_order_by(&CONTEXT->selection, &order_attr);
	}
#line 2476 "yacc_sql.tab.c"
    break;

  case 134:
#line 705 "yacc_sql.y"
                              {
		OrderAttr order_attr;
		relation_attr_init(&order_attr.rel_attr, (yyvsp[-3].string), (yyvsp[-1].string));
		order_attr.order_type = CONTEXT->order_type;

		selects_append_order_by(&CONTEXT->selection, &order_attr);
	}
#line 2488 "yacc_sql.tab.c"
    break;

  case 135:
#line 714 "yacc_sql.y"
                    {
		CONTEXT->order_type = ORDER_ASC;
	}
#line 2496 "yacc_sql.tab.c"
    break;

  case 136:
#line 717 "yacc_sql.y"
         {
		CONTEXT->order_type = ORDER_ASC;
	}
#line 2504 "yacc_sql.tab.c"
    break;

  case 137:
#line 720 "yacc_sql.y"
              {
		CONTEXT->order_type = ORDER_DESC;
	}
#line 2512 "yacc_sql.tab.c"
    break;

  case 139:
#line 726 "yacc_sql.y"
                                            {
		
	}
#line 2520 "yacc_sql.tab.c"
    break;

  case 141:
#line 732 "yacc_sql.y"
             {
		RelAttr rel_attr;
		relation_attr_init(&rel_attr, NULL, (yyvsp[0].string));
		selects_append_group_by(&CONTEXT->selection, &rel_attr);
	}
#line 2530 "yacc_sql.tab.c"
    break;

  case 142:
#line 737 "yacc_sql.y"
                    {
		RelAttr rel_attr;
		relation_attr_init(&rel_attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_group_by(&CONTEXT->selection, &rel_attr);
	}
#line 2540 "yacc_sql.tab.c"
    break;

  case 143:
#line 745 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2549 "yacc_sql.tab.c"
    break;


#line 2553 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, scanner);
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
  return yyresult;
}
#line 751 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
