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
#include"../../include/konoha1/konohalang.h"
#define Token_fn(ctx, tk) FN_UNMASK(Token_fnq(ctx, tk))

/* ************************************************************************ */

#include <ffi/ffi.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ------------------------------------------------------------------------ */

typedef void (*ffi_pconv)(CTX, knh_rbp_t *rbp, void**);
typedef void (*ffi_rfunc)(CTX, knh_sfp_t *, void * _RIX);

//static void arraysize(CTX ctx, knh_rbp_t* rp, void **pdp)
//{
//	size_t *param = (size_t*)pdp;
//	param[0] = knh_Array_size(rp->a);
//}
//
//static void arraychar(CTX ctx, knh_rbp_t* rp, void **pdp)
//{
//	const char **param = (const char**)pdp;
////	param[0] = Array_size(rp->a);
//}

static void ffi_pconvNOP(CTX ctx, knh_rbp_t *rp, void **pdp)
{
	knh_rbp_t *nrp = (knh_rbp_t*)pdp;
	nrp->ndata = rp->ndata;
}

extern ffi_type	ffi_type_void;
extern ffi_type	ffi_type_uint8;
extern ffi_type	ffi_type_sint8;
extern ffi_type	ffi_type_uint16;
extern ffi_type	ffi_type_sint16;
extern ffi_type	ffi_type_uint32;
extern ffi_type	ffi_type_sint32;
extern ffi_type	ffi_type_uint64;
extern ffi_type	ffi_type_sint64;
extern ffi_type	ffi_type_float;
extern ffi_type	ffi_type_double;
extern ffi_type	ffi_type_longdouble;
extern ffi_type	ffi_type_pointer;

static ffi_type* type_ffitype(CTX ctx, knh_type_t ptype)
{
	if(IS_Tunbox(ptype)) {
		if(IS_Tint(ptype)) {
			return &ffi_type_sint64;
		}
		else if(ptype == CLASS_Boolean) {
			return &ffi_type_sint32;  // ?
		}
		return &ffi_type_double;
	}
	else {
		if(ptype == TYPE_void) {
			return &ffi_type_void;
		}
		return &ffi_type_pointer;
	}
}

typedef struct {
	const char *key;
	void *value;
} knh_keyvalue_t;

static knh_keyvalue_t tdata[] = {
		{"byte",  &ffi_type_uint8},
		{"char",  &ffi_type_sint8},
		{"float",  &ffi_type_float},
		{"double",  &ffi_type_double},

#if defined(__LP64__)
		{"int",   &ffi_type_sint32},
#elif defined(__WIN64)
		{"int",   &ffi_type_sint64},
#else
		{"int",   &ffi_type_sint32},
#endif

		{"int8",  &ffi_type_sint8},
		{"int16",  &ffi_type_sint16},
		{"int32",  &ffi_type_sint32},
		{"int64",  &ffi_type_sint64},

#if defined(__LP64__)
		{"long",   &ffi_type_sint64},
#elif defined(__WIN64)
		{"long",   &ffi_type_sint64},
#else
		{"long",   &ffi_type_sint32},
#endif

		{"longdouble", &ffi_type_longdouble},
		{"pointer", &ffi_type_pointer},

		{"sint8",   &ffi_type_sint8},
		{"sint16",  &ffi_type_sint16},
		{"sint32",  &ffi_type_sint32},
		{"sint64",  &ffi_type_sint64},

		{"uchar",   &ffi_type_uint8},

#if defined(__LP64__)
		{"uint",   &ffi_type_uint32},
#elif defined(__WIN64)
		{"uint",   &ffi_type_uint64},
#else
		{"uint",   &ffi_type_uint32},
#endif
		{"uint8",   &ffi_type_uint8},
		{"uint16",  &ffi_type_uint16},
		{"uint32",  &ffi_type_uint32},
		{"uint64",  &ffi_type_uint64},

#if defined(__LP64__)
		{"ulong",   &ffi_type_uint64},
#elif defined(__WIN64)
		{"ulong",   &ffi_type_uint64},
#else
		{"ulong",   &ffi_type_uint32},
#endif
		{"void",    &ffi_type_void},
};

static void *bfind(const char *key, knh_keyvalue_t *data, size_t s, size_t e)
{
	while(s + 1 < e) {
		size_t m = (s + e) / 2;
		int n = strcmp(key, data[m].key);
		if(n == 0) return data[m].value;
		if(n < 0) {
			e = m;
		}
		else {
			s = m;
		}
	}
	return NULL;
}

static void *bytes_find(knh_bytes_t t, knh_keyvalue_t *data, size_t n)
{
	if(t.buf[t.len-1] == '*') {
		return &ffi_type_pointer;
	}
	if(t.len + 1 < 80) {
		size_t i;
		char buf[80];
		for(i = 0; i < t.len; i++) {
			buf[i] = t.buf[i];
		}
		buf[i] = 0;
		DBG_P("finding '%s'..", buf);
		return bfind((const char*)buf, data, 0, n);
	}
	return NULL;
}

static ffi_type* bytes_ffitype(CTX ctx, knh_bytes_t t, ffi_type *def)
{
	ffi_type *ctype = (ffi_type*)bytes_find(t, tdata, sizeof(tdata) / sizeof(knh_keyvalue_t));
	if(ctype == NULL) {
		DBG_P("Not find '%s'..", t.text);
		ctype = def;
	}
	return ctype;
}

static int ffi_rbpidx(CTX ctx, knh_type_t ptype, int sfpidx)
{
	int rbpidx = (IS_Tunbox(ptype)) ? 1: 0;
	return rbpidx + (sfpidx) * 2;
}

static int bytes_rbpidx(CTX ctx, knh_bytes_t t, knh_type_t ptype, int def)
{
	knh_int_t n;
	if(knh_bytes_parseint(t, &n)) {
		return ((int)n) * 2 + IS_Tunbox(ptype) ? 1 : 0;
	}
	return def;
}

static ffi_pconv bytes_fficonv(CTX ctx, knh_bytes_t t)
{
	return ffi_pconvNOP;
}

