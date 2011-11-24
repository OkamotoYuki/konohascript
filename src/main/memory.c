/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2006-2011, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Team konohaken@googlegroups.com
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * If you want to use the latter license, please contact us.
 *
 * (1) GNU General Public License 3.0 (with K_UNDER_GPL)
 * (2) Konoha Non-Disclosure License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* ************************************************************************ */

#include"commons.h"

#ifdef K_USING_POSIX_
#include <sys/mman.h>
#define knh_mlock(p, size)   mlock(p, size)
#define knh_unmlock(p)       unmlock(p)
#endif

#ifndef knh_mlock
#define knh_mlock(p, size)
#define knh_unmlock(p)
#endif

//#ifdef K_USING_DEBUG
//#define K_USING_CTRACE 1
//#endif

#ifdef K_USING_CTRACE
#define _GNU_SOURCE
#define __USE_GNU
#include <dlfcn.h>
#include <execinfo.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

#define KB_   (1024)
#define MB_   (KB_*1024)
#define GB_   (MB_*1024)

#define K_USING_MEMSTAT  1
//#define K_USING_MEMLOG   1

#ifdef K_USING_MEMLOG
static knh_uint64_t memlog_start = 0;

#define MEMLOG_INIT()  memlog_start = knh_getTimeMilliSecond()

#define MEMLOG(action, fmt, ...) { \
		knh_logprintf(action, 0, "T%llu, " fmt , (knh_getTimeMilliSecond()-memlog_start),  ## __VA_ARGS__);\
	} \

#else
#define MEMLOG_INIT()
#define MEMLOG(action, fmt, ...)

#endif

/* ------------------------------------------------------------------------ */

#define KNH_ATOMIC_ADD(a, b) __sync_add_and_fetch(&(a), b)
#define KNH_ATOMIC_SUB(a, b) __sync_sub_and_fetch(&(a), b)

#ifdef K_USING_MEMSTAT
#define STAT_mem(ctx, SIZE) { \
		knh_stat_t *stat = ctx->stat;\
		KNH_ATOMIC_ADD(stat->usedMemorySize, (SIZE));\
		if(stat->usedMemorySize > stat->maxMemoryUsage) stat->maxMemoryUsage = stat->usedMemorySize;\
	}\

#define STAT_dmem(ctx, SIZE)   KNH_ATOMIC_SUB((ctx->stat)->usedMemorySize, (SIZE))

#define STAT_Object(ctx, ct) { \
		((knh_ClassTBL_t*)ct)->count += 1; \
		((knh_ClassTBL_t*)ct)->total += 1; \
	}\

#define STAT_dObject(ctx, ct) \
	((knh_ClassTBL_t*)ct)->count -= 1; \


#else
#define STAT_mem(ctx, SIZE)
#define STAT_dmem(ctx, SIZE)
#define STAT_Object(ctx, ct)
#define STAT_dObject(ctx, ct)

#endif

void *knh_malloc(CTX ctx, size_t size)
{
	void *block = malloc(size);
	MEMLOG("malloc", "ptr=%p, size=%lu", block, size);
	if (unlikely(block == NULL)) {
		THROW_OutOfMemory(ctx, size);
	}
	STAT_mem(ctx, size);
	return block;
}

void knh_free(CTX ctx, void *block, size_t size)
{
	MEMLOG("free", "ptr=%p, size=%lu", block, size);
	free(block);
	STAT_dmem(ctx, size);
}

void *knh_valloc(CTX ctx, size_t size)
{
#if defined(HAVE_POSIX_MEMALIGN)
	void *block = NULL;
	int ret = posix_memalign(&block, K_PAGESIZE, size);
	MEMLOG("valloc", "ptr=%p, size=%lu", block, size);
	if(ret != 0) {
		THROW_OutOfMemory(ctx, size);
	}
	STAT_mem(ctx, size);
	return block;
#elif defined(HAVE_MEMALIGN)
	void *block = memalign(K_PAGESIZE, size);
	MEMLOG("valloc", "ptr=%p, size=%lu", block, size);
	if (unlikely(block == NULL)) {
		THROW_OutOfMemory(ctx, size);
	}
	return block;
#elif defined(K_USING_WINDOWS_)
	void *block = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	MEMLOG("valloc", "ptr=%p, size=%lu", block, size);
	if (unlikely(block == NULL)) {
		THROW_OutOfMemory(ctx, size);
	}
	return block;
#else
	void *block = malloc(size + K_PAGESIZE);
	MEMLOG("valloc", "ptr=%p, size=%lu", block, size);
	if (unlikely(block == NULL)) {
		THROW_OutOfMemory(ctx, size);
	}
	if((knh_uintptr_t)block % K_PAGESIZE != 0) {
		char *t2 = (char*)((((knh_uintptr_t)block / K_PAGESIZE) + 1) * K_PAGESIZE);
		void **p = (void**)(t2 + size);
		DBG_ASSERT((char*)p < ((char*)block) + size + K_PAGESIZE);
		p[0] = block;
		block = (void*)t2;
		DBG_ASSERT((knh_uintptr_t)block % K_PAGESIZE == 0);
	}
	else {
		void **p = (void**)((char*)block + size);
		p[0] = block;
	}
	STAT_mem(ctx, size + K_PAGESIZE);
	return block;
#endif
}

void knh_vfree(CTX ctx, void *block, size_t size)
{
	MEMLOG("vfree", "ptr=%p, size=%lu", block, size);
#if defined(HAVE_POSIX_MEMALIGN) || defined(HAVE_MEMALIGN)
	free(block);
	STAT_dmem(ctx, size);
#elif defined(K_USING_WINDOWS_)
	VirtualFree(block, 0, MEM_RELEASE);
	STAT_dmem(ctx, size);
#else
	void **p = (void**)((char*)block + size);
	block = p[0];
	free(block);
	STAT_dmem(ctx, size + K_PAGESIZE);
#endif
}

#if defined(K_USING_TRACEMALLOC)
void *TRACE_malloc(CTX ctx, size_t size K_TRACEARGV)
{
	DBG_ASSERT(size != 0);
	size_t *block = (size_t*)malloc(size + sizeof(size_t));
	if (unlikely(block == NULL)) {
		THROW_OutOfMemory(ctx, size);
	}
	STAT_mem(ctx, size);
	block[0] = size;
	return (void*)(block + 1);
}

void TRACE_free(CTX ctx, void *p, size_t size K_TRACEARGV)
{
	DBG_ASSERT(size != 0);
	size_t *block = ((size_t*)p) - 1;
	if(unlikely(size != block[0])) {
		fprintf(stderr, "%s:%d(%s) ptr = %p, block.size = %d, free.size=%d\n",
				_file, _line, _func, p, (int)block[0], (int)size);
		KNH_ABORT();
	}
	knh_bzero(block, size + sizeof(size_t));
	free(block);
	STAT_dmem(ctx, size);
}

void *TRACE_realloc(CTX ctx, void *p, size_t os, size_t ns, size_t wsize K_TRACEARGV)
{
	size_t oldsize = os * wsize, newsize = ns * wsize;
	size_t *block = (size_t*)malloc(newsize + sizeof(size_t));
	knh_bzero(block, newsize + sizeof(size_t));
	if (unlikely(block == NULL)) {
		THROW_OutOfMemory(ctx, newsize);
	}
	STAT_mem(ctx, newsize);
	block[0] = newsize;
	if(p != NULL) {
		DBG_ASSERT(os > 0);
		knh_memcpy(block+1, p, oldsize);
	}
	else {
		DBG_ASSERT(os == 0);
	}
	void *newp = (void*)(block+1);
	if(p != NULL) {
		block = ((size_t*)p) - 1;
		if(unlikely(oldsize != block[0])) {
			fprintf(stderr, "%s:%d(%s) ptr = %p, block.size = %d, free.size=%d\n",
					_file, _line, _func, p, (int)block[0], (int)oldsize);
			KNH_ABORT();
		}
		knh_bzero(block, oldsize + sizeof(size_t));
		free(block);
		STAT_dmem(ctx, oldsize);
	}
	return newp;
}

