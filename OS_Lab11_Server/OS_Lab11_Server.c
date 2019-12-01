#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "filemapping.h"
#include <conio.h>

int cleanupAndExit(int code, void* mutex, void* file, void* fileMap, BYTE* fileMapView);

int main()
{
	void* mutex = CreateMutexA(NULL, FALSE, MUTEX_NAME);
	if (!mutex)
	{
		printf("Can't create mutex. Error code: %lu\n", GetLastError());
		return GetLastError();
	}

	printf("Mutex was created with name: %s\n", MUTEX_NAME);

	WaitForSingleObject(mutex, INFINITE);

	HANDLE file = CreateFileA(FILEMAP_PATH, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (!file) {
		printf("Can't create file: %s. Error code: %lu\n", FILEMAP_PATH, GetLastError());
		return cleanupAndExit(GetLastError(), mutex, NULL, NULL, NULL);
	}

	printf("File was created: %s\n", FILEMAP_PATH);

	HANDLE fileMap = CreateFileMappingA(file, NULL, PAGE_READWRITE, 0, FILEMAP_BUFFER_SIZE, FILEMAP_NAME);
	if (!fileMap) {
		printf("Can't create file mapping: %s. Error code: %lu\n", FILEMAP_NAME, GetLastError());
		return cleanupAndExit(GetLastError(), mutex, file, NULL, NULL);
	}

	printf("File map was created: %s\n", FILEMAP_NAME);

	PBYTE fileMapView = (PBYTE)MapViewOfFile(fileMap, FILE_MAP_ALL_ACCESS, 0, 0, FILEMAP_BUFFER_SIZE);
	if (!fileMapView) {
		printf("Can't map view of file. Error code: %lu\n", GetLastError());
		return cleanupAndExit(GetLastError(), mutex, file, fileMap, NULL);
	}

	ReleaseMutex(mutex);

	printf("File view was created with size: %d\n", FILEMAP_BUFFER_SIZE);

	printf("Press Q to close the program.\n");

	int bookFlag = fileMapView[FILEMAP_FLAG_ADDRESS];
	while (1)
	{
		if (_kbhit())
		{
			if (tolower(_getch()) == 'q')
			{
				printf("Exiting...\n");
				break;
			}
		}

		int curBookFlag = fileMapView[FILEMAP_FLAG_ADDRESS];
		if (bookFlag != curBookFlag)
		{
			if (curBookFlag)
			{
				printf("A book appeared in shop: \"%s\"\n", &fileMapView[FILEMAP_PATH_ADDRESS]);
			}
			else
			{
				printf("A book was read: \"%s\"\n", &fileMapView[FILEMAP_PATH_ADDRESS]);
			}
			bookFlag = curBookFlag;
		}

		Sleep(100);
	}

	return cleanupAndExit(0, mutex, file, fileMap, fileMapView);
}