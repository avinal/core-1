/*
 *	MetaCall Library by Parra Studios
 *	Copyright (C) 2016 - 2017 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
 *
 *	A library for providing a foreign function interface calls.
 *
 */

 /* -- Headers -- */

#include <metacall/metacall_allocator.h>

#include <memory/memory.h>

/* -- Methods -- */

void * metacall_allocator_create(enum metacall_allocator_id allocator_id, void * ctx)
{
	switch (allocator_id)
	{
		case METACALL_ALLOCATOR_STD :
		{
			metacall_allocator_std std_ctx = (metacall_allocator_std)ctx;

			return memory_allocator_std(std_ctx->malloc, std_ctx->realloc, std_ctx->free);
		}

		case METACALL_ALLOCATOR_NGINX :
		{
			metacall_allocator_nginx nginx_ctx = (metacall_allocator_nginx)ctx;

			return memory_allocator_nginx(nginx_ctx->pool, nginx_ctx->palloc, nginx_ctx->pfree);
		}
	}

	return NULL;
}

void * metacall_allocator_alloc(void * allocator, size_t size)
{
	return memory_allocator_allocate((memory_allocator)allocator, size);
}

void * metacall_allocator_realloc(void * allocator, void * data, size_t size)
{
	return memory_allocator_reallocate((memory_allocator)allocator, data, size);
}

void metacall_allocator_free(void * allocator, void * data)
{
	memory_allocator_deallocate((memory_allocator)allocator, data);
}

void metacall_allocator_destroy(void * allocator)
{
	memory_allocator_destroy((memory_allocator)allocator);
}
