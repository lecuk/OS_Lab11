#include <stdio.h>
#include <Windows.h>
#include "book.h"
#include "llist.h"

//READER
int main()
{
	printf("[Reader] You are reader.\n");

	//TODO: Take mapped file and get data from it
	//Take data from map file somewhere from here
	char readName[BOOK_NAME_LEN] = "The King in Yellow";
	char *readText = calloc(500, sizeof(char));
	readText = "Along the shore the cloud waves break,\n"
		"The twin suns sink behind the lake,\n"
		"The shadows lengthen\n"
		"In Carcosa.\n";
	//To here

	Book *book = book_createFromText(readName, readText);
	printf("[Reader] Proceed to read a book \"%s\".\n", book->name);
	printf("[Reader] Now, read the book till it's finished.\n");
	printf("> ");
	for (char* characher = book->text; *characher != '\0'; ++characher)
	{
		putchar(*characher);
		Sleep((strchr(" .,?!\n\t", *characher)) ? 300 : 50);
		if (*characher == '\n')
			printf("> ");
	}
	printf("[Reader] Reading finished.\n");

	book_dispose(book);

	return 0;
}