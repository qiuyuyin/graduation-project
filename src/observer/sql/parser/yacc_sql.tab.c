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
  YYSYMBOL_IN_ = 44,                       /* IN_  */
  YYSYMBOL_NOT = 45,                       /* NOT  */
  YYSYMBOL_LIKE_ = 46,                     /* LIKE_  */
  YYSYMBOL_GROUP = 47,                     /* GROUP  */
  YYSYMBOL_BY = 48,                        /* BY  */
  YYSYMBOL_ORDER = 49,                     /* ORDER  */
  YYSYMBOL_HAVING = 50,                    /* HAVING  */
  YYSYMBOL_AS = 51,                        /* AS  */
  YYSYMBOL_NULLABLE = 52,                  /* NULLABLE  */
  YYSYMBOL_NULL_ = 53,                     /* NULL_  */
  YYSYMBOL_EQ = 54,                        /* EQ  */
  YYSYMBOL_LT = 55,                        /* LT  */
  YYSYMBOL_GT = 56,                        /* GT  */
  YYSYMBOL_LE = 57,                        /* LE  */
  YYSYMBOL_GE = 58,                        /* GE  */
  YYSYMBOL_NE = 59,                        /* NE  */
  YYSYMBOL_PLUS = 60,                      /* PLUS  */
  YYSYMBOL_DIV = 61,                       /* DIV  */
  YYSYMBOL_MINUS = 62,                     /* MINUS  */
  YYSYMBOL_UNIQUE = 63,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_AGGREGATION_FUNC = 67,          /* AGGREGATION_FUNC  */
  YYSYMBOL_AGGREGATION_FUNC_VALUE = 68,    /* AGGREGATION_FUNC_VALUE  */
  YYSYMBOL_PATH = 69,                      /* PATH  */
  YYSYMBOL_SSS = 70,                       /* SSS  */
  YYSYMBOL_STAR = 71,                      /* STAR  */
  YYSYMBOL_STRING_V = 72,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 73,                  /* DATE_STR  */
  YYSYMBOL_U_neg = 74,                     /* U_neg  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_commands = 76,                  /* commands  */
  YYSYMBOL_command = 77,                   /* command  */
  YYSYMBOL_exit = 78,                      /* exit  */
  YYSYMBOL_help = 79,                      /* help  */
  YYSYMBOL_sync = 80,                      /* sync  */
  YYSYMBOL_begin = 81,                     /* begin  */
  YYSYMBOL_commit = 82,                    /* commit  */
  YYSYMBOL_rollback = 83,                  /* rollback  */
  YYSYMBOL_drop_table = 84,                /* drop_table  */
  YYSYMBOL_show_tables = 85,               /* show_tables  */
  YYSYMBOL_desc_table = 86,                /* desc_table  */
  YYSYMBOL_index_field_list = 87,          /* index_field_list  */
  YYSYMBOL_index_field_list_ = 88,         /* index_field_list_  */
  YYSYMBOL_create_index = 89,              /* create_index  */
  YYSYMBOL_drop_index = 90,                /* drop_index  */
  YYSYMBOL_show_index = 91,                /* show_index  */
  YYSYMBOL_create_table = 92,              /* create_table  */
  YYSYMBOL_attr_def_list = 93,             /* attr_def_list  */
  YYSYMBOL_attr_def = 94,                  /* attr_def  */
  YYSYMBOL_number = 95,                    /* number  */
  YYSYMBOL_type = 96,                      /* type  */
  YYSYMBOL_ID_get = 97,                    /* ID_get  */
  YYSYMBOL_insert = 98,                    /* insert  */
  YYSYMBOL_value_tuple = 99,               /* value_tuple  */
  YYSYMBOL_value_tuple_list = 100,         /* value_tuple_list  */
  YYSYMBOL_value_list = 101,               /* value_list  */
  YYSYMBOL_value = 102,                    /* value  */
  YYSYMBOL_delete = 103,                   /* delete  */
  YYSYMBOL_update = 104,                   /* update  */
  YYSYMBOL_more_update = 105,              /* more_update  */
  YYSYMBOL_select = 106,                   /* select  */
  YYSYMBOL_select_list = 107,              /* select_list  */
  YYSYMBOL_selects_expression_all = 108,   /* selects_expression_all  */
  YYSYMBOL_expr = 109,                     /* expr  */
  YYSYMBOL_expr_cell = 110,                /* expr_cell  */
  YYSYMBOL_rel = 111,                      /* rel  */
  YYSYMBOL_rel_list = 112,                 /* rel_list  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_condition = 114,                /* condition  */
  YYSYMBOL_condition_list = 115,           /* condition_list  */
  YYSYMBOL_having = 116,                   /* having  */
  YYSYMBOL_having_condition = 117,         /* having_condition  */
  YYSYMBOL_having_condition_list = 118,    /* having_condition_list  */
  YYSYMBOL_group_by = 119,                 /* group_by  */
  YYSYMBOL_group_by_rel_list = 120,        /* group_by_rel_list  */
  YYSYMBOL_order_by = 121,                 /* order_by  */
  YYSYMBOL_od_type = 122,                  /* od_type  */
  YYSYMBOL_order_by_info = 123,            /* order_by_info  */
  YYSYMBOL_condition_expression_all = 124, /* condition_expression_all  */
  YYSYMBOL_expr_list = 125,                /* expr_list  */
  YYSYMBOL_comOp = 126,                    /* comOp  */
  YYSYMBOL_load_data = 127                 /* load_data  */
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
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  147
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  311

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   171,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   196,   201,   206,   212,   218,   224,   230,   236,
     242,   249,   255,   259,   265,   272,   282,   290,   299,   308,
     310,   314,   325,   336,   347,   358,   369,   383,   386,   387,
     388,   389,   390,   393,   402,   418,   424,   426,   430,   432,
     437,   440,   443,   452,   455,   462,   472,   482,   484,   494,
     514,   519,   524,   529,   539,   547,   555,   559,   560,   561,
     562,   563,   570,   571,   572,   577,   580,   583,   586,   589,
     592,   599,   608,   616,   619,   622,   627,   629,   632,   635,
     638,   641,   644,   647,   650,   653,   658,   660,   666,   676,
     678,   683,   685,   690,   701,   703,   708,   710,   715,   723,
     725,   730,   738,   740,   745,   754,   755,   756,   760,   762,
     767,   777,   782,   786,   788,   793,   794,   795,   796,   797,
     798,   799,   800,   801,   802,   803,   804,   808
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
  "IS_", "IN_", "NOT", "LIKE_", "GROUP", "BY", "ORDER", "HAVING", "AS",
  "NULLABLE", "NULL_", "EQ", "LT", "GT", "LE", "GE", "NE", "PLUS", "DIV",
  "MINUS", "UNIQUE", "NUMBER", "FLOAT", "ID", "AGGREGATION_FUNC",
  "AGGREGATION_FUNC_VALUE", "PATH", "SSS", "STAR", "STRING_V", "DATE_STR",
  "U_neg", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "index_field_list", "index_field_list_", "create_index", "drop_index",
  "show_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "value_tuple", "value_tuple_list",
  "value_list", "value", "delete", "update", "more_update", "select",
  "select_list", "selects_expression_all", "expr", "expr_cell", "rel",
  "rel_list", "where", "condition", "condition_list", "having",
  "having_condition", "having_condition_list", "group_by",
  "group_by_rel_list", "order_by", "od_type", "order_by_info",
  "condition_expression_all", "expr_list", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-261)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -261,   168,  -261,     0,    22,    38,   -28,    14,    39,    16,
      23,   -15,    56,    66,    69,    72,    93,    84,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,    63,    81,   154,
     104,   108,    68,  -261,    68,  -261,  -261,   145,   162,  -261,
     166,  -261,  -261,   153,   174,   141,  -261,   192,   195,   171,
    -261,   133,   140,   172,  -261,  -261,  -261,  -261,  -261,   167,
     194,   178,   152,   219,   233,    92,   173,   -52,    51,    68,
     175,    68,   176,    68,    68,    68,  -261,  -261,    68,  -261,
    -261,   177,   206,   203,   179,   180,   181,   182,   201,  -261,
    -261,  -261,  -261,  -261,  -261,    -6,   226,   228,   174,    -1,
     203,   174,  -261,   100,   173,   100,   173,   246,   234,    78,
     249,   199,   223,  -261,   236,   208,   239,   191,  -261,   193,
    -261,  -261,   196,   225,   197,    -2,  -261,   211,  -261,    28,
     242,    68,   159,   227,   170,  -261,    28,   259,   181,   248,
    -261,  -261,  -261,  -261,  -261,    -4,   202,   250,   251,     1,
     204,    -2,  -261,   224,   221,   254,   234,   271,    52,    78,
    -261,   230,  -261,    43,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,    78,   257,   212,   236,   274,   215,   229,   263,   262,
     265,   202,  -261,   218,    -2,  -261,    -8,  -261,   220,    78,
     238,    28,   267,   242,  -261,    68,   270,   227,  -261,  -261,
    -261,  -261,   231,   203,   286,  -261,  -261,   272,   275,   215,
     232,  -261,   288,   276,    -2,  -261,    78,   235,    10,  -261,
      15,   256,   170,   247,   293,   254,  -261,  -261,   105,  -261,
    -261,   245,   297,  -261,  -261,   215,   284,   262,  -261,   300,
    -261,   227,    34,    78,  -261,   240,   241,  -261,    78,  -261,
      78,   243,  -261,  -261,  -261,    28,  -261,   287,  -261,  -261,
    -261,    -2,    78,  -261,   227,    27,   285,   256,  -261,   109,
     257,  -261,  -261,   227,    -2,   244,  -261,  -261,  -261,  -261,
    -261,   252,   289,  -261,    -2,  -261,   285,   147,   253,  -261,
    -261,  -261,   289,   116,  -261,   255,   289,   147,  -261,   289,
    -261
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
       0,     0,     0,    63,     0,    60,    61,    85,     0,    64,
      70,    62,    92,     0,    72,    73,    84,     0,     0,     0,
      24,     0,     0,     0,    25,    26,    27,    23,    22,     0,
       0,     0,     0,     0,     0,     0,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,    75,     0,    30,
      29,     0,     0,   106,     0,     0,     0,     0,     0,    28,
      36,    82,    87,    86,    47,     0,     0,     0,    71,    96,
     106,    76,    74,    77,    80,    78,    79,     0,     0,     0,
       0,     0,     0,    53,    39,     0,     0,     0,    88,     0,
      90,    91,     0,     0,     0,    96,    93,   116,    37,     0,
      56,     0,   131,   109,     0,    65,     0,     0,     0,     0,
      51,    48,    49,    50,    52,    42,     0,     0,     0,    96,
       0,    96,    95,     0,   111,    58,     0,     0,     0,     0,
     107,   144,   145,     0,   142,   135,   136,   137,   138,   139,
     140,     0,    67,     0,    39,     0,     0,     0,    44,    32,
       0,     0,    89,     0,    96,    97,    96,    94,     0,     0,
     122,     0,     0,    56,    54,     0,     0,   109,   143,   146,
     141,   108,     0,   106,     0,    40,    38,     0,    46,     0,
       0,    31,     0,     0,    96,    99,     0,     0,    96,   100,
     119,   114,     0,     0,     0,    58,    55,    57,   133,   132,
     110,     0,     0,   147,    41,     0,     0,    32,    34,     0,
      98,   109,    96,     0,   102,     0,     0,   117,     0,   112,
       0,     0,    69,    59,   134,     0,    66,     0,    43,    33,
      35,    96,     0,   101,   109,   119,   119,   114,   113,   125,
      67,    45,   103,   109,    96,     0,   120,   118,   115,   127,
     126,     0,   128,    68,    96,   105,   119,   125,     0,   123,
     104,   121,   128,   125,   124,     0,   128,   125,   129,   128,
     130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,   120,    65,  -261,  -261,  -261,  -261,   129,   169,
    -179,  -261,  -261,  -261,   148,   112,    85,  -137,  -261,  -261,
      36,  -261,  -261,    18,    -5,  -261,  -261,  -134,  -107,  -165,
    -197,  -261,    64,    46,  -261,  -260,  -261,  -148,  -115,  -176,
      86,    94,  -261
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,   190,   221,    28,    29,    30,    31,   149,   124,
     107,   155,   125,    32,   140,   167,   202,    52,    33,    34,
     213,    35,    53,    54,   142,    56,   110,   136,   120,   143,
     170,   200,   231,   259,   164,   257,   234,   292,   299,   144,
     206,   181,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,   162,   165,   137,   207,   211,    37,   217,    38,   182,
     240,   132,   128,   186,   102,   286,   287,   132,   132,   103,
     132,    58,    59,   232,   129,   195,   133,   197,    40,   132,
      41,   226,   133,   133,   255,   133,   301,    75,    57,    76,
     246,   187,    60,   227,   133,   256,   255,    61,   188,   253,
     134,    63,   193,   132,   271,    42,    62,   285,   228,    64,
     225,   251,   229,    39,   235,   135,   267,   194,   133,    65,
     101,   205,    66,   272,    55,    67,    55,   284,   113,   114,
     115,    43,   232,   116,   278,    42,   294,   209,   274,   210,
     250,    43,    45,    46,   254,   141,    68,   108,    49,   111,
      44,    51,    45,    46,    47,    48,   242,   283,    49,    50,
     101,    51,    83,    84,    85,   104,    86,   105,   273,   289,
     290,    43,   106,    88,   205,    69,   289,   290,   280,    70,
      44,    43,    45,    46,    47,    48,   168,   282,    49,   291,
      44,    51,    45,    46,    47,    48,   305,    71,    49,   302,
     295,    51,    83,    84,    85,   306,    86,   289,   290,   309,
     300,    84,    72,    88,    86,    83,    84,    85,     2,    86,
      73,    88,     3,     4,    74,    77,    88,     5,     6,    78,
       7,     8,     9,    10,    11,    79,    80,   304,    12,    13,
      14,   308,    82,    81,   310,    89,    15,    16,    90,    92,
     238,    83,    84,    85,    91,    86,    93,    87,    17,    95,
      94,    96,    88,   171,   172,   173,   174,    97,    98,    83,
      84,    85,    99,    86,   175,   176,   177,   178,   179,   180,
      88,   150,   151,   152,   153,   154,   100,    86,   118,   119,
     127,   109,   112,   117,   130,   121,   131,   123,   126,   138,
     122,   139,   145,   146,   147,   148,   156,   157,   163,   158,
     160,   166,   159,   161,   169,   183,   185,   191,   189,   192,
     196,   199,   198,   201,   204,   208,   212,   216,   214,   104,
     219,   220,   218,   222,   224,   236,   230,   233,   239,   243,
     244,   248,   245,   258,   249,   261,   262,   241,   247,   265,
     266,   252,   268,   270,   255,   281,   275,   276,   298,   279,
     296,   223,   269,   215,   203,   237,   293,   184,   297,   303,
     263,   307,   277,   288,   264,     0,   260
};

