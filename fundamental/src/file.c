#include "file.h"
#include "windows_stripped.h"

nomangle u8* loadfile(cstr path, usize* fileSize)
{
#ifdef FUNDAMENTAL_SYSTEM_WINDOWS
	HANDLE file = CreateFileA((char*)path, GENERIC_READ, 0, 0, OPEN_EXISTING, 128, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
#ifdef FUNDAMENTAL_DEBUG
		DWORD err = GetLastError();
#endif
		return nullptr;
	}

	u32 amountRead;
	LARGE_INTEGER size;
	GetFileSizeEx(file, &size);
#ifdef FUNDAMENTAL_32_BIT
	*fileSize = size.LowPart;
	void* data = malloc(size.LowPart);
	ReadFile(file, data, size.LowPart, &amountRead, nullptr);
#else
	*fileSize = size.QuadPart;
	i64 amountLeftToRead = size.QuadPart;
	void* data = alloc_heap((usize)amountLeftToRead);

	while (amountLeftToRead > 0)
	{
		u32 amountToRead = amountLeftToRead > (u32)(-1) ? (u32)(-1) : (u32)amountLeftToRead;
		ReadFile(file, data, amountToRead, &amountRead, nullptr);
		amountLeftToRead -= amountToRead;
	}
#endif

	CloseHandle(file);

	return (u8*)data;
#endif
}

nomangle u8* wide_loadfile(wstr path, usize* fileSize)
{
#ifdef FUNDAMENTAL_SYSTEM_WINDOWS
	HANDLE file = CreateFileW(path, GENERIC_READ, 0, 0, OPEN_EXISTING, 128, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
#ifdef FUNDAMENTAL_DEBUG
		DWORD err = GetLastError();
#endif
		return nullptr;
	}

	u32 amountRead;

	LARGE_INTEGER size;
	GetFileSizeEx(file, &size);
#ifdef FUNDAMENTAL_32_BIT
	*fileSize = size.LowPart;
	void* data = malloc(size.LowPart);
	ReadFile(file, data, size.LowPart, &amountRead, nullptr);
#else
	*fileSize = size.QuadPart;
	i64 amountLeftToRead = size.QuadPart;
	void* data = alloc_heap((usize)amountLeftToRead);

	while (amountLeftToRead > 0)
	{
		u32 amountToRead = amountLeftToRead > (u32)(-1) ? (u32)(-1) : (u32)amountLeftToRead;
		ReadFile(file, data, amountToRead, &amountRead, nullptr);
		amountLeftToRead -= amountToRead;
	}
#endif

	CloseHandle(file);

	return (u8*)data;
#endif
}
