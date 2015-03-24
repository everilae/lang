#ifndef DEBUG_H
#define DEBUG_H 1

#ifndef NDEBUG
# include <stdio.h>

# define DPRINTF(...) do { \
	fprintf(stderr, "DEBUG: %s: ", __FILE__); \
	fprintf(stderr, __VA_ARGS__); \
} while (0);

# define DPRINTFIF(pred, ...) do { \
	if (pred) { \
		DPRINTF(__VA_ARGS__); \
	} \
} while (0);

#else
# define DPRINTF(...) ((void) 0)
# define DPRINTFIF(...) ((void) 0)
#endif

#endif
