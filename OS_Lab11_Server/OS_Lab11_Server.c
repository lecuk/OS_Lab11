#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main()
{
		int buffer_size = 512;

		HANDLE hFile = CreateFileA("aaa", GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);

		HANDLE hFileMap = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, buffer_size, "aaa.dat");
		if (hFileMap == NULL) {
			fprintf(stderr, "Can't open memory mapped file. Error code: %lu\n", GetLastError());
			return 1;
		}

		PBYTE pbMapView = (PBYTE)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, buffer_size);
		if (pbMapView == NULL) {
			fprintf(stderr, "Can't map view of file. Error code: %lu\n", GetLastError());
			return 1;
		}
		// делаю приостановку, чтобы можно было запустить подчиненный 
		// процесс, который хочет получить доступ к буферу
		printf("Press Enter to continue...\n");
		getchar();


		UnmapViewOfFile(pbMapView);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		printf("Map handles closed\n");
		return 0;
	
}