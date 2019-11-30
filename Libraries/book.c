#include "Book.h"
#include <string.h>
#include <stdlib.h>

Book* book_create(const char* name, char** lines)
{
	Book* book = malloc(sizeof(Book));
	if (!book) return NULL;
	strcpy(book->name, name);
	book->lines = lines;
}
