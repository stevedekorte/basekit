/*
 *  CHash.h
 *  CuckooHashTable
 *
 *  Created by Steve Dekorte on 2009 04 28.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CHASH_DEFINED
#define CHASH_DEFINED 1

#include "Common.h"
#include <stddef.h>
#include <stdint.h>

/*
#define BASEKIT_API 
#define io_calloc calloc
#define io_free free
#define io_malloc malloc
#define IOINLINE
*/

#ifdef __cplusplus
extern "C" {
#endif

#define CHASH_MAXLOOP 10
	
typedef int (CHashEqualFunc)(void *, void *);
typedef intptr_t (CHashHashFunc)(void *);

typedef struct
{
	void *k;
	void *v;
} CHashRecord;
	
typedef struct
{
	unsigned char *records;
	size_t size;
	size_t keyCount;
	CHashHashFunc *hash1;
	CHashHashFunc *hash2;
	CHashEqualFunc *equals;
	intptr_t modMask;
} CHash;

BASEKIT_API CHash *CHash_new(void);
BASEKIT_API void CHash_copy_(CHash *self, const CHash *other);
BASEKIT_API CHash *CHash_clone(CHash *self);
BASEKIT_API void CHash_free(CHash *self);

BASEKIT_API void CHash_setHash1Func_(CHash *self, CHashHashFunc *f);
BASEKIT_API void CHash_setHash2Func_(CHash *self, CHashHashFunc *f);
BASEKIT_API void CHash_setEqualFunc_(CHash *self, CHashEqualFunc *f);

BASEKIT_API void CHash_setSize_(CHash *self, size_t size); // private
BASEKIT_API void CHash_insert_(CHash *self, CHashRecord *x); // private
BASEKIT_API void CHash_grow(CHash *self); // private
BASEKIT_API void CHash_shrinkIfNeeded(CHash *self); // private
BASEKIT_API void CHash_shrink(CHash *self); // private
BASEKIT_API void CHash_show(CHash *self);
BASEKIT_API void CHash_updateMask(CHash *self); // private

BASEKIT_API void CHash_at_put_(CHash *self, void *k, void *v);
BASEKIT_API void CHash_removeKey_(CHash *self, void *k);
BASEKIT_API size_t CHash_size(CHash *self); // actually the keyCount

BASEKIT_API size_t CHash_memorySize(CHash *self);
BASEKIT_API void CHash_compact(CHash *self);
//BASEKIT_API void *CHash_firstKeyForValue_(CHash *self, void *v);
//BASEKIT_API void CHash_removeValue_(CHash *self, void *value);

#include "CHash_inline.h"

#ifdef __cplusplus
}
#endif
#endif