static const yytype_int16 yycheck[] =
{
       5,   135,   139,   110,   169,   181,     6,   186,     8,   146,
     207,    19,    18,    17,    66,   275,   276,    19,    19,    71,
      19,     7,     8,   199,    30,   159,    34,   161,     6,    19,
       8,    39,    34,    34,    19,    34,   296,    42,    66,    44,
     219,    45,     3,    51,    34,    30,    19,    31,    52,    39,
      51,    66,    51,    19,   251,    17,    33,    30,    66,     3,
     194,   226,   196,    63,   201,    66,   245,    66,    34,     3,
      18,    19,     3,    39,    79,     3,    81,   274,    83,    84,
      85,    53,   258,    88,   260,    17,   283,    44,   253,    46,
     224,    53,    64,    65,   228,    17,     3,    79,    70,    81,
      62,    73,    64,    65,    66,    67,   213,   272,    70,    71,
      18,    73,    60,    61,    62,    64,    64,    66,   252,    10,
      11,    53,    71,    71,    19,    41,    10,    11,   265,    66,
      62,    53,    64,    65,    66,    67,   141,   271,    70,    30,
      62,    73,    64,    65,    66,    67,    30,    66,    70,   297,
     284,    73,    60,    61,    62,   303,    64,    10,    11,   307,
     294,    61,     8,    71,    64,    60,    61,    62,     0,    64,
      66,    71,     4,     5,    66,    30,    71,     9,    10,    17,
      12,    13,    14,    15,    16,    19,    33,   302,    20,    21,
      22,   306,    51,    19,   309,     3,    28,    29,     3,    66,
     205,    60,    61,    62,    33,    64,    66,    66,    40,    42,
      38,    17,    71,    43,    44,    45,    46,    39,    66,    60,
      61,    62,     3,    64,    54,    55,    56,    57,    58,    59,
      71,    23,    24,    25,    26,    27,     3,    64,    32,    36,
      39,    66,    66,    66,    18,    66,    18,    66,    66,     3,
      70,    17,     3,    54,    31,    19,    17,    66,    47,    66,
      35,    19,    66,    66,    37,     6,    18,    17,    66,    18,
      66,    50,    48,    19,     3,    45,    19,     3,    66,    64,
      17,    19,    53,    18,    66,    18,    66,    49,    18,     3,
      18,     3,    17,    37,    18,    48,     3,    66,    66,    54,
       3,    66,    18,     3,    19,    18,    66,    66,    19,    66,
      66,   191,   247,   184,   166,   203,   280,   148,    66,    66,
     235,    66,   258,   277,   238,    -1,   232
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    76,     0,     4,     5,     9,    10,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    40,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    89,    90,
      91,    92,    98,   103,   104,   106,   127,     6,     8,    63,
       6,     8,    17,    53,    62,    64,    65,    66,    67,    70,
      71,    73,   102,   107,   108,   109,   110,    66,     7,     8,
       3,    31,    33,    66,     3,     3,     3,     3,     3,    41,
      66,    66,     8,    66,    66,   109,   109,    30,    17,    19,
      33,    19,    51,    60,    61,    62,    64,    66,    71,     3,
       3,    33,    66,    66,    38,    42,    17,    39,    66,     3,
       3,    18,    66,    71,    64,    66,    71,    95,   108,    66,
     111,   108,    66,   109,   109,   109,   109,    66,    32,    36,
     113,    66,    70,    66,    94,    97,    66,    39,    18,    30,
      18,    18,    19,    34,    51,    66,   112,   113,     3,    17,
      99,    17,   109,   114,   124,     3,    54,    31,    19,    93,
      23,    24,    25,    26,    27,    96,    17,    66,    66,    66,
      35,    66,   112,    47,   119,   102,    19,   100,   109,    37,
     115,    43,    44,    45,    46,    54,    55,    56,    57,    58,
      59,   126,   102,     6,    94,    18,    17,    45,    52,    66,
      87,    17,    18,    51,    66,   112,    66,   112,    48,    50,
     116,    19,   101,    99,     3,    19,   125,   114,    45,    44,
      46,   124,    19,   105,    66,    93,     3,    95,    53,    17,
      19,    88,    18,    87,    66,   112,    39,    51,    66,   112,
      66,   117,   124,    49,   121,   102,    18,   100,   109,    18,
     115,    66,   113,     3,    18,    17,    95,    66,     3,    18,
     112,   114,    66,    39,   112,    19,    30,   120,    37,   118,
     126,    48,     3,   101,   125,    54,     3,    95,    18,    88,
       3,   115,    39,   112,   114,    66,    66,   117,   124,    66,
     102,    18,   112,   114,   115,    30,   120,   120,   118,    10,
      11,    30,   122,   105,   115,   112,    66,    66,    19,   123,
     112,   120,   122,    66,   123,    30,   122,    66,   123,   122,
     123
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    88,    89,    89,    90,    91,    92,    93,
      93,    94,    94,    94,    94,    94,    94,    95,    96,    96,
      96,    96,    96,    97,    98,    99,   100,   100,   101,   101,
     102,   102,   102,   102,   102,   103,   104,   105,   105,   106,
     107,   107,   107,   108,   108,   108,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   111,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   113,   113,   114,   115,
     115,   116,   116,   117,   118,   118,   119,   119,   119,   120,
     120,   120,   121,   121,   121,   122,   122,   122,   123,   123,
     123,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   127
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     2,     0,     3,     9,    10,     4,     5,     8,     0,
       3,     5,     2,     6,     3,     7,     4,     1,     1,     1,
       1,     1,     1,     1,     7,     4,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     5,     9,     0,     5,     9,
       1,     3,     1,     1,     3,     2,     3,     3,     3,     3,
       3,     2,     3,     2,     1,     1,     3,     3,     4,     6,
       4,     4,     1,     2,     4,     3,     0,     3,     5,     4,
       4,     6,     5,     7,     9,     8,     0,     3,     3,     0,
       3,     0,     3,     3,     0,     3,     0,     4,     6,     0,
       3,     5,     0,     5,     7,     0,     1,     1,     0,     4,
       6,     1,     4,     0,     3,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     1,     2,     8
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
#line 196 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1480 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 201 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1488 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 206 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1496 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 212 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1504 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 218 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1512 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 224 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1520 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 230 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1529 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 236 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1537 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 242 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1546 "yacc_sql.tab.c"
    break;

  case 31: /* index_field_list: ID index_field_list_  */
#line 249 "yacc_sql.y"
                         {
            create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
    }
#line 1554 "yacc_sql.tab.c"
    break;

  case 32: /* index_field_list_: %empty  */
#line 255 "yacc_sql.y"
        {
			create_index_init(&CONTEXT->ssql->sstr.create_index);
        }
#line 1562 "yacc_sql.tab.c"
    break;

  case 33: /* index_field_list_: COMMA ID index_field_list_  */
#line 259 "yacc_sql.y"
                                 {
            create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
    }
#line 1570 "yacc_sql.tab.c"
    break;

  case 34: /* create_index: CREATE INDEX ID ON ID LBRACE index_field_list RBRACE SEMICOLON  */
#line 266 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			CONTEXT->ssql->sstr.create_index.is_unique = 0;
			create_index_set_relation_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[-4].string));
			create_index_set_index_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string));
		}
