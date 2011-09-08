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

#ifndef KONOHA_GLUE_H_
#define KONOHA_GLUE_H_

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* driver */

//typedef struct {
//	int   type;
//	const char *name;
//} knh_DSPI_t ;
//
#define K_DSPI_PATH             1
#define K_DSPI_CONVTO           2
#define K_DSPI_CONVFROM         3
//#define K_DSPI_STREAM           4
#define K_DSPI_REGEX            5
#define K_DSPI_QUERY            6
#define K_DSPI_MAP              7
//
//#define IS_DSPI(c)   (0 < c && c < 8)
//#define K_DEFAULT_DSPI          STEXT("")

/* ------------------------------------------------------------------------ */
/* K_DSPI_PATH */


/* ------------------------------------------------------------------------ */
/* K_BCONV_DSPI */


/* ------------------------------------------------------------------------ */
/* K_DSPI_STREAM */

/* ------------------------------------------------------------------------ */
/* K_DSPI_QUERY */

typedef struct knh_QueryDPI_t {
	int   type;
	const char *name;
	knh_qconn_t* (*qopen)(CTX ctx, knh_bytes_t);
	knh_qcur_t* (*qexec)(CTX ctx, knh_qconn_t *, knh_bytes_t, knh_ResultSet_t*);
	void   (*qclose)(CTX ctx, knh_qconn_t *);
	int    (*qcurnext)(CTX, knh_qcur_t *, knh_ResultSet_t*);
	void   (*qcurfree)(knh_qcur_t *);
} knh_QueryDPI_t;

/* ------------------------------------------------------------------------ */
/* K_DSPI_MAP */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ConstData  */
/* ------------------------------------------------------------------------ */

typedef struct {
	const char *name;
	knh_int_t ivalue;
} knh_IntData_t;

typedef struct {
	const char *name;
	knh_float_t fvalue;
} knh_FloatData_t;

typedef struct {
	const char *name;
	const char *value;
} knh_StringData_t;

typedef struct {
	const char *name;
	knh_Fmethod ptr;
} knh_FuncData_t;

#define _DATA(s)    (knh_intptr_t)(s)
#define DATA_END      0
#define DATA_STRUCT0   1
#define DATA_CLASS0    2
#define DATA_CPARAM    3
#define DATA_GENERICS  4
#define DATA_EXPT      5
#define DATA_METHOD0   6
#define DATA_METHOD    7
#define DATA_TYPEMAP     8
#define DATA_PARAM     9

typedef knh_intptr_t knh_data_t;

/* ------------------------------------------------------------------------ */

typedef struct knh_LoaderAPI_t {
	/* global */
	void (*loadData)(CTX, const knh_data_t *, knh_ParamArray_t **);
	void (*loadFuncData)(CTX, const knh_FuncData_t *);
	/* constant */
	void (*loadIntData)(CTX, knh_NameSpace_t *ns, const knh_IntData_t *);
	void (*loadFloatData)(CTX, knh_NameSpace_t *ns, const knh_FloatData_t *);
	void (*loadStringData)(CTX, knh_NameSpace_t *ns, const knh_StringData_t *);
	void (*loadClassIntConst)(CTX, knh_class_t cid, const knh_IntData_t *);
	void (*loadClassFloatConst)(CTX, knh_class_t cid, const knh_FloatData_t *);
	void (*loadStringClassConst)(CTX, knh_class_t cid, const knh_StringData_t *);
	void (*setPackageProperty)(CTX, const char*, const char*);
	void (*setPackageIntProperty)(CTX, const char*, knh_int_t);
	void (*setPackageFloatProperty)(CTX, const char*, knh_float_t);
	/* namespace */
//	void (*setRegexSPI)(CTX, knh_NameSpace_t *ns, const knh_RegexSPI_t *);
//	void (*addLinkClass)(CTX, knh_NameSpace_t *ns, const char*, knh_class_t cid);
	void (*addStreamDPI)(CTX, const char*, const knh_StreamDPI_t *);
	void (*addQueryDPI)(CTX, const char *, const knh_QueryDPI_t *);
	void (*addMapDPI)(CTX,   const char *, const knh_MapDPI_t*);
	void (*addConverterDPI)(CTX, const char *, const knh_ConverterDPI_t*, const knh_ConverterDPI_t*);
} knh_LoaderAPI_t;

#define RETURN_PKGINFO(NAME) {\
		static const knh_PackageDef_t pkginfo_ = {K_BUILDID, K_API2_CRC32, NAME};\
		return &pkginfo_;\
	}\

typedef struct {
	size_t buildid;
	size_t crc32;
	const char *name;     /* pacakge name */
} knh_PackageDef_t;

