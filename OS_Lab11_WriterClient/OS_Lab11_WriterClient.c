#include <stdio.h>
#include <Windows.h>
#include "llist.h"
#include "book.h"
#include <string.h>

//WRITER
int main()
{
	LinkedList* linesList = llist_create(NULL, FALSE, sizeof(char*));

	printf("You are writer.\n");

	printf("Write a book. Enter book name:\n");
	char name[BOOK_NAME_LEN];
	fgets(name, BOOK_NAME_LEN, stdin);
	name[strlen(name) - 1] = 0;

	printf("Now, write text of your book. Write /stop to finish.\n");
	while (TRUE)
	{
		char line[100];
		fgets(line, 100, stdin);
		line[strlen(line) - 1] = 0;
		if (!strcmp(line, "/stop")) break;
		char* allocatedLine = calloc(strlen(line) + 1, sizeof(char));
		strcpy(allocatedLine, line);
		llist_add(linesList, allocatedLine);
	}

	char** lines = calloc(linesList->count, sizeof(char*));

	printf("Book: \"%s\"\n", name);
	int lineNumber = 1;
	llist_foreach(linesList, line)
	{
		char* line = line_node->item;
		lines[lineNumber - 1] = line;
		printf("%3d: %s\n", lineNumber, line);
		++lineNumber;
	}

	Book* book = book_create(name, lines, linesList->count);

	for (int i = 0; i < linesList->count; ++i)
	{
		free(lines[i]);
	}
	free(lines);

	return 0;
}