#line 1581 "yacc_sql.tab.c"
    break;

  case 35: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE index_field_list RBRACE SEMICOLON  */
#line 273 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			CONTEXT->ssql->sstr.create_index.is_unique = 1;
			create_index_set_relation_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[-4].string));
			create_index_set_index_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string));
		}
#line 1592 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 283 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1601 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 291 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_SHOW_INDEX;
            show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
        }
#line 1610 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 300 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零
			CONTEXT->value_length = 0;
		}
#line 1622 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 310 "yacc_sql.y"
                                   {    }
#line 1628 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 315 "yacc_sql.y"
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
#line 1643 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 326 "yacc_sql.y"
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
#line 1658 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NULLABLE LBRACE number RBRACE  */
#line 337 "yacc_sql.y"
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
#line 1673 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 348 "yacc_sql.y"
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
#line 1688 "yacc_sql.tab.c"
    break;

  case 45: /* attr_def: ID_get type NOT NULL_ LBRACE number RBRACE  */
#line 359 "yacc_sql.y"
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
#line 1703 "yacc_sql.tab.c"
    break;

  case 46: /* attr_def: ID_get type NOT NULL_  */
#line 370 "yacc_sql.y"
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
#line 1718 "yacc_sql.tab.c"
    break;

  case 47: /* number: NUMBER  */
