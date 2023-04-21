/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
 #include "keytoktab.h"          /* when the keytoktab is added   */
 #include "lexer.h"              /* when the lexer     is added   */
 #include "symtab.h"             /* when the symtab    is added   */
 #include "optab.h"              /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int  lookahead=0;
static int  is_parse_ok=1;

/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/
/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
static int tokens[] = {program, id, '(', input, ',', output, ')', ';',
               '$' };

/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
static int pget_token()
{  
   static int i=0;
   if (tokens[i] != '$') return tokens[i++]; else return '$';
   }

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   	if(DEBUG) printf("\n --------In match expected: %4s, found: %4s",
                tok2lex(t), tok2lex(lookahead));
   	if (lookahead == t) lookahead = get_token();
   	else {
      		is_parse_ok=0;
      		printf("\n *** Unexpected Token: expected: %4s found: %4s (in match)",
              	tok2lex(t), get_lexeme(t));
	}
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/
static void program_header() {
   	if (DEBUG) printf("\n *** In  program_header");

	match(program);	
	if(lookahead == id) { 
		addp_name(get_lexeme());	
		match(id);	
	}
	else
		is_parse_ok = 0;
	match('(');
	match(input);
	match(',');
	match(output);
	match(')');
	match(';');
}
static void type() { 
	switch(lookahead) {
		case real:
			setv_type(real);
			match(real);
			break;
		case boolean:
			setv_type(boolean);
			match(boolean);
			break;
		case integer:
			setv_type(integer);
			match(integer);
			break;
		default:
			is_parse_ok = 0;
	}
}
static void id_list() { 
	if(lookahead == id) {
		char * name = get_lexeme();
		if(!find_name(name)) { 
			addv_name(name);
			match(id);
		}
		else
			is_parse_ok = 0;
	}
	if(lookahead == ',') { 
		match(',');
		id_list();
	}
}

static void var_dec() { 
	id_list();
	match(':');
	type();
	match(';');
}

static void var_dec_list() { 
	var_dec();
	if(lookahead == id)
		var_dec_list();
}

static void var_part() { 
	if (DEBUG) printf("\n *** In var part");
	match(var);
	var_dec_list();
}


static toktyp expr();
static toktyp operand() { 
	toktyp t = undef;
	if(lookahead == id) { 
		char * name = get_lexeme();
		if(find_name(name)) { 
			t = get_ntype(name);	
			match(id);
		}
		else { 
			t = undef;	
			match(id);
		}		
	}
	else if(lookahead == number) { 
		match(number);
		t = integer;
	}
	else {  
		t = error;
	}
	return t;
}

static toktyp factor() { 
	if(lookahead == '(') { 
		match('(');
		toktyp t = expr();
		match(')');
		return t;
	}
	else
		return operand();
}
static toktyp term() { 
	toktyp t = factor();
	if(lookahead == '*') { 
		match('*');	
		t = get_otype('*', t, term());
	}
	return t;
}



static toktyp expr() { 
	toktyp t = term();
	if(lookahead == '+') { 
		match('+');	
		t = get_otype('+', t, expr());
	}
	return t;
}
static void assign_stat() { 
	toktyp left = undef;
	toktyp right = undef;
	char * name = get_lexeme();
	if(lookahead == id) {
		if(find_name(name))
			left = get_ntype(name);
		match(id);
	}
	
	else
		is_parse_ok = 0; 
	match(assign);

	right = expr();
	if(left != right)
		//printf("%s%s\n", tok2lex(left), tok2lex(right));
		is_parse_ok = 0;
}
static void stat() { 
	assign_stat();	
}

static void stat_list() { 
	stat();
	if(lookahead == ';') { 
		match(';');	
		stat_list();
	}
}

static void stat_part() { 
	if(DEBUG) printf("\n *** In stat part");
	match(begin);
	stat_list();
	match(end);
	match('.');
	p_symtab();
}
   
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG) printf("\n *** In  parser\n");
   lookahead = get_token();       // get the first token
	if(lookahead != '$') { 
		program_header();
		var_part();
		stat_part();
		match('$');
		return is_parse_ok;
	}
	else
		is_parse_ok = 0;
   return is_parse_ok;             // status indicator
   }

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/

