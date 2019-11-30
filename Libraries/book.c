#include "book.h"
#include <string.h>
#include <stdlib.h>

Book* book_create(const char* name, const char** lines, int lineCount)
{
	Book* book = malloc(sizeof(Book));
	if (!book) return NULL;
	strcpy(book->name, name);
	book->lines = calloc(lineCount, sizeof(char*));
	for (int i = 0; i < lineCount; ++i)
	{
		book->lines[i] = calloc(strlen(lines[i]), sizeof(char));
		strcpy(book->lines[i], lines[i]);
	}
	return book;
}
