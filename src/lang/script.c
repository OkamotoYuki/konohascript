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

#define USE_RCinc 1

#define USE_STEXT 1
#define USE_B     1
#define USE_bytes_first       1
#define USE_bytes_index       1
#define USE_bytes_last        1
#define USE_bytes_index       1
#define USE_bytes_next        1
#define USE_bytes_rindex      1
#define USE_bytes_equals      1
#define USE_bytes_startsWith  1
//#define USE_bytes_endsWith    1

#define USE_cwb_open      1
#define USE_cwb_tobytes   1
#define USE_cwb_write     1

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* [namespace] */

knh_NameSpace_t* new_NameSpace(CTX ctx, knh_NameSpace_t *nsNULL)
{
	knh_NameSpace_t* ns = new_(NameSpace);
	if(nsNULL != NULL) {
		DBG_ASSERT(IS_NameSpace(nsNULL));
		KNH_INITv(DP(ns)->parentNULL, nsNULL);
		KNH_SETv(ctx, DP(ns)->nsname, DP(nsNULL)->nsname);
		DP(ns)->regexSPI = DP(nsNULL)->regexSPI;
	}
	return ns;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_NameSpace_getcid(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t sname)
{
	if(knh_bytes_equals(sname, STEXT("Script"))) {
		return O_cid(knh_getGammaScript(ctx));
	}
	L_TAIL:
	if(DP(ns)->name2cidDictSetNULL != NULL) {
		knh_uintptr_t cid = knh_DictSet_get(ctx, DP(ns)->name2cidDictSetNULL, sname);
		if(cid > 0) return (knh_class_t)(cid-1);
	}
	if(DP(ns)->parentNULL != NULL) {
		ns = DP(ns)->parentNULL;
		goto L_TAIL;
	}
	return knh_getcid(ctx, sname);
}

/* ------------------------------------------------------------------------ */
/* [stmt] */

knh_flag_t knh_Stmt_flag_(CTX ctx, knh_Stmt_t *stmt, knh_bytes_t name, knh_flag_t flag)
{
	if(IS_Map(DP(stmt)->metaDictCaseMap)) {
		Object *v = knh_DictMap_getNULL(ctx, DP(stmt)->metaDictCaseMap, name);
		return (v != NULL) ? flag : 0;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */
/* [function] */

//static
//void NameSpace_setFuncClass(CTX ctx, knh_NameSpace_t *ns, knh_methodn_t mn, knh_class_t c)
//{
//	if(!MN_isGETTER(mn) && !MN_isSETTER(mn)) {
//		if(!IS_DictSet(DP(ns)->func2cidDictSet)) {
//			KNH_SETv(ctx, DP(ns)->func2cidDictSet, new_DictSet(ctx, 0));
//		}
//		knh_DictSet_set(ctx, DP(ns)->func2cidDictSet, knh_getFieldName(ctx, MN_toFN(mn)), (knh_uintptr_t)(c+1));
//	}
//}

/* ------------------------------------------------------------------------ */

knh_class_t knh_NameSpace_getFuncClass(CTX ctx, knh_NameSpace_t *ns, knh_methodn_t mn)
{
	if(!MN_isGETTER(mn) && !MN_isSETTER(mn)) {
		knh_bytes_t name = S_tobytes(knh_getFieldName(ctx, MN_toFN(mn)));
		L_TAIL:
		if(DP(ns)->func2cidDictSetNULL != NULL) {
			knh_uintptr_t cid = knh_DictSet_get(ctx, DP(ns)->func2cidDictSetNULL, name);
			if(cid != 0) {
				return (knh_class_t)(cid-1);
			}
		}
		if(DP(ns)->parentNULL != NULL) {
			ns = DP(ns)->parentNULL;
			goto L_TAIL;
		}
	}
	return CLASS_unknown; /* if not found */
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_NameSpace_gettype(CTX ctx, knh_NameSpace_t *ns, knh_bytes_t name)
{
	if(name.ustr[0] == 'v') {
		if(name.len == 4 && name.ustr[1] == 'o' &&
				name.ustr[2] == 'i' && name.ustr[3] == 'd') return TYPE_void;
		if(name.len == 3 && name.ustr[1] == 'a' && name.ustr[2] == 'r') {
			return TYPE_var;
		}
	}
	return knh_NameSpace_getcid(ctx, ns, name);
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_NameSpace_tagcid(CTX ctx, knh_NameSpace_t *o, knh_class_t cid, knh_bytes_t tag)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	knh_class_t bcid = ClassTBL(cid)->bcid;
	knh_printf(ctx, cwb->w, "%C:%B", bcid, tag);
	cid = knh_NameSpace_getcid(ctx, o, knh_cwb_tobytes(cwb));
	knh_cwb_close(cwb);
	return cid;
}

/* ------------------------------------------------------------------------ */
/* [include] */

static knh_bool_t INCLUDE_eval(CTX ctx, knh_Stmt_t *stmt, knh_type_t reqt, knh_Array_t *resultsNULL)
{
	int isCONTINUE = 1;
	knh_bytes_t include_name = S_tobytes(tkNN(stmt, 0)->text);
	if(DP(ctx->gma)->dlhdr != NULL && knh_bytes_startsWith(include_name, STEXT("func:"))) {
		const char *funcname = knh_bytes_next(include_name, ':').text;
		knh_Fpkgload pkgload = (knh_Fpkgload)knh_dlsym(ctx, LOG_DEBUG, DP(ctx->gma)->dlhdr, funcname);
		if(pkgload != NULL) {
			pkgload(ctx, knh_getPackageAPI(), NULL);
		}
		else {
			knh_Stmt_toERR(ctx, stmt, ERROR_NotFound(ctx, "loader function", funcname));
			isCONTINUE = 0;
		}
	}
	else if(knh_bytes_strcasecmp(include_name, STEXT("nativelink")) == 0) {
		knh_bytes_t path = S_tobytes(knh_getURN(ctx, ULINE_uri(stmt->uline)));
		if(path.ustr[0] != '(' && !knh_bytes_startsWith(path, STEXT("http://"))) {
			knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
			knh_index_t idx = knh_bytes_rindex(path, '.'); //'.'
			if(idx > 0) path = knh_bytes_first(path, idx);
			knh_cwb_write(ctx, cwb, path);
			DP(ctx->gma)->dlhdr = knh_cwb_dlopen(ctx, LOG_NOTICE, cwb);
			knh_cwb_close(cwb);
			if(DP(ctx->gma)->dlhdr != NULL) {
				knh_Fpkginit pkginit = (knh_Fpkginit)knh_dlsym(ctx, LOG_DEBUG, DP(ctx->gma)->dlhdr, "init");
				if(pkginit != NULL) {
					const knh_PackageDef_t *pkgdef = pkginit(ctx);
					if(pkgdef->crc32 != K_API2_CRC32) {
						DP(ctx->gma)->dlhdr = NULL;
						knh_Stmt_toERR(ctx, stmt, ERROR_IncompatiblePackage(ctx, include_name, pkgdef));
						isCONTINUE = 0;
					}
				}
				else {
					const knh_PackageDef_t pkgdef = {};
					DP(ctx->gma)->dlhdr = NULL;
					knh_Stmt_toERR(ctx, stmt, ERROR_IncompatiblePackage(ctx, include_name, &pkgdef));
					isCONTINUE = 0;
				}
				goto L_RETURN;
			}
			knh_Stmt_toERR(ctx, stmt, ERROR_NotFound(ctx, "package", path.text));
			isCONTINUE = 0;
		}
	}
	else {
		if(knh_bytes_index(include_name, ':') > 0) {
			isCONTINUE = knh_loadScript(ctx, include_name, reqt, resultsNULL);
		}
		else {
			knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
			knh_Bytes_write(ctx, cwb->ba, STEXT("script:"));
			knh_Bytes_write(ctx, cwb->ba, include_name);
			isCONTINUE = knh_loadScript(ctx, knh_cwb_tobytes(cwb), reqt, resultsNULL);
			knh_cwb_close(cwb);
		}
	}
	L_RETURN:;
	knh_Stmt_done(ctx, stmt);
	return isCONTINUE;
}

/* ------------------------------------------------------------------------ */
/* [using] */

static knh_Package_t *new_Package(CTX ctx, knh_String_t *nsname)
{
	knh_Package_t *pkg = new_(Package);
	KNH_INITv(pkg->ns, new_NameSpace(ctx, NULL));
	KNH_SETv(ctx, DP(pkg->ns)->nsname, nsname);
	KNH_INITv(pkg->script, new_(Script));
	return pkg;
}

static void Gamma_swapPackage(CTX ctx, knh_Package_t *pkg)
{
	knh_NameSpace_t *ns = KNH_GMA_NS;
	knh_Script_t *script = DP(ctx->gma)->script;
	KNH_GMA_NS = pkg->ns;
	pkg->ns = ns;
	DP(ctx->gma)->script = pkg->script;
	pkg->script = script;
}

knh_bool_t knh_loadScriptPackage(CTX ctx, knh_bytes_t path)
{
	int res = 1;
	knh_bytes_t name = knh_bytes_last(path, sizeof("pkg:") - 1);
	knh_NameSpace_t *ns = KNH_GMA_NS;
	knh_Package_t *pkg = (knh_Package_t*)knh_DictMap_getNULL(ctx, DP(ctx->sys)->PackageDictMap, name);
	if(pkg == NULL) {
		knh_PathDSPI_t *dspi = knh_NameSpace_getPathDSPINULL(ctx, ns, path);
		if(dspi->exists(ctx, path, ns) != PATH_unknown) {
			knh_String_t *nameS = new_S(ctx, name);
			knh_Array_t * a = KNH_TNULL(Array);
			pkg = new_Package(ctx, nameS);
			knh_DictMap_set(ctx, DP(ctx->sys)->PackageDictMap, nameS, pkg);
			Gamma_swapPackage(ctx, pkg);
			res = knh_loadScript(ctx, path, TYPE_void, a);
			knh_Array_clear(ctx, a, 0);
			Gamma_swapPackage(ctx, pkg);
		}
		else {
			res = 0;
		}
	}
	if(pkg != NULL) {
		knh_NameSpace_t *ns = knh_getGammaNameSpace(ctx);
		knh_NameSpace_t *pkgns = SP(pkg)->ns;
		if(DP(pkgns)->regexSPI != DP(pkgns)->strregexSPI) {
			DP(ns)->regexSPI = DP(pkgns)->regexSPI;
		}
	}
	return res;
}

/* ------------------------------------------------------------------------ */

static void NameSpace_setcid(CTX ctx, knh_NameSpace_t *ns, knh_String_t *name, knh_class_t cid, int isOVERRIDE)
{
	if(DP(ns)->name2cidDictSetNULL == NULL) {
		KNH_INITv(DP(ns)->name2cidDictSetNULL, new_DictSet0(ctx, 0, 0/*isCaseMap*/, "NameSpace.name2cid"));
	}
	else {
		knh_class_t oldcid = knh_NameSpace_getcid(ctx, ns, S_tobytes(name));
		if(oldcid != CLASS_unknown && cid != oldcid) {
			ErrorOverrideName(ctx, CLASS__(oldcid), CLASS__(cid), isOVERRIDE);
			KNH_TODO("error handling");
			if(!isOVERRIDE) return;
		}
	}
	knh_DictSet_set(ctx, DP(ns)->name2cidDictSetNULL, name, (knh_uintptr_t)(cid+1));
}

static int StmtUSINGCLASS_eval(CTX ctx, knh_Stmt_t *stmt, size_t n)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	knh_Bytes_write(ctx, cwb->ba, STEXT("pkg:"));
	knh_Token_t *tkPKG = tkNN(stmt, n), *tkN;
	knh_Bytes_write(ctx, cwb->ba, S_tobytes((tkPKG)->text));
	while(1) {
		tkN = tkNN(stmt, ++n);
		if(TT_(tkN) == TT_ASIS) break;
		if(TT_(tkN) == TT_DOT) continue;
		if(TT_(tkN) == TT_NAME) {
			knh_Bytes_putc(ctx, cwb->ba, '.');
			knh_Bytes_write(ctx, cwb->ba, S_tobytes((tkN)->text));
			continue;
		}
		break;
	}
	KNH_SETv(ctx, (tkPKG)->data, knh_cwb_newString(ctx, cwb));
	if(knh_loadScriptPackage(ctx, S_tobytes((tkPKG)->text))) {
		knh_NameSpace_t *ns = knh_getGammaNameSpace(ctx);
		int isOVERRIDE = knh_Stmt_flag(ctx, stmt, "Override", 1);
		if(TT_(tkN) == TT_MUL) {
			knh_bytes_t pkgname = knh_bytes_last(S_tobytes((tkPKG)->text), 4/* strlen("pkg:") */);
			size_t cid;
			for(cid = 0; cid < ctx->share->sizeClassTBL; cid++) {
				if(ClassTBL(cid)->lname == NULL) continue;
				if(class_isPrivate(cid) && class_isGenerics(ctx, cid)) continue;
				knh_bytes_t cname = S_tobytes(ClassTBL(cid)->lname);
				if(knh_bytes_startsWith(cname, pkgname)
						&& cname.ustr[pkgname.len] == '.' && isupper(cname.ustr[pkgname.len+1])) {
					NameSpace_setcid(ctx, ns, ClassTBL(cid)->sname, (knh_class_t)cid, isOVERRIDE);
				}
			}
		}
		else if(TT_(tkN) == TT_UNAME) {
			knh_class_t newcid;
			knh_String_t* cname = (tkN)->text;
			knh_Bytes_write(ctx, cwb->ba, knh_bytes_last(S_tobytes((tkPKG)->text), sizeof("pkg")));
			knh_Bytes_putc(ctx, cwb->ba, '.');
			knh_Bytes_write(ctx, cwb->ba, S_tobytes(cname));
			newcid = knh_getcid(ctx, knh_cwb_tobytes(cwb));
			if(newcid == CLASS_unknown) {
				KNH_SETv(ctx, (tkPKG)->data, knh_cwb_newString(ctx, cwb));
				goto L_ERROR;
			}
			else {
//#ifdef TT_AS
//				if(n+2 < DP(stmt)->size &&
//					TT_(tkNN(stmt, n+1]) == TT_AS && TT_(DP(stmt)->tokens[n+2)) == TT_UNAME) {
//					cname = (tkNN(stmt, n+2))->text;
//				}
//#endif
				NameSpace_setcid(ctx, ns, cname, newcid, isOVERRIDE);
			}
			knh_cwb_clear(cwb, 0);
		}
		return 1;
	}
	L_ERROR:;
	while(n + 1 < DP(stmt)->size) {
		if(TT_(tkNN(stmt, n)) == TT_OR) return 0;
		n++;
	}
	knh_Stmt_toERR(ctx, stmt, ERROR_NotFound(ctx, "package", S_tochar((tkPKG)->text)));
	return 0;
}

/* ------------------------------------------------------------------------ */

//static int knh_StmtUALIAS_decl(CTX ctx, knh_Stmt_t *stmt)
//{
//	DBG_DUMP(ctx, stmt, KNH_NULL, "decl");
//	TODO();
//	return 1;
//}

///* ------------------------------------------------------------------------ */
//
//static
//char *knh_format_classurn(CTX ctx, char *buf, size_t bufsiz, knh_class_t bcid, knh_bytes_t urn)
//{
//	knh_snprintf(buf, bufsiz, KNH_SEMANTICS_FMT, CLASS__(bcid), urn.buf);
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//static
//void NameSpace_setTagName(CTX ctx, knh_NameSpace_t *o, knh_String_t *name, knh_class_t cid)
//{
//	KNH_ASSERT(IS_NameSpace(o));
//	DBG_ASSERT_cid(cid);
//	knh_DictSet_set(ctx, DP(o)->name2cidDictSet, name, (knh_uintptr_t)(cid+1));
////	knh_bytes_t n = S_tobytes(name);
////	knh_index_t loc = knh_bytes_index(n, ':');
////	if(loc != -1) {
////		n = knh_bytes_last(n, loc+1);
////		if(isupper(n.ustr[0])) {
////			knh_DictSet_set(ctx, DP(o)->name2cidDictSet, new_String(ctx, n, name), (knh_uintptr_t)(cid+1));
////		}
////	}
//}

/* ------------------------------------------------------------------------ */

//static int knh_StmtXCLASS_decl(CTX ctx, knh_Stmt_t *stmt, knh_class_t bcid)
//{
//
//	knh_NameSpace_t *ns = knh_getGammaNameSpace(ctx);
//	knh_Token_t *tkclassn = tkNN(stmt, 0);
//	knh_Token_t *tkurn = tkNN(stmt, 1);
//
//	char bufcu[CLASS__AME_BUFSIZ];
//	knh_format_classurn(ctx, bufcu, sizeof(bufcu), bcid, knh_getURNAlias(ctx, knh_Token_tobytes(ctx, tkurn)));
//
//	knh_class_t cid = knh_findcid(ctx, B(bufcu));
//	if(cid == bcid || cid == CLASS_unknown) {
//		knh_Token_perror(ctx, tkurn, KC_EWARN, _("resource not found: %L"), tkurn);
//		cid = bcid;
//	}
//
//	knh_class_t oldcid = knh_NameSpace_findcid(ctx, ns, knh_Token_tobytes(ctx, tkclassn));
//	if(oldcid != CLASS_unknown && cid != oldcid) {
//		KNH_SYSLOG(ctx, LOG_WARNING, _("overriding %s"), knh_Token_tobytes(ctx, tkclassn));
//	}
//
//	KNH_ASSERT(IS_String((tkclassn)->data));
//	NameSpace_setTagName(ctx, ns, (tkclassn)->text, cid);
//	TODO();
//	return 1;
//}

/* ------------------------------------------------------------------------ */

//static int knh_StmtUVOCAB_decl(CTX ctx, knh_Stmt_t *stmt)
//{
//	return knh_StmtXCLASS_decl(ctx, stmt, CLASS_String);
//}

/* ------------------------------------------------------------------------ */

//static int knh_StmtUENUM_decl(CTX ctx, knh_Stmt_t *stmt)
//{
//	return knh_StmtXCLASS_decl(ctx, stmt, CLASS_Int);
//}

/* ------------------------------------------------------------------------ */

//static int knh_StmtUUNIT_decl(CTX ctx, knh_Stmt_t *stmt)
//{
//	return knh_StmtXCLASS_decl(ctx, stmt, CLASS_Float);
//}

/* ------------------------------------------------------------------------ */

//static int knh_StmtUFUNC_decl(CTX ctx, knh_Stmt_t *stmt)
//{
//	knh_NameSpace_t *ns = knh_getGammaNameSpace(ctx);
//	knh_Token_t *tk = tkNN(stmt, 0);
//	knh_bytes_t name = knh_Token_tobytes(ctx, tk);
//	if(SP(tk)->tt == TT_LONGNAME) {
//		knh_index_t loc = knh_bytes_rindex(name, '.');
//		knh_class_t cid = knh_NameSpace_findcid(ctx, ns, knh_bytes_first(name, loc));
//		if(cid == CLASS_unknown) {
//			knh_Token_perror(ctx, tk, KC_ERR, _("unknown class: %L"), tk);
//			return 0;
//		}
//		knh_methodn_t mn = knh_getmn(ctx, knh_bytes_last(name, loc+1), MN_NONAME);
//		if(mn == MN_NONAME) {
//			knh_Token_perror(ctx, tk, KC_ERR, _("unknown method: %C.%L"), cid, tk);
//			return 0;
//		}
//		NameSpace_setFuncClass(ctx, ns, mn, cid);
//	}
//	else {
//		knh_class_t cid = knh_NameSpace_findcid(ctx, ns, name);
//		if(cid == CLASS_unknown) {
//			knh_Token_perror(ctx, tk, KC_ERR, _("unknown class: %L"), tk);
//			return 0;
//		}
//		else {
//			DBG_ASSERT_cid(cid);
//			knh_Array_t *a = ClassTBL(cid)->methods;
//			size_t i;
//			for(i = 0; i < knh_Array_size(a); i++) {
//				knh_Method_t *mtd = (knh_Method_t*)knh_Array_n(a, i);
//				KNH_ASSERT(IS_Method(mtd));
//				if(!Method_isStatic(mtd)) continue;
//				NameSpace_setFuncClass(ctx, ns, (mtd)->mn, cid);
//				if(CTX_isVerbose(ctx)) {
//					KNH_SYSLOG(ctx, LOG_NOTICE, _("using %C.%M"), cid, (mtd)->mn);
//				}
//			}
//		}
//	}
//	return 1;
//}

/* ------------------------------------------------------------------------ */

//static int knh_StmtUMAPMAP_decl(CTX ctx, knh_Stmt_t *stmt)
//{
//	DBG_DUMP(ctx, stmt, KNH_NULL, "decl");
//	return 1;
//}


static knh_bool_t USING_eval(CTX ctx, knh_Stmt_t *stmt)
{
	int isCONTINUE = 1;
	size_t n = 0;
	L_TRYAGAIN:; {
		knh_Token_t *tkF = tkNN(stmt, n);
		if(TT_(tkF) == TT_NAME) {
			if(StmtUSINGCLASS_eval(ctx, stmt, n)) {
				goto L_RETURN;
			}
		}
	}
	while(n + 1 < DP(stmt)->size) {  // find next or
		knh_Token_t *tkF = tkNN(stmt, n);
		n++;
		if(TT_(tkF) == TT_OR) goto L_TRYAGAIN;
	}
	isCONTINUE = 0;
	L_RETURN:;
	knh_Stmt_done(ctx, stmt);
	return isCONTINUE;
}

/* ------------------------------------------------------------------------ */
/* [CLASS] */

static knh_flag_t knh_StmtCLASS_flag(CTX ctx, knh_Stmt_t *stmt)
{
	knh_flag_t flag = 0;
	if(IS_Map(DP(stmt)->metaDictCaseMap)) {
		flag |= knh_Stmt_flag(ctx, stmt, "Final",     FLAG_Class_Final);
		flag |= knh_Stmt_flag(ctx, stmt, "Private",   FLAG_Class_Private);
		flag |= knh_Stmt_flag(ctx, stmt, "Interface", FLAG_Class_Interface);
		flag |= knh_Stmt_flag(ctx, stmt, "Singleton", FLAG_Class_Singleton);
//		flag |= knh_Stmt_flag(ctx, stmt, "Release",   FLAG_Class_Release);
	}
	return flag;
}

/* ------------------------------------------------------------------------ */

void knh_RefTraverse(CTX ctx, knh_Ftraverse ftr)
{
#ifdef K_USING_RCGC
	int i;
	for(i = ctx->ref_size - 1; i >= 0; i--) {
		knh_Object_t *ref = ctx->refs[i];
		ftr(ctx, ref);
	}
#endif
}

static knh_bool_t CLASS_decl(CTX ctx, knh_Stmt_t *stmt)
{
	knh_class_t cid;
	knh_Token_t *tkC = tkNN(stmt, 0); // CNAME
	knh_Token_t *tkE = tkNN(stmt, 2); // extends
	knh_ClassTBL_t *ct = NULL;
	knh_NameSpace_t *ns = knh_getGammaNameSpace(ctx);
	{
		knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
		knh_Bytes_write(ctx, cwb->ba, S_tobytes(DP(ns)->nsname));
		knh_Bytes_putc(ctx, cwb->ba, '.');
		knh_Bytes_write(ctx, cwb->ba, TK_tobytes(tkC));
		cid = knh_getcid(ctx, knh_cwb_tobytes(cwb));
		if(cid == CLASS_unknown) {  // new class //
			cid = new_ClassId(ctx);
			ct = varClassTBL(cid);
			knh_setClassName(ctx, cid, knh_cwb_newString(ctx, cwb), (tkC)->text);
			ct->cflag  = knh_StmtCLASS_flag(ctx, stmt);
			ct->magicflag  = KNH_MAGICFLAG(ct->cflag);
			NameSpace_setcid(ctx, ns, (tkC)->text, cid, 1);
			KNH_INITv(ct->methods, KNH_EMPTYLIST);
			KNH_INITv(ct->tmaps, KNH_EMPTYLIST);

			// class C extends E ..
			ct->supcid = knh_Token_cid(ctx, tkE, CLASS_Object);
			if(class_isFinal(ct->supcid)) {
				knh_Stmt_toERR(ctx, stmt, ErrorExtendingFinalClass(ctx, ct->supcid));
				return 0;
			}
			ct->supTBL = ClassTBL(ct->supcid);
			ct->keyidx = ct->supTBL->keyidx;
			ct->metaidx = ct->supTBL->keyidx;
			((knh_ClassTBL_t*)ct->supTBL)->subclass += 1;
			KNH_SYSLOG(ctx, LOG_INFO, "NEW_CLASS", "*cid=%d, name='%s'", cid, CLASS__(cid));
			if(knh_StmtMETA_is(ctx, stmt, "Native")) {
				if(DP(ctx->gma)->dlhdr != NULL) {
					knh_Fclass classload = (knh_Fclass)knh_dlsym(ctx, LOG_DEBUG, DP(ctx->gma)->dlhdr, S_tochar((tkC)->text));
					const knh_ClassDef_t *cdef = classload(ctx);
					KNH_ASSERT(cdef != NULL);
					fprintf(stderr, "CDEF=%p, name=%s", cdef, cdef->name);
					ct->bcid = cid;
					ct->baseTBL = ct;
					knh_setClassDef(ct, cdef);
					ct->cflag = ct->cflag | cdef->cflag;
					ct->magicflag = KNH_MAGICFLAG(ct->cflag);
				}
				else {
					KNH_TODO("error message");
				}
			}
			else {
				knh_Object_t *obj = new_hObject_(ctx, ct);
				knh_Object_t *tmp = new_hObject_(ctx, ct);
				Object_setNullObject(obj, 1);
				ct->bcid = CLASS_Object;
				ct->baseTBL = ClassTBL(CLASS_Object);
				knh_setClassDef(ct, ct->baseTBL->ospi);
				obj->ref = NULL; tmp->ref = NULL;
				knh_setClassDefaultValue(ctx, cid, obj, NULL);
				KNH_INITv(ct->protoNULL, tmp);
			}
		}
		else {
			knh_cwb_close(cwb);
			ct = varClassTBL(cid);
			if(!(ct->bcid == CLASS_Object && ct->fields == NULL)) {
				knh_Stmt_toERR(ctx, stmt, ErrorRedefinedClass(ctx, S_tobytes((tkC)->text), cid));
				return 0;
			}
		}
	}
	(tkC)->cid = cid;
	if(IS_Tfield(cid)) {
		DBG_P("superclass=%s, fsize=%d, fcapacity=%d", CLASS__(ct->supcid), ct->supTBL->fsize, ct->supTBL->fcapacity);
		if(ct->supTBL->fcapacity > 0 && ct->fcapacity == 0) {
			ct->fields = (knh_fields_t*)KNH_MALLOC(ctx, ct->supTBL->fcapacity * sizeof(knh_fields_t));
			knh_memcpy(ct->fields, ct->supTBL->fields, ct->supTBL->fcapacity * sizeof(knh_fields_t));
			ct->fsize = ct->supTBL->fsize;
			ct->fcapacity = ct->supTBL->fcapacity;
			if(ct->fsize > 0) {
				knh_Object_t *suptmp = (knh_Object_t*)ct->supTBL->protoNULL, *supobj = ct->supTBL->defnull;
				knh_ObjectField_expand(ctx, ct->protoNULL, 0, ct->fsize);
				knh_ObjectField_expand(ctx, ct->defobj, 0, ct->fsize);
				knh_memcpy(ct->protoNULL->fields, suptmp->ref, ct->fsize*sizeof(knh_Object_t*));
				knh_memcpy(ct->defnull->ref, supobj->ref, ct->fsize*sizeof(knh_Object_t*));
#ifdef K_USING_RCGC
#ifdef K_USING_CSTACK_TRAVERSE_
#define ARG RCinc
#else
#define ARG ctx->refs
#endif
				ct->supTBL->ospi->reftrace(ctx, suptmp, ARG);
#ifndef K_USING_CSTACK_TRAVERSE_
				knh_RefTraverse(ctx, RCinc);
#endif
				ct->supTBL->ospi->reftrace(ctx, supobj, ARG);
#ifndef K_USING_CSTACK_TRAVERSE_
				knh_RefTraverse(ctx, RCinc);
#endif
#undef ARG
#endif
			}
		}
	}
	DBG_P("DP(stmt)->size=%d", DP(stmt)->size);
	if(DP(stmt)->size == 4 && TT_(tkNN(stmt, 1)) == TT_ASIS) {
		knh_Stmt_done(ctx, stmt);
	}
	return 1;
}

void SCRIPT_asm(CTX ctx, knh_Stmt_t *stmtITR);

static knh_Method_t *Script_getEvalMethod(CTX ctx, knh_Script_t *scr)
{
	knh_Method_t *mtd = knh_NameSpace_getMethodNULL(ctx, O_cid(scr), MN_LAMBDA);
	if(mtd == NULL) {
		mtd = new_Method(ctx, 0, O_cid(scr), MN_LAMBDA, NULL);
		KNH_SETv(ctx, DP(mtd)->mp, new_ParamArrayR0(ctx, TYPE_dynamic));
		knh_NameSpace_addMethod(ctx, O_cid(scr), mtd);
	}
	return mtd;
}

static knh_bool_t Stmt_eval(CTX ctx, knh_Stmt_t *stmtITR, knh_type_t reqt, knh_Array_t *resultsNULL)
{
	knh_bool_t isCONTINUE = 1;
	BEGIN_LOCAL(ctx, lsfp, 5);
	knh_Stmt_t *stmt = NULL;
	KNH_SETv(ctx, lsfp[0].o, stmtITR); // lsfp[1] stmtNEXT
	stmt = stmtITR;
	while(stmt != NULL) {
		ctx->gma->uline = stmt->uline;
		switch(STT_(stmt)) {
		case STT_NAMESPACE:
		{
			knh_NameSpace_t *ns = new_NameSpace(ctx, KNH_GMA_NS);
			KNH_SETv(ctx, KNH_GMA_NS, ns);
			isCONTINUE = Stmt_eval(ctx, stmtNN(stmt, 0), reqt, resultsNULL);
			DBG_ASSERT(KNH_GMA_NS == ns);
			DBG_ASSERT(DP(ns)->parentNULL != NULL);
			KNH_SETv(ctx, KNH_GMA_NS, DP(ns)->parentNULL);
			knh_Stmt_done(ctx, stmt);
			break;
		}
		case STT_SCRIPT:
		{
			knh_Script_t *pscript = knh_getGammaScript(ctx);
			knh_Script_t *script = new_(Script);
			KNH_SETv(ctx, DP(ctx->gma)->script, script);
			isCONTINUE = Stmt_eval(ctx, stmtNN(stmt, 0), reqt, resultsNULL);
			KNH_SETv(ctx, DP(ctx->gma)->script, pscript);
			knh_Stmt_done(ctx, stmt);
			break;
		}
//		case STT_IF: /* Conditional Compilation */
//		if(knh_Stmt_flag(ctx, stmt, "Static", 1)) {
//			knh_Gamma_initThisScript(ctx);
//			stmt = knh_StmtIF_decl(ctx, stmt);
//			isCONTINUE = 0;
//			if(stmt != NULL) {
//				isCONTINUE = knh_Stmt_eval(ctx, stmt, reqt, resultsNULL);
//			}
//			knh_Stmt_done(ctx, stmt);
//			break;
//		}
		case STT_INCLUDE:
			isCONTINUE = INCLUDE_eval(ctx, stmt, reqt, resultsNULL);
			break;
		case STT_USING:
			isCONTINUE = USING_eval(ctx, stmt);
			break;
		case STT_CLASS:
			isCONTINUE = CLASS_decl(ctx, stmt);
			break;
		case STT_CONTINUE:
			knh_Stmt_done(ctx, stmt); break;
		case STT_RETURN:
			WarningMuchBetter(ctx, "break");
		case STT_BREAK:
			isCONTINUE = 0;
		}
		if(STT_(stmt) == STT_ERR) {
			isCONTINUE = 0;
		}
		if(isCONTINUE == 0) {
			goto L_BREAK;
		}
		stmt = DP(stmt)->nextNULL;
	}

	SCRIPT_typing(ctx, stmtITR);

	stmt = stmtITR;
	while(stmt != NULL) {
		knh_Stmt_t *stmtNEXT = DP(stmt)->nextNULL;
		if(stmtNEXT != NULL) {
			KNH_SETv(ctx, lsfp[0].o, stmt);
			KNH_SETv(ctx, lsfp[1].o, stmtNEXT);
			KNH_FINALv(ctx, DP(stmt)->nextNULL);
			DP(stmt)->nextNULL = NULL;
		}
		ctx->gma->uline = stmt->uline;
		SCRIPT_asm(ctx, stmt);
		if(STT_(stmt) != STT_DONE) {
			knh_Script_t *scr = knh_getGammaScript(ctx);
			knh_Method_t *mtd = Script_getEvalMethod(ctx, scr);
			int isExpr = stmt_isExpr(STT_(stmt));
			int rtnidx=3+1, thisidx = rtnidx + K_CALLDELTA;
			knh_class_t cid =  O_cid(ctx->evaled);
			if(STT_(stmt) == STT_ERR) {
				isCONTINUE = 0; goto L_BREAK;
			}
			knh_Method_asm(ctx, mtd, NULL, cid, stmt, knh_Method_typing);
			if(Method_isAbstract(mtd) || STT_(stmt) == STT_ERR) {
				isCONTINUE = 0; goto L_BREAK;
			}
			if(resultsNULL != NULL) {
				DP(mtd)->uri = ULINE_uri(stmt->uline);
				KNH_SETv(ctx, lsfp[1+1].o, DP(mtd)->kcode);
				// lsfp[2+1] exception handler
				lsfp[thisidx+K_PCIDX].pc = NULL;
				klr_setmtdNC(ctx, lsfp[thisidx+K_MTDIDX], mtd);
				KNH_SETv(ctx, lsfp[thisidx].o, scr);
				KNH_SETv(ctx, lsfp[thisidx+1].o, ctx->evaled);
				if(IS_Tunbox(cid)) {
					lsfp[thisidx+1].ndata = O_data(ctx->evaled);
				}
				klr_setesp(ctx, lsfp + thisidx+2);
				if(knh_VirtualMachine_run(ctx, lsfp + thisidx, CODE_LAUNCH) == NULL) {
					knh_type_t stmttype = SP(stmt)->type;
					if(isExpr && stmttype != TYPE_void) {
						cid = O_cid(lsfp[rtnidx].o);
						if(cid != CLASS_ExceptionHandler && class_isa(cid, stmttype)) {
							KNH_SETv(ctx, ((knh_context_t*)ctx)->evaled, lsfp[rtnidx].o);
							if(reqt != TYPE_void && (reqt == TYPE_dynamic || class_isa(cid, reqt))) {
								knh_Array_add(ctx, resultsNULL, lsfp[rtnidx].o);
							}
							else {
								DBG_P("returning sfpidx=%d, rtnidx=%d, %s %lld %ld %f", sfpidx_, sfpidx_ + rtnidx, O__(lsfp[rtnidx].o), lsfp[rtnidx].ivalue, lsfp[rtnidx].bvalue, lsfp[rtnidx].fvalue);
							}
						}
					}
				}
				else {
					isCONTINUE = 0;
					goto L_BREAK;
				}
			}
		}
		stmt = stmtNEXT;
	}

	L_BREAK:;
	END_LOCAL_(ctx, lsfp);
	ctx->gma->uline = 0;
	return isCONTINUE;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_eval(CTX ctx, knh_InputStream_t *in, knh_type_t reqt, knh_Array_t *resultsNULL)
{
	int isCONTINUE = 1;
	BEGIN_LOCAL(ctx, lsfp, 3);
	KNH_SETv(ctx, lsfp[0].o, in);
	if(resultsNULL != NULL) {
		KNH_SETv(ctx, lsfp[1].o, resultsNULL);
	}
	LOCAL_NEW(ctx, lsfp, 2, knh_Stmt_t *, stmt, knh_InputStream_parseStmt(ctx, in));
	isCONTINUE = Stmt_eval(ctx, stmt, reqt, resultsNULL);
	END_LOCAL_(ctx, lsfp);
	return isCONTINUE;
}

/* ------------------------------------------------------------------------ */

static int bytes_isempty(knh_bytes_t t)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		if(!isspace(t.ustr[i])) return 0;
	}
	return 1;
}

static void Bytes_addQUOTE(CTX ctx, knh_Bytes_t *ba, knh_InputStream_t *in, int quote)
{
	int ch, prev = quote;
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		knh_Bytes_putc(ctx, ba, ch);
		if(ch == quote && prev != '\\') {
			return;
		}
		prev = ch;
	}
}

static void Bytes_addCOMMENT(CTX ctx, knh_Bytes_t *ba, knh_InputStream_t *in)
{
	int ch, prev = 0, level = 1;
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		knh_Bytes_putc(ctx, ba, ch);
		if(prev == '*' && ch == '/') level--;
		if(prev == '/' && ch == '*') level++;
		if(level == 0) return;
		prev = ch;
	}
}

