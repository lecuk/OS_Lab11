#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <filemapping.h>

int main()
{
		void* mutex = CreateMutexA(NULL, FALSE, MUTEX_NAME);
		if (!mutex)
		{
			printf("Can't create mutex. Error code: %lu\n", GetLastError());
			return 1;
		}

		printf("Mutex was created with name: %s\n", MUTEX_NAME);

		HANDLE file = CreateFileA(FILEMAP_PATH, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);

		if (file) {
			printf("File was created: %s\n", FILEMAP_PATH);
		}

		HANDLE fileMap = CreateFileMappingA(file, NULL, PAGE_READWRITE, 0, FILEMAP_BUFFER_SIZE, FILEMAP_NAME);
		if (!fileMap) {
			printf("Can't create file: %s. Error code: %lu\n", FILEMAP_PATH, GetLastError());
			return 1;
		}

		printf("File map was created: %s\n", FILEMAP_NAME);

		PBYTE fileMapView = (PBYTE)MapViewOfFile(fileMap, FILE_MAP_ALL_ACCESS, 0, 0, FILEMAP_BUFFER_SIZE);
		if (!fileMapView) {
			printf("Can't map view of file. Error code: %lu\n", GetLastError());
			return 1;
		}

		printf("File view was created with size: %d\n", FILEMAP_BUFFER_SIZE);

		printf("Press ENTER to close the program...\n");
		getchar();

		UnmapViewOfFile(fileMapView);
		CloseHandle(fileMap);
		CloseHandle(file);
		printf("All handles were closed.\n");
		return 0;
	
}