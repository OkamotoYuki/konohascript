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

#define K_DEFINE_API2
#include"commons.h"

#define K_USING_LOADDATA
#include"../../include/konoha1/konohalang.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* [ContextTable] */

static knh_context_t* new_hcontext(CTX ctx0)
{
	knh_context_t *ctx;
	static volatile size_t ctxid_counter = 0;
	if(ctx0 == NULL) {
		ctx = (knh_context_t*)malloc(sizeof(knh_context_t));
		knh_bzero(ctx, sizeof(knh_context_t));
//		ctx0 = ctx;
	}
	else {
		KNH_ASSERT_CTX0(ctx0);
		ctx = (knh_context_t*)KNH_MALLOC(ctx0, sizeof(knh_context_t));
		knh_bzero(ctx, sizeof(knh_context_t));
	}
	ctx->flag = 0;
	ctx->ctxid = ctxid_counter;
	ctxid_counter++;
	ctx->freeObjectList = NULL;
	ctx->freeMemoryList = NULL;
	ctx->parent = (knh_context_t*)ctx;
	ctx->api2 = getapi2();
	{
		knh_uintptr_t i = 0, ch;
		knh_uint_t t = knh_rand();
		ch = t % 26;
		ctx->trace[i] = 'A' + ch;
		for(i = 1; i < 9; i++) {
			t = t / 36;
			if (t == 0) t = knh_rand();
			ch = t % 36;
			ctx->trace[i] = (ch < 10) ? '0' + ch : 'A' + (ch - 10);
		}
	}
	ctx->seq = 0;
	return ctx;
}

/* ------------------------------------------------------------------------ */
/* [ContextCommon] */

static void knh_CommonContext_init(CTX ctx, knh_context_t *o)
{
	KNH_ASSERT_CTX0(ctx);
	DBG_ASSERT(o->sys != NULL);
	DBG_ASSERT(o->script != NULL);
	DBG_ASSERT(o->gma != NULL);
	KNH_INITv(o->enc, DP(ctx->sys)->enc);
	KNH_INITv(o->in,  DP(ctx->sys)->in);
	KNH_INITv(o->out, DP(ctx->sys)->out);
	KNH_INITv(o->err, DP(ctx->sys)->err);
	KNH_INITv(o->e, KNH_NULL);
	KNH_INITv(o->evaled, KNH_NULL);
#ifndef K_USING_STRINGPOOL
	KNH_INITv(o->symbolDictMap, new_DictMap0(ctx, 256, 0/*isCaseMap*/, "Context.symbolDictMap"));
#endif
//	KNH_INITv(o->constPools, new_Array0(ctx, 0));
	o->ctxlock = knh_mutex_malloc(ctx);
}

static knh_Object_t** knh_CommonContext_reftrace(CTX ctx, knh_context_t *ctxo FTRARG)
{
	size_t i;
#ifndef K_USING_STRINGPOOL
	KNH_ADDREF(ctx, ctxo->symbolDictMap);
#endif
//	KNH_ADDREF(ctx, ctxo->constPools);
	KNH_ADDREF(ctx, ctxo->e);
	KNH_ADDREF(ctx, ctxo->evaled);
	KNH_ADDREF(ctx, (ctxo->script));
	KNH_ADDREF(ctx, (ctxo->enc));
	KNH_ADDREF(ctx, (ctxo->in));
	KNH_ADDREF(ctx, (ctxo->out));
	KNH_ADDREF(ctx, (ctxo->err));
	KNH_ADDREF(ctx, ctxo->gma);
	// stack
	KNH_ADDREF(ctx, (ctxo->bufa));
	KNH_ADDREF(ctx, (ctxo->bufw));
#ifdef K_USING_RCGC
	KNH_ENSUREREF(ctx, ctxo->stacksize);
	for(i = 0; i < ctxo->stacksize; i++) {
		KNH_ADDREF(ctx, ctxo->stack[i].o);
	}
#else
	{
		size_t stacksize = (ctxo->esp - ctx->stack) + 8;
		KNH_ENSUREREF(ctx, stacksize);
		for(i = 0; i < stacksize; i++) {
			KNH_ADDREF(ctx, ctxo->stack[i].o);
		}
	}
#endif
	return tail_;
}