#line 383 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1724 "yacc_sql.tab.c"
    break;

  case 48: /* type: INT_T  */
#line 386 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1730 "yacc_sql.tab.c"
    break;

  case 49: /* type: STRING_T  */
#line 387 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1736 "yacc_sql.tab.c"
    break;

  case 50: /* type: FLOAT_T  */
#line 388 "yacc_sql.y"
                  { (yyval.number)=FLOATS; }
#line 1742 "yacc_sql.tab.c"
    break;

  case 51: /* type: DATE_T  */
#line 389 "yacc_sql.y"
                  { (yyval.number)=DATES; }
#line 1748 "yacc_sql.tab.c"
    break;

  case 52: /* type: TEXT_T  */
#line 390 "yacc_sql.y"
                  { (yyval.number)=TEXT; }
#line 1754 "yacc_sql.tab.c"
    break;

  case 53: /* ID_get: ID  */
#line 394 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string);
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1763 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES value_tuple value_tuple_list SEMICOLON  */
#line 403 "yacc_sql.y"
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
#line 1781 "yacc_sql.tab.c"
    break;

  case 55: /* value_tuple: LBRACE value value_list RBRACE  */
#line 418 "yacc_sql.y"
                                   {
        CONTEXT->ssql->sstr.insertion.tuple_size[CONTEXT->ssql->sstr.insertion.tuple_num]++;
        CONTEXT->ssql->sstr.insertion.tuple_num++;
    }
