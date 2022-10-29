/* A Bison parser, made by GNU Bison 3.8.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30800

/* Bison version string.  */
#define YYBISON_VERSION "3.8"

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

int yydebug = 1;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];

  size_t expr_cell_buffer_condition_first_position;
  size_t expr_cell_buffer_num;
  ExprCellBuffer expr_cells[100];

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
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 135 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_ASC = 11,                       /* ASC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_DATE_T = 23,                    /* DATE_T  */
  YYSYMBOL_INT_T = 24,                     /* INT_T  */
  YYSYMBOL_STRING_T = 25,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_TEXT_T = 27,                    /* TEXT_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_INNER = 34,                     /* INNER  */
  YYSYMBOL_JOIN = 35,                      /* JOIN  */
  YYSYMBOL_WHERE = 36,                     /* WHERE  */
  YYSYMBOL_AND = 37,                       /* AND  */
  YYSYMBOL_SET = 38,                       /* SET  */
  YYSYMBOL_ON = 39,                        /* ON  */
  YYSYMBOL_LOAD = 40,                      /* LOAD  */
  YYSYMBOL_DATA = 41,                      /* DATA  */
  YYSYMBOL_INFILE = 42,                    /* INFILE  */
  YYSYMBOL_IS_ = 43,                       /* IS_  */
  YYSYMBOL_NOT = 44,                       /* NOT  */
  YYSYMBOL_LIKE_ = 45,                     /* LIKE_  */
  YYSYMBOL_GROUP = 46,                     /* GROUP  */
  YYSYMBOL_BY = 47,                        /* BY  */
  YYSYMBOL_ORDER = 48,                     /* ORDER  */
  YYSYMBOL_HAVING = 49,                    /* HAVING  */
  YYSYMBOL_AS = 50,                        /* AS  */
  YYSYMBOL_NULLABLE = 51,                  /* NULLABLE  */
  YYSYMBOL_NULL_ = 52,                     /* NULL_  */
  YYSYMBOL_EQ = 53,                        /* EQ  */
  YYSYMBOL_LT = 54,                        /* LT  */
  YYSYMBOL_GT = 55,                        /* GT  */
  YYSYMBOL_LE = 56,                        /* LE  */
  YYSYMBOL_GE = 57,                        /* GE  */
  YYSYMBOL_NE = 58,                        /* NE  */
  YYSYMBOL_PLUS = 59,                      /* PLUS  */
  YYSYMBOL_DIV = 60,                       /* DIV  */
  YYSYMBOL_MINUS = 61,                     /* MINUS  */
  YYSYMBOL_NUMBER = 62,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 63,                     /* FLOAT  */
  YYSYMBOL_ID = 64,                        /* ID  */
  YYSYMBOL_AGGREGATION_FUNC = 65,          /* AGGREGATION_FUNC  */
  YYSYMBOL_AGGREGATION_FUNC_VALUE = 66,    /* AGGREGATION_FUNC_VALUE  */
  YYSYMBOL_PATH = 67,                      /* PATH  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_STAR = 69,                      /* STAR  */
  YYSYMBOL_STRING_V = 70,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 71,                  /* DATE_STR  */
  YYSYMBOL_U_neg = 72,                     /* U_neg  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_commands = 74,                  /* commands  */
  YYSYMBOL_command = 75,                   /* command  */
  YYSYMBOL_exit = 76,                      /* exit  */
  YYSYMBOL_help = 77,                      /* help  */
  YYSYMBOL_sync = 78,                      /* sync  */
  YYSYMBOL_begin = 79,                     /* begin  */
  YYSYMBOL_commit = 80,                    /* commit  */
  YYSYMBOL_rollback = 81,                  /* rollback  */
  YYSYMBOL_drop_table = 82,                /* drop_table  */
  YYSYMBOL_show_tables = 83,               /* show_tables  */
  YYSYMBOL_desc_table = 84,                /* desc_table  */
  YYSYMBOL_create_index = 85,              /* create_index  */
  YYSYMBOL_drop_index = 86,                /* drop_index  */
  YYSYMBOL_show_index = 87,                /* show_index  */
  YYSYMBOL_create_table = 88,              /* create_table  */
  YYSYMBOL_attr_def_list = 89,             /* attr_def_list  */
  YYSYMBOL_attr_def = 90,                  /* attr_def  */
  YYSYMBOL_number = 91,                    /* number  */
  YYSYMBOL_type = 92,                      /* type  */
  YYSYMBOL_ID_get = 93,                    /* ID_get  */
  YYSYMBOL_insert = 94,                    /* insert  */
  YYSYMBOL_value_tuple = 95,               /* value_tuple  */
  YYSYMBOL_value_tuple_list = 96,          /* value_tuple_list  */
  YYSYMBOL_value_list = 97,                /* value_list  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_delete = 99,                    /* delete  */
  YYSYMBOL_update = 100,                   /* update  */
  YYSYMBOL_select = 101,                   /* select  */
  YYSYMBOL_select_list = 102,              /* select_list  */
  YYSYMBOL_selects_expression_all = 103,   /* selects_expression_all  */
  YYSYMBOL_expr = 104,                     /* expr  */
  YYSYMBOL_expr_cell = 105,                /* expr_cell  */
  YYSYMBOL_rel = 106,                      /* rel  */
  YYSYMBOL_rel_list = 107,                 /* rel_list  */
  YYSYMBOL_where = 108,                    /* where  */
  YYSYMBOL_condition = 109,                /* condition  */
  YYSYMBOL_condition_list = 110,           /* condition_list  */
  YYSYMBOL_having = 111,                   /* having  */
  YYSYMBOL_having_condition = 112,         /* having_condition  */
  YYSYMBOL_having_condition_list = 113,    /* having_condition_list  */
  YYSYMBOL_group_by = 114,                 /* group_by  */
  YYSYMBOL_group_by_rel_list = 115,        /* group_by_rel_list  */
  YYSYMBOL_order_by = 116,                 /* order_by  */
  YYSYMBOL_od_type = 117,                  /* od_type  */
  YYSYMBOL_order_by_info = 118,            /* order_by_info  */
  YYSYMBOL_condition_expression_all = 119, /* condition_expression_all  */
  YYSYMBOL_comOp = 120,                    /* comOp  */
  YYSYMBOL_load_data = 121                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   268

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  269

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   167,   167,   169,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   194,   199,   204,   210,   216,   222,   228,   234,
     240,   247,   255,   263,   272,   281,   283,   287,   298,   309,
     320,   331,   342,   356,   359,   360,   361,   362,   363,   366,
     375,   391,   397,   399,   403,   405,   410,   413,   416,   425,
     428,   435,   445,   455,   475,   480,   485,   490,   500,   508,
     512,   513,   514,   515,   516,   517,   518,   523,   526,   529,
     532,   535,   542,   551,   559,   562,   567,   569,   572,   575,
     578,   581,   584,   589,   591,   597,   607,   609,   614,   616,
     621,   632,   634,   639,   641,   646,   654,   656,   661,   669,
     671,   676,   685,   686,   687,   691,   693,   698,   708,   718,
     719,   720,   721,   722,   723,   724,   725,   726,   727,   731
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "ASC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "DATE_T", "INT_T", "STRING_T",
  "FLOAT_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "INNER", "JOIN", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE",
  "IS_", "NOT", "LIKE_", "GROUP", "BY", "ORDER", "HAVING", "AS",
  "NULLABLE", "NULL_", "EQ", "LT", "GT", "LE", "GE", "NE", "PLUS", "DIV",
  "MINUS", "NUMBER", "FLOAT", "ID", "AGGREGATION_FUNC",
  "AGGREGATION_FUNC_VALUE", "PATH", "SSS", "STAR", "STRING_V", "DATE_STR",
  "U_neg", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "show_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "value_tuple", "value_tuple_list", "value_list", "value", "delete",
  "update", "select", "select_list", "selects_expression_all", "expr",
  "expr_cell", "rel", "rel_list", "where", "condition", "condition_list",
  "having", "having_condition", "having_condition_list", "group_by",
  "group_by_rel_list", "order_by", "od_type", "order_by_info",
  "condition_expression_all", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-184)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -184,    98,  -184,    66,   109,    26,   -54,    15,    56,   -13,
      16,     4,    68,    73,    81,    93,   125,    94,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,  -184,    83,    97,   100,
     103,    -8,  -184,    -8,  -184,  -184,   106,   129,  -184,   144,
    -184,  -184,   135,   156,    72,  -184,   173,   174,   145,  -184,
     115,   116,   143,  -184,  -184,  -184,  -184,  -184,   140,   166,
     146,   181,   183,    40,  -184,   123,    96,    -8,   124,    -8,
     126,    -8,    -8,    -8,    -8,  -184,  -184,   127,   157,   158,
     128,   130,   131,   132,  -184,  -184,  -184,  -184,  -184,     6,
     175,   179,   156,    -4,   158,   156,  -184,   -44,  -184,   -44,
    -184,   196,   184,    -8,   197,   149,   172,  -184,   185,   147,
     188,  -184,   142,  -184,  -184,   148,   176,   150,  -184,   161,
    -184,    77,   189,    90,   178,    99,  -184,    77,   203,   131,
     192,  -184,  -184,  -184,  -184,  -184,    -9,   152,   195,    87,
     153,    -6,   171,   170,   201,   184,   218,    -8,  -184,   180,
     177,  -184,  -184,  -184,  -184,  -184,  -184,  -184,    -8,   158,
     159,   185,   222,   164,   182,   210,   211,  -184,   167,  -184,
      -5,  -184,   168,    -8,   187,    77,   212,   189,  -184,   178,
    -184,  -184,  -184,   225,   230,  -184,  -184,   219,   221,   164,
     233,    -6,    -8,   186,  -184,     7,   202,    99,   193,   238,
     201,  -184,  -184,  -184,  -184,  -184,  -184,   164,   224,  -184,
    -184,   178,    -7,   190,   191,  -184,    -8,  -184,    -8,   194,
    -184,  -184,   226,  -184,    -6,    -8,  -184,    86,   227,   202,
    -184,    10,  -184,  -184,   178,   198,  -184,  -184,  -184,  -184,
    -184,   199,   228,    -6,   227,    82,   200,  -184,  -184,  -184,
     228,    37,  -184,   204,   228,    82,  -184,   228,  -184
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
       0,     0,    59,     0,    56,    57,    77,     0,    60,    64,
      58,    83,     0,    66,    67,    76,     0,     0,     0,    24,
       0,     0,     0,    25,    26,    27,    23,    22,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    29,     0,     0,    93,
       0,     0,     0,     0,    28,    32,    74,    78,    43,     0,
       0,     0,    65,    86,    93,    69,    68,    70,    73,    71,
      72,     0,     0,     0,     0,     0,     0,    49,    35,     0,
       0,    79,     0,    81,    82,     0,     0,     0,    84,   103,
      33,     0,    52,   118,    96,     0,    61,     0,     0,     0,
       0,    47,    44,    45,    46,    48,    38,     0,     0,    86,
       0,    86,     0,    98,    54,     0,     0,     0,    94,   128,
       0,   126,   119,   120,   121,   122,   123,   124,     0,    93,
       0,    35,     0,     0,     0,    40,     0,    80,     0,    87,
      86,    85,     0,     0,   109,     0,     0,    52,    50,    96,
     127,   125,    95,     0,     0,    36,    34,     0,    42,     0,
       0,    86,     0,     0,    89,   106,   101,     0,     0,     0,
      54,    51,    53,    97,    62,   129,    37,     0,     0,    31,
      88,    96,    86,     0,     0,   104,     0,    99,     0,     0,
      63,    55,     0,    39,    86,     0,    90,   106,   106,   101,
     100,   112,    41,    91,    96,     0,   107,   105,   102,   114,
     113,     0,   115,    86,   106,   112,     0,   110,    92,   108,
     115,   112,   111,     0,   115,   112,   116,   115,   117
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,    74,   104,  -166,  -184,
    -184,  -184,   101,    61,    39,  -120,  -184,  -184,  -184,  -184,
      46,    -2,  -184,  -184,  -149,  -103,  -152,  -183,  -184,    25,
      13,  -184,  -168,  -184,  -131,   -98,  -164,    50,  -184
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   140,   118,   101,   146,
     119,    32,   132,   156,   186,    51,    33,    34,    35,    52,
      53,   133,    55,   104,   128,   114,   134,   158,   184,   206,
     227,   153,   225,   209,   252,   257,   135,   168,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     179,   129,   181,    54,   192,   189,   213,   197,   173,    41,
      56,   154,   125,   125,   125,   125,    82,   169,    60,   207,
     249,   250,    57,    58,   121,    84,   223,   126,   126,   126,
     126,   204,   235,   218,   202,   174,   122,   224,   234,    73,
     251,    74,   175,    41,    42,   203,   127,   249,   250,    61,
     221,   232,   220,    43,    44,    45,    46,    47,    96,    59,
      48,   253,   207,    50,   240,   210,   193,   263,    62,   246,
     247,    63,    37,   236,    38,    54,    64,    54,    42,   107,
     108,   109,   110,   244,    65,   243,   259,    43,    44,    45,
      46,    47,   249,   250,    48,    49,    66,    50,     2,    81,
      82,    83,     3,     4,   258,   223,   125,     5,     6,    84,
       7,     8,     9,    10,    11,    39,   245,    40,    12,    13,
      14,   126,    80,   102,   260,   105,    15,    16,    67,    42,
     264,    81,    82,    83,   267,    68,    75,   178,    17,    44,
      45,    84,   159,   160,   161,    48,    76,    69,    50,    81,
      82,    83,   162,   163,   164,   165,   166,   167,    98,    84,
      99,    70,   262,    77,    71,   100,   266,    72,    78,   268,
     141,   142,   143,   144,   145,    79,    85,    86,    87,    88,
      89,    90,    91,    92,    94,    93,    95,    97,   103,   112,
     106,   111,   115,   123,   113,   117,   120,   124,   116,   130,
     136,   131,   137,   138,   139,   147,   148,   152,   155,   170,
     172,   150,   149,   177,   151,   157,   176,   180,   182,   183,
     185,   188,   191,   194,   190,   196,    98,   199,   214,   200,
     211,   201,   205,   215,   198,   208,   219,   216,   217,   226,
     229,   230,   233,   171,   242,   195,   223,   256,   212,   231,
     222,   239,   248,     0,   237,   238,   187,   228,   241,     0,
       0,     0,   254,   255,   261,     0,     0,     0,   265
};