static void knh_CommonContext_free(CTX ctx, knh_context_t *ctxo)
{
	KNH_FREE(ctx, ctxo->stack, sizeof(knh_sfp_t) * ctxo->stacksize);
	ctxo->stack = NULL;
	ctxo->esp = NULL;
	ctxo->stacktop = NULL;
	ctxo->stacksize = 0;
	KNH_FREE(ctx, ctxo->mtdcache,  K_MTDCACHE_SIZE * sizeof(knh_mtdcache_t));
	KNH_FREE(ctx, ctxo->tmrcache, K_TMAPCACHE_SIZE * sizeof(knh_tmrcache_t));
	ctxo->mtdcache  = NULL;
	ctxo->tmrcache = NULL;
	if(ctxo->queue_capacity > 0) {
		/* XXX(@imasahiro) */
		/* to remove memory leaks, queue_capacity must increment */
		/* see src/main/memory.c ostack_init() */
		KNH_FREE(ctx, ctxo->queue,  (ctxo->queue_capacity + 1) * sizeof(knh_Object_t*));
		ctxo->queue_capacity = 0;
	}
	if(ctx->ref_capacity > 0) {
		KNH_FREE(ctx, ctxo->ref_buf, ctxo->ref_capacity * sizeof(knh_Object_t*));
		ctxo->ref_capacity = 0;
	}
	knh_mutex_free(ctxo, ctxo->ctxlock);
	ctxo->ctxlock = NULL;
	ctxo->bufa = NULL;
}

/* ------------------------------------------------------------------------ */
/* [RootContext] */

static void knh_expandClassTBL(CTX ctx)
{
	size_t max = ctx->share->capacityClassTBL * 2;
	const knh_ClassTBL_t **newt = (const knh_ClassTBL_t**)
		KNH_REALLOC(ctx, "ClassTBL", ctx->share->ClassTBL, (ctx->share->capacityClassTBL), max, sizeof(knh_ClassTBL_t*));
	((knh_share_t*)ctx->share)->ClassTBL = newt;
	((knh_share_t*)ctx->share)->capacityClassTBL = max;
}

knh_class_t new_ClassId(CTX ctx)
{
	knh_class_t newid = ctx->share->sizeClassTBL;
	if(ctx->share->sizeClassTBL == ctx->share->capacityClassTBL) {
		knh_expandClassTBL(ctx);
	}
	DBG_ASSERT(ctx->share->ClassTBL[newid] == NULL);
	{
		knh_ClassTBL_t *ct = (knh_ClassTBL_t*)KNH_MALLOC(ctx, sizeof(knh_ClassTBL_t));
		knh_bzero(ct, sizeof(knh_ClassTBL_t));
		ct->cid    = newid;
		ct->keyidx = -1;
		ct->metaidx = -1;
		ctx->share->ClassTBL[newid] = ct;
	}
	((knh_share_t*)ctx->share)->sizeClassTBL = newid + 1;
	return newid;
}

/* ------------------------------------------------------------------------ */

void knh_expandEventTBL(CTX ctx)
{
	size_t s = ctx->share->sizeEventTBL, max = ctx->share->capacityEventTBL * 2;
	knh_EventTBL_t *newt = (knh_EventTBL_t*)KNH_MALLOC(ctx, SIZEOF_TEXPT(max));
	knh_bzero(newt, SIZEOF_TEXPT(max));
	knh_memcpy(newt, ctx->share->EventTBL, SIZEOF_TEXPT(s));
	((knh_share_t*)ctx->share)->EventTBL = newt;
	((knh_share_t*)ctx->share)->capacityEventTBL = max;
}

static void initServiceSPI(knh_ServiceSPI_t *spi);
void knh_loadScriptAliasTokenData(CTX ctx);

