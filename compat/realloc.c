#include <config.h>
#undef realloc

#include <sys/types.h>

void *realloc();

/* Allocate an N-byte block of memory from the heap.
   If N is zero, allocate a 1-byte block.  */

void *
rpl_realloc (void *ptr, size_t n)
{
  if (!ptr)
    if (!n)
      return NULL;
    else
      return malloc (n);

  if (ptr && !n)
    return free(ptr);

  return realloc (ptr, n);
}