static void Array_addCtype(CTX ctx, knh_Array_t *a, knh_bytes_t t, knh_type_t ptype, int sfpidx)
{
	ffi_type *ctype = type_ffitype(ctx, ptype);
	int rbpidx = ffi_rbpidx(ctx, ptype, sfpidx);
	ffi_pconv tr = ffi_pconvNOP;
	knh_index_t loc = knh_bytes_index(t, ':');
	if(loc != -1) {
		t = knh_bytes_last(t, loc+1);  // skip ctype:
		loc = knh_bytes_index(t, ':');
		if(loc != -1) {
			ctype = bytes_ffitype(ctx, knh_bytes_first(t, loc), ctype);
			t = knh_bytes_last(t, loc+1);
			if(isdigit(t.buf[0])) {
				loc = knh_bytes_index(t, ':');
				if(loc != -1) {
					rbpidx = bytes_rbpidx(ctx, knh_bytes_first(t, loc), ptype, rbpidx);
					t = knh_bytes_last(t, loc+1);
				}
				else {
					rbpidx = bytes_rbpidx(ctx, t, ptype, rbpidx);
					goto L_ADD;
				}
			}
			tr = bytes_fficonv(ctx, knh_bytes_last(t, loc+1));
		}
		else {
			ctype = bytes_ffitype(ctx, t, ctype);
		}
	}
	L_ADD:;
	knh_Array_add(ctx, a, new_Int_(ctx, CLASS_Int, rbpidx));
	knh_Array_add(ctx, a, new_Pointer(ctx, "ffi_conv", tr, NULL));
	knh_Array_add(ctx, a, new_Pointer(ctx, "ffi_type", ctype, NULL));
}


static knh_type_t ptype_getsfpidx(CTX ctx, knh_Method_t *mtd, int sfpidx)
{
	if(sfpidx == 0) return mtd->cid;
	knh_ParamArray_t *pa = DP(mtd)->mp;
	if(sfpidx - 1 < pa->psize) {
		return knh_ParamArray_get(pa, sfpidx-1)->type;
	}
	return TYPE_void;
}

static knh_bool_t Method_addParam(CTX ctx, knh_Method_t *mtd, knh_Array_t *a, Object *pdata)
{
	int sfpidx = Method_isStatic(mtd) ? 1 : 0;
	knh_type_t ptype = TYPE_void;
	if(pdata == NULL) {
		ptype = ptype_getsfpidx(ctx, mtd, sfpidx);
		while(ptype != TYPE_void) {
			Array_addCtype(ctx, a, STEXT(""), ptype_getsfpidx(ctx, mtd, sfpidx), sfpidx);
			sfpidx++;
			ptype = ptype_getsfpidx(ctx, mtd, sfpidx);
		}
	}
	else if(IS_bString(pdata)) {
		knh_bytes_t t = S_tobytes((knh_String_t*)pdata);
		ptype = ptype_getsfpidx(ctx, mtd, sfpidx);
		Array_addCtype(ctx, a, t, ptype, sfpidx);
	}
	else if(O_cid(pdata) == CLASS_StringARRAY) {
		knh_Array_t *as = (knh_Array_t*)pdata;
		size_t i;
		for(i = 0; i < knh_Array_size(as); i++) {
			knh_bytes_t t = S_tobytes(as->strings[i]);
			ptype = ptype_getsfpidx(ctx, mtd, sfpidx);
			Array_addCtype(ctx, a, t, ptype, sfpidx);
			sfpidx++;
		}
	}
	return 1;
}

static void freecif(void *p)
{
	ffi_cif *cif = (ffi_cif*)p;
	free(cif->arg_types);
	free(cif);
}

static knh_bool_t Array_addCIF(CTX ctx, knh_Array_t *a, ffi_type *return_type)
{
	size_t i, psize = knh_Array_size(a) / 3;
	ffi_type *ctypes[psize];
	ffi_cif   cif, *kcif;
	ffi_status status;
	for(i = 0; i < psize; i++) {
		ctypes[i] = (ffi_type*)a->ptrs[(i * 3) + 2]->rawptr;
	}
	if ((status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, psize, return_type, ctypes)) == FFI_OK) {
		kcif = (ffi_cif*)malloc(sizeof(ffi_cif));
		if(kcif != NULL) {
			knh_memcpy(kcif, &cif, sizeof(ffi_cif));
			kcif->arg_types = (ffi_type**)malloc(sizeof(ffi_type*) * cif.nargs);
			for(i = 0; i < psize; i++) {
				kcif->arg_types[i] = ctypes[i];
			}
			knh_Array_add(ctx, a, new_Pointer(ctx, "ffi_cif", kcif, freecif));
			return 1;
		}
	}
	return 0;
}

#define RTYPE_void     0
#define RTYPE_boolean  1
#define RTYPE_int      2
#define RTYPE_float    3
#define RTYPE_String   4
#define RTYPE_RawPtr   5

//static int RTYPE__(knh_class_t bcid)
//{
//	switch(bcid) {
//	case CLASS_Tvoid: return RTYPE_void;
//	case CLASS_Boolean: return RTYPE_boolean;
//	case CLASS_Int: return RTYPE_int;
//	case CLASS_Float: return RTYPE_float;
//	case CLASS_String: return RTYPE_String;
//	}
//	return RTYPE_RawPtr;
//}

static void rconv_void(CTX ctx, knh_sfp_t *sfp, void *rvalue _RIX)
{
	RETURNvoid_();
}

static void rconv_bool(CTX ctx, knh_sfp_t *sfp, void *rvalue _RIX)
{
	knh_bool_t *v = (knh_bool_t*)rvalue;
	RETURNb_(v[0]);
}

static void rconv_int(CTX ctx, knh_sfp_t *sfp, void *rvalue _RIX)
{
	knh_int_t *v = (knh_int_t*)rvalue;
	RETURNi_(v[0]);
}

static void rconv_float(CTX ctx, knh_sfp_t *sfp, void *rvalue _RIX)
{
	knh_float_t *v = (knh_float_t*)rvalue;
	RETURNf_(v[0]);
}

