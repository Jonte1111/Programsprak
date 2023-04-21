/**********************************************************************/
/* lab 1 DVG C01 - Operator Table OBJECT                              */
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
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define NENTS 4

static int optab[][NENTS] = {
   {'+', integer, integer, integer},
   {'+', real,    real,    real},
   {'+', integer, real,    real},
   {'+', real,    integer, real},
   {'*', integer, integer, integer},
   {'*', real,    real,    real},
   {'*', integer, real,    real},
   {'*', real,    integer, real},
   {'$', undef,   undef,   undef}
   };

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* display the op tab                                                 */
/**********************************************************************/
void p_optab() {
	printf("----------------------------------------------------------------\n");
	printf("\tTHE OPERATOR TABLE\n");
	printf("----------------------------------------------------------------\n");
	printf("\toperator\targ1\t\targ2\t\tresult\n");
	printf("----------------------------------------------------------------\n");
	for(int i = 0;i < 8;i++) { 
		for(int j = 0;j < 4;j++) { 
			printf("\t%s\t", tok2lex(optab[i][j]));
		}	
		printf("\t\n");
	}
}

/**********************************************************************/
/* return the type of a binary expression op arg1 arg2                */
/**********************************************************************/
int get_otype(int op, int arg1, int arg2) {  
	for(int i = 0;i < 8;i++) { 
		//for(int j = 0;j < 4;j++) { 
		if(optab[i][0] == op && optab[i][1] == arg1 && optab[i][2] == arg2)	
			return optab[i][3];
	}
	return undef;

}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