static knh_context_t* new_RootContext(void)
{
	knh_context_t *ctx = (knh_context_t*)new_hcontext(NULL);
	const knh_PackageLoaderAPI_t *kapi = knh_getPackageLoaderAPI();
	knh_share_t *share = (knh_share_t*)malloc(sizeof(knh_share_t) + sizeof(knh_stat_t) + sizeof(knh_ServiceSPI_t));
	ctx->share = share;
	knh_bzero(share, sizeof(knh_share_t) + sizeof(knh_stat_t) + sizeof(knh_ServiceSPI_t));
	ctx->stat = (knh_stat_t*)((share+1));
	ctx->spi = (const knh_ServiceSPI_t*)(ctx->stat + 1);
	initServiceSPI((knh_ServiceSPI_t*)ctx->spi);

	knh_share_initArena(ctx, share);
	share->memlock = knh_mutex_malloc(ctx);
	share->ClassTBL = (const knh_ClassTBL_t**)KNH_MALLOC((CTX)ctx, sizeof(knh_ClassTBL_t*)*(K_CLASSTABLE_INIT));
	knh_bzero(share->ClassTBL, sizeof(knh_ClassTBL_t*)*(K_CLASSTABLE_INIT));
	share->sizeClassTBL = 0;
	share->capacityClassTBL  = K_CLASSTABLE_INIT;

	share->EventTBL = (knh_EventTBL_t*)KNH_MALLOC(ctx, SIZEOF_TEXPT(K_EVENTTBL_INIT));
	knh_bzero((void*)share->EventTBL, SIZEOF_TEXPT(K_EVENTTBL_INIT));
	share->sizeEventTBL = 0;
	share->capacityEventTBL  = K_EVENTTBL_INIT;
	knh_loadScriptSystemStructData(ctx, kapi);
	knh_initFirstObjectArena(ctx);

	KNH_INITv(share->funcDictSet, new_DictSet0(ctx, 0, 0, "funcDictSet"));
	KNH_INITv(share->constPtrMap, new_PtrMap(ctx, 0));
	KNH_INITv(share->inferPtrMap, new_PtrMap(ctx, 0));
	KNH_INITv(share->xdataPtrMap, new_PtrMap(ctx, 0));
	KNH_INITv(share->constPools, new_Array0(ctx, 0));
	knh_loadSystemTypeMapRule(ctx);
	knh_ClassTBL_setConstPool(ctx, ClassTBL(CLASS_Int));
	knh_ClassTBL_setConstPool(ctx, ClassTBL(CLASS_Float));
#ifdef K_USING_STRINGPOOL
	knh_ClassTBL_setConstPool(ctx, ClassTBL(CLASS_String));
#endif
	{
		knh_Object_t *p = (knh_Object_t*)new_hObject_(ctx, ClassTBL(CLASS_Object));
		Object_setNullObject(p, 1);
		KNH_INITv(share->constNull, p);
	}
	{
		knh_Boolean_t *o = new_H(Boolean);
		o->n.bvalue = 1;
		KNH_INITv(share->constTrue, o);
		o = new_H(Boolean);
		o->n.bvalue = 0;
		KNH_INITv(share->constFalse, o);
	}
	{
		static const knh_dim_t dimINIT = {0};
		knh_Array_t *a = new_H(Array);
		(a)->size = 0;
		(a)->dim = &dimINIT;
		KNH_INITv(share->emptyArray, a);
	}
	share->tString = (knh_String_t**)KNH_MALLOC(ctx, SIZEOF_TSTRING);
	knh_bzero(share->tString, SIZEOF_TSTRING);
	knh_loadScriptSystemString(ctx);
	KNH_INITv(share->cwdPath, new_CurrentPath(ctx));

	/* These are not shared, but needed to initialize System*/
	knh_stack_initexpand(ctx, NULL, K_STACKSIZE);
	KNH_INITv(ctx->sys, new_(System));
	KNH_INITv(share->rootns, new_(NameSpace));
	knh_loadScriptSystemData(ctx, share->rootns, kapi);
	knh_System_initPath(ctx, ctx->sys);       // require rootns
	KNH_INITv(ctx->script, new_(Script));     // require rootns
	KNH_INITv(ctx->gma, new_(Gamma));         // require script
	knh_loadScriptSystemKonohaCode(ctx);      // require gamma
	knh_loadScriptSystemMethod(ctx, kapi);
	knh_CommonContext_init(ctx, ctx);
	knh_loadScriptTokenData(ctx);
	knh_loadScriptAliasTokenData(ctx);
	share->ctx0 = ctx;
	knh_Gamma_init(ctx);  // initalize gamma->gf, reported by uh
	knh_initBuiltInPackage(ctx, knh_getPackageLoaderAPI());
	return ctx;
}

