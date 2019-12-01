#include <stdio.h>
#include <Windows.h>
#include "book.h"
#include "filemapping.h"

void reading(Book *bookToRead)
{
	printf("[Reader] Proceed to read a book \"%s\".\n", bookToRead->name);
	printf("[Reader] Now, read the book till it's finished.\n");
	printf("> ");
	for (char* characher = bookToRead->text; *characher != '\0'; ++characher)
	{
		putchar(*characher);
		Sleep((strchr(" .,?!\n\t", *characher)) ? 300 : 50);
		if (*characher == '\n')
			printf("> ");
	}
	printf("[Reader] Reading finished.\n");
}

//READER
int main()
{
	printf("[Reader] You are reader.\n");

	HANDLE hFileMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, FILEMAP_NAME);
	if (hFileMap == NULL) {
		printf(stderr, "Can't open memory mapped file. Error code: %lu\n", GetLastError());
		return -1;
	}

	PBYTE pbMapView = (PBYTE)MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		FILEMAP_BUFFER_SIZE);
	if (pbMapView == NULL) {
		printf(stderr, "Can't map view of file. Error code: %lu\n", GetLastError());
		return -1;
	}

	//Dummy begin
	char readName[BOOK_NAME_LEN] = "The King in Yellow";
	char *readText = calloc(500, sizeof(char));
	readText = "Along the shore the cloud waves break,\n"
		"The twin suns sink behind the lake,\n"
		"The shadows lengthen\n"
		"In Carcosa.\n";
	//Dummy end

	Book *book = book_createFromText(readName, readText);
	reading(book);
	book_dispose(book);

	//Clean up
	//TODO: Insert clean up function here
	UnmapViewOfFile(pbMapView);
	CloseHandle(hFileMap);

	return 0;
}