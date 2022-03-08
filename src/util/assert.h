#ifndef ASSERT_H
#define ASSERT_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define gf_abort(...) fprintf(stderr, __VA_ARGS__); abort();

#define gf_assert(cond) if (cond) { } else { gf_abort("Assertion failed: %s:%d\n", __FILE__, __LINE__) }

#endif