static int _lock(knh_mutex_t *m DBG_TRACE)
{
	TRACE_P("LOCK mutex=%p", m);
	return 0;
}

static int _unlock(knh_mutex_t *m DBG_TRACE)
{
	TRACE_P("UNLOCK mutex=%p", m);
	return 0;
}

static int thread_lock(knh_mutex_t *m DBG_TRACE)
{
	TRACE_P("LOCK mutex=%p", m);
	return knh_mutex_lock(m);
}

static int thread_unlock(knh_mutex_t *m DBG_TRACE)
{
	TRACE_P("UNLOCK mutex=%p", m);
	return knh_mutex_unlock(m);
}

static knh_iconv_t knh_iconv_open(const char *t, const char *f)
{
	return (knh_iconv_t)(-1);
}
static size_t knh_iconv(knh_iconv_t i, char **t, size_t *ts, char **f, size_t *fs)
{
	return 0;
}
static int knh_iconv_close(knh_iconv_t i)
{
	return 0;
}

static void _setsfp(CTX ctx, knh_sfp_t *sfp, void *v)
{
	knh_Object_t *o = (knh_Object_t*)v;
	DBG_ASSERT_ISOBJECT(o);
	knh_Object_RCinc(o);
	knh_Object_RCdec(sfp[0].o);
	if(Object_isRC0(sfp[0].o)) {
		knh_Object_RCfree(ctx, sfp[0].o);
	}
	sfp[0].o = o;
}

static void initServiceSPI(knh_ServiceSPI_t *spi)
{
	spi->syncspi = "nothread";
	spi->lockSPI = _lock;
	spi->unlockSPI = _unlock;
	spi->syslogspi = "fprintf(stderr)";
	spi->syslog = pseudo_syslog;
	spi->vsyslog = pseudo_vsyslog;
	spi->iconvspi       = "noiconv";
	spi->iconv_openSPI  = knh_iconv_open;
	spi->iconvSPI       = knh_iconv;
	spi->iconv_closeSPI = knh_iconv_close;
	spi->mallocSPI = knh_fastmalloc;
	spi->freeSPI = knh_fastfree;
	spi->setsfpSPI = _setsfp;
	spi->closeItrSPI = knh_Iterator_close;
	spi->recordSPI = knh_record;
	spi->pSPI = dbg_p;
}

/* ------------------------------------------------------------------------ */
void context_init_multithread(CTX ctx)
{
	knh_ServiceSPI_t *spi = __CONST_CAST__(knh_ServiceSPI_t*, ctx->spi);
	spi->syncspi   = "thread";
	spi->lockSPI   = thread_lock;
	spi->unlockSPI = thread_unlock;
}
/* ------------------------------------------------------------------------ */

