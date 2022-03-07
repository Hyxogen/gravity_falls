#include "memory.h"

#include "assert.h"
#include <stdlib.h>

void *gf_safe_malloc(size_t size) {
	void *ptr;

	ptr = malloc(size);
	gf_assert(ptr);
	return (ptr);
}
