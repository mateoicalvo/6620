#ifndef _HASH_H_INCLUDED_
#define _HASH_H_INCLUDED_

#define STRING_HASH_INIT 1
#define STRING_HASH_MORE 2
#define STRING_HASH_DONE 3

#ifndef __ASSEMBLER__

#include <string.h>
#include <assert.h>

typedef struct {
	int8_t flag;
	int32_t hash;
	size_t size;
} string_hash;


extern void string_hash_init(string_hash *);
extern void string_hash_more(string_hash *, char *, size_t);
extern void string_hash_done(string_hash *);
extern int32_t string_hash_value(string_hash *);
#endif

#endif