static knh_Object_t **knh_share_reftrace(CTX ctx, knh_share_t *share FTRARG)
{
	size_t i;
	KNH_ADDREF(ctx,   share->constNull);
	KNH_ADDREF(ctx,   share->constTrue);
	KNH_ADDREF(ctx,   share->constFalse);
	KNH_ADDREF(ctx,   share->emptyArray);
	KNH_ADDREF(ctx,   share->cwdPath);
	KNH_ADDREF(ctx,   ctx->sys);
	KNH_ADDREF(ctx,   share->rootns);
	KNH_ADDREF(ctx,   share->funcDictSet);
	KNH_ADDNNREF(ctx, share->sysAliasDictMapNULL);
	KNH_ADDREF(ctx,   share->constPtrMap);
	KNH_ADDREF(ctx,   share->inferPtrMap);
	KNH_ADDREF(ctx,   share->xdataPtrMap);
	KNH_ADDREF(ctx,   share->constPools);
	KNH_ENSUREREF(ctx, K_TSTRING_SIZE);
	for(i = 0; i < K_TSTRING_SIZE; i++) {
		KNH_ADDREF(ctx, share->tString[i]);
	}
	KNH_ENSUREREF(ctx, share->sizeEventTBL);
	for(i = 0; i < share->sizeEventTBL; i++) {
		if(EventTBL(i).name != NULL) {
			KNH_ADDREF(ctx, EventTBL(i).name);
		}
	}
	/* tclass */
	KNH_ENSUREREF(ctx, share->sizeClassTBL * 11);
	for(i = 0; i < share->sizeClassTBL; i++) {
		const knh_ClassTBL_t *ct = ClassTBL(i);
		DBG_ASSERT(ct->lname != NULL);
		KNH_ADDNNREF(ctx,   ct->typeNULL);
		KNH_ADDREF(ctx,     ct->methods);
		KNH_ADDREF(ctx,     ct->typemaps);
		KNH_ADDNNREF(ctx,   ct->cparam);
		KNH_ADDNNREF(ctx,   ct->defnull);
		KNH_ADDNNREF(ctx,   ct->constDictCaseMapNULL);
		KNH_ADDREF(ctx,     ct->sname);
		KNH_ADDREF(ctx,     ct->lname);
		if(ct->bcid == CLASS_Object && ct->cid > ct->bcid) {
			KNH_ADDREF(ctx, ct->protoNULL);
		}
		KNH_ADDNNREF(ctx, ct->constPoolMapNULL);
	}
	return tail_;
}

static void knh_share_free(CTX ctx, knh_share_t *share)
{
	size_t i;
	KNH_FREE(ctx, (void*)share->EventTBL, SIZEOF_TEXPT(ctx->share->capacityEventTBL));
	share->EventTBL = NULL;
	KNH_FREE(ctx, share->tString, SIZEOF_TSTRING);
	share->tString = NULL;
	xmem_freeall(ctx);
	for(i = 0; i < share->sizeClassTBL; i++) {
		knh_ClassTBL_t *ct = varClassTBL(i);
		if(ct->constPoolMapNULL) {
			knh_PtrMap_stat(ctx, ct->constPoolMapNULL, S_totext(ct->sname));
			ct->constPoolMapNULL = NULL;
		}
	}
	knh_ObjectArena_finalfree(ctx, share->ObjectArenaTBL, share->sizeObjectArenaTBL);
	for(i = 0; i < share->sizeClassTBL; i++) {
		knh_ClassTBL_t *ct = varClassTBL(i);
		if(ct->cdef->asize > 0) {
			DBG_P("freeing ClassDef cid=%d %s", i, ct->cdef->name);
			KNH_FREE(ctx, (void*)ct->cdef, ct->cdef->asize);
		}
		if(ct->fcapacity > 0) {
			KNH_FREE(ctx, ct->fields, sizeof(knh_fields_t) * ct->fcapacity);
			ct->fields = NULL;
		}
		KNH_FREE(ctx, ct, sizeof(knh_ClassTBL_t));
	}
	KNH_FREE(ctx, (void*)share->ClassTBL, sizeof(knh_ClassTBL_t*)*(share->capacityClassTBL));
	share->ClassTBL = NULL;
	knh_share_freeArena(ctx, share);
	if(ctx->stat->usedMemorySize != 0) {
		GC_LOG("memory leaking size=%ldbytes", (long)ctx->stat->usedMemorySize);
	}
	knh_bzero(share, sizeof(knh_share_t) + sizeof(knh_stat_t) + sizeof(knh_ServiceSPI_t));
	free(share);
}