#line 1790 "yacc_sql.tab.c"
    break;

  case 57: /* value_tuple_list: COMMA value_tuple value_tuple_list  */
#line 426 "yacc_sql.y"
                                         {
    }
#line 1797 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 432 "yacc_sql.y"
                              {
  		CONTEXT->ssql->sstr.insertion.tuple_size[CONTEXT->ssql->sstr.insertion.tuple_num]++;
	  }
#line 1805 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 437 "yacc_sql.y"
          {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1813 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 440 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1821 "yacc_sql.tab.c"
    break;

  case 62: /* value: DATE_STR  */
#line 443 "yacc_sql.y"
                 {
            (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		int ret = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
  		if (ret){
			// TODO: find an elegant way to do this
			CONTEXT->ssql->flag = SCF_ERROR;
			return -1;
        }
	    }
#line 1835 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_  */
#line 452 "yacc_sql.y"
           {
            CONTEXT->value_length++;
        }
#line 1843 "yacc_sql.tab.c"
    break;

  case 64: /* value: SSS  */
#line 455 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1852 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 463 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1864 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET ID EQ value more_update where SEMICOLON  */
#line 473 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-7].string), (yyvsp[-5].string), value,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1876 "yacc_sql.tab.c"
    break;

  case 68: /* more_update: COMMA ID EQ value more_update  */
#line 485 "yacc_sql.y"
        {
            Value *value = &CONTEXT->values[CONTEXT->value_length-1-CONTEXT->ssql->sstr.update.update_attr_num];
            updates_append(&CONTEXT->ssql->sstr.update,(yyvsp[-3].string),value);
            printf("%d",CONTEXT->value_length-1);
        }
#line 1886 "yacc_sql.tab.c"
    break;

  case 69: /* select: SELECT select_list FROM rel where group_by having order_by SEMICOLON  */
#line 495 "yacc_sql.y"
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
#line 1907 "yacc_sql.tab.c"
    break;

  case 70: /* select_list: STAR  */
#line 514 "yacc_sql.y"
         {
            RelAttr attr;
            relation_attr_init(&attr, NULL, "*", NULL);
            selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 1917 "yacc_sql.tab.c"
    break;

  case 71: /* select_list: STAR COMMA selects_expression_all  */
#line 519 "yacc_sql.y"
                                        {
            RelAttr attr;
            relation_attr_init(&attr, NULL, "*", NULL);
            selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1927 "yacc_sql.tab.c"
    break;

  case 72: /* select_list: selects_expression_all  */
#line 524 "yacc_sql.y"
                             {
      }
#line 1934 "yacc_sql.tab.c"
    break;

  case 73: /* selects_expression_all: expr  */
#line 529 "yacc_sql.y"
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
#line 1949 "yacc_sql.tab.c"
    break;

  case 74: /* selects_expression_all: expr AS ID  */
#line 539 "yacc_sql.y"
                 {
            append_buffer_expr_to_select_attribute(&CONTEXT->ssql->sstr.selection, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            append_buffer_expr_to_select_exprlist(&CONTEXT->ssql->sstr.selection.expr_list, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            append_alias_to_expr(&CONTEXT->ssql->sstr.selection.expr_list, (yyvsp[0].string));
            CONTEXT->ssql->sstr.selection.expr_list.exprs_num++;
            clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            CONTEXT->expr_cell_buffer_num = 0;
        }
#line 1962 "yacc_sql.tab.c"
    break;

  case 75: /* selects_expression_all: expr ID  */
#line 547 "yacc_sql.y"
              {
            append_buffer_expr_to_select_attribute(&CONTEXT->ssql->sstr.selection, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            append_buffer_expr_to_select_exprlist(&CONTEXT->ssql->sstr.selection.expr_list, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            append_alias_to_expr(&CONTEXT->ssql->sstr.selection.expr_list, (yyvsp[0].string));
            CONTEXT->ssql->sstr.selection.expr_list.exprs_num++;
            clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
            CONTEXT->expr_cell_buffer_num = 0;
        }
#line 1975 "yacc_sql.tab.c"
    break;

  case 76: /* selects_expression_all: selects_expression_all COMMA selects_expression_all  */
#line 555 "yacc_sql.y"
                                                          {
        }
#line 1982 "yacc_sql.tab.c"
    break;

  case 77: /* expr: expr PLUS expr  */
#line 559 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 8, "+", NULL, NULL);}
#line 1988 "yacc_sql.tab.c"
    break;

  case 78: /* expr: expr MINUS expr  */
#line 560 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 9, "-", NULL, NULL);}
#line 1994 "yacc_sql.tab.c"
    break;

  case 79: /* expr: expr STAR expr  */
#line 561 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 10, "*", NULL, NULL);}
#line 2000 "yacc_sql.tab.c"
    break;

  case 80: /* expr: expr DIV expr  */
#line 562 "yacc_sql.y"
                           {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 11, "/", NULL, NULL);}
#line 2006 "yacc_sql.tab.c"
    break;

  case 81: /* expr: expr NUMBER  */
#line 563 "yacc_sql.y"
                           {
                                value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number) * -1);
                                char* temp = value_to_string(&CONTEXT->values[CONTEXT->value_length-1]);
                                set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num], 13, temp, NULL, NULL);
                                set_buffer_expr_cell_value_pos(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], CONTEXT->value_length-1);
                                set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 13, "-", NULL, NULL);
                            }
#line 2018 "yacc_sql.tab.c"
    break;

  case 82: /* expr: LBRACE expr RBRACE  */
#line 570 "yacc_sql.y"
                           {}
#line 2024 "yacc_sql.tab.c"
    break;

  case 83: /* expr: MINUS expr  */
#line 571 "yacc_sql.y"
                               {set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 12, "-", NULL, NULL);}