#endif/*TRACE_MALLOC*/

/* ------------------------------------------------------------------------ */

typedef struct xmeminfo_t {
	size_t size;
	struct xmeminfo_t *next;
} xmeminfo_t;

#define XMEM_PAGESIZE (1024 * 64)

static char* new_xmemarena(CTX ctx, size_t size)
{
	if(size < XMEM_PAGESIZE) size = XMEM_PAGESIZE;
	xmeminfo_t *ptr = (xmeminfo_t*)KNH_VALLOC(ctx, size);
	int mret;
#ifdef K_USING_POSIX_
	mret = mprotect(ptr, size, PROT_READ | PROT_WRITE | PROT_EXEC);
#elif K_USING_WINDOWS_
	/* TODO(@imasahiro) need debug 
	 * http://msdn.microsoft.com/ja-jp/library/cc430214.aspx
	 */
	DWORD old_protect;
	if (VirtualProtect(ptr, size, PAGE_EXECUTE_READWRITE, &old_protect) != 0) {
		mret = -1;
	}
#else
	mret = -1;
#endif
	if(mret == -1) {
		KNH_DIE("mprotect is not working.");
	}
	ptr->size = size;
	ptr->next = NULL;
	return (char*)ptr;
}

#define XMEM_BSIZE   sizeof(void*)

void *knh_xmalloc(CTX ctx, size_t size)
{
	size_t freesize = ctx->share->xmem_freelist - ctx->share->xmem_top;
	size_t asize = (size % XMEM_BSIZE == 0) ? size : ((size / XMEM_BSIZE) + 1) * XMEM_BSIZE;
	if(!(freesize > asize + sizeof(xmeminfo_t))) {
		char *p = new_xmemarena(ctx, asize);
		if(ctx->wshare->xmem_root == NULL) {
			ctx->wshare->xmem_root = p;
		}
		else {
			xmeminfo_t *xmeminfo = (xmeminfo_t*)ctx->wshare->xmem_top;
			xmeminfo->next = (xmeminfo_t*)p;
		}
		ctx->wshare->xmem_top = p;
		ctx->wshare->xmem_freelist = p + sizeof(xmeminfo_t);
	}
	void *p = (void*)ctx->wshare->xmem_freelist;
	ctx->wshare->xmem_freelist += asize;
	return p;
}

void xmem_freeall(CTX ctx)
{
	xmeminfo_t *xmeminfo = (xmeminfo_t*)ctx->wshare->xmem_root;
	while(xmeminfo != NULL) {
		void *p     = xmeminfo;
		size_t size = xmeminfo->size;
		xmeminfo    = xmeminfo->next;
		KNH_VFREE(ctx, p, size);
	}
}

/* ------------------------------------------------------------------------ */

#ifndef K_USING_BMGC
static void knh_fastmemset(void *p, size_t n, knh_intptr_t M)
{
	size_t i, size = n / sizeof(knh_intptr_t);
	knh_intptr_t *np = (knh_intptr_t*)p;
	for(i = 0; i < size; i+=8) {
		np[0] = M; np[1] = M; np[2] = M; np[3] = M;
		np[4] = M; np[5] = M; np[6] = M; np[7] = M;
		np += 8;
	}
}
#endif

/* ------------------------------------------------------------------------ */
/* [fastmalloc] */

struct knh_memslot_t {
	union {
		struct knh_memslot_t *ref;
		char body[K_FASTMALLOC_SIZE];
	};
};
struct knh_MemoryArenaTBL_t {
	knh_memslot_t *head;
	knh_memslot_t *bottom;
};

static knh_memslot_t *new_FastMemoryList(CTX ctx)
{
	KNH_MEMLOCK(ctx);
	knh_share_t *ctxshare = (knh_share_t*)ctx->share;
	size_t pageindex = ctxshare->sizeMemoryArenaTBL;
	if(unlikely(!(pageindex < ctxshare->capacityMemoryArenaTBL))) {
		size_t newsize = ctxshare->capacityMemoryArenaTBL * 2;
		ctxshare->MemoryArenaTBL = (knh_MemoryArenaTBL_t*)KNH_REALLOC(ctx, "MemoryArenaTBL", ctxshare->MemoryArenaTBL, ctxshare->capacityMemoryArenaTBL, newsize, sizeof(knh_MemoryArenaTBL_t));
		ctxshare->capacityMemoryArenaTBL = newsize;
	}
	ctxshare->sizeMemoryArenaTBL += 1;
	KNH_MEMUNLOCK(ctx);
	{
		knh_MemoryArenaTBL_t *at = &ctxshare->MemoryArenaTBL[pageindex];
		knh_memslot_t *mslot = (knh_memslot_t*)KNH_MALLOC(ctx, K_PAGESIZE * 8);
		knh_bzero(mslot, K_PAGESIZE * 8);
		at->head =   mslot;
		at->bottom = (knh_memslot_t*)K_SHIFTPTR(mslot, (K_PAGESIZE * 8));
		DBG_ASSERT(ctx->freeMemoryList == NULL);
		((knh_context_t*)ctx)->freeMemoryList = mslot;
		for(;mslot < at->bottom; mslot++) {
			mslot->ref = (mslot + 1);
		}
		(mslot-1)->ref = NULL;
		GC_LOG("Allocated MemoryArena id=%d region=(%p-%p)", pageindex, at->head, at->bottom);
	}
	return ctx->freeMemoryList;
}

#ifdef K_USING_FASTMALLOC2
struct knh_memslotX2_t {
	union {
		struct knh_memslotX2_t *ref;
		char body[K_FASTMALLOC_SIZE*2];
	};
};
struct knh_MemoryX2ArenaTBL_t {
	knh_memslotX2_t *head;
	knh_memslotX2_t *bottom;
};
static knh_memslotX2_t *freeMemoryListX2(CTX ctx)
{
	OLD_LOCK(ctx, LOCK_MEMORY, NULL);
	knh_share_t *ctxshare = (knh_share_t*)ctx->share;
	size_t pageindex = ctxshare->MemoryX2ArenaTBLSize;
	if(unlikely(!(pageindex < ctxshare->capacityMemoryX2ArenaTBL))) {
		size_t newsize = ctxshare->capacityMemoryX2ArenaTBL * 2;
		ctxshare->MemoryX2ArenaTBL = (knh_MemoryX2ArenaTBL_t*)KNH_REALLOC(ctx, ctxshare->MemoryX2ArenaTBL, ctxshare->capacityMemoryX2ArenaTBL, newsize, sizeof(knh_MemoryX2ArenaTBL_t));
		ctxshare->capacityMemoryX2ArenaTBL = newsize;
		KNH_SYSLOG(ctx, LOG_INFO, "EXTENDED_MemoryX2ArenaTBL", "*newsize=%d", newsize);
	}
	ctxshare->MemoryX2ArenaTBLSize += 1;
	OLD_UNLOCK(ctx, LOCK_MEMORY, NULL);
	{
		knh_MemoryX2ArenaTBL_t *at = &ctxshare->MemoryX2ArenaTBL[pageindex];
		knh_memslotX2_t *mslot = (knh_memslotX2_t*)KNH_MALLOC(ctx, K_PAGESIZE * 2);
		knh_bzero(mslot, K_PAGESIZE * 2);
		at->head =   mslot;
		at->bottom = (knh_memslotX2_t*)K_PTRSHIFT(mslot, (K_PAGESIZE * 2));
		DBG_ASSERT(ctx->freeMemoryListX2 == NULL);
		((knh_context_t*)ctx)->freeMemoryListX2 = mslot;
		while(mslot < at->bottom) {
			mslot->ref = (mslot + 1);
			mslot++;
		}
		(mslot-1)->ref = NULL;
		KNH_SYSLOG(ctx, LOG_INFO, "NEW_MemoryX2Arena", "*id=%d region=(%p-%p)", pageindex, at->head, at->bottom);
	}
	return ctx->freeMemoryListX2;
}
#endif