static const yytype_int16 yycheck[] =
{
     149,   104,   151,     5,   168,   157,   189,   173,    17,    17,
      64,   131,    19,    19,    19,    19,    60,   137,    31,   183,
      10,    11,     7,     8,    18,    69,    19,    34,    34,    34,
      34,   180,    39,   199,    39,    44,    30,    30,   221,    41,
      30,    43,    51,    17,    52,    50,    50,    10,    11,    33,
     202,   217,   201,    61,    62,    63,    64,    65,    18,     3,
      68,   244,   226,    71,   228,   185,   169,    30,    64,   237,
     238,     3,     6,   222,     8,    77,     3,    79,    52,    81,
      82,    83,    84,   235,     3,   234,   254,    61,    62,    63,
      64,    65,    10,    11,    68,    69,     3,    71,     0,    59,
      60,    61,     4,     5,   253,    19,    19,     9,    10,    69,
      12,    13,    14,    15,    16,     6,    30,     8,    20,    21,
      22,    34,    50,    77,   255,    79,    28,    29,     3,    52,
     261,    59,    60,    61,   265,    41,    30,    50,    40,    62,
      63,    69,    43,    44,    45,    68,    17,    64,    71,    59,
      60,    61,    53,    54,    55,    56,    57,    58,    62,    69,
      64,    64,   260,    19,    64,    69,   264,    64,    33,   267,
      23,    24,    25,    26,    27,    19,     3,     3,    33,    64,
      64,    38,    42,    17,     3,    39,     3,    64,    64,    32,
      64,    64,    64,    18,    36,    64,    64,    18,    68,     3,
       3,    17,    53,    31,    19,    17,    64,    46,    19,     6,
      18,    35,    64,    18,    64,    37,    64,    64,    47,    49,
      19,     3,    45,    64,    44,     3,    62,    17,     3,    18,
      18,    64,    64,     3,    52,    48,     3,    18,    17,    37,
      47,     3,    18,   139,    18,   171,    19,    19,   187,   210,
      64,   226,   239,    -1,    64,    64,   155,   207,    64,    -1,
      -1,    -1,    64,    64,    64,    -1,    -1,    -1,    64
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,     0,     4,     5,     9,    10,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    40,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    94,    99,   100,   101,   121,     6,     8,     6,
       8,    17,    52,    61,    62,    63,    64,    65,    68,    69,
      71,    98,   102,   103,   104,   105,    64,     7,     8,     3,
      31,    33,    64,     3,     3,     3,     3,     3,    41,    64,
      64,    64,    64,   104,   104,    30,    17,    19,    33,    19,
      50,    59,    60,    61,    69,     3,     3,    33,    64,    64,
      38,    42,    17,    39,     3,     3,    18,    64,    62,    64,
      69,    91,   103,    64,   106,   103,    64,   104,   104,   104,
     104,    64,    32,    36,   108,    64,    68,    64,    90,    93,
      64,    18,    30,    18,    18,    19,    34,    50,   107,   108,
       3,    17,    95,   104,   109,   119,     3,    53,    31,    19,
      89,    23,    24,    25,    26,    27,    92,    17,    64,    64,
      35,    64,    46,   114,    98,    19,    96,    37,   110,    43,
      44,    45,    53,    54,    55,    56,    57,    58,   120,    98,
       6,    90,    18,    17,    44,    51,    64,    18,    50,   107,
      64,   107,    47,    49,   111,    19,    97,    95,     3,   109,
      44,    45,   119,   108,    64,    89,     3,    91,    52,    17,
      18,    64,    39,    50,   107,    64,   112,   119,    48,   116,
      98,    18,    96,   110,     3,     3,    18,    17,    91,     3,
     107,   109,    64,    19,    30,   115,    37,   113,   120,    47,
       3,    97,    91,    18,   110,    39,   107,    64,    64,   112,
     119,    64,    18,   107,   109,    30,   115,   115,   113,    10,
      11,    30,   117,   110,    64,    64,    19,   118,   107,   115,
     117,    64,   118,    30,   117,    64,   118,   117,   118
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    89,    90,    90,    90,
      90,    90,    90,    91,    92,    92,    92,    92,    92,    93,
      94,    95,    96,    96,    97,    97,    98,    98,    98,    98,
      98,    99,   100,   101,   102,   102,   102,   103,   103,   103,
     104,   104,   104,   104,   104,   104,   104,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   108,   108,   109,   110,   110,   111,   111,
     112,   113,   113,   114,   114,   114,   115,   115,   115,   116,
     116,   116,   117,   117,   117,   118,   118,   118,   119,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     9,     4,     5,     8,     0,     3,     5,     2,     6,
       3,     7,     4,     1,     1,     1,     1,     1,     1,     1,
       7,     4,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     5,     8,     9,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     3,     4,
       6,     4,     4,     1,     2,     4,     0,     3,     5,     4,
       6,     7,     9,     0,     3,     3,     0,     3,     0,     3,
       3,     0,     3,     0,     4,     6,     0,     3,     5,     0,
       5,     7,     0,     1,     1,     0,     4,     6,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 22: /* exit: EXIT SEMICOLON  */
#line 194 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1438 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 199 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1446 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 204 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1454 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 210 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1462 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 216 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 222 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1478 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 228 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1487 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 234 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1495 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 240 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1504 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 248 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1513 "yacc_sql.tab.c"
    break;

  case 32: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 256 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1522 "yacc_sql.tab.c"
    break;

  case 33: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 264 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_SHOW_INDEX;
            show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
        }