static void rconv_String(CTX ctx, knh_sfp_t *sfp, void *rvalue _RIX)
{
	const char** v = (const char **)rvalue;
	RETURN_(new_String(ctx, v[0]));
}

static void rconv_RawPtr(CTX ctx, knh_sfp_t *sfp, void *rvalue _RIX)
{
	void** v = (void**)rvalue;
	knh_Method_t *mtd = sfp[K_MTDIDX].mtdNC;
	RETURN_(knh_Method_newRawPtr(ctx, mtd, v[0]));
}

static ffi_rfunc bcid_rfunc(knh_class_t bcid)
{
	switch(bcid) {
	case CLASS_Tvoid: return rconv_void;
	case CLASS_Boolean: return rconv_bool;
	case CLASS_Int: return rconv_int;
	case CLASS_Float: return rconv_float;
	case CLASS_String: return rconv_String;
	}
	return rconv_RawPtr;
}

static ffi_rfunc bytes_rfunc(CTX ctx, knh_bytes_t t, knh_type_t rtype)
{
	knh_class_t bcid = C_bcid(rtype);
	switch(bcid) {
	case CLASS_Tvoid: return rconv_void;
	case CLASS_Boolean: return rconv_bool;
	case CLASS_Int: return rconv_int;
	case CLASS_Float: return rconv_float;
	case CLASS_String: return rconv_String;
	}
	return rconv_RawPtr;
}

static knh_bool_t Method_setReturn(CTX ctx, knh_Method_t *mtd, knh_Array_t *a, Object *rdata)
{
	knh_ParamArray_t *pa = DP(mtd)->mp;
	knh_type_t rtype = knh_ParamArray_rtype(pa);
	ffi_type *return_type = type_ffitype(ctx, rtype);
	ffi_rfunc tr = bcid_rfunc(C_bcid(rtype));
	if(rdata != NULL && IS_bString(rdata)) {
		knh_bytes_t t = S_tobytes((knh_String_t*)rdata);
		knh_index_t loc = knh_bytes_index(t, ':');
		t = knh_bytes_last(t, loc+1);  // skip ctype:
		loc = knh_bytes_index(t, ':');
		if(loc != -1) {
			tr = bytes_rfunc(ctx, knh_bytes_last(t, loc+1), rtype);
			if(tr == NULL) {
				DBG_P("nofunction: %s", t.text);
				return 0;
			}
			t = knh_bytes_first(t, loc);
		}
		return_type = bytes_ffitype(ctx, t, return_type);
	}
	KNH_SETv(ctx, DP(mtd)->rfunc, new_Pointer(ctx, "ffi_rfunc", tr, NULL));
	return Array_addCIF(ctx, a, return_type);
}

#define Method_infoFFI(mtd)        DP(mtd)->paramsNULL;
#define FFI_psize(a)               ((knh_Array_size(a) - 1) / 3)
#define FFI_cif(a)                 (ffi_cif*)((a)->ptrs[knh_Array_size(a)-1]->rawptr)
#define FFI_rbpidx(a, n)           (int)(N_toint((a)->ints[((n)*3)]))
#define FFI_values(rbp, a, n)      &(rbp[FFI_rbpidx(a,n)].pc)
#define FFI_tr(a, n)               (ffi_pconv)(a->ptrs[((n)*3)+1]->rawptr)

static METHOD Fmethod_FFI(CTX ctx, knh_sfp_t *sfp _RIX)
{
	knh_rbp_t *rp = (knh_rbp_t*)sfp;
	knh_Method_t *mtd = sfp[K_MTDIDX].mtdNC;
	knh_Array_t *ffi_info = Method_infoFFI(mtd)
	ffi_cif* cif = FFI_cif(ffi_info);
	size_t i, psize = FFI_psize(ffi_info), pos = BA_size(ctx->bufa);
	void *cbuf[psize*4], *cvalues[psize];
    ffi_arg result;
	for(i = 0; i < psize; i++) {
		ffi_pconv tr = FFI_tr(ffi_info, i);
		cvalues[i] = &cbuf[i*4];
		tr(ctx, rp + FFI_rbpidx(ffi_info, i), cbuf + i * 4);
	}
	ffi_rfunc freturn = (ffi_rfunc)DP(mtd)->rfunc->rawptr;
	ffi_call(cif, FFI_FN(DP(mtd)->cfunc), &result, cvalues);
    knh_Bytes_clear(ctx->bufa, pos);
    freturn(ctx, sfp, &result, K_RIX);
}

typedef void* (*Fgetfunc)(const char *symbol);

static void* knh_loadCFUNC(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t cfunc)
{
	const char *funcname = knh_bytes_next(cfunc, ':').text;
	void *func = NULL;
	if(ns->gluehdr != NULL) {
		Fgetfunc f = (Fgetfunc) knh_dlsym(ctx, ns->gluehdr, "localfunc", 0);
		if(f != NULL) {
			func = f(funcname);
			if(func != NULL) return func;
		}
	}
	while(ns != NULL) {
		if(DP(ns)->ffilinksNULL != NULL) {
			long i;
			knh_Array_t *a = DP(ns)->ffilinksNULL;
			for(i = knh_Array_size(a) -1; i >= 0; i--) {
				func = knh_dlsym(ctx, a->ptrs[i]->rawptr, funcname, 0);
				if(func != NULL) return func;
			}
		}
		ns = ns->parentNULL;
	}
	return NULL;
}

knh_Fmethod knh_gluefunc(CTX ctx, knh_Method_t *mtd, knh_NameSpace_t *ns, knh_DictMap_t *mdata)
{
	knh_Fmethod gluefunc = NULL;
	knh_Object_t *gluedata = knh_DictMap_getNULL(ctx, mdata, STEXT("gluefunc"));
	if(gluedata != NULL && IS_bString(gluedata)) {
		if(ns->gluehdr == NULL) {
			DBG_P("gluehdr is not open");
		}
		else {
			gluefunc = (knh_Fmethod)knh_dlsym(ctx, ns->gluehdr, S_tochar((knh_String_t*)gluedata), 0);
			if(gluefunc == NULL) {
				DBG_P("gluefunc is not found: %s", S_tochar((knh_String_t*)gluedata));
			}
		}
	}
	if(gluefunc == NULL) {
		gluefunc = Fmethod_FFI;
	}
	return gluefunc;
}