#ifdef K_USING_FASTMALLOC256
struct knh_memslot256_t {
	union {
		struct knh_memslot256_t *ref;
		char body[256];
	};
};
struct knh_Memory256ArenaTBL_t {
	knh_memslot256_t *head;
	knh_memslot256_t *bottom;
};

static knh_memslot256_t *freeMemoryList256(CTX ctx)
{
	OLD_LOCK(ctx, LOCK_MEMORY, NULL);
	knh_share_t *ctxshare = (knh_share_t*)ctx->share;
	size_t pageindex = ctxshare->Memory256ArenaTBLSize;
	if(unlikely(!(pageindex < ctxshare->capacityMemory256ArenaTBL))) {
		size_t newsize = ctxshare->capacityMemory256ArenaTBL * 2;
		ctxshare->Memory256ArenaTBL = (knh_Memory256ArenaTBL_t*)KNH_REALLOC(ctx, ctxshare->Memory256ArenaTBL, ctxshare->capacityMemory256ArenaTBL, newsize, sizeof(knh_Memory256ArenaTBL_t));
		ctxshare->capacityMemory256ArenaTBL = newsize;
		KNH_SYSLOG(ctx, LOG_INFO, "EXTENDED_Memory256ArenaTBL", "*newsize=%d", newsize);
	}
	ctxshare->Memory256ArenaTBLSize += 1;
	OLD_UNLOCK(ctx, LOCK_MEMORY, NULL);
	{
		knh_Memory256ArenaTBL_t *at = &ctxshare->Memory256ArenaTBL[pageindex];
		knh_memslot256_t *mslot = (knh_memslot256_t*)KNH_MALLOC(ctx, K_PAGESIZE * 2);
		knh_bzero(mslot, K_PAGESIZE * 2);
		at->head =   mslot;
		at->bottom = (knh_memslot256_t*)K_PTRSHIFT(mslot, (K_PAGESIZE * 2));
		DBG_ASSERT(ctx->freeMemoryList256 == NULL);
		((knh_context_t*)ctx)->freeMemoryList256 = mslot;
		while(mslot < at->bottom) {
			mslot->ref = (mslot + 1);
			mslot++;
		}
		(mslot-1)->ref = NULL;
		KNH_SYSLOG(ctx, LOG_INFO, "NEW_Memory256Arena", "*id=%d region=(%p-%p)", pageindex, at->head, at->bottom);
	}
	return ctx->freeMemoryList256;
}
#endif

void *knh_fastmalloc(CTX ctx, size_t size)
{
	DBG_ASSERT(size != 0);
	if(size <= K_FASTMALLOC_SIZE) {
		knh_memslot_t *m;
		if(ctx->freeMemoryList == NULL) {
			((knh_context_t*)ctx)->freeMemoryList = new_FastMemoryList(ctx);
		}
		m = ctx->freeMemoryList;
		((knh_context_t*)ctx)->freeMemoryList = m->ref;
		m->ref = NULL;
		MEMLOG("fastmalloc", "ptr=%p, size=%lu", m, size);
		return (void*)m;
	}
	else {
		void *block = malloc(size);
		MEMLOG("fastmalloc", "ptr=%p, size=%lu", block, size);
		if (unlikely(block == NULL)) {
			THROW_OutOfMemory(ctx, size);
		}
		STAT_mem(ctx, size);
		return block;
	}
}

void knh_fastfree(CTX ctx, void *block, size_t size)
{
	MEMLOG("fastfree", "ptr=%p, size=%lu", block, size);
	if(size <= K_FASTMALLOC_SIZE) {
		knh_memslot_t *m = (knh_memslot_t*)block;
		KNH_FREEZERO(m, K_FASTMALLOC_SIZE);
		m->ref = ctx->freeMemoryList;
		((knh_context_t*)ctx)->freeMemoryList = m;
	}
	else {
		KNH_FREEZERO(block, size);
		free(block);
		STAT_dmem(ctx, size);
	}
}

void* knh_fastrealloc(CTX ctx, void *block, size_t os, size_t ns, size_t wsize)
{
	size_t oldsize = os * wsize, newsize = ns * wsize;
	if(oldsize <= K_FASTMALLOC_SIZE) {
		void *newblock = knh_fastmalloc(ctx, newsize);
		if(oldsize > 0) {
			knh_memcpy(newblock, block, oldsize);
			knh_bzero((char*)newblock + oldsize, newsize - oldsize);
			knh_fastfree(ctx, block, oldsize);
		}
		else {
			DBG_ASSERT(block == NULL);
			knh_bzero(newblock, newsize);
		}
		MEMLOG("fastrealloc", "ptr=%p, size=%lu, newptr=%p, newsize=%lu", block, oldsize, newblock, newsize);
		return newblock;
	}
	else {
		void *newblock = realloc(block, newsize);
		DBG_ASSERT(newsize > oldsize);
		if (unlikely(newblock == NULL)) {
			THROW_OutOfMemory(ctx, newsize);
		}
		STAT_mem(ctx, (newsize - oldsize));
		knh_bzero((char*)newblock + oldsize, (newsize - oldsize));
		MEMLOG("fastrealloc", "ptr=%p, size=%lu, newptr=%p, newsize=%lu", block, oldsize, newblock, newsize);
		return newblock;
	}
}

/* ------------------------------------------------------------------------ */
/* [Object] */

#define K_OPAGEOFFSET(o, opage)\
	(((knh_uintptr_t)o) / sizeof(knh_Object_t)) % (K_PAGESIZE / sizeof(knh_Object_t))

#define UINTPTR8 (sizeof(knh_uintptr_t) * 8)
#define INDEX2OFFSET(index_) ((index_) / UINTPTR8)
#if defined(__i386__) || defined(__power__)
#define INDEX2MASK(n) (((knh_uintptr_t)1) << (n % UINTPTR8))
#else
#define INDEX2MASK(n) (((knh_uintptr_t)1) << (n /*% UINTPTR8*/))
#endif

#define bit_test(b, offset)   (b[INDEX2OFFSET(offset)] & INDEX2MASK(offset))
#define bit_set(b, offset)    (b[INDEX2OFFSET(offset)] |= INDEX2MASK(offset))
#define bit_unset(b, offset)  (b[INDEX2OFFSET(offset)] &= ~(INDEX2MASK(offset)))

#define prefetch_bitmap(o)   prefetch(K_OPAGE(o)->h.bitmap)
#define prefetch_tenure(o)   prefetch(K_OPAGE(o)->h.tenure)

#define O_set_tenure(o) {\
		knh_ObjectPage_t *opage = K_OPAGE(o);\
		knh_uintptr_t *tenure = opage->h.tenure;\
		size_t offset = K_OPAGEOFFSET(o, opage);\
		bit_set(tenure, offset);\
	}\

#define O_unset_tenure(o) {\
		knh_ObjectPage_t *opage = K_OPAGE(o);\
		knh_uintptr_t *tenure = opage->h.tenure;\
		size_t offset = K_OPAGEOFFSET(o, opage);\
		bit_unset(tenure, offset);\
	}\

typedef struct {
	knh_hObject_t h;
	knh_uintptr_t *bitmap;
	knh_uintptr_t *tenure;
	knh_context_t *ctx;
	void *unused;
} knh_hOArena_t;

typedef struct knh_ObjectPage_t knh_ObjectPage_t;
struct knh_ObjectPage_t {
	knh_hOArena_t h;
	knh_Object_t  slots[K_PAGEOBJECTSIZE];
};

struct knh_ObjectArenaTBL_t {
	knh_ObjectPage_t *head;
	knh_ObjectPage_t *bottom;
	size_t            arenasize;
	knh_uintptr_t    *bitmap;
	knh_uintptr_t     bitmapsize;
	knh_uintptr_t    *tenure;
};

