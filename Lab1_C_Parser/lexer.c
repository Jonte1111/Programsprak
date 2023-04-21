/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
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
#define BUFSIZE 1024
#define LEXSIZE   30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int  pbuf  = 0;               /* current index program buffer  */
static int  plex  = 0;               /* current index lexeme  buffer  */
/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

static void get_prog() {

	//Read pas file into buffer and add $ to the end
//   	FILE *fp = fopen("testok1.pas", "r");
   	//FILE *fp = fopen(stdin, "r");
	//fseek (fp, 0, SEEK_END);
	fseek (stdin, 0, SEEK_END);
	int fSize = ftell(stdin);
	rewind(stdin);
   	//if(fp != NULL) {
   	if(stdin != NULL) {
		//fread(buffer, fSize, 1, fp);	
		fread(buffer, fSize, 1, stdin);	
		//Adds $ to the end of the file
		buffer[strlen(buffer)] = '$';
	}
	//fclose(fp);

}     

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/  

static void pbuffer()
{   
	printf("------------------- start of program text\n");
   	for(int i = 0; i <BUFSIZE;i++)
	   	printf("%c", buffer[i]);
	printf("\n");
	printf("------------------- end of program text\n");
   }

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char()
{   
   lexbuf[plex++] = buffer[pbuf++];
   }

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
int get_token() {  
	if(pbuf == 0) {

   		get_prog();
		pbuffer();
	}
	memset(lexbuf, '\0', LEXSIZE);
	plex = 0;
	while(isspace(buffer[pbuf]))
		pbuf++;
	get_char();
	if(isdigit(lexbuf[0])) { 
		while(!isspace(buffer[pbuf]) && isdigit(buffer[pbuf]))	
			get_char();
		return number;
	}	
	else if(isalpha(lexbuf[0])) { 
		while(!isspace(buffer[pbuf]) && (isdigit(buffer[pbuf]) || isalpha(buffer[pbuf])))	
			get_char();
		return key2tok(lexbuf);
	}
	else {
		if(lexbuf[0] == ':' && (buffer[pbuf] == '=')) { 
			get_char();				
		}
		return lex2tok(lexbuf);
	}

	return 0;
}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/
char * get_lexeme() {  
	return lexbuf;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/