#line 1531 "yacc_sql.tab.c"
    break;

  case 34: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 273 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零
			CONTEXT->value_length = 0;
		}
#line 1543 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 283 "yacc_sql.y"
                                   {    }
#line 1549 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 288 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1564 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type  */
#line 299 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1579 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type NULLABLE LBRACE number RBRACE  */
#line 310 "yacc_sql.y"
        {
            AttrInfo attribute;
            attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number), 1);
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
            // strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
            CONTEXT->value_length++;
        }
#line 1594 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type NULLABLE  */
#line 321 "yacc_sql.y"
        {
            AttrInfo attribute;
            attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
            // strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
            CONTEXT->value_length++;
        }
#line 1609 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type NOT NULL_ LBRACE number RBRACE  */
#line 332 "yacc_sql.y"
            {
                AttrInfo attribute;
                attr_info_init(&attribute, CONTEXT->id, (yyvsp[-5].number), (yyvsp[-1].number), 0);
                create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
                // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
                // strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
                // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;
                // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
                CONTEXT->value_length++;
            }
#line 1624 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type NOT NULL_  */
#line 343 "yacc_sql.y"
            {
                AttrInfo attribute;
                attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
                create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
                // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
                // strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
                // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
                // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
                CONTEXT->value_length++;
            }
