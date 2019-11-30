#pragma once

#define BOOK_NAME_LEN 25

//we allocate text in heap because it's too large
typedef struct
{
	char name[BOOK_NAME_LEN];
	char* text;
} Book;