#ifndef K_USING_BMGC
void knh_share_initArena(CTX ctx, knh_share_t *share)
{
	share->ObjectArenaTBL = (knh_ObjectArenaTBL_t*)KNH_MALLOC(ctx, K_ARENATBL_INITSIZE * sizeof(knh_ObjectArenaTBL_t));
	knh_bzero(share->ObjectArenaTBL, K_ARENATBL_INITSIZE * sizeof(knh_ObjectArenaTBL_t));
	share->sizeObjectArenaTBL = 0;
	share->capacityObjectArenaTBL = K_ARENATBL_INITSIZE;

	share->MemoryArenaTBL = (knh_MemoryArenaTBL_t*)KNH_MALLOC(ctx, K_ARENATBL_INITSIZE * sizeof(knh_MemoryArenaTBL_t));
	knh_bzero(share->MemoryArenaTBL, K_ARENATBL_INITSIZE * sizeof(knh_MemoryArenaTBL_t));
	share->sizeMemoryArenaTBL = 0;
	share->capacityMemoryArenaTBL = K_ARENATBL_INITSIZE;
}

void knh_share_freeArena(CTX ctx, knh_share_t *share)
{
	size_t i;
	DBG_ASSERT(share->ObjectArenaTBL != NULL);
	for(i = 0; i < share->sizeObjectArenaTBL; i++) {
		knh_ObjectArenaTBL_t *oat = share->ObjectArenaTBL + i;
		DBG_ASSERT(K_MEMSIZE(oat->bottom, oat->head) == oat->arenasize);
		KNH_FREE(ctx, oat->bitmap, oat->bitmapsize * K_NBITMAP);
		KNH_VFREE(ctx, oat->head, oat->arenasize);
	}
	KNH_FREE(ctx, share->ObjectArenaTBL, share->capacityObjectArenaTBL * sizeof(knh_ObjectArenaTBL_t));
	share->ObjectArenaTBL = NULL;
	for(i = 0; i < share->sizeMemoryArenaTBL; i++) {
		knh_MemoryArenaTBL_t *at = share->MemoryArenaTBL + i;
		KNH_FREE(ctx, at->head, K_MEMSIZE(at->bottom, at->head));
	}
	KNH_FREE(ctx, share->MemoryArenaTBL, share->capacityMemoryArenaTBL * sizeof(knh_MemoryArenaTBL_t));
	share->MemoryArenaTBL = NULL;
}

static void ObjectPage_init(knh_ObjectPage_t *opage)
{
	size_t i;
	knh_Object_t *o = opage->slots;
	for(i = 0; i < K_PAGEOBJECTSIZE - 1; i++) {
		DBG_ASSERT(K_OPAGE(opage->slots + i) == opage);
		o[i].h.cTBL = NULL;
		o[i].ref = &(o[i+1]);
	}
	opage->slots[K_PAGEOBJECTSIZE-1].h.cTBL = NULL;
	opage->slots[K_PAGEOBJECTSIZE-1].ref = opage[1].slots;
}

#ifdef K_USING_DEBUG
static void ObjectArenaTBL_checkSize(knh_ObjectArenaTBL_t *oat, size_t arenasize, size_t object_count)
{
	size_t cnt2=0;
	knh_Object_t *p = oat->head->slots;
	while(p->ref != NULL) {
		knh_ObjectPage_t *opage = K_OPAGE(p);
		DBG_ASSERT(oat->bitmap <= opage->h.bitmap && opage->h.bitmap < oat->bitmap + ((arenasize/sizeof(knh_Object_t))/sizeof(knh_uintptr_t)));
		cnt2++;
		p = (knh_Object_t*) p->ref;
	}
	DBG_ASSERT(cnt2 + 1 == object_count * K_PAGEOBJECTSIZE);
}
#endif

static void ObjectArenaTBL_init(CTX ctx, knh_ObjectArenaTBL_t *oat, size_t arenasize)
{
	size_t object_count, bitmapsize = (arenasize/sizeof(knh_Object_t));
	knh_ObjectPage_t *opage = (knh_ObjectPage_t*)KNH_VALLOC(ctx, arenasize);
	knh_uintptr_t *bitmap = (knh_uintptr_t*)KNH_MALLOC(ctx, bitmapsize * K_NBITMAP);
	KNH_ASSERT((knh_uintptr_t)opage % K_PAGESIZE == 0);
	oat->head =   opage;
	oat->bottom = (knh_ObjectPage_t*)K_SHIFTPTR(opage, arenasize);
	oat->bitmap = bitmap;
	oat->arenasize = arenasize;
	oat->bitmapsize = bitmapsize;
	oat->tenure = (knh_uintptr_t*)K_SHIFTPTR(bitmap, bitmapsize);
	knh_fastmemset(oat->tenure, bitmapsize, ((knh_intptr_t)-1));
	object_count = (oat->bottom - oat->head);
	//knh_mlock(oat->bitmap, bitmapsize * K_NBITMAP);
	for(; opage < oat->bottom; opage++) {
		opage->h.bitmap = bitmap;
		opage->h.tenure = (knh_uintptr_t*)K_SHIFTPTR(bitmap, bitmapsize);
		bitmap += (K_PAGESIZE/sizeof(knh_Object_t))/sizeof(knh_uintptr_t);
		opage->h.ctx = NULL;
		ObjectPage_init(opage);
	}
	(opage-1)->slots[K_PAGEOBJECTSIZE - 1].ref = NULL;

	DBG_ASSERT((bitmap - oat->bitmap) * sizeof(knh_uintptr_t) == arenasize/sizeof(knh_Object_t));
	ctx->stat->gcObjectCount += (object_count * K_PAGEOBJECTSIZE);
	DBG_(ObjectArenaTBL_checkSize(oat, arenasize, object_count););
}

static knh_Object_t *new_ObjectArena(CTX ctx, size_t arenasize)
{
	OLD_LOCK(ctx, LOCK_MEMORY, NULL);
	knh_ObjectArenaTBL_t *oat;
	knh_share_t *ctxshare = (knh_share_t*)ctx->share;
	size_t pageindex = ctxshare->sizeObjectArenaTBL;
	if(unlikely(!(pageindex < ctxshare->capacityObjectArenaTBL))) {
		size_t newsize = ctxshare->capacityObjectArenaTBL * 2;
		ctxshare->ObjectArenaTBL = (knh_ObjectArenaTBL_t*)KNH_REALLOC(ctx, "ObjectArenaTBL", ctxshare->ObjectArenaTBL, ctxshare->capacityObjectArenaTBL, newsize, sizeof(knh_ObjectArenaTBL_t));
		ctxshare->capacityObjectArenaTBL = newsize;
	}
	ctxshare->sizeObjectArenaTBL += 1;
	OLD_UNLOCK(ctx, LOCK_MEMORY, NULL);
	DBG_ASSERT(sizeof(knh_ObjectPage_t) == K_PAGESIZE);
	oat = &ctxshare->ObjectArenaTBL[pageindex];
	ObjectArenaTBL_init(ctx, oat, arenasize);
	GC_LOG("Allocated object arena id=%d region=(%p-%p), %d objects", pageindex, oat->head, oat->bottom, ((oat->bottom - oat->head) * K_PAGEOBJECTSIZE));
	{
		knh_Object_t *p = oat->head->slots;
		p->ref4_tail = &(((knh_Object_t*)(oat->bottom))[-1]);
		return p;
	}
}

knh_bool_t knh_isObject(CTX ctx, knh_Object_t *o)
{
	void *ptr = (void*) o;
	knh_uintptr_t n = (knh_uintptr_t)ptr;
	if(ptr != NULL && n % sizeof(knh_Object_t) == 0) {
		size_t i, size = ctx->share->sizeObjectArenaTBL;
		knh_ObjectArenaTBL_t *oat = ctx->share->ObjectArenaTBL;
		for(i = 0; i < size; i++) {
			if((void*)oat[i].head < ptr && ptr < (void*)oat[i].bottom) return 1;
		}
	}
	return 0;
}
#endif

