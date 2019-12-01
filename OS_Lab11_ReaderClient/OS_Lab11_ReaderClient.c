#include <stdio.h>
#include <Windows.h>
#include <conio.h>
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
	Sleep(1000);
	printf("[Reader] You are reader.\n");

	HANDLE hFileMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, FILEMAP_NAME);
	if (hFileMap == NULL) {
		fprintf(stderr, "Can't open memory mapped file. Error code: %lu\n", GetLastError());
		return -1;
	}

	PBYTE pbMapView = (PBYTE)MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		FILEMAP_BUFFER_SIZE);
	if (pbMapView == NULL) {
		fprintf(stderr, "Can't map view of file. Error code: %lu\n", GetLastError());
		return -1;
	}

	while (!kbhit())
	{
		Sleep(100);
		if (!pbMapView[FILEMAP_FLAG_ADDRESS])
			continue;

		char fileName[BOOK_NAME_LEN];
		strncpy(fileName, pbMapView + FILEMAP_PATH_ADDRESS, BOOK_NAME_LEN);

		HANDLE hFile = CreateFileA(
			fileName,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			fprintf(stderr, "Can't open a file. Error code: %lu\n", GetLastError());
			continue;
		}

		DWORD fileSize = GetFileSize(hFile, &fileSize);
		char *readText = calloc(fileSize + 1, sizeof(char));
		unsigned long readBytes;
		if (!ReadFile(hFile, readText, fileSize, &readBytes, NULL)) {
			fprintf(stderr, "Can't read from a file. Error code: %lu\n", GetLastError());
			continue;
		}

		Book *book = book_createFromText(fileName, readText);
		reading(book);
		book_dispose(book);

		CloseHandle(hFile);

		pbMapView[FILEMAP_FLAG_ADDRESS] = 0;
	}

	//Clean up
	UnmapViewOfFile(pbMapView);
	CloseHandle(hFileMap);

	return 0;
}