knh_Context_t* toContext(CTX ctx)
{
	if(ctx->ctxobjNC == NULL) {
		knh_Context_t *cx = new_H(Context);
		cx->ctx = (knh_context_t*)ctx;
		((knh_context_t*)ctx)->ctxobjNC = cx;
	}
	return ctx->ctxobjNC;
}

/* ------------------------------------------------------------------------ */

static knh_context_t* knh_getRootContext(CTX ctx)
{
	knh_context_t *ctx0 = (knh_context_t*)ctx;
	while(ctx0->parent != ctx0) {
		ctx0 = ctx0->parent;
	}
	return ctx0;
}

void knh_context_reftrace(CTX ctx, knh_context_t *o FTRARG)
{
	tail_ = knh_CommonContext_reftrace(ctx, (knh_context_t*)o FTRDATA);
	if(knh_getRootContext(ctx) == (CTX)o) {
		tail_ = knh_share_reftrace(ctx, (knh_share_t*)o->share FTRDATA);
	}
	KNH_SIZEREF(ctx);
}

void knh_Context_free(CTX ctx, knh_context_t* ctxo)
{
	knh_CommonContext_free(ctx, ctxo);
	if(knh_getRootContext(ctx) == (CTX)ctxo) {
		size_t i, j;
		for(i = 0; i < ctxo->share->sizeClassTBL; i++) {
			knh_ClassTBL_t *t = varClassTBL(i);
			knh_Array_t *a = t->methods;
			for(j = 0; j < knh_Array_size(a); j++) {
				knh_Method_toAbstract(ctx, a->methods[j]);
			}
		}
		knh_mutex_free(ctx, ctxo->share->memlock);
		knh_share_free(ctx, (knh_share_t*)ctxo->share);
		knh_bzero((void*)ctxo, sizeof(knh_context_t));
		free((void*)ctxo);
	}
	else {
		knh_bzero((void*)ctxo, sizeof(knh_context_t));
		knh_free(ctx, (void*)ctxo, sizeof(knh_context_t));
	}
}

/* ------------------------------------------------------------------------ */
/* [konohaapi] */

konoha_t konoha_open(size_t stacksize)
{
	konoha_t k = {KONOHA_MAGIC};
	konoha_init();
	{
		CTX ctx = new_RootContext();
		k.ctx = (knh_context_t*)ctx;
	}
	return k;
}

void knh_reftraceAll(CTX ctx FTRARG)
{
	CTX ctx0 = knh_getRootContext(ctx);
	knh_context_reftrace(ctx0, (knh_context_t*)ctx0 FTRDATA);
}

void konoha_close(konoha_t konoha)
{
	CTX ctx = (knh_context_t*)konoha.ctx;
	KONOHA_CHECK_(konoha);
	if(ctx->share->threadCounter > 1) {
		LOGSFPDATA = {LOGMSG("stil threads running"), iDATA("threads", ctx->share->threadCounter)};
		LIB_Failed("konoha_close", NULL);
		return;
	}
	knh_showMemoryStat(ctx);
#ifdef K_USING_RCGC
	knh_context_reftrace(ctx, (knh_context_t*)ctx, ctx->ref_buf);
	//knh_RefTraverse(ctx, knh_Object_RCsweep);
#endif
	{
		LOGSFPDATA = {uDATA("gc_count", ctx->stat->gcCount),
				uDATA("marking_time(ms)", ctx->stat->markingTime),
				uDATA("sweeping_time(ms)", ctx->stat->sweepingTime),
				uDATA("total_time(ms)", ctx->stat->gcTime)};
		NOTE_OK("GC");
	}
	((knh_context_t*)ctx)->bufa = NULL; // necessary for KNH_SYSLOG
	knh_Context_free(ctx, (knh_context_t*)ctx);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