/* ------------------------------------------------------------------------ */
/* [cstack trace] */

#ifdef K_USING_CTRACE
#define K_TRACE_LENGTH 128
static const char* addr_to_name(void* p)
{
	Dl_info info;
	if (dladdr(p, &info) != 0) {
		return info.dli_sname;
	}
	return NULL;
}

static void dumpObject(CTX ctx, knh_uintptr_t* p)
{
	knh_Object_t* o = (knh_Object_t*)(*p);
	if (knh_isObject(ctx, (void*) o) && O_cTBL(o) != NULL) {
		if (O_cid(o) < K_CLASS_INITSIZE) {
			knh_putc(ctx, KNH_STDERR, '\t');
			knh_write_Object(ctx, KNH_STDERR, o, FMT_s);
		}
		else {
			knh_printf(ctx, KNH_STDERR, "\t%p %p %s\n", p, o, S_totext(O_cTBL(o)->sname));
		}
	}
}

static void knh_dump_cstack(CTX ctx)
{
	void *trace[K_TRACE_LENGTH];
	int i = 1;
	backtrace(trace, K_TRACE_LENGTH);
	void* bottom = ctx->cstack_bottom;
	void* stack = __builtin_frame_address(0);
	knh_printf(ctx, KNH_STDERR, "========== backtrace start ==========\n");
	for (; stack < bottom; stack++) {
		knh_uintptr_t** ptr = (knh_uintptr_t**) stack;
		dumpObject(ctx, (knh_uintptr_t*) ptr);
		if (trace[i] == *ptr) {
			knh_printf(ctx, KNH_STDERR, "TRACE: %p %s\n", trace[i], addr_to_name(trace[i]));
			i++;
		}
	}
	knh_printf(ctx, KNH_STDERR, "========== backtrace end ==========\n");
	knh_flush(ctx, KNH_STDERR);
}
#endif /* K_USING_CTRACE */

#ifdef __GNUC__
#define C_STACK_TOP(ctx) ((void**) __builtin_frame_address(0))
#else
#define C_STACK_TOP(ctx) ((void**) &ctx)
#endif
static void cstack_mark(CTX ctx FTRARG)
{
	void** stack  = C_STACK_TOP(ctx);
	void** bottom = (void**) ctx->cstack_bottom;
	for (; stack < bottom; ++stack) {
		knh_Object_t *o = (knh_Object_t*)(*stack);
		if (knh_isObject(ctx, o)) {
			KNH_ADDREF(ctx, o);
		}
	}
	KNH_SIZEREF(ctx);
}

/* ------------------------------------------------------------------------ */


#ifdef K_USING_DEBUG
#define DBG_CHECK_ONARENA(ctx, p) DBG_checkOnArena(ctx, p K_TRACEPOINT)
//#define DBG_CHECK_UNOBJECT(ctx) DBG_ASSERT(ctx->freeObjectListSize == 0)
//#define DBG_UNOBJinc(ctx, N) ((knh_context_t*)ctx)->freeObjectListSize += N
//#define DBG_UNOBJdec(ctx, N) ((knh_context_t*)ctx)->freeObjectListSize -= N

#ifndef K_USING_BMGC
static void DBG_checkOnArena(CTX ctx, void *used K_TRACEARGV)
{
	size_t i, size = ctx->share->sizeObjectArenaTBL;
	knh_ObjectArenaTBL_t *t = ctx->share->ObjectArenaTBL;
	for(i = 0; i < size; i++) {
		if((void*)t->head <= used && used < (void*)t->bottom) return;
		t++;
	}
	TRACE_P("not paged object %p", used);
}
#endif

#else/*K_USING_DEBUG*/
#define DBG_CHECK_ONARENA(ctx, p)
//#define DBG_CHECK_UNOBJECT(ctx)
//#define DBG_UNOBJinc(ctx, N)
//#define DBG_UNOBJdec(ctx, N)
#endif

#ifndef K_USING_BMGC
#define K_MEMBLOCKPAGE			64
#define K_MEMBLOCKSIZE			(K_MEMBLOCKPAGE * K_PAGESIZE)
#define GET_PAGECTX(page)		((knh_context_t *)((page)->h.ctx))
#define SET_PAGECTX(page, ctx1)	(page)->h.ctx = (void *)(ctx1)

static knh_Object_t* get_memBlock(CTX ctx, size_t mbsize)
{
	KNH_MEMLOCK(ctx);
	knh_ObjectArenaTBL_t *oat = ctx->share->ObjectArenaTBL;
	knh_ObjectPage_t *page;
	size_t i, arenasize = ctx->share->sizeObjectArenaTBL;
	for(i = 0; i < arenasize; i++) {
		knh_ObjectPage_t *bottom = oat[i].bottom;
		for(page = oat[i].head; page < bottom; page += K_MEMBLOCKPAGE) {
			if(GET_PAGECTX(page) == NULL) {
				goto SETFLAG;
			}
		}
	}
	page = K_OPAGE(new_ObjectArena(ctx, K_ARENASIZE));
	SETFLAG:
	for(i=0; i<K_MEMBLOCKPAGE; i++) SET_PAGECTX(page + i, ctx);
	KNH_MEMUNLOCK(ctx);
	knh_Object_t *p = page->slots;
	p->ref4_tail = &(((knh_Object_t*)((page + K_MEMBLOCKPAGE)))[-1]);
	p->ref4_tail->ref = NULL;
	WCTX(ctx)->freeObjectListSize += K_PAGEOBJECTSIZE * K_MEMBLOCKPAGE;
	return p;
}
#endif

#define CHECK_UNUSED_OBJECT(ctx) { \
		if(ctx->freeObjectList == NULL) { \
			knh_Object_t *p = get_memBlock(ctx, K_MEMBLOCKSIZE);\
			((knh_context_t*)ctx)->freeObjectList = p; \
			((knh_context_t*)ctx)->freeObjectTail = p->ref4_tail;\
		} \
		DBG_CHECK_ONARENA(ctx, ctx->freeObjectList);\
	} \

#define FREELIST_POP(o) {\
		o = ctx->freeObjectList;\
		((knh_context_t*)ctx)->freeObjectList = (Object*)(o)->ref;\
		prefetch(o->ref);\
		/*TODO(imasahiro) measure GC performance */\
		o->ref = NULL;\
		/*DBG_UNOBJdec(ctx ,1);*/\
	}\

#define FREELIST_PUSH(o) {\
		o->ref = ctx->freeObjectList;\
		((knh_context_t*)ctx)->freeObjectList = o;\
		/*DBG_UNOBJinc((ctx), 1);*/\
	}\

#define K_OZERO(o) do {\
	o->h.cTBL = NULL;\
} while(0)


#define K_OZERO2(o) {\
		knh_intptr_t *p = (knh_intptr_t*)o;\
		p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = p[6] = p[7] = K_INT0;\
	}\

#define OBJECT_REUSE(used) { \
		DBG_CHECK_ONARENA(ctx, used);\
		K_OZERO(used);\
		FREELIST_PUSH(used);\
	}\

/* ------------------------------------------------------------------------ */
/* [hObject] */

#ifndef K_USING_BMGC
void knh_initFirstObjectArena(CTX ctx)
{
	DBG_ASSERT(ctx->freeObjectList == NULL);
	knh_Object_t *p = get_memBlock(ctx, K_ARENASIZE);
	((knh_context_t*)ctx)->freeObjectList = p;
	((knh_context_t*)ctx)->freeObjectTail = p->ref4_tail;
	ctx->stat->gcObjectCount -= K_GC_MARGIN; // important
	ctx->stat->latestGcTime = knh_getTimeMilliSecond();
}