#line 2030 "yacc_sql.tab.c"
    break;

  case 84: /* expr: expr_cell  */
#line 572 "yacc_sql.y"
                  {}
#line 2036 "yacc_sql.tab.c"
    break;

  case 85: /* expr_cell: ID  */
#line 577 "yacc_sql.y"
       {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 1, (yyvsp[0].string), NULL, NULL);
       }
#line 2044 "yacc_sql.tab.c"
    break;

  case 86: /* expr_cell: ID DOT STAR  */
#line 580 "yacc_sql.y"
                  {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 2, (yyvsp[-2].string), "*", NULL);
       }
#line 2052 "yacc_sql.tab.c"
    break;

  case 87: /* expr_cell: ID DOT ID  */
#line 583 "yacc_sql.y"
                {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 2, (yyvsp[-2].string), (yyvsp[0].string), NULL);
       }
#line 2060 "yacc_sql.tab.c"
    break;

  case 88: /* expr_cell: AGGREGATION_FUNC LBRACE ID RBRACE  */
#line 586 "yacc_sql.y"
                                        {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 3, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
       }
#line 2068 "yacc_sql.tab.c"
    break;

  case 89: /* expr_cell: AGGREGATION_FUNC LBRACE ID DOT ID RBRACE  */
#line 589 "yacc_sql.y"
                                               {
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 4, (yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].string));
       }
#line 2076 "yacc_sql.tab.c"
    break;

  case 90: /* expr_cell: AGGREGATION_FUNC LBRACE STAR RBRACE  */
#line 592 "yacc_sql.y"
                                          {
            if (strcmp((yyvsp[-3].string), "count") != 0 && strcmp((yyvsp[-3].string), "COUNT") != 0) {
            			CONTEXT->ssql->flag = SCF_ERROR;
            			return -1;
            }
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 5, (yyvsp[-3].string), NULL, NULL);
       }
#line 2088 "yacc_sql.tab.c"
    break;

  case 91: /* expr_cell: AGGREGATION_FUNC LBRACE number RBRACE  */
#line 599 "yacc_sql.y"
                                            {
            char num[20];
            sprintf(num, "%d", (yyvsp[-1].number));
            if ((strcmp((yyvsp[-3].string), "count") != 0 && strcmp((yyvsp[-3].string), "COUNT") != 0) || (yyvsp[-1].number) != 1) {
                        CONTEXT->ssql->flag = SCF_ERROR;
                        return -1;
            }
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], 6, (yyvsp[-3].string), num, NULL);
       }
#line 2102 "yacc_sql.tab.c"
    break;

  case 92: /* expr_cell: value  */
#line 608 "yacc_sql.y"
            {
            char* temp = value_to_string(&CONTEXT->values[CONTEXT->value_length-1]);
            set_buffer_expr_cell(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num], 7, temp, NULL, NULL);
            set_buffer_expr_cell_value_pos(&CONTEXT->expr_cells[CONTEXT->expr_cell_buffer_num++], CONTEXT->value_length-1);
    }
#line 2112 "yacc_sql.tab.c"
    break;

  case 93: /* rel: ID rel_list  */
#line 616 "yacc_sql.y"
               {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
        }
#line 2120 "yacc_sql.tab.c"
    break;

  case 94: /* rel: ID AS ID rel_list  */
#line 619 "yacc_sql.y"
                       {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
   }
#line 2128 "yacc_sql.tab.c"
    break;

  case 95: /* rel: ID ID rel_list  */
#line 622 "yacc_sql.y"
                   {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string), (yyvsp[-1].string));
   }
#line 2136 "yacc_sql.tab.c"
    break;

  case 97: /* rel_list: COMMA ID rel_list  */
#line 629 "yacc_sql.y"
                        {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
		  }
#line 2144 "yacc_sql.tab.c"
    break;

  case 98: /* rel_list: COMMA ID AS ID rel_list  */
#line 632 "yacc_sql.y"
                              {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
        }
#line 2152 "yacc_sql.tab.c"
    break;

  case 99: /* rel_list: COMMA ID ID rel_list  */
#line 635 "yacc_sql.y"
                           {
                selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string), (yyvsp[-1].string));
            }
#line 2160 "yacc_sql.tab.c"
    break;

  case 100: /* rel_list: INNER JOIN ID rel_list  */
#line 638 "yacc_sql.y"
                             {
              selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
          }
#line 2168 "yacc_sql.tab.c"
    break;

  case 101: /* rel_list: INNER JOIN ID AS ID rel_list  */
#line 641 "yacc_sql.y"
                                   {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
          }
#line 2176 "yacc_sql.tab.c"
    break;

  case 102: /* rel_list: INNER JOIN ID ID rel_list  */
#line 644 "yacc_sql.y"
                                {
                selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string), (yyvsp[-1].string));
              }
#line 2184 "yacc_sql.tab.c"
    break;

  case 103: /* rel_list: INNER JOIN ID ON condition condition_list rel_list  */
#line 647 "yacc_sql.y"
                                                         {
                selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), NULL);
          }
#line 2192 "yacc_sql.tab.c"
    break;

  case 104: /* rel_list: INNER JOIN ID AS ID ON condition condition_list rel_list  */
#line 650 "yacc_sql.y"
                                                               {
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-6].string), (yyvsp[-4].string));
        }
#line 2200 "yacc_sql.tab.c"
    break;

  case 105: /* rel_list: INNER JOIN ID ID ON condition condition_list rel_list  */
#line 653 "yacc_sql.y"
                                                            {
                selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string), (yyvsp[-4].string));
            }
#line 2208 "yacc_sql.tab.c"
    break;

  case 107: /* where: WHERE condition condition_list  */
