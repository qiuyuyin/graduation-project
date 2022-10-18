gen_parser:
	cd src/observer/sql/parser && pwd && flex --header-file=lex.yy.h lex_sql.l && bison -d -b yacc_sql yacc_sql.y