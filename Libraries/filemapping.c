#include <Windows.h>

int cleanupAndExit(int code, void* mutex, void* file, void* fileMap, BYTE* fileMapView)
{
	if (fileMapView)
	{
		UnmapViewOfFile(fileMapView);
	}

	if (fileMap)
	{
		CloseHandle(fileMap);
	}

	if (file)
	{
		CloseHandle(file);
	}

	if (mutex)
	{
		ReleaseMutex(mutex);
		CloseHandle(mutex);
	}

	return code;
}