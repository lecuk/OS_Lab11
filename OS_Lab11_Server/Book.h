#pragma once

//we allocate text in heap because it's too large
typedef struct
{
	char name[30];
	char* text;
} Book;
