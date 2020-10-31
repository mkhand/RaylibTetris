//gcc -std=c99 -Wall main.c mpc.c -ledit -lm -o main




#include <stdio.h>
#include <stdlib.h>
#include "mpc.h" // parser lib

#include <editline/readline.h>
#include <editline/history.h>



void parsing(char* line,mpc_parser_t* Zezay){

    /* Attempt to parse the user input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", line, Zezay, &r)) {
      /* On success print and delete the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise print and delete the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
}



int main(int argc, char** argv) {

  /* Create Some Parsers */
  mpc_parser_t* Valeur   = mpc_new("number");
  mpc_parser_t* Operateur = mpc_new("operator");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Zezay    = mpc_new("lispy");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' ;                  \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Valeur, Operateur, Expr, Zezay);

  puts("Zezay Version 0.0.0.0.2");
  puts("Appuyez sur Ctrl+c pour sortir\n");



  while (1) {

	char* input = readline("zezay> ");
	add_history(input);

	parsing(input,Zezay);

    free(input);
  }

  /* Undefine and delete our parsers */
  mpc_cleanup(4, Valeur, Operateur, Expr, Zezay);

  return 0;
}
