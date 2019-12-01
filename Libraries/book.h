#pragma once

#define BOOK_NAME_LEN 25

//we allocate text in heap because it's too large
typedef struct sBook
{
	char name[BOOK_NAME_LEN];
	char* text;
} Book;

Book* book_createFromText(const char* name, const char* text);
Book* book_createFromLines(const char* name, const char** lines, int lineCount);
void book_dispose(Book* book);