#line 660 "yacc_sql.y"
                                     {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2216 "yacc_sql.tab.c"
    break;

  case 108: /* condition: condition_expression_all comOp condition_expression_all  */
#line 666 "yacc_sql.y"
                                                            {
        Condition condition;
        build_condition_by_buffer_expr(CONTEXT->comp, &CONTEXT->values, &condition, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_condition_first_position, CONTEXT->expr_cell_buffer_num);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
        CONTEXT->expr_cell_buffer_condition_first_position = 0;
        clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
        CONTEXT->expr_cell_buffer_num = 0;
    }
#line 2229 "yacc_sql.tab.c"
    break;

  case 110: /* condition_list: AND condition condition_list  */
#line 678 "yacc_sql.y"
                                   {
                // CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
            }
#line 2237 "yacc_sql.tab.c"
    break;

  case 112: /* having: HAVING having_condition having_condition_list  */
#line 685 "yacc_sql.y"
                                                    {
        }
#line 2244 "yacc_sql.tab.c"
    break;

  case 113: /* having_condition: condition_expression_all comOp condition_expression_all  */
#line 690 "yacc_sql.y"
                                                            {
        Condition condition;
        build_condition_by_buffer_expr(CONTEXT->comp, &CONTEXT->values, &condition, &CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_condition_first_position, CONTEXT->expr_cell_buffer_num);
        CONTEXT->ssql->sstr.selection.group_by.having_condition[CONTEXT->ssql->sstr.selection.group_by.having_condition_num++] = condition;
        CONTEXT->expr_cell_buffer_condition_first_position = 0;
        clear_buffer_expr_cell_list(&CONTEXT->expr_cells, CONTEXT->expr_cell_buffer_num);
        CONTEXT->expr_cell_buffer_num = 0;
    }
#line 2257 "yacc_sql.tab.c"
    break;

  case 115: /* having_condition_list: AND having_condition having_condition_list  */
#line 703 "yacc_sql.y"
                                                 {
            }
#line 2264 "yacc_sql.tab.c"
    break;

  case 117: /* group_by: GROUP BY ID group_by_rel_list  */
#line 710 "yacc_sql.y"
                                    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2274 "yacc_sql.tab.c"
    break;

  case 118: /* group_by: GROUP BY ID DOT ID group_by_rel_list  */
#line 715 "yacc_sql.y"
                                           {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2284 "yacc_sql.tab.c"
    break;

  case 120: /* group_by_rel_list: COMMA ID group_by_rel_list  */
#line 725 "yacc_sql.y"
                                 {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2294 "yacc_sql.tab.c"
    break;

  case 121: /* group_by_rel_list: COMMA ID DOT ID group_by_rel_list  */
#line 730 "yacc_sql.y"
                                        {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
        groupby_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2304 "yacc_sql.tab.c"
    break;

  case 123: /* order_by: ORDER BY ID od_type order_by_info  */
#line 740 "yacc_sql.y"
                                        {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2314 "yacc_sql.tab.c"
    break;

  case 124: /* order_by: ORDER BY ID DOT ID od_type order_by_info  */
#line 745 "yacc_sql.y"
                                               {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2324 "yacc_sql.tab.c"
    break;

  case 125: /* od_type: %empty  */
#line 754 "yacc_sql.y"
                { (yyval.number)=ASC_ORDER; }
#line 2330 "yacc_sql.tab.c"
    break;

  case 126: /* od_type: ASC  */
#line 755 "yacc_sql.y"
              { (yyval.number)=ASC_ORDER; }
#line 2336 "yacc_sql.tab.c"
    break;

  case 127: /* od_type: DESC  */
#line 756 "yacc_sql.y"
               { (yyval.number)=DESC_ORDER; }
#line 2342 "yacc_sql.tab.c"
    break;

  case 129: /* order_by_info: COMMA ID od_type order_by_info  */
#line 762 "yacc_sql.y"
                                     {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2352 "yacc_sql.tab.c"
    break;

  case 130: /* order_by_info: COMMA ID DOT ID od_type order_by_info  */
#line 767 "yacc_sql.y"
                                            {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
        selects_append_order_by_attr(&CONTEXT->ssql->sstr.selection,&attr,(yyvsp[-1].number));
    }
#line 2362 "yacc_sql.tab.c"
    break;

  case 131: /* condition_expression_all: expr  */
#line 777 "yacc_sql.y"
         {
            if (CONTEXT->expr_cell_buffer_condition_first_position == 0) {
                CONTEXT->expr_cell_buffer_condition_first_position = CONTEXT->expr_cell_buffer_num;
            }
         }
#line 2372 "yacc_sql.tab.c"
    break;

  case 132: /* condition_expression_all: LBRACE expr expr_list RBRACE  */
#line 782 "yacc_sql.y"
                                   {
    }
#line 2379 "yacc_sql.tab.c"
    break;

  case 134: /* expr_list: COMMA expr expr_list  */
#line 788 "yacc_sql.y"
                           {
    }
#line 2386 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: EQ  */
#line 793 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2392 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: LT  */
#line 794 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2398 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: GT  */
#line 795 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2404 "yacc_sql.tab.c"
    break;

  case 138: /* comOp: LE  */
#line 796 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2410 "yacc_sql.tab.c"
    break;

  case 139: /* comOp: GE  */
#line 797 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2416 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: NE  */
#line 798 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2422 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: NOT LIKE_  */
#line 799 "yacc_sql.y"
                { CONTEXT->comp = NOT_LIKE; }
#line 2428 "yacc_sql.tab.c"
    break;

  case 142: /* comOp: LIKE_  */
#line 800 "yacc_sql.y"
            { CONTEXT->comp = LIKE; }
#line 2434 "yacc_sql.tab.c"
    break;

  case 143: /* comOp: IS_ NOT  */
#line 801 "yacc_sql.y"
              { CONTEXT->comp = IS_NOT; }
#line 2440 "yacc_sql.tab.c"
    break;

  case 144: /* comOp: IS_  */
#line 802 "yacc_sql.y"
          {CONTEXT->comp = IS; }
#line 2446 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: IN_  */
#line 803 "yacc_sql.y"
          { CONTEXT->comp = IN; }
#line 2452 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: NOT IN_  */
#line 804 "yacc_sql.y"
              { CONTEXT->comp = NOT_IN; }
#line 2458 "yacc_sql.tab.c"
    break;

  case 147: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 809 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2467 "yacc_sql.tab.c"
    break;


#line 2471 "yacc_sql.tab.c"

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

#line 814 "yacc_sql.y"

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