knh_bool_t knh_Method_ffi(CTX ctx, knh_Method_t *mtd, knh_NameSpace_t *ns, knh_DictMap_t *mdata)
{
	DBG_P("class %s", CLASS__(O_cid(mdata)));
	knh_write_Object(ctx, KNH_STDOUT, UPCAST(mdata), FMT_dump);
	knh_Object_t *fdata = knh_DictMap_getNULL(ctx, mdata, STEXT("cfunc"));
	if(fdata == NULL) {
		fdata = knh_DictMap_getNULL(ctx, mdata, STEXT("func"));
	}
	void *cfunc = NULL;
	if(fdata != NULL && IS_bString(fdata)) {
		cfunc = knh_loadCFUNC(ctx, ns, S_tobytes((knh_String_t*)fdata));
		if(cfunc == NULL) {
			DBG_P("cfunc: %s is not found", S_tochar((knh_String_t*)fdata));
		}
	}
	if(cfunc != NULL) {
		knh_Object_t *pdata = knh_DictMap_getNULL(ctx, mdata, STEXT("param"));
		if(pdata == NULL) {
			knh_DictMap_getNULL(ctx, mdata, STEXT("params"));
		}
		knh_Object_t *rdata = knh_DictMap_getNULL(ctx, mdata, STEXT("return"));
		if(DP(mtd)->paramsNULL == NULL) {
			KNH_INITv(DP(mtd)->paramsNULL, new_Array0(ctx, 0));
		}
		else {
			KNH_SETv(ctx, DP(mtd)->paramsNULL, new_Array0(ctx, 0));
		}
		if(Method_addParam(ctx, mtd, DP(mtd)->paramsNULL, pdata) && Method_setReturn(ctx, mtd, DP(mtd)->paramsNULL, rdata)) {
			mtd->fcall_1 = knh_gluefunc(ctx, mtd, ns, mdata);
			DP(mtd)->cfunc = cfunc;
			return 1;
		}
	}
	knh_Method_toAbstract(ctx, mtd);
	return 0;
}


/* ------------------------------------------------------------------------ */

static knh_bool_t LIB_hasType(CTX ctx, knh_class_t cid)
{
	return 0;
}

static void *knh_open_gluelink(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t libname)
{
	void *p = NULL;
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	knh_buff_addospath(ctx, cwb->ba, cwb->pos, 0, S_tobytes(ns->rpath));
	knh_buff_trim(ctx, cwb->ba, cwb->pos, '.');
	knh_buff_addospath(ctx, cwb->ba, cwb->pos, 0, STEXT(K_OSDLLEXT));
	p = knh_dlopen(ctx, knh_cwb_tochar(ctx, cwb));
	knh_cwb_close(cwb);
	if(p != NULL) {
		knh_Fpkginit pkginit = (knh_Fpkginit)knh_dlsym(ctx, p, "init", 1/*isTest*/);
		if(pkginit != NULL) {
			const knh_PackageDef_t *pkgdef = pkginit(ctx, knh_getPackageLoaderAPI());
			LOGSFPDATA = {sDATA("package_name", pkgdef->name),
					iRANGE("buildid", K_BUILDID, pkgdef->buildid), iRANGE("crc32", K_API2_CRC32, pkgdef->crc32)};
			if((long)pkgdef->crc32 == (long)K_API2_CRC32) {
				LIB_OK("gluelink");
				return p;
			}
			else {
				LIB_Failed("gluelink", NULL);
			}
		}
		p = NULL;
	}
	return p;
}

static void *knh_open_ffilink(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t libname)
{
	void *p = NULL;
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	libname = knh_cwb_ensure(ctx, cwb, libname, K_PATHMAX);
	knh_buff_addospath(ctx, cwb->ba, cwb->pos, 0, libname);
	knh_buff_trim(ctx, cwb->ba, cwb->pos, '.');
	knh_buff_addospath(ctx, cwb->ba, cwb->pos, 0, STEXT(K_OSDLLEXT));
	p = knh_dlopen(ctx, knh_cwb_tochar(ctx, cwb));
	if(p == NULL && !knh_bytes_startsWith(libname, STEXT("lib"))) {
		knh_cwb_clear2(cwb, 0);
		knh_buff_addospath(ctx, cwb->ba, cwb->pos, 0, STEXT("lib"));
		knh_buff_addospath(ctx, cwb->ba, cwb->pos, 0, libname);
		knh_buff_trim(ctx, cwb->ba, cwb->pos, '.');
		knh_buff_addospath(ctx, cwb->ba, cwb->pos, 0, STEXT(K_OSDLLEXT));
		p = knh_dlopen(ctx, knh_cwb_tochar(ctx, cwb));
	}
	knh_cwb_close(cwb);
	return p;
}

knh_bool_t knh_NameSpace_addFFIlink(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t path)
{
	knh_bytes_t libname = knh_bytes_next(path, ':');
	if(libname.text[0] == '*' || knh_bytes_equals(libname, STEXT("gluelink"))) {
		ns->gluehdr = knh_open_gluelink(ctx, ns, libname);
		return (ns->gluehdr != NULL);
	}
	else {
		void *p = knh_open_ffilink(ctx, ns, libname);
		if(p != NULL) {
			if(DP(ns)->ffilinksNULL == NULL) {
				KNH_INITv(DP(ns)->ffilinksNULL, new_Array0(ctx, 0));
			}
			knh_Array_add(ctx, DP(ns)->ffilinksNULL, new_Pointer(ctx, "dl", p, NULL));
			return 1;
		}
	}
	return 0;
}