knh_Object_t *new_hObject_(CTX ctx, const knh_ClassTBL_t *ct)
{
	knh_Object_t *o = NULL;
	CHECK_UNUSED_OBJECT(ctx);
	FREELIST_POP(o);
	prefetch_tenure(o);
	o->h.magicflag = ct->magicflag;
	knh_Object_RCset(o, K_RCGC_INIT);
	o->h.cTBL = ct;
	O_unset_tenure(o); // collectable
	WCTX(ctx)->freeObjectListSize -= 1;
	if(ctx->freeObjectListSize == 0) {
		SAFEPOINT_SETGC(ctx);
	}
	STAT_Object(ctx, ct);
	MEMLOG("new", "ptr=%p, cid=%d", o, ct->cid);
	return o;
}

knh_Object_t *new_Object_init2(CTX ctx, const knh_ClassTBL_t *ct)
{
	knh_Object_t *o = NULL;
	CHECK_UNUSED_OBJECT(ctx);
	FREELIST_POP(o);
	o->h.magicflag = ct->magicflag;
	knh_Object_RCset(o, K_RCGC_INIT);
	o->h.cTBL = ct;
	ct->cdef->init(ctx, RAWPTR(o));
	O_unset_tenure(o); // collectable
	WCTX(ctx)->freeObjectListSize -= 1;
	if(ctx->freeObjectListSize == 0) {
		SAFEPOINT_SETGC(ctx);
	}
	STAT_Object(ctx, ct);
	MEMLOG("new", "ptr=%p, cid=%d", o, ct->cid);
	return o;
}

void TR_NEW(CTX ctx, knh_sfp_t *sfp, knh_sfpidx_t c, const knh_ClassTBL_t *ct)
{
	knh_Object_t *o = NULL;
	CHECK_UNUSED_OBJECT(ctx);
	FREELIST_POP(o);
	o->h.magicflag = ct->magicflag;
	knh_Object_RCset(o, K_RCGC_INIT);
	o->h.cTBL = ct;
	ct->cdef->init(ctx, RAWPTR(o));
	O_unset_tenure(o); // collectable
	WCTX(ctx)->freeObjectListSize -= 1;
	if(ctx->freeObjectListSize == 0) {
		SAFEPOINT_SETGC(ctx);
	}
	STAT_Object(ctx, ct);
	MEMLOG("new", "ptr=%p, cid=%d", o, ct->cid);
	KNH_SETv(ctx, sfp[c].o, o);
}

/* ------------------------------------------------------------------------ */

static void knh_Object_finalfree(CTX ctx, knh_Object_t *o)
{
	const knh_ClassTBL_t *ct = O_cTBL(o);
	RCGC_(DBG_ASSERT(Object_isRC0(o)));
	MEMLOG("~Object", "ptr=%p, cid=%d", o, ct->cid);
	if(Object_isXData(o)) {
		knh_PtrMap_rm(ctx, ctx->share->xdataPtrMap, o);
		Object_setXData(o, 0);
	}
	ct->cdef->free(ctx, RAWPTR(o));
	OBJECT_REUSE(o);
	WCTX(ctx)->freeObjectListSize += 1;
	STAT_dObject(ctx, ct);
	O_set_tenure(o); // uncollectable
}

#endif /* K_USING_BMGC */

typedef struct knh_ostack_t {
	knh_Object_t **stack;
	size_t cur;
	size_t tail;
	size_t capacity;
	size_t capacity_log2;
} knh_ostack_t;

static knh_ostack_t *ostack_init(CTX ctx, knh_ostack_t *ostack)
{
	ostack->capacity = ctx->queue_capacity;
	ostack->stack = ctx->queue;
	ostack->capacity_log2  = ctx->queue_log2;
	if(ostack->capacity == 0) {
		ostack->capacity_log2 = 12;
		ostack->capacity = (1 << ostack->capacity_log2) - 1;
		DBG_ASSERT(K_PAGESIZE == 1 << 12);
		ostack->stack = (knh_Object_t**)KNH_MALLOC(ctx, sizeof(knh_Object_t*) * (ostack->capacity + 1));
	}
	ostack->cur  = 0;
	ostack->tail = 0;
	return ostack;
}

static void ostack_push(CTX ctx, knh_ostack_t *ostack, knh_Object_t *ref)
{
	size_t ntail = (ostack->tail + 1 ) & ostack->capacity;
	if(unlikely(ntail == ostack->cur)) {
		size_t capacity = 1 << ostack->capacity_log2;
		ostack->stack = (knh_Object_t**)KNH_REALLOC(ctx, "ostack", ostack->stack, capacity, capacity * 2, sizeof(knh_Object_t*));
		ostack->capacity_log2 += 1;
		ostack->capacity = (1 << ostack->capacity_log2) - 1;
		ntail = (ostack->tail + 1) & ostack->capacity;
	}
	ostack->stack[ostack->tail] = ref;
	ostack->tail = ntail;
}

static knh_Object_t *ostack_next(knh_ostack_t *ostack)
{
	knh_Object_t *ref = NULL;
	if(likely(ostack->cur != ostack->tail)) {
		ostack->tail -=1;
		ref = ostack->stack[ostack->tail];
		prefetch(ref);
	}
	return ref;
}

static void ostack_free(CTX ctx, knh_ostack_t *ostack)
{
	knh_context_t *wctx = (knh_context_t*)ctx;
	wctx->queue_capacity = ostack->capacity;
	wctx->queue = ostack->stack;
	wctx->queue_log2 = ostack->capacity_log2;
}

knh_Object_t** knh_ensurerefs(CTX ctx, knh_Object_t** tail, size_t size)
{
	size_t ref_size = tail - ctx->ref_buf;
	if(unlikely(ctx->ref_capacity < size + ref_size)) {
		knh_context_t *wctx = (knh_context_t*)ctx;
		size_t newsize = (ctx->ref_capacity == 0) ? 8 : ctx->ref_capacity * 2;
		while(newsize < size + ref_size) {
			newsize *= 2;
		}
		wctx->ref_buf = (knh_Object_t**)KNH_REALLOC(ctx, "ctx->ref_buf", ctx->ref_buf, ctx->ref_capacity, newsize, sizeof(knh_Object_t*));
		wctx->ref_capacity = newsize;
		wctx->refs = ctx->ref_buf;
		tail = ctx->ref_buf + ref_size;
	}
	return tail;
}

#ifdef K_USING_RCGC
static void deref_ostack(CTX ctx, knh_Object_t *ref, knh_ostack_t *ostack)
{
	if (knh_Object_RCdec(ref) == 1) {
		ostack_push(ctx, ostack, ref);
	}
}

void knh_Object_RCfree(CTX ctx, Object *o)
{
#define ctx_update_refs(ctx, buf, size) \
		((knh_context_t*)ctx)->refs = buf;\
		((knh_context_t*)ctx)->ref_size = size;

	long i;
	knh_Object_t *ref;
	knh_ostack_t ostackbuf, *ostack = ostack_init(ctx, &ostackbuf);
	knh_ensurerefs(ctx, ctx->ref_buf, K_PAGESIZE);
	ostack_push(ctx, ostack, o);
	while((ref = ostack_next(ostack)) != NULL) {
		ctx_update_refs(ctx, ctx->ref_buf, 0);
		O_cTBL(ref)->cdef->reftrace(ctx, RAWPTR(ref), ctx->refs);
		if (ctx->ref_size > 0) {
			for(i = ctx->ref_size - 1; prefetch(ctx->refs[i-1]), i >= 0; i--)
			//for (i = 0; prefetch(ctx->refs[i+1]), i < ctx->ref_size; i++) /* slow */
			{
				deref_ostack(ctx, ctx->refs[i], ostack);
			}
		}
		knh_Object_finalfree(ctx, ref);
	}
	ostack_free(ctx, ostack);
}

void knh_Object_RCsweep(CTX ctx, Object *o)
{
	knh_Object_RCdec(o);
	if(Object_isRC0(o)) {
		knh_Object_RCfree(ctx, o);
	}
}
#elif defined(K_USING_BMGC)
#include "bmgc.c"
#else

