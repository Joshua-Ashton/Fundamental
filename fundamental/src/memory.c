#include "memory.h"
#include "memory_private.h"

#include "compilerinfo.h"
#include "windows_stripped.h"

#ifdef FUNDAMENTAL_SYSTEM_WINDOWS
HANDLE fundamental_heap;
#endif

nomangle void fundamental_memory_init()
{
#ifdef FUNDAMENTAL_SYSTEM_WINDOWS
	fundamental_heap = HeapCreate(0, 0, 0);
#endif
}

nomangle usize get_memory_size(void* ptr)
{
	MemoryHeader* memory = (MemoryHeader*)(ptr);
	memory--;

	return memory->size;
}

nomangle void* alloc_heap(usize allocSize)
{
	MemoryHeader header;
	header.size = allocSize;

	allocSize += sizeof(MemoryHeader);

	MemoryHeader* data;

#ifdef FUNDAMENTAL_SYSTEM_WINDOWS
	 data = (MemoryHeader*) HeapAlloc(fundamental_heap, 0, allocSize);
#else
#endif

	*data = header;
	data++;

	return (void*)(data);
}

void free_heap(void* ptr)
{
	MemoryHeader* memory = (MemoryHeader*)(ptr);
	memory--;

#ifdef FUNDAMENTAL_SYSTEM_WINDOWS
	HeapFree(fundamental_heap, 0, (void*) memory);
#endif
}

nomangle void set_memory(void *dest, int c, size_t count)
{
	char *bytes = (char *)dest;
	while (count--)
		*bytes++ = (char)c;
}

nomangle void copy_memory(void *dest, const void *src, size_t count)
{
	char *dest8 = (char *)dest;
	const char *src8 = (const char *)src;
	while (count--)
		*dest8++ = *src8++;
}