static knh_InputStream_t* knh_openPathNULL(CTX ctx, knh_bytes_t path)
{
	knh_NameSpace_t *ns = KNH_GMA_NS;
	knh_StreamDSPI_t *sdspi = knh_getStreamDSPI(ctx, path);
	knh_io_t fd = sdspi->fopen(ctx, path, "r");
	if(fd == IO_NULL) {
		KNH_SYSLOG(ctx, LOG_ERR, "NotFound", "script='%B'", path);
		return NULL;
	}
	else {
		knh_uintptr_t id = 0;
		knh_PathDSPI_t *pdspi = knh_NameSpace_getPathDSPINULL(ctx, ns, path);
		if(pdspi != NULL) id = pdspi->exists(ctx, path, ns);
		knh_InputStream_t *in = new_InputStreamDSPI(ctx, fd, sdspi);
		if(id != PATH_unknown) {
			DBG_P("URI=%ld, URN='%s'", id, path.text);
			ULINE_setURI(in->uline, id);
			KNH_SETv(ctx, DP(in)->urn, knh_getURN(ctx, (knh_uri_t)id));
		}
		return in;
	}
}

KNHAPI2(knh_bool_t) knh_loadScript(CTX ctx, knh_bytes_t path, knh_type_t reqt, knh_Array_t *resultsNULL)
{
	knh_bool_t res = 0;
	long linenum = 1;
	void *dlhdrSTACK = DP(ctx->gma)->dlhdr;
	BEGIN_LOCAL(ctx, lsfp, 2);
	DP(ctx->gma)->dlhdr = NULL;
	LOCAL_NEW(ctx, lsfp, 1, knh_InputStream_t *, bin, new_BytesInputStream(ctx, new_Bytes(ctx, K_PAGESIZE)));
	knh_Bytes_t *ba = DP(bin)->ba;
	knh_InputStream_t *in = knh_openPathNULL(ctx, path);
	if(in == NULL) {
		goto L_RETURN;
	}
	KNH_SETv(ctx, lsfp[0].o, in);
	if(!CTX_isCompiling(ctx)) {
		KNH_SYSLOG(ctx, LOG_NOTICE, "RUN_SCRIPT", "*path='%s'", path.text);
	}
	L_READLINE:;
	knh_Bytes_clear(ba, 0);
	if(!InputStream_isClosed(ctx, in)) {
		int ch;
		int prev = 0, isBLOCK = 0;
		linenum = ULINE_line(in->uline);
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			if(ch == '\r') continue;
			knh_Bytes_putc(ctx, ba, ch);
			if(prev == '/' && ch == '*') {
				Bytes_addCOMMENT(ctx, ba, in);
				continue;
			}
			if(ch == '\'' || ch == '"' || ch == '`') {
				Bytes_addQUOTE(ctx, ba, in, ch);
				continue;
			}
			if(isBLOCK != 1 && prev == '\n' && ch == '\n') {
				goto L_PARSE;
			}
			if(prev == '{') {
				isBLOCK = 1;
			}
			if(prev == '\n' && ch == '}') {
				isBLOCK = 0;
			}
			prev = ch;
		}
	}
	L_PARSE:;
	if(!bytes_isempty(ba->bu)) {
		knh_uri_t uri = ULINE_uri(in->uline);
		BytesInputStream_setpos(ctx, bin, 0, BA_size(ba));
		bin->uline = linenum;
		ULINE_setURI(bin->uline, uri);
		//InputStream_setCharset(ctx, bin, DP(in)->enc);
		DBG_(if(knh_isSystemVerbose()) {
			fprintf(stderr, "\n>>>--------------------------------\n");
			fprintf(stderr, "%s<<<--------------------------------\n", knh_Bytes_ensureZero(ctx, ba));
		});
		res = knh_eval(ctx, bin, reqt, resultsNULL);
		if(res == 0) goto L_RETURN;
		goto L_READLINE;
	}
	if(BA_size(ba) > 0) {
		goto L_READLINE;
	}
	L_RETURN:;