static knh_bool_t LIB_exists(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t path)
{
	knh_bytes_t libname = knh_bytes_next(path, ':');
	knh_bytes_t funcname = knh_bytes_rnext(path, '.');
	void *p = knh_open_ffilink(ctx, ns, path);
	knh_bool_t res = 0;
	if(p != NULL) {
		res = 1;
		if(funcname.len < libname.len) {
			void *f = knh_dlsym(ctx, p, funcname.text, 1/*isTest*/);
			res = (f != NULL);
		}
		knh_dlclose(ctx, p);
	}
	return res;
}

static knh_Object_t* LIB_newObjectNULL(CTX ctx, knh_NameSpace_t *ns, knh_class_t cid, knh_String_t *s)
{
	return NULL/*(knh_Object_t*)s*/;
}

static const knh_LinkDPI_t LINK_LIB = {
	"lib", NULL, LIB_hasType, LIB_exists, LIB_newObjectNULL,
};

static knh_bool_t CFUNC_hasType(CTX ctx, knh_class_t cid)
{
	return 0;
}

static knh_bool_t CFUNC_exists(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t path)
{
	return (knh_loadCFUNC(ctx, ns, path) != NULL);
}

static knh_Object_t* CFUNC_newObjectNULL(CTX ctx, knh_NameSpace_t *ns, knh_class_t cid, knh_String_t *s)
{
	return NULL/*(knh_Object_t*)s*/;
}

static const knh_LinkDPI_t LINK_CFUNC = {
	"cfunc", NULL, CFUNC_hasType, CFUNC_exists, CFUNC_newObjectNULL,
};

static knh_bool_t CTYPE_hasType(CTX ctx, knh_class_t cid)
{
	return 0;
}

static knh_bool_t CTYPE_exists(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t path)
{
	void *ctype = bytes_find(knh_bytes_next(path, ':'), tdata, sizeof(tdata) / sizeof(knh_keyvalue_t));
	return (ctype != NULL);
}

static knh_Object_t* CTYPE_newObjectNULL(CTX ctx, knh_NameSpace_t *ns, knh_class_t cid, knh_String_t *s)
{
	return NULL/*(knh_Object_t*)s*/;
}

static const knh_LinkDPI_t LINK_CTYPE = {
	"ctype", NULL, CTYPE_hasType, CTYPE_exists, CTYPE_newObjectNULL,
};

void knh_loadFFIDriver(CTX ctx, knh_NameSpace_t *ns)
{
	const knh_PackageLoaderAPI_t *api = knh_getPackageLoaderAPI();
	api->addLinkDPI(ctx, ns, "lib", &LINK_LIB);
	api->addLinkDPI(ctx, ns, "cfunc", &LINK_CFUNC);
	api->addLinkDPI(ctx, ns, "ctype", &LINK_CTYPE);
}








/* 
 * Contributors
 *  Shinpei Nakata <shinpei.nakata(at)gmail.com>
 */

/*
// for FFI DSL
typedef struct knh_xblock_t {
	unsigned char *block;
	struct knh_xblock_t *next;
} knh_xblock_t;


static knh_xblock_t* xfreelist = NULL;

static void* get_unused_xblock(CTX ctx)
{
	if (unlikely(xfreelist == NULL)) {
		unsigned char *xmem = (unsigned char*)knh_xmalloc(ctx, 1);
		assert(xmem != NULL);
		knh_xblock_t *p = (knh_xblock_t*)knh_malloc(ctx, XBLOCK_NUMBER * sizeof(knh_xblock_t));
		size_t idx = 0;
		for (idx = 0; idx < XBLOCK_NUMBER - 1; idx++) {
			p[idx].block = &(xmem[idx * XBLOCK_SIZE]);
			p[idx].next = &(p[idx + 1]);
			//			fprintf(stderr, "idx:%d, p:%p, block:%p, next:%p\n", idx, &(p[idx]), p[idx].block, p[idx].next);
		}
		p[idx].block = &(xmem[idx * XBLOCK_SIZE]);
		p[idx].next = NULL;
		xfreelist = p;
	}
	if (xfreelist->next == NULL) {
		unsigned char *xmem = (unsigned char*)knh_xmalloc(ctx, 1);
		knh_xblock_t *p = (knh_xblock_t*)knh_malloc(ctx, XBLOCK_NUMBER * sizeof(knh_xblock_t));
		size_t idx = 0;
		for (idx = 0; idx < XBLOCK_NUMBER - 1; idx++) {
			p[idx].block = &(xmem[idx * XBLOCK_SIZE]);
			p[idx].next = &(p[idx + 1]);
		}
		p[idx].block = &(xmem[idx * XBLOCK_SIZE]);
		p[idx].next = NULL;
		xfreelist->next = p;
	}
	assert(xfreelist->next != NULL);
	knh_xblock_t *ret = xfreelist;
	xfreelist = ret->next;
	return ret;
}
*/

/*
	// this supposed to be a libffi version
static knh_xblock_t *knh_generateWrapper(CTX ctx, void *callee, int argc, knh_ffiparam_t *argv)
{
  knh_xblock_t *blk = get_unused_xblock(ctx);
  void *function = blk->block;

  size_t fidx = 0;
  int i = 0;
  knh_ffiparam_t *t;

  for (i = 0; i < argc; i++) {
	t = &argv[i];
	if (t->sfpidx = -1) {
	  // it means arguments	
	  switch(t->type) {
	    case CLASS_Tvoid:
		  // do nothing
		  break;
	    case CLASS_Int:
		  break;
	  }
	}
  }
}
  */



/* ------------------------------------------------------------------------ */
// FFI DSL generator
//  knh_Fmethod : void 
#ifdef K_USING_FFIDSL

// (eax)
#define MOD_EADDR (0)
// (eax + disp8)
#define MOD_PLUS8 (1)
// (eax + disp32)
#define MOD_PLUS32 (2)
// $eax
#define MOD_IMD (3)

// Reg/opcode
#define _EAX (0)
#define _ECX (1)
#define _EDX (2)
#define _EBX (3)
#define _ESP (4)
#define _EBP (5)
#define _ESI (6)
#define _EDI (7)


