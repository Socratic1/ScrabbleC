make: Scrabble.c
	gcc -o Scrabble Scrabble.c -I.

scrabbleTest : TestScrabble.c
	gcc TestScrabble.c Scrabble.c ./Unity/src/unity.c -o TestScrabble