//	if(DP(ctx->gma)->dlhdr != NULL) {
//		knh_FsetupPKG f = (knh_FsetupPKG)knh_dlsym(ctx, DP(ctx->gma)->dlhdr, "setup", 0);
//		if(f != NULL) f(ctx, knh_getPackageAPI(), NULL, 0/*isOVERRIDE*/);
//		DP(ctx->gma)->dlhdr = NULL;
//	}
	DP(ctx->gma)->dlhdr = dlhdrSTACK;
	END_LOCAL_(ctx, lsfp);
	return res;
}

/* ------------------------------------------------------------------------ */

int konoha_load(konoha_t konoha, knh_bytes_t path, int isCompileOnly)
{
	int isCONTINUE;
	KONOHA_CHECK(konoha, 0);
	CTX ctx = (CTX)konoha.ctx;
	KONOHA_BEGIN(ctx);
	char buf[256];
	knh_Array_t *resultsNULL = isCompileOnly ? NULL : KNH_TNULL(Array);
	knh_snprintf(buf, sizeof(buf), "file:%s", path.text);
	isCONTINUE = knh_loadScript(ctx, B(buf), TYPE_void, resultsNULL);
	if(resultsNULL != NULL) knh_Array_clear(ctx, resultsNULL, 0);
	knh_stack_clear(ctx, ctx->stack);
	KONOHA_END(ctx);
	return isCONTINUE;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