#line 1639 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 356 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1645 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 359 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1651 "yacc_sql.tab.c"
    break;

  case 45: /* type: STRING_T  */
#line 360 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1657 "yacc_sql.tab.c"
    break;

  case 46: /* type: FLOAT_T  */
#line 361 "yacc_sql.y"
                  { (yyval.number)=FLOATS; }
#line 1663 "yacc_sql.tab.c"
    break;

  case 47: /* type: DATE_T  */
#line 362 "yacc_sql.y"
                  { (yyval.number)=DATES; }
#line 1669 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 363 "yacc_sql.y"
                  { (yyval.number)=TEXT; }
#line 1675 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 367 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string);
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1684 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES value_tuple value_tuple_list SEMICOLON  */
#line 376 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
            inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->values, CONTEXT->value_length);
      //临时变量清零
      CONTEXT->value_length=0;
    }
#line 1702 "yacc_sql.tab.c"
    break;

  case 51: /* value_tuple: LBRACE value value_list RBRACE  */
#line 391 "yacc_sql.y"
                                   {
        CONTEXT->ssql->sstr.insertion.tuple_size[CONTEXT->ssql->sstr.insertion.tuple_num]++;
        CONTEXT->ssql->sstr.insertion.tuple_num++;
    }
#line 1711 "yacc_sql.tab.c"
    break;

  case 53: /* value_tuple_list: COMMA value_tuple value_tuple_list  */