#define FUNCTION function
#define FIDX fidx

#define WRITE_ASM(MOD, REG, RM) FUNCTION[FIDX++] = (MOD << 6) | (REG << 3) | RM
#define WRITE_HEX(hex) { FUNCTION[FIDX++] = hex; }


typedef struct knh_xcode_t {
	void *code;
	size_t codesize;
} knh_xcode_t;


static knh_xblock_t* knh_generateWrapper(CTX ctx, void* callee, int argc, knh_ffiparam_t *argv)
{
	//unsigned char *FUNCTION = (unsigned char*)knh_xmalloc(ctx, 1);
	knh_xblock_t *blk = get_unused_xblock(ctx);
	unsigned char *function = blk->block;
	
	size_t fidx = 0;

	// magick word
	WRITE_HEX(0x55); // push ebp 
	WRITE_HEX(0x89); // mov esp->ebp
	WRITE_ASM(MOD_IMD, _ESP, _EBP);

	// incase we use ebp, store it.
	WRITE_HEX(0x53); // push ebx

	// we need stack argc * 8bytes at most
	size_t stacksize = argc * 8;
	// allocate stack (sub esp 0x38)
	WRITE_HEX(0x83);
	WRITE_HEX(0xec);
	WRITE_HEX((unsigned char)(stacksize + 0x8));

	// before going, we need edx to be store;
	// mov edx --> -0x4(ebp)
	WRITE_HEX(0x89); // mov r+disp r
	WRITE_ASM(MOD_PLUS8, _EDX, _EBP);
    WRITE_HEX(0xfc);

	//now, process first argument;
	int i;
	knh_ffiparam_t *t;

	for (i = 0; i < argc; i++) {
		t = &(argv[i]);
		if (t->sfpidx != -1) {
			// if sfpidx == -1, its ret value;
			// prepare ebx (put sfp from edx);
			WRITE_HEX(0x89);
			WRITE_ASM(MOD_IMD, _EDX, _EBX);

			switch(t->type) {
			case CLASS_Tvoid:
				// do noting.
				break;
			case CLASS_Int:
				// its 64bit int
				//TODO: we need to call translater, but now, we ignore
				//TODO: assume we cast Int --> int;
				// add ebx[sfp] + sfpidx * 16;
				WRITE_HEX(0x83); //add
				WRITE_ASM(MOD_IMD,  _EAX , _EBX);
				WRITE_HEX((unsigned char)(t->sfpidx * 16));

				// move ivalue(offset is 8);
				WRITE_HEX(0x8b); // mov r+disp, r
				WRITE_ASM(MOD_PLUS8, _EAX, _EBX);
				WRITE_HEX(0x8);

				// move eax to local value
				//WRITE_HEX(0x89);
				//WRITE_ASM(MOD_IMD, _EBP, _EAX);
				//				WRITE_HEX(0xf4);
				break;
			case CLASS_Float:
				WRITE_HEX(0x83);
				WRITE_ASM(MOD_IMD, _EAX, _EBX);
				WRITE_HEX((unsigned char)(t->sfpidx * 16));

				// load fvalue;

				WRITE_HEX(0xdd);// fld 64bit
				WRITE_HEX(0x43);// eax
				WRITE_HEX(0x8); // offset

				// push it to eax;
				WRITE_HEX(0xdd); // fstp : store & pop 64
				WRITE_HEX(0x1c);
				WRITE_HEX(0x24);

				break;
			default:
				break;
			}
		} else continue; // if its ret value
	}

	// now, call foreign function
	// NOT SURE??? since konoha is using FASTCALL,
	// call convension is always Fastcall.

	unsigned char default_disp = 0x8;
	unsigned char disp = 0x0;

	// argc contains ret value. remeber...
	// TODO :only for a single argument...
	for (i = argc - 1; i > 0; i--) {
		// push aruguments on the stack;
		// mov argument to eax!
		// TODO : now, we only consider 32 bit values

		if (argv[i].type == CLASS_Int) {
			function[fidx++] = 0x89; // mov r+disp r
			function[fidx++] = 0x45; // 0xXX(ebp)
			disp = default_disp + i * 4;
			disp = 0x100 - disp;
			function[fidx++] = disp; // -0x8
			//move to esp
			function[fidx++] = 0x89;
			function[fidx++] = 0x04;
			function[fidx++] = 0x24;
		}

	}

	//now call.
	// call foreign function
	//	intptr_t ucallee = (intptr_t)callee;
	//	intptr_t next_addr = (intptr_t)function + (intptr_t)fidx + 5 /*for call instruction */;
	//intptr_t rel = (ucallee > next_addr) ? ucallee - next_addr : next_addr - ucallee;
	//rel = -rel;
	//unsigned char *src = (unsigned char*)&rel;

	// absolute call
	unsigned char *src = (unsigned char*)&callee;
	// mov this to eax;
	WRITE_HEX(0xb8); // mov to eax
	WRITE_HEX(src[0]);
	WRITE_HEX(src[1]);
	WRITE_HEX(src[2]);
	WRITE_HEX(src[3]);

	// now call
	WRITE_HEX(0xff);
	WRITE_HEX(0xd0);

	//  function[fidx++] = 0xcc;
	// after calling, restore edx;
	// restore edx;
	WRITE_HEX(0x8b);
	WRITE_ASM(MOD_PLUS8, _EDX, _EBP);
	WRITE_HEX(0xfc);

	if (argv[0].sfpidx == -1) {
		switch(argv[0].type) {
		case CLASS_Tvoid:
			goto STEP_OUT;
			break;
		case CLASS_Int:
			// get return value, and give it to Konoha
			// ret value is on eax;
			// push eax
			function[fidx++] = 0x50; // push eax
			break;
		case CLASS_Float:
			// it is on FPU. we need no concern.
			break;
		}
	}

	// get rix (at 0x8(ebp)) --> eax
	WRITE_HEX(0x8b);  // mov
	WRITE_ASM(MOD_PLUS8, _EAX, _EBP); // 0xXX(ebp) eax
	WRITE_HEX(0x8); // 8

	// get edx --> ebx
	WRITE_HEX(0x89);
	WRITE_ASM(MOD_IMD, _EDX, _EBX);

	// ebx[sfp] + 16 * rix
	// first, 16 * rix = 2^4 * rix
	WRITE_HEX(0xc1); // shl
	WRITE_ASM(MOD_IMD, _ESP, _EAX);
	WRITE_HEX(0x4);

	// second, add eax to ebx;
	WRITE_HEX(0x01); //add
	WRITE_ASM(MOD_IMD, _EAX, _EBX); // add eax -> ebx;

	// now at ebx is pointing to sfp[K_RIX];
	// copy retvalue to sfp[K_RIX].ivalue (offset is 0x8)
	// pop eax;


	// offset is different for each types
	if (argv[0].sfpidx == -1) {
		switch (argv[0].type) {
		case CLASS_Int:
			function[fidx++] = 0x58; // pop eax
			// mov eax --> 0x8(%ebx)
			function[fidx++] = 0x89; // mov r+disp r
			function[fidx++] = 0x43; // eax: ebx
			function[fidx++] = 0x8; // 0x8
			break;
		case CLASS_Float:
			//fstpl 0x8(ebx)
			WRITE_HEX(0xdd);
			WRITE_ASM(MOD_PLUS8, _EBX, _EBX);
			WRITE_HEX(0x8);
			break;
		}
	}

	// from here, closing this function
	// close stack; add 0xXX esp
 STEP_OUT:
	WRITE_HEX(0x83);
	WRITE_HEX(0xc4);
	WRITE_HEX((unsigned char)(stacksize + 0x8));

	// restore ebx
	WRITE_HEX(0x5b); // pop ebx
	WRITE_HEX(0x5d);	// pop ebp;

	// ret $0x4
	WRITE_HEX(0xc2); // ret
	WRITE_HEX(0x4);
	WRITE_HEX(0x0);

	//	return function;
	return blk;
}
#endif/*K_USING_FFIDSL*/
//typedef struct {
//	knh_type_t type;
//	knh_short_t sfpidx;
//	void *conv_func;
//} knh_ffiparam_t;  // for ffi
// sfp: -1 --> return
// sfp: 1+ --> arguments

