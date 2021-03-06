#pragma once

#include "../types.hpp"

void kmalloc_init();

void* kmalloc(size_t);

//kmalloc, but 4 bytes aligned
void* kmalloc_4(size_t);

void kfree(void*);

#ifdef DEBUG
void kmalloc_dump();
#endif

inline void* operator new(unsigned long size)
{
    return kmalloc(size);
}

inline void operator delete(void* ptr)
{
    return kfree(ptr);
}

inline void operator delete(void* ptr, unsigned long)
{
    return kfree(ptr);
}

inline void* operator new[](unsigned long size)
{
    return kmalloc(size);
}

inline void operator delete[](void* ptr)
{
    return kfree(ptr);
}

inline void operator delete[](void* ptr, unsigned long)
{
    return kfree(ptr);
}

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

inline void* operator new[](unsigned long, void* ptr)
{
    return ptr;
}

// inline void* operator new(unsigned long, unsigned long);
