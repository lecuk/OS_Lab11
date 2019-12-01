#include <stdio.h>
#include <Windows.h>
#include "llist.h"
#include "book.h"
#include <string.h>
#include "filemapping.h"

int cleanupAndExit(int code, void* mutex, void* file, void* fileMap, BYTE* fileMapView);

//WRITER
int main()
{
	Sleep(1000);

	void* mutex = CreateMutexA(NULL, FALSE, MUTEX_NAME);
	if (!mutex)
	{
		printf("Can't open mutex \"%s\". Error code: %lu\n", MUTEX_NAME, GetLastError());
		return cleanupAndExit(GetLastError(), NULL, NULL, NULL, NULL);
	}

	WaitForSingleObject(mutex, INFINITE);

	void* fileMap = OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, FILEMAP_NAME);
	if (!fileMap) {
		printf("Can't create file map: %s. Error code: %lu\n", FILEMAP_NAME, GetLastError());
		return cleanupAndExit(GetLastError(), mutex, NULL, NULL, NULL);
	}

	printf("File map was created: %s\n", FILEMAP_NAME);

	BYTE* fileMapView = (BYTE*)MapViewOfFile(fileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, FILEMAP_BUFFER_SIZE);
	if (!fileMapView) {
		printf("Can't map view of file. Error code: %lu\n", GetLastError());
		return cleanupAndExit(GetLastError(), mutex, NULL, fileMap, NULL);
	}

	ReleaseMutex(mutex);

	while (1)
	{
		printf("Do you want to write a book? (Y/N)\n");
		int input = tolower(_getch());
		if (input == 'n')
		{
			printf("OK.\n");
			break;
		}
		if (input == 'y')
		{
			if (fileMapView[FILEMAP_FLAG_ADDRESS] == 1)
			{
				printf("Book store is full, try later.\n");
				continue;
			}
		}
		else
		{
			printf("What?\n");
			continue;
		}

		printf("Enter book name:\n");
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
		char path[100];
		sprintf(path, "../%s", book->name);
		fileMapView[FILEMAP_FLAG_ADDRESS] = 1;
		strcpy(&fileMapView[FILEMAP_PATH_ADDRESS], path);
		FILE* file = fopen(path, "w");
		if (!file)
		{
			printf("Cannot open file: %s\n", path);
		}
		else
		{
			fprintf(file, "%s", book->text);
			fclose(file);
			printf("Successfully posted book \"%s\"\n", book->name);
		}

		for (int i = 0; i < linesList->count; ++i)
		{
			free(lines[i]);
		}
		free(lines);

		book_dispose(book);
		llist_dispose(linesList);
	}
	return cleanupAndExit(0, mutex, NULL, fileMap, fileMapView);
}