#define FUNC_SIZE (256)

#ifndef __x86_64__

static void *knh_generateCallbackFunc32(CTX ctx, void *tmpl, void *dest, knh_Func_t *fo)
{
  knh_uchar_t *function = NULL;
#if !defined(K_USING_WINDOWS) && !defined(K_USING_BTRON)
  function = (knh_uchar_t*)tmpl;
  //search -1
  int i, marker = -1, jmp_pos = -1, shrink_pos = -1;
  for (i = 0; i < FUNC_SIZE; i++) {
	//	fprintf(stderr, "dump:%02x\n", *(int*)&function[i]);
	if (*(int*)&function[i] == -1 && marker == -1) {
	  marker = i;
	  i += 3;
	}

	// for thunk.bx, they call thunk, and add.
	if (function[i] == 0xe8 && function[i+5] == 0x81 && function[i+6] == 0xc3){
	  shrink_pos = i;
	  continue;
	} else 	if (function[i] == 0xe8 && *(int*)&function[i+1] < 0 && jmp_pos < 0) {
	  jmp_pos = i;
	}
	// loop condition
	if (function[i] == 0x5d && function[i + 1] == 0xc3) {
	  i += 14;
	  break;
	}
	if (i != 0 && function[i] == 0x55 && function[i + 1] == 0x89 && function[i+2] == 0xe5) {
	  // next prologue
	  i -= 1;
	  break;
	}
  }
  //  fprintf(stderr, "i=%d\n", i);
  function = (knh_uchar_t*)knh_xmalloc(ctx, i);
  memcpy(function, tmpl, i);
  //  fprintf(stderr, "marker:%d, jmp:%d, shrink:%d\n", marker, jmp_pos, shrink_pos);
  knh_uchar_t buf[FUNC_SIZE]={0};
  //  dumpBinary(function, 48);
  size_t funcsize = i;
  if (shrink_pos > 0) {
	// shrinking call xxx, add xxx
	// they always moving ebx;
	memcpy(buf, &function[shrink_pos + 11], funcsize - (shrink_pos + 11));
	function[shrink_pos] = 0x90;
	memcpy(&function[shrink_pos + 1], buf, funcsize - (shrink_pos + 11));
	marker -= 10;
	jmp_pos -= 10;
	funcsize -= 10;
	//	fprintf(stderr, "marker:%d, jmp:%d, shrink:%d\n", marker, jmp_pos, shrink_pos);
  }

  if (marker > 0){
	*(intptr_t*)&function[marker] = (intptr_t)fo;
  }


  //  fprintf(stderr, "jpos:%x\n", *(int*)&function[jmp_pos]);
  if (jmp_pos > 0) {
	//	int disp =  (intptr_t)dest - (intptr_t)&function[jmp_pos + 5];
	// it is too far.. make far calling
	function[jmp_pos] = 0xb8;
	*(intptr_t*)&function[jmp_pos+1] = (intptr_t)dest;
	memcpy(buf, &function[jmp_pos + 5], funcsize - (jmp_pos + 5));
	// insert 2 values;
	//before jmp!
	size_t seekidx = jmp_pos + 5;
	function[seekidx] = 0x90;
	function[seekidx+1] = 0xff;
	function[seekidx+2] = 0xd0;
	// shift the rest;
	memcpy(&function[seekidx+3], buf, funcsize - (seekidx+3));
	//	dumpBinary(function, 48);
  }

#endif
  return function;
}
#endif