#line 399 "yacc_sql.y"
                                         {
    }
#line 1718 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 405 "yacc_sql.y"
                              {
  		CONTEXT->ssql->sstr.insertion.tuple_size[CONTEXT->ssql->sstr.insertion.tuple_num]++;
	  }
#line 1726 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 410 "yacc_sql.y"
          {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1734 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 413 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1742 "yacc_sql.tab.c"
    break;

  case 58: /* value: DATE_STR  */
#line 416 "yacc_sql.y"
                 {
            (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		int ret = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
  		if (ret){
			// TODO: find an elegant way to do this
			CONTEXT->ssql->flag = SCF_ERROR;
			return -1;
        }
	    }
#line 1756 "yacc_sql.tab.c"
    break;

  case 59: /* value: NULL_  */
#line 425 "yacc_sql.y"
           {
            CONTEXT->value_length++;
        }
#line 1764 "yacc_sql.tab.c"
    break;

  case 60: /* value: SSS  */
#line 428 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1773 "yacc_sql.tab.c"
    break;

  case 61: /* delete: DELETE FROM ID where SEMICOLON  */
#line 436 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1785 "yacc_sql.tab.c"
    break;

  case 62: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 446 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1797 "yacc_sql.tab.c"
    break;

  case 63: /* select: SELECT select_list FROM rel where group_by having order_by SEMICOLON  */
#line 456 "yacc_sql.y"
                {
		    printf("have done");
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;


			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1818 "yacc_sql.tab.c"
    break;

  case 64: /* select_list: STAR  */
#line 475 "yacc_sql.y"
         {
            RelAttr attr;
            relation_attr_init(&attr, NULL, "*", NULL);
            selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 1828 "yacc_sql.tab.c"
    break;

  case 65: /* select_list: STAR COMMA selects_expression_all  */
#line 480 "yacc_sql.y"
                                        {
            RelAttr attr;
            relation_attr_init(&attr, NULL, "*", NULL);
            selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1838 "yacc_sql.tab.c"
    break;

  case 66: /* select_list: selects_expression_all  */
#line 485 "yacc_sql.y"
                             {
      }
#line 1845 "yacc_sql.tab.c"
    break;

  case 67: /* selects_expression_all: expr  */
#line 490 "yacc_sql.y"
         {
            //把存在buffer中的expr_cells转换为attribute放进sql中
            append_buffer_expr_to_select_attribute(&CONTEXT->ssql->sstr.selection, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            //把存在buffer中的expr_cells放进sql的ExprList中
            append_buffer_expr_to_select_exprlist(&CONTEXT->ssql->sstr.selection.expr_list, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            CONTEXT->ssql->sstr.selection.expr_list.exprs_num++;
            //清楚expr_cells缓存
            clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            CONTEXT->expr_cell_buffer_num = 0;
        }
#line 1860 "yacc_sql.tab.c"
    break;

  case 68: /* selects_expression_all: expr AS ID  */
#line 500 "yacc_sql.y"
                 {
            append_buffer_expr_to_select_attribute(&CONTEXT->ssql->sstr.selection, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            append_buffer_expr_to_select_exprlist(&CONTEXT->ssql->sstr.selection.expr_list, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            append_alias_to_expr(&CONTEXT->ssql->sstr.selection.expr_list, (yyvsp[0].string));
            CONTEXT->ssql->sstr.selection.expr_list.exprs_num++;
            clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            CONTEXT->expr_cell_buffer_num = 0;
        }
#line 1873 "yacc_sql.tab.c"
    break;

  case 69: /* selects_expression_all: selects_expression_all COMMA selects_expression_all  */
#line 508 "yacc_sql.y"
                                                          {
        }
#line 1880 "yacc_sql.tab.c"
    break;

  case 70: /* expr: expr PLUS expr  */
#line 512 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 8, "+", NULL, NULL);}
#line 1886 "yacc_sql.tab.c"
    break;

  case 71: /* expr: expr MINUS expr  */
#line 513 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 9, "-", NULL, NULL);}
#line 1892 "yacc_sql.tab.c"
    break;

  case 72: /* expr: expr STAR expr  */
#line 514 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 10, "*", NULL, NULL);}
#line 1898 "yacc_sql.tab.c"
    break;

  case 73: /* expr: expr DIV expr  */
#line 515 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 11, "/", NULL, NULL);}
#line 1904 "yacc_sql.tab.c"
    break;

  case 74: /* expr: LBRACE expr RBRACE  */
#line 516 "yacc_sql.y"
                           {}
#line 1910 "yacc_sql.tab.c"
    break;

  case 75: /* expr: MINUS expr  */
#line 517 "yacc_sql.y"
                               {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 12, "-", NULL, NULL);}
#line 1916 "yacc_sql.tab.c"
    break;

  case 76: /* expr: expr_cell  */
#line 518 "yacc_sql.y"
                  {}
#line 1922 "yacc_sql.tab.c"
    break;

  case 77: /* expr_cell: ID  */
#line 523 "yacc_sql.y"
       {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 1, (yyvsp[0].string), NULL, NULL);
       }
#line 1930 "yacc_sql.tab.c"
    break;

  case 78: /* expr_cell: ID DOT ID  */
#line 526 "yacc_sql.y"
                {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 2, (yyvsp[-2].string), (yyvsp[0].string), NULL);
       }
#line 1938 "yacc_sql.tab.c"
    break;

  case 79: /* expr_cell: AGGREGATION_FUNC LBRACE ID RBRACE  */
#line 529 "yacc_sql.y"
                                        {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 3, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
       }
#line 1946 "yacc_sql.tab.c"
    break;

  case 80: /* expr_cell: AGGREGATION_FUNC LBRACE ID DOT ID RBRACE  */
#line 532 "yacc_sql.y"
                                               {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 4, (yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].string));
       }
#line 1954 "yacc_sql.tab.c"
    break;

  case 81: /* expr_cell: AGGREGATION_FUNC LBRACE STAR RBRACE  */
#line 535 "yacc_sql.y"
                                          {
            if (strcmp((yyvsp[-3].string), "count") != 0 && strcmp((yyvsp[-3].string), "COUNT") != 0) {
            			CONTEXT->ssql->flag = SCF_ERROR;
            			return -1;
            }
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 5, (yyvsp[-3].string), NULL, NULL);
       }
#line 1966 "yacc_sql.tab.c"
    break;

  case 82: /* expr_cell: AGGREGATION_FUNC LBRACE number RBRACE  */
#line 542 "yacc_sql.y"
                                            {
            char num[20];
            sprintf(num, "%d", (yyvsp[-1].number));
            if ((strcmp((yyvsp[-3].string), "count") != 0 && strcmp((yyvsp[-3].string), "COUNT") != 0) || (yyvsp[-1].number) != 1) {
                        CONTEXT->ssql->flag = SCF_ERROR;
                        return -1;
            }
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 6, (yyvsp[-3].string), num, NULL);
       }
#line 1980 "yacc_sql.tab.c"
    break;

  case 83: /* expr_cell: value  */
#line 551 "yacc_sql.y"
            {
            char* temp = value_to_string(&CONTEXT->values[CONTEXT->value_length-1]);
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num], 7, temp, NULL, NULL);
            set_buffer_expr_cell_value_pos(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], CONTEXT->value_length-1);
    }