typedef const knh_PackageDef_t* (*knh_Fpkginit)(CTX, const knh_LoaderAPI_t *);
typedef void (*knh_Fpkgload)(CTX, const knh_LoaderAPI_t *, knh_NameSpace_t *ns);
typedef void (*knh_Fclassdef)(CTX, knh_class_t, knh_ClassDef_t*);
typedef void (*knh_Fconstdef)(CTX, knh_class_t, const knh_LoaderAPI_t*);

/* ------------------------------------------------------------------------ */
/* new version */

#define Boolean_to(T, a)           ((T)a.bvalue)
#define Int_to(T, a)               ((T)a.ivalue)
#define Float_to(T, a)             ((T)a.fvalue)
#define String_to(T, a)            ((T)S_totext(a.s))
#define StringNull_to(T, a, def)   ((T)(IS_bString(a.o) ? S_totext(a.s) : def))
#define RawPtr_to(T, a)            ((T)((a.p)->rawptr))
//#define RawPtrNull_to(T, a, def)   (IS_bRawPtr(a.o) ? ((T)((a.p)->rawptr)) : (def))
#define Class_tocid(a)             ((a.c)->cid)

/* ------------------------------------------------------------------------ */
/* closure macros, added by @shinpei_NKT */
#define CLOSURE_start(argc)			   \
  CTX lctx = (CTX)knh_getCurrentContext(); \
  knh_intptr_t thisidx = K_CALLDELTA; \
  BEGIN_LOCAL(lctx, lsfp, thisidx + argc + 1);


#define CLOSURE_putInt(idx, val) \
  lsfp[idx].ivalue = val

#define CLOSURE_putFloat(idx, val) \
  lsfp[idx].fvalue = val

#define CLOSURE_putArg(idx, type, val) \
  CLOSURE_put##type(idx, val)


#define CLOSURE_call(fo) \
  if (fo->baseNULL != NULL) {					\
	KNH_SETv(lctx, fo, fo->baseNULL);			\
  }												\
  klr_setmtdNC(lctx, lsfp[K_MTDIDX], fo->mtd);	\
  KNH_SELFCALL(lctx, lsfp, fo->mtd, K_RTNIDX);


#define CLOSURE_getInt() \
  lsfp[K_RTNIDX].ivalue

#define CLOSURE_getFloat() \
  lsfp[K_RTNIDX].fvalue

#define CLOSURE_getReturn(type) \
  CLOSURE_get##type()


#define CLOSURE_end(exp) \
  END_LOCAL(lctx, lsfp); \
  exp

#ifndef __x86_64__
#define CALLBACK_MARKER (-1)
#else
#define CALLBACK_MARKER (0xfffffff0fffffff0)
#endif
/* ------------------------------------------------------------------------ */

#ifdef K_EXPORTS

#define RETURN_(vv) {\
		ctx->spi->setsfpSPI(ctx, sfp+_rix, vv);\
		return; \
	}\

#else

#define RETURN_(vv) {\
		KNH_SETv(ctx, sfp[_rix].o, vv);\
		KNH_SAFEPOINT(ctx, sfp);\
		return; \
	}\

#endif

#define RETURNd_(d) {\
		sfp[_rix].ndata = d; \
		return; \
	}\

#define RETURNb_(c) {\
		sfp[_rix].bvalue = c; \
		return; \
	}\

#define RETURNi_(c) {\
		sfp[_rix].ivalue = c; \
		return; \
	}\

#define RETURNf_(c) {\
		sfp[_rix].fvalue = c; \
		return; \
	}\

#define RETURNvoid_() {\
		(void)_rix;\
		return; \
	}\


#ifdef K_EXPORTS

#define ITREND_() {\
		ctx->spi->closeItrSPI(ctx, sfp[0].it);\
		return 0; \
	}\

#define ITRNEXT_(vv) {\
		ctx->spi->setsfpSPI(ctx, sfp+rix_, vv);\
		return 1; \
	}\

#else

#define ITREND_() {\
		knh_Iterator_close(ctx, sfp[0].it);\
		return 0; \
	}\

#define ITRNEXT_(vv) {\
		KNH_SETv(ctx, sfp[_rix].o, vv);\
		return 1; \
	}\

#endif

#define ITRNEXTd_(d) {\
		sfp[_rix].ndata = d;\
		return 1; \
	}\

#define ITRNEXTi_(n) {\
		sfp[_rix].ivalue = n;\
		return 1; \
	}\

#define ITRNEXTf_(n) {\
		sfp[_rix].fvalue = n;\
		return 1; \
	}\

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /*KONOHA_GLUE_H_*/