static void knh_ObjectObjectArenaTBL_free(CTX ctx, const knh_ObjectArenaTBL_t *oat)
{
	knh_ObjectPage_t *opage = oat->head;
	while(opage < oat->bottom) {
		size_t i;
		for(i = 0; i < K_PAGEOBJECTSIZE; i++) {
			Object *o = &opage->slots[i];
			if(O_cTBL(o) == NULL) continue;
#ifdef K_USING_RCGC
//			DBG_({
//				fprintf(stderr, "async object %p cid=%s(%d), ref=%d ", o, STRUCT__(O_bcid(o)), (int)O_cid(o), (int)O_bcid(o));
//				switch(O_bcid(o)) {
//				case CLASS_Boolean:
//					fprintf(stderr, "bvalue='%d' true?=%d false?=%d\n", (int)((knh_Int_t*)o)->n.bvalue, (o == KNH_TRUE), (o == KNH_FALSE));
//				break;
//				case CLASS_Int:
//					fprintf(stderr, "ivalue='%lld'\n", (long long int)((knh_Int_t*)o)->n.ivalue);
//				break;
//				case CLASS_Class:
//					fprintf(stderr, "o->cid=%d\n", (int)((knh_Class_t*)o)->cid);
//				break;
//				case CLASS_String:
//					fprintf(stderr, "str='%s'\n", S_totext((knh_String_t*)o));
//				break;
//				case CLASS_Term:
//					fprintf(stderr, "tt='%s'\n", TT__(((knh_Term_t*)o)->tt));
//				break;
//				case CLASS_Method: {
//					knh_Method_t *mtd = (knh_Method_t*)o;
//					fprintf(stderr, "(mtd)->cid=%s, (mtd)->mn=%d\n", STRUCT__((mtd)->cid), (mtd)->mn);
//					break;
//				}
//				case CLASS_Stmt:
//					fprintf(stderr, "stmt='%s'\n", TT__((SP(knh_StmtExpr_t*)o)->stt));
//				break;
//				default:
//					fprintf(stderr, "\n");
//				}
//			});
			o->h.refc = 0;
#endif
			knh_Object_finalfree(ctx, o);
		}
		opage++;
	}
}

void knh_ObjectArena_finalfree(CTX ctx, knh_ObjectArenaTBL_t *oat, size_t oatSize)
{
	size_t i;
	DBG_ASSERT(oat != NULL);
	for(i = 0; i < oatSize; i++) {
		knh_ObjectArenaTBL_t *t = oat + i;
		knh_ObjectObjectArenaTBL_free(ctx, t);
	}
}

/* ------------------------------------------------------------------------ */

//#define BSHIFT ((K_PAGESIZE / sizeof(knh_Object_t)) / (sizeof(knh_uintptr_t) * 8))

static inline int bit_test_and_set(knh_uintptr_t *b, size_t offset)
{
	int x = INDEX2OFFSET(offset);
	knh_uintptr_t mask = INDEX2MASK(offset);
	if (!(b[x] & mask)) {
		b[x] |= mask;
		return 0;
	}
	return 1;
}

static void gc_init(CTX ctx, int a)
{
	knh_ObjectArenaTBL_t *oat = ctx->share->ObjectArenaTBL;
	size_t atindex, size = ctx->share->sizeObjectArenaTBL;
	for(atindex = 0; atindex < size; atindex++) {
		knh_memcpy(oat->bitmap, oat->tenure, oat->bitmapsize);
		oat++;
	}
	STAT_(ctx->stat->markedObject = 0;)
}

static void mark_ostack(CTX ctx, knh_Object_t *ref, knh_ostack_t *ostack)
{
	knh_ObjectPage_t *opage = K_OPAGE(ref);
	prefetch(opage);
	size_t n = K_OPAGEOFFSET(ref, opage);
	knh_uintptr_t *b = opage->h.bitmap;
	if(!(bit_test_and_set(b, n))) {
		STAT_(ctx->stat->markedObject++;)
		if(O_hasRef(ref)) {
			ostack_push(ctx, ostack, ref);
		}
	}
}

#define CONTEXT_REFINIT(ctx) \
	((knh_context_t*)ctx)->refs = ctx->ref_buf;\
	((knh_context_t*)ctx)->ref_size = 0;

static void gc_mark(CTX ctx, int needsCStackTrace)
{
	long i;
	knh_ostack_t ostackbuf, *ostack = ostack_init(ctx, &ostackbuf);
	knh_Object_t *ref = NULL, **reftail = NULL;

	knh_ensurerefs(ctx, ctx->ref_buf, K_PAGESIZE);
	CONTEXT_REFINIT(ctx);
	reftail = knh_reftraceRoot(ctx, ctx->refs);
	if (unlikely(needsCStackTrace)) {
		cstack_mark(ctx, reftail);
	}
	//fprintf(stderr, "%s first refs %ld\n", __FUNCTION__, ctx->ref_size);
	goto L_INLOOP;
	while((ref = ostack_next(ostack)) != NULL) {
		const knh_ClassTBL_t *ct = O_cTBL(ref);
		DBG_ASSERT(O_hasRef(ref));
		CONTEXT_REFINIT(ctx);
		ct->cdef->reftrace(ctx, RAWPTR(ref), ctx->refs);
		if(ctx->ref_size > 0) {
			L_INLOOP:;
			prefetch(ctx->refs[0]);
			for(i = ctx->ref_size - 1; i >= 0; --i) {
				mark_ostack(ctx, ctx->refs[i], ostack);
			}
		}
	}
	ostack_free(ctx, ostack);
}

static void gc_move(CTX ctx, int needsCStackTrace)
{
	// yoan
}

static inline void Object_MSfree(CTX ctx, knh_Object_t *o)
{
	const knh_ClassTBL_t *ct = O_cTBL(o);
	MEMLOG("~Object", "ptr=%p, cid=%d", o, ct->cid);
	if(unlikely(Object_isXData(o))) {
		knh_PtrMap_rm(ctx, ctx->share->xdataPtrMap, o);
		Object_setXData(o, 0);
	}
	ct->cdef->free(ctx, RAWPTR(o));
	OBJECT_REUSE(o);
	WCTX(ctx)->freeObjectListSize += 1;
	STAT_dObject(ctx, ct);
	O_set_tenure(o); // uncollectable
}

static void gc_extendMemBlock(CTX ctx)
{
	knh_Object_t *block = get_memBlock(ctx, K_MEMBLOCKSIZE);
	knh_Object_t *tail = block->ref4_tail;
	tail->ref = ctx->freeObjectList;
	WCTX(ctx)->freeObjectList = block;
}

#if !defined(__GNUC__) || !defined(HAVE_BUILTIN_CTZLL)
static void gc_sweep(CTX ctx)
{
	knh_ObjectArenaTBL_t *oat = ctx->share->ObjectArenaTBL;
	size_t collected=0, moved = 0, atindex, size = ctx->share->sizeObjectArenaTBL;
	size_t listSize = 0;
	(void)moved;
	for(atindex = 0; atindex < size; atindex++) {
		knh_ObjectPage_t *opage = oat[atindex].head;
		for(;opage < oat[atindex].bottom; opage++) {
			if(ctx == GET_PAGECTX(opage)) {
				knh_uintptr_t i, *b = opage->h.bitmap;
				for(i = 1; i <= K_PAGEOBJECTSIZE; i++) {
					knh_Object_t *o = &opage->slots[i-1];
					if(!bit_test(b, (i))) {
						//prefetch(o);
						Object_MSfree(ctx, o);
						collected++;
					}
				}
			}
		}
	}
	if(ctx->freeObjectListSize < listSize / 4) { // 75%
		gc_extendMemBlock(ctx);
	}
	STAT_(
		ctx->stat->collectedObject = collected;
		ctx->stat->movedObject = moved;
	)
}

#else/*GNUC*/