#line 1990 "yacc_sql.tab.c"
    break;

  case 84: /* rel: ID rel_list  */
#line 559 "yacc_sql.y"
               {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
        }
#line 1998 "yacc_sql.tab.c"
    break;

  case 85: /* rel: ID AS ID rel_list  */
#line 562 "yacc_sql.y"
                       {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
   }
#line 2006 "yacc_sql.tab.c"
    break;

  case 87: /* rel_list: COMMA ID rel_list  */
#line 569 "yacc_sql.y"
                        {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
		  }
#line 2014 "yacc_sql.tab.c"
    break;

  case 88: /* rel_list: COMMA ID AS ID rel_list  */
#line 572 "yacc_sql.y"
                              {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
        }
#line 2022 "yacc_sql.tab.c"
    break;

  case 89: /* rel_list: INNER JOIN ID rel_list  */
#line 575 "yacc_sql.y"
                             {
              selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
          }
#line 2030 "yacc_sql.tab.c"
    break;

  case 90: /* rel_list: INNER JOIN ID AS ID rel_list  */
#line 578 "yacc_sql.y"
                                   {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
          }
#line 2038 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: INNER JOIN ID ON condition condition_list rel_list  */
#line 581 "yacc_sql.y"
                                                         {
                selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), NULL);
          }
#line 2046 "yacc_sql.tab.c"
    break;

  case 92: /* rel_list: INNER JOIN ID AS ID ON condition condition_list rel_list  */
#line 584 "yacc_sql.y"
                                                               {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-6].string), (yyvsp[-4].string));
        }
#line 2054 "yacc_sql.tab.c"
    break;

  case 94: /* where: WHERE condition condition_list  */
#line 591 "yacc_sql.y"
                                     {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2062 "yacc_sql.tab.c"
    break;

  case 95: /* condition: condition_expression_all comOp condition_expression_all  */
#line 597 "yacc_sql.y"
                                                            {
        Condition condition;
        build_condition_by_buffer_expr(CONTEXT->comp, &CONTEXT->values, &condition, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_condition_first_position, CONTEXT->expr_cell_buffer_num);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
        CONTEXT->expr_cell_buffer_condition_first_position = 0;
        clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
        CONTEXT->expr_cell_buffer_num = 0;
    }
#line 2075 "yacc_sql.tab.c"
    break;

  case 97: /* condition_list: AND condition condition_list  */
#line 609 "yacc_sql.y"
                                   {
                // CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
            }
#line 2083 "yacc_sql.tab.c"
    break;

  case 99: /* having: HAVING having_condition having_condition_list  */
#line 616 "yacc_sql.y"
                                                    {
        }
#line 2090 "yacc_sql.tab.c"
    break;

  case 100: /* having_condition: condition_expression_all comOp condition_expression_all  */
#line 621 "yacc_sql.y"
                                                            {
        Condition condition;
        build_condition_by_buffer_expr(CONTEXT->comp, &CONTEXT->values, &condition, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_condition_first_position, CONTEXT->expr_cell_buffer_num);
        CONTEXT->ssql->sstr.selection.group_by.having_condition[CONTEXT->ssql->sstr.selection.group_by.having_condition_num++] = condition;
        CONTEXT->expr_cell_buffer_condition_first_position = 0;
        clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
        CONTEXT->expr_cell_buffer_num = 0;
    }
#line 2103 "yacc_sql.tab.c"
    break;

  case 102: /* having_condition_list: AND having_condition having_condition_list  */
#line 634 "yacc_sql.y"
                                                 {
            }
#line 2110 "yacc_sql.tab.c"
    break;

  case 104: /* group_by: GROUP BY ID group_by_rel_list  */
#line 641 "yacc_sql.y"
                                    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2120 "yacc_sql.tab.c"
    break;

  case 105: /* group_by: GROUP BY ID DOT ID group_by_rel_list  */
#line 646 "yacc_sql.y"
                                           {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2130 "yacc_sql.tab.c"
    break;

  case 107: /* group_by_rel_list: COMMA ID group_by_rel_list  */
#line 656 "yacc_sql.y"
                                 {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2140 "yacc_sql.tab.c"
    break;

  case 108: /* group_by_rel_list: COMMA ID DOT ID group_by_rel_list  */
#line 661 "yacc_sql.y"
                                        {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2150 "yacc_sql.tab.c"
    break;

  case 110: /* order_by: ORDER BY ID od_type order_by_info  */
#line 671 "yacc_sql.y"
                                        {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2160 "yacc_sql.tab.c"
    break;

  case 111: /* order_by: ORDER BY ID DOT ID od_type order_by_info  */
#line 676 "yacc_sql.y"
                                               {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2170 "yacc_sql.tab.c"
    break;

  case 112: /* od_type: %empty  */
#line 685 "yacc_sql.y"
                { (yyval.number)=ASC_ORDER; }
#line 2176 "yacc_sql.tab.c"
    break;

  case 113: /* od_type: ASC  */
#line 686 "yacc_sql.y"
              { (yyval.number)=ASC_ORDER; }
#line 2182 "yacc_sql.tab.c"
    break;

  case 114: /* od_type: DESC  */
#line 687 "yacc_sql.y"
               { (yyval.number)=DESC_ORDER; }
#line 2188 "yacc_sql.tab.c"
    break;

  case 116: /* order_by_info: COMMA ID od_type order_by_info  */
#line 693 "yacc_sql.y"
                                     {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2198 "yacc_sql.tab.c"
    break;

  case 117: /* order_by_info: COMMA ID DOT ID od_type order_by_info  */
#line 698 "yacc_sql.y"
                                            {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2208 "yacc_sql.tab.c"
    break;

  case 118: /* condition_expression_all: expr  */
#line 708 "yacc_sql.y"
         {
            if (CONTEXT->expr_cell_buffer_condition_first_position == 0) {
                CONTEXT->expr_cell_buffer_condition_first_position = CONTEXT->expr_cell_buffer_num;
            }
         }
#line 2218 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: EQ  */
#line 718 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2224 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: LT  */
#line 719 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2230 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: GT  */
#line 720 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2236 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: LE  */
#line 721 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2242 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: GE  */
#line 722 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2248 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: NE  */
#line 723 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2254 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: NOT LIKE_  */
#line 724 "yacc_sql.y"
                { CONTEXT->comp = NOT_LIKE; }
#line 2260 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: LIKE_  */
#line 725 "yacc_sql.y"
            { CONTEXT->comp = LIKE; }
#line 2266 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: IS_ NOT  */
#line 726 "yacc_sql.y"
              { CONTEXT->comp = IS_NOT; }
#line 2272 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: IS_  */
#line 727 "yacc_sql.y"
          {CONTEXT->comp = IS; }
#line 2278 "yacc_sql.tab.c"
    break;

  case 129: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 732 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2287 "yacc_sql.tab.c"
    break;


#line 2291 "yacc_sql.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 737 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));
	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	memset(context.ssql->sstr.selection.expr_list.exprs, 0, 20 * 20 * 20 * sizeof(char));
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
