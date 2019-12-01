#include "book.h"
#include <string.h>
#include <stdlib.h>

Book* book_createFromText(const char* name, const char* text)
{
	Book* book = malloc(sizeof(Book));
	if (!book) return NULL;
	strcpy(book->name, name);
	book->text = calloc(strlen(text) + 1, sizeof(char));
	if (!book->text)
	{
		free(book);
		return NULL;
	}
	strcpy(book->text, text);
	return book;
}

Book* book_createFromLines(const char* name, const char** lines, int lineCount)
{
	Book* book = malloc(sizeof(Book));
	if (!book) return NULL;
	strcpy(book->name, name);

	int totalTextLength = 1; //one byte for null terminator
	for (int i = 0; i < lineCount; ++i)
	{
		totalTextLength += strlen(lines[i]);
	}
	book->text = calloc(totalTextLength, sizeof(char));
	if (!book->text)
	{
		free(book);
		return NULL;
	}
	char* curPtr = book->text;
	for (int i = 0; i < lineCount; ++i)
	{
		curPtr = strcat(curPtr, lines[i]);
	}
	return book;
}

void book_dispose(Book* book)
{
	free(book->text);
	free(book);
}