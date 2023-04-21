tparser:
	gcc -Wall -c driver.c
	gcc -Wall -c parser.c
	gcc -Wall -o tparser driver.c parser.c
tkeytoktab:
	gcc -Wall -c Dkeytoktab.c
	gcc -Wall -c keytoktab.c
	gcc -Wall -o tkeytoktab Dkeytoktab.c keytoktab.c
tlexer:
	gcc -Wall -c Dlexer.c
	gcc -Wall -c lexer.c
	gcc -Wall -c keytoktab.c
	gcc -Wall -o tlexer Dlexer.c lexer.c keytoktab.c
tsymtab:
	gcc -Wall -c Dsymtab.c
	gcc -Wall -c symtab.c
	gcc -Wall -c keytoktab.c
	gcc -Wall -o tsymtab Dsymtab.c symtab.c keytoktab.c
toptab:
	gcc -Wall -c Doptab.c
	gcc -Wall -c optab.c
	gcc -Wall -o toptab Doptab.c optab.c keytoktab.c 
parser:
	gcc -Wall -c driver.c
	gcc -Wall -c parser.c
	gcc -Wall -c Dkeytoktab.c
	gcc -Wall -c keytoktab.c
	gcc -Wall -c lexer.c
	gcc -Wall -o parser driver.c parser.c keytoktab.c lexer.c symtab.c optab.c


