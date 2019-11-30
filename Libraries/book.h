#pragma once

#define BOOK_NAME_LEN 25

//we allocate text in heap because it's too large
typedef struct sBook
{
	char name[BOOK_NAME_LEN];
	char** lines;
} Book;

Book* book_create(const char* name, char** lines);