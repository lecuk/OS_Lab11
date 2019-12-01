#include <stdio.h>
#include <Windows.h>
#include "llist.h"
#include "book.h"
#include <string.h>

//WRITER
int main()
{
	printf("You are writer.\n");

	printf("Write a book. Enter book name:\n");
	char name[BOOK_NAME_LEN];
	fgets(name, BOOK_NAME_LEN, stdin);
	name[strlen(name) - 1] = 0;

	printf("Now, write text of your book. Write /stop to finish.\n");
	LinkedList* linesList = llist_create(NULL, FALSE, sizeof(char*));
	while (TRUE)
	{
		printf("> ");
		char line[100];
		fgets(line, 100, stdin);
		if (!strcmp(line, "/stop\n")) break;
		char* allocatedLine = calloc(strlen(line) + 1, sizeof(char));
		strcpy(allocatedLine, line);
		llist_add(linesList, allocatedLine);
	}

	char** lines = calloc(linesList->count, sizeof(char*));

	int lineNumber = 0;
	llist_foreach(linesList, line)
	{
		char* line = line_node->item;
		lines[lineNumber] = line;
		++lineNumber;
	}

	Book* book = book_createFromLines(name, lines, linesList->count);

	for (int i = 0; i < linesList->count; ++i)
	{
		free(lines[i]);
	}
	free(lines);

	llist_dispose(linesList);

	printf("Book: \"%s\"\n", name);
	lineNumber = 1;
	printf("%3d | ", lineNumber);
	for (char* c = book->text; *c != 0; ++c)
	{
		putchar(*c);
		if (*c == '\n')
		{
			++lineNumber;
			printf("%3d | ", lineNumber);
		}
		Sleep((strchr(" .,?!;:\n", *c)) ? 150 : 40);
	}

	book_dispose(book);

	return 0;
}