#ifdef __x86_64__
enum last_inst {
	jmp_only,
	leave_jmp,
	call_leave_ret
};
static void *knh_generateCallbackFunc64(CTX ctx, void *tmpl, void *dest, knh_Func_t *fo)
{
	knh_uchar_t *function = NULL;
#if !defined(K_USING_WINDOWS) && !defined(K_USING_BTRON)
	function = (knh_uchar_t*)tmpl;
	// search -1 (0xfffffff0fffffff0)
	int i, marker = -1, jmp_pos = -1;
	enum last_inst lastInst = call_leave_ret;
	for (i = 0; i < FUNC_SIZE; i++) {
		if (*(intptr_t*)&function[i] == 0xfffffff0fffffff0 && marker == -1) {
			marker = i;
			i += 8;
		}
		// XXX ??? function[i] == 0xe8 && 0x66
		/* jmp instruction
		 * e8 00 00 00  */
		if (function[i] == 0xe8 /*&& function[i] == 0x66*/) {
			jmp_pos = i;
		}
		// jmppos for x86_64
		// c9 : leave
		// e9 xxxxxxxx : jmp xxxxxxxx
		if(function[i] == 0xc9 && function[i + 1] == 0xe9) {
			lastInst = leave_jmp;
			jmp_pos = i + 1;
			i += 4; // rel address is 4 bytes
			break; 
		}
		//linux amd64
		if (function[i] == 0xe9 && *(int*)&function[i+1] < 0) {
			lastInst = jmp_only;
			jmp_pos = i;
			i += 5 + 4;
			break;
		}

		// typical epilogue.
		if (function[i] == 0xc9 && function[i+1] == 0xc3) {
			i += 2;
			break;
		}
	}
	// copy function
	size_t funcsize = i;
	function = (knh_uchar_t*)knh_xmalloc(ctx, funcsize);
	memcpy(function, tmpl, i);
	if (marker > 0) {
		memcpy(&function[marker], &fo, sizeof(void*));
	}
	// now, patch
	if (jmp_pos > 0) {
		//linux
		// happend to use rax
		// movq 0x(dest) %rax
		function[jmp_pos+0] = 0x48;
		function[jmp_pos+1] = 0xb8;
		union {
			unsigned char code[sizeof(intptr_t)];
			intptr_t v;
		} code;
		code.v = (intptr_t) dest;
		memcpy(function+(jmp_pos+2), code.code, sizeof(code));

		size_t seekidx = jmp_pos + 2 + sizeof(intptr_t);
		// call
		switch (lastInst) {
		case leave_jmp:
			/* leave */
			//function[seekidx++] = 0xc9;
			/* fall through */
		case jmp_only: /*case leave_jmp:*/
			/* jmp *%rax */
			function[seekidx+0] = 0xff;
			function[seekidx+1] = 0xe0;
			break;
		case call_leave_ret:
			/* callq *%rax */
			function[seekidx+0] = 0xff;
			function[seekidx+1] = 0xd0;
			/* leave */
			function[seekidx+2] = 0xc9;
			/* ret */
			function[seekidx+3] = 0xc3;
			break;
		}
	}

#endif /* tron, lkm */
	return function;
}
#endif /*__x86_64__ */

void *knh_copyCallbackFunc(CTX ctx, void *tmpl, void *dest, knh_Func_t *fo)
{
	void *function = NULL;
#ifdef __x86_64__
	function = knh_generateCallbackFunc64(ctx, tmpl, dest, fo);
#else
	function = knh_generateCallbackFunc32(ctx, tmpl, dest, fo);
#endif
	return function;
}

/*
static void dumpBinary(unsigned char *ptr, size_t size)
{
	int i = 0;
	unsigned char byte;
	for (i = 0; i < size; i++) {
		byte = ptr[i];
		fprintf(stderr, "%02x ", byte);
		if (i % 16 == 15) fprintf(stderr, "\n");
	}
}
*/

//knh_Fmethod knh_makeFmethod(CTX ctx, void *func, int argc, knh_ffiparam_t *argv)
//{
//#ifdef K_USING_FFIDSL
////	void *f = knh_generateWrapper(ctx, (void*)func, argc, argv);
//	knh_xblock_t* blk = knh_generateWrapper(ctx, (void*)func, argc, argv);
//	void *f = blk->block;
//	if (f != NULL) {
//		//		dumpBinary(f, 128);
//		return (void*)f;
//	}
//#endif
//	return NULL; /* if FAILED */
//}

//const char* TT__(knh_term_t tt);
///* ------------------------------------------------------------------------ */
//
//void Method_linkFFI(CTX ctx, knh_Method_t *mtd, knh_Stmt_t *stmt)
//{
//	int argc = 0;
//	knh_ffiparam_t params[16] = {};
//	knh_Token_t *tkF = NULL;
//	if(STT_(stmt) != STT_FUNCCALL) goto L_ERROR;
//	tkF = tkNN(stmt, 0);
//	DBG_P("TT=%s, '%s'", TT__(tkF->tt), S_tochar(tkF->text));
//	if(TT_(tkF) != TT_URN) {
//		set_ffireturn(ctx, params, mtd, tkF);
//		if(DP(stmt)->size != 3) {
//			goto L_ERROR;
//		}
//		argc = 1;
//		stmt = stmtNN(stmt, 2);
//		tkF = tkNN(stmt, 0);
//	}
//	if(TT_(tkF) == TT_URN) {
//		size_t i;
//		void *cfunc = knh_lookupLibraryFunc(ctx, S_tobytes(tkF->text));
//		if(cfunc == NULL) {
//			goto L_ERROR;
//		}
//		if(argc == 0) {
//			set_ffireturn(ctx, params + argc, mtd, NULL);
//			argc = 1;
//		}
//		for(i = 2; (i < DP(stmt)->size && argc < 16); i++) {
//			if(set_ffiparam(ctx, params + argc, mtd, tkNN(stmt, i))) {
//				argc++;
//			}
//			else {
//				goto L_ERROR;
//			}
//		}
//		{
//			knh_Fmethod fmethod = knh_makeFmethod(ctx, cfunc, argc, params);
//			if(fmethod != NULL) {
//				knh_Method_setFunc(ctx, mtd, fmethod);
//				return;
//			}
//		}
//	}
//	L_ERROR:;
//	DBG_P("ERROR");
//}
//
///* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