#define CLEAR(b,n)     (b &= ~(INDEX2MASK(n)))
#ifndef CTZ
#define CTZ(x)    __builtin_ctzl(x)
#endif

static void gc_sweep(CTX ctx)
{
	knh_ObjectArenaTBL_t *oat = ctx->share->ObjectArenaTBL;
	size_t collected = 0, moved = 0, atindex, size = ctx->share->sizeObjectArenaTBL;
	size_t listSize = 0;
	(void)moved;
	for(atindex = 0; atindex < size; atindex++) {
		knh_ObjectPage_t *opage, *bottom = oat[atindex].bottom;
		for (opage = oat[atindex].head; opage < bottom; opage++) {
			knh_uintptr_t i, *bitmap = opage->h.bitmap;
			if(GET_PAGECTX(opage) == ctx) {
				listSize += K_PAGEOBJECTSIZE;
				for(i = 0; i <= K_PAGEOBJECTSIZE/UINTPTR8; i++) {
					knh_uintptr_t b = ~bitmap[i];
					while (b != 0) {
						knh_uintptr_t n = CTZ(b);
						register knh_Object_t *o = &(opage->slots[i * UINTPTR8 + n - 1]);
						Object_MSfree(ctx, o);
						collected++;
						CLEAR(b, n);
					}
				}
			}
		}
	}
	if(ctx->freeObjectListSize < listSize/4) { // 75%
		gc_extendMemBlock(ctx);
		listSize += K_PAGEOBJECTSIZE * K_MEMBLOCKPAGE;
	}
	STAT_(
		ctx->stat->collectedObject = collected;
		ctx->stat->movedObject = moved;
	)
}
#endif

//#ifndef K_USING_RCGC
//static void gc_extendObjectArena(CTX ctx)
//{
//	knh_share_t *ctxshare = (knh_share_t*) ctx->share;
//	knh_ObjectArenaTBL_t *oat = ctxshare->ObjectArenaTBL + (ctxshare->sizeObjectArenaTBL - 1);
//	size_t arenasize = oat->arenasize;
//	knh_uint64_t stime = knh_getTimeMilliSecond();
////	const knh_sysinfo_t *sysinfo = knh_getsysinfo();
////	size_t max = (sysinfo->hw_usermem > 0) ? sysinfo->hw_usermem / 20 : 64 * (1024 * 1024);
////	if(arenasize <= max) arenasize *= 2;
//	knh_Object_t *newobj = get_memBlock(ctx, arenasize);
//	knh_Object_t *p = ctx->freeObjectList;
//	if(p == NULL) {
//		((knh_context_t*)ctx)->freeObjectList = newobj;
//		((knh_context_t*)ctx)->freeObjectTail = newobj->ref4_tail;
//	}
//	else {
//		p = ctx->freeObjectTail;
//		p->ref = newobj;
//		((knh_context_t*)ctx)->freeObjectTail = newobj->ref4_tail;
//	}
//	GC_LOG("extendObjectArena: id=%d newarena=%luMb, used_memory=%luMb extending_time=%dms",
//			(int)(ctx->share->sizeObjectArenaTBL - 1),
//			(arenasize / MB_), (ctx->stat->usedMemorySize / MB_),
//			(int)(knh_getTimeMilliSecond()-stime));
//}
//#endif

static void gc_freeMemBlock(CTX ctx, knh_context_t *deadCtx)
{
	knh_ObjectArenaTBL_t *oat = ctx->share->ObjectArenaTBL;
	size_t collected=0, moved = 0, atindex, size = ctx->share->sizeObjectArenaTBL;
	(void)collected;
	(void)moved;
	for(atindex = 0; atindex < size; atindex++) {
		knh_ObjectPage_t *opage = oat[atindex].head;
		for(;opage < oat[atindex].bottom; opage++) {
			if(deadCtx == GET_PAGECTX(opage)) {
				SET_PAGECTX(opage, ctx);
			}
		}
	}
}

static void gc_freeCtx(CTX ctx)
{
	int i;
	knh_share_t *share = ctx->wshare;
	for(i = knh_Array_size(share->contextListNULL) - 1; i >= 0; i--) {
		knh_context_t *c = WCTX(((knh_Context_t *)knh_Array_n(share->contextListNULL, i))->ctx);
		if(!IS_RUNNING(c)) {
			gc_freeMemBlock(ctx, c);
			knh_Context_free(ctx, c);
			knh_Array_remove(ctx, share->contextListNULL, i);
		}
	}
}

static int stop_the_world(CTX ctx)
{
	knh_share_t *share = ctx->wshare;
	KNH_SYSLOCK(ctx);
	if(share->gcStopCounter == 0) {
		size_t i, size = knh_Array_size(share->contextListNULL);
		share->gcStopCounter = 1;
		share->stopCounter++;
		if(size > 1) {
			for(i = 0; i < size; i++) {
				knh_Context_t *c = (knh_Context_t *)knh_Array_n(share->contextListNULL, i);
				if(ctx != c->ctx) {
					SAFEPOINT_SETGC(c->ctx);
				}
			}
			gc_freeCtx(ctx);
			while(share->stopCounter != share->threadCounter) {
				knh_thread_cond_wait(share->start_cond, share->syslock);
			}
		}
		return 1;
	}else{
		share->stopCounter++;
		share->gcStopCounter++;
		if(share->stopCounter == share->threadCounter) {
			knh_thread_cond_signal(share->start_cond);
		}
		knh_thread_cond_wait(share->stop_cond, share->syslock);
		KNH_SYSUNLOCK(ctx);
		return 0;
	}
}

static void start_the_world(CTX ctx)
{
	ctx->wshare->stopCounter -= ctx->share->gcStopCounter;
	ctx->wshare->gcStopCounter = 0;
	knh_thread_cond_broadcast(ctx->share->stop_cond);
	KNH_SYSUNLOCK(ctx);
}
#endif /* K_USING_BMGC */


#define GCLOCK(ctx)
#define GCUNLOCK(ctx)

void knh_System_gc(CTX ctx, int needsCStackTrace)
{
	knh_stat_t *ctxstat = ctx->stat;
	size_t avail = ctx->freeObjectListSize;
	knh_uint64_t start_time = knh_getTimeMilliSecond(), mark_time = 0, sweep_time= 0, intval;
	if(stop_the_world(ctx)) {
#ifdef K_USING_CTRACE
		knh_dump_cstack(ctx);
#endif
		gc_init(ctx);
		gc_mark(ctx, needsCStackTrace);
		gc_move(ctx, needsCStackTrace);
		mark_time = knh_getTimeMilliSecond();
		start_the_world(ctx);
	}
	gc_sweep(ctx);
	sweep_time = knh_getTimeMilliSecond();
	intval = start_time - ctxstat->latestGcTime;
//	if(knh_isVerboseGC()) {
//		STAT_(
		GC_LOG("GC(%dMb): marked=%lu, collected=%lu, avail=%lu=>%lu, interval=%dms, marking_time=%dms, sweeping_time=%dms",
				ctxstat->usedMemorySize/ MB_,
				ctxstat->markedObject, ctxstat->collectedObject,
				avail, ctx->freeObjectListSize,
				(int)(intval), (int)(mark_time-start_time), (int)(sweep_time-mark_time));
//		)
//	}
	//STAT_(KNH_ASSERT(ctxstat->markedObject == ctxstat->usedObjectSize);)
	//MSGC_(if(ctxstat->gcObjectCount < K_ARENASIZE/sizeof(knh_Object_t)) {
//	MSGC_(if(!(ctxstat->usedObjectSize < ((ctxstat->gcBoundary * 3) / 4))) { /* 75%*/
//		gc_extendObjectArena(ctx);
//	})
	ctxstat->gcCount++;
	ctxstat->markingTime += (mark_time-start_time);
	ctxstat->sweepingTime += (sweep_time-mark_time);
	ctxstat->latestGcTime = knh_getTimeMilliSecond();
	ctxstat->gcTime += (ctxstat->latestGcTime - start_time);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
