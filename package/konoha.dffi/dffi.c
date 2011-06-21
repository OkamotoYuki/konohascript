/* Glue 
 *  ffi package, for DEOS
 *  written by shinpei(c)2011
 */

#define  USE_B 1
#define USE_new_bytes 1
#define USE_cwb 1
#define USE_cwb_open 1

#include <konoha1.h>

//#define MACOSX
#include <ffi/ffi.h>

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* [Glue] */
#include <dglue.h> // for DEOS
// #include <glue.h>

/* ------------------------------------------------------------------------ */
/* [Clib] */

#define CLIB_ARGMAX 3

typedef struct knh_CLib_t {
  void *handler;
} knh_CLib_t;


static void Clib_init(CTX ctx, knh_RawPtr_t *po)
{
  po->rawptr = (void*)KNH_MALLOC(ctx, sizeof(knh_CLib_t));
  knh_CLib_t *clib  = (knh_CLib_t*)po->rawptr;
  clib->handler = NULL;
}

static void Clib_free(CTX ctx, knh_RawPtr_t *po)
{
	if (po->rawptr != NULL) {
	  knh_CLib_t *clib = (knh_CLib_t*)po->rawptr;
	  if (clib->handler != NULL) {
		knh_dlclose(ctx, clib->handler);
	  }
	  KNH_FREE(ctx, clib, sizeof(knh_CLib_t));
	  po->rawptr = NULL;
	}
}

DEFAPI(void) defClib(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	cdef->name = "Clib";
	cdef->init = Clib_init;
	cdef->free = Clib_free;
}

/* ------------------------------------------------------------------------ */
/* [Process] */

typedef struct knh_Process_t {
  char *path;
  size_t path_size;
  int pid;
} knh_Process_t;

static void Process_init(CTX ctx, knh_RawPtr_t *po)
{
  po->rawptr = (void*)KNH_MALLOC(ctx, sizeof(knh_Process_t));
}

static void Process_free(CTX ctx, knh_RawPtr_t *po)
{
	if (po->rawptr != NULL) {
	  po->rawptr = NULL;
	}
}

DEFAPI(void) defProcess(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	cdef->name = "Process";
	cdef->init = Process_init;
	cdef->free = Process_free;
}


/* ------------------------------------------------------------------------ */
/* [Dglue:internal] */

#define DGLUE_NOT_UNBOXED 0
#define DGLUE_UNBOXED 1

typedef struct knh_ClibGlue_t {
  void *fptr;
  ffi_cif cif;
  int argCount;
  ffi_type *retT;
  ffi_type *argT[CLIB_ARGMAX];
  int argT_isUnboxed[CLIB_ARGMAX];
  void *argV[CLIB_ARGMAX];
  void *retV;
} knh_ClibGlue_t;

  /*typedef struct knh_DGlue_t {
  knh_CLib_t *clib;
  void *fptr;
  ffi_cif cif;
  int argCount;
  ffi_type *retT;
  ffi_type *argT[CLIB_ARGMAX];
  int argT_isUnboxed[CLIB_ARGMAX];
  void *argV[CLIB_ARGMAX];
  void *retV;
} knh_DGlue_t;
  */

static void ClibGlue_init(CTX ctx, knh_ClibGlue_t *cglue)
{
  int i;
  cglue->fptr = NULL;
  cglue->argCount = 0;
  for (i = 0; i < CLIB_ARGMAX; i++) {
	cglue->argT[i] = NULL;
	cglue->argT_isUnboxed[i] = 0;
	cglue->argV[i] = NULL;
  }
  cglue->retV = NULL;
}

static void ClibGlue_free(CTX ctx, void *ptr)
{
  if (ptr != NULL) {
	knh_ClibGlue_t *cglue = (knh_ClibGlue_t*)ptr;
	KNH_FREE(ctx, cglue, sizeof(knh_ClibGlue_t));
	ptr = NULL;
  }
}

/* ------------------------------------------------------------------------ */
/* [Dglue:Local] */

typedef struct knh_ProcessGlue_t {
  char *path;  
  size_t path_size;
} knh_ProcessGlue_t;

static void ProcessGlue_init(CTX ctx, knh_ProcessGlue_t *po)
{
  po->path = NULL;
}

static void ProcessGlue_free(CTX ctx, void *ptr)
{
	if (ptr != NULL) {
	  ptr = NULL;
	}
}

/* ------------------------------------------------------------------------ */
// Clib Clib.new(String libname) 
METHOD Clib_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_CLib_t *clib = (knh_CLib_t *)(sfp[0].p->rawptr);
  const char *libname = String_to(const char *, sfp[1]);
  clib->handler = knh_dlopen(ctx, libname);
  RETURN_(sfp[0].o);
}

static METHOD Fmethod_wrapCLib(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_type_t rtype = knh_ParamArray_rtype(DP(sfp[K_MTDIDX].mtdNC)->mp);
  knh_Func_t *fo = sfp[0].fo;
  knh_ClibGlue_t *cglue = (knh_ClibGlue_t*)(((fo->mtd)->b)->cfunc);
  //  fprintf(stderr, "fptr:%p, %p, %d, %p, %p\n", 
  //		  dg->fptr,
  //		  &(dg->cif), dg->argCount,
  //		  dg->retT, dg->argT);
  
  if(rtype != TYPE_void) {
	if(IS_Tunbox(rtype)) {
	  int idx = 0;
	  for (idx = 0; idx < cglue->argCount; idx++) {
		if (cglue->argT_isUnboxed[idx] == DGLUE_UNBOXED) {
		  cglue->argV[idx] = &(sfp[idx+1].ndata);
		} else {
		  cglue->argV[idx] = &(sfp[idx+1].o);
		}
	  }
	  //	  double arg1 = Float_to(double, sfp[1]);
	  //	  (cglue->argV[0]) = &arg1;
	  if (rtype == TYPE_Int || rtype == TYPE_Boolean) {
		knh_int_t return_i = 0;
		if (ffi_prep_cif(&(cglue->cif), FFI_DEFAULT_ABI, cglue->argCount,
						 cglue->retT, cglue->argT) == FFI_OK) {
		  ffi_call(&(cglue->cif), cglue->fptr, &(cglue->retV), cglue->argV);
		  return_i = *(knh_int_t*)(&cglue->retV);
		}
		RETURNi_(return_i);
	  } else if (rtype == TYPE_Float) {
		double return_f = 0.0;
		if (ffi_prep_cif(&(cglue->cif), FFI_DEFAULT_ABI, cglue->argCount,
						 cglue->retT, cglue->argT) == FFI_OK) {
		  ffi_call(&(cglue->cif), cglue->fptr, &(cglue->retV), cglue->argV);
		  return_f = *(double*)(&cglue->retV);
		} else {
		  fprintf(stderr, "prep_cif FAILED\n:");
		}
		RETURNf_(return_f);
	  } 
	} else {
	  // its Object
	  RETURN_(KNH_NULVAL(CLASS_t(rtype)));
	}
  }
}

static knh_RawPtr_t *ClibGlue_getFunc(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_Glue_t *glue = (knh_Glue_t*)((sfp[0].p)->rawptr);
  knh_ClibGlue_t *cglue = (knh_ClibGlue_t*)(glue->glueInfo);
  knh_CLib_t *clib = (knh_CLib_t*)glue->componentInfo;
  if (clib == NULL) {
	fprintf(stderr, "invalid Dglue\n");
	RETURN_(sfp[3].fo);
  }
  const char *symstr = String_to(const char *, sfp[1]);
  knh_Class_t *klass = (knh_Class_t*)sfp[2].o;
  knh_Func_t *fo = (knh_Func_t *)sfp[3].o;

  // requested type
  //  fprintf(stderr, "%s %s\n", CLASS__(O_cid(klass)), CLASS__(klass->cid));
  const knh_ClassTBL_t *tbl = ClassTBL(klass->cid);
  knh_ParamArray_t *pa = tbl->cparam;

  if ((cglue->fptr = knh_dlsym(ctx, clib->handler, symstr, 0))== NULL) {
	fprintf(stderr, "dlsym_ERROR!!!\n");
  }

  // type a method from requested type
  // retT
  size_t argCount = pa->rsize;
  cglue->argCount = argCount;
  if (argCount < 3) {
	if (pa->p0.type == TYPE_Int) {
	  cglue->retT = &ffi_type_uint64;
	} else if (pa->p0.type == TYPE_Float) {
	  cglue->retT = &ffi_type_double;
	} else {
	  TODO();
	}
  } else {
	TODO();
  }

  //argT
  if (argCount < 3) {
	if (argCount == 1) {
	  if (pa->p1.type == TYPE_Int) {
		cglue->argT[0] = &ffi_type_uint64;
		cglue->argT_isUnboxed[0] = DGLUE_UNBOXED;
	  } else if (pa->p1.type == TYPE_Float) {
		cglue->argT[0] = &ffi_type_double;
		cglue->argT_isUnboxed[0] = DGLUE_UNBOXED;
	  } else {
		TODO();
	  }
	} else if (argCount == 2) {
	  if (pa->p1.type == TYPE_Int) {
		cglue->argT[0] = &ffi_type_uint64;
		cglue->argT_isUnboxed[0] = DGLUE_UNBOXED;
	  } else if (pa->p1.type == TYPE_Float) {
		cglue->argT[0] = &ffi_type_double;
		cglue->argT_isUnboxed[0] = DGLUE_UNBOXED;
	  } else {
		TODO();
	  }

	  if (pa->p2.type == TYPE_Int) {
		cglue->argT[1] = &ffi_type_uint64;
		cglue->argT_isUnboxed[1] = DGLUE_UNBOXED;
	  } else if (pa->p2.type == TYPE_Float) {
		cglue->argT[1] = &ffi_type_double;
		cglue->argT_isUnboxed[1] = DGLUE_UNBOXED;
	  } else {
		TODO();
	  }
	} // there are no more... argCount == 0 ?
  } else {
	// more than 3 args
	TODO();
  }
  // type Func object
  fo->h.cTBL= tbl;
  //cid = knh_class_Generics(ctx, CLASS_Func, pa);
  
  // set wrapper method
  knh_Method_t *mtd = new_Method(ctx, 0, O_cid(klass), MN_LAMBDA, Fmethod_wrapCLib);
  mtd->b->cfunc = (void*)cglue;
  KNH_SETv(ctx, ((mtd)->b)->mp, tbl->cparam);
  KNH_INITv(fo->mtd, mtd);
  return (knh_RawPtr_t*)fo;
}


static knh_GlueSPI_t CLibGlueSPI = {
  ClibGlue_getFunc,
  /*  Clib_component_free*/ NULL,
  ClibGlue_free
};


// @Native Glue Clib_genGlue (Glue _)
METHOD Clib_genGlue(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_CLib_t *clib = (knh_CLib_t *)((sfp[0].p)->rawptr);
  knh_RawPtr_t *po = sfp[1].p;
  if (clib != NULL) {
	knh_Glue_t *glue = (knh_Glue_t *)po->rawptr;
	glue->glueType = GLUE_TYPE_INTERNAL;
	glue->gapi = &CLibGlueSPI;
	glue->componentInfo = (void*)clib;
	knh_ClibGlue_t *cglue = (knh_ClibGlue_t*)KNH_MALLOC(ctx, sizeof(knh_ClibGlue_t));
	ClibGlue_init(ctx, cglue);
	glue->glueInfo = (void*)cglue;
	RETURN_(po);
  }
  RETURN_(sfp[1].p);
}


/* ------------------------------------------------------------------------ */
/* [Process] */
#define PROCESS_PATH_MAX 256

METHOD Process_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_RawPtr_t *po = sfp[0].p;
  knh_Process_t *proc = (knh_Process_t*)po->rawptr;
  char *pname = String_to(char *, sfp[1]);
  size_t path_size = knh_strlen(pname);
  if (pname != NULL && path_size < PROCESS_PATH_MAX) {
	proc->path = KNH_MALLOC(ctx, path_size * sizeof(char));
	knh_memcpy(proc->path, pname, path_size+1);
	proc->path_size = path_size;
  }
  RETURN_(po);
}


//#include <crt_externs.h>
static METHOD Fmethod_wrapProcess(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_type_t rtype = knh_ParamArray_rtype(DP(sfp[K_MTDIDX].mtdNC)->mp);
  knh_Func_t *fo = sfp[0].fo;
  knh_ProcessGlue_t *pglue = (knh_ProcessGlue_t*)(((fo->mtd)->b)->cfunc);
  const char *arg1 = String_to(const char *, sfp[1]);
  char *args[] = {pglue->path, arg1, NULL};
#ifdef K_USING_POSIX_
  // create pipe
  int pipe_c2p[2], pipe_p2c[2];
  int pid;
  if (pipe(pipe_c2p) < 0) {
	fprintf(stderr, "POPEN C2P!!\n");
  }
  if (pipe(pipe_p2c) < 0) {
	fprintf(stderr, "POPEN P2C\n");
	close(pipe_c2p[0]/* R */);
	close(pipe_c2p[1]/* W */);
  }
  if ((pid = fork()) < 0) {
	close(pipe_c2p[0]);
	close(pipe_c2p[1]);
	close(pipe_p2c[0]);
	close(pipe_p2c[1]);
  }
  if (pid == 0) {
	/* child */
	close(pipe_p2c[1]); // parent writing in this pipe
	close(pipe_c2p[0]); // parent reading from this pipe
	dup2(pipe_p2c[0] , 0); // stdin
	dup2(pipe_c2p[1], 1); // stdout
	close(pipe_p2c[0]); // after duplicate, close pipe
	close(pipe_c2p[1]); // same as above
	if (execvp(pglue->path, args) < 0) {
	  perror("execvp");
	  fprintf(stderr, "execvp error!\n");
	  exit(1);
	}
  } else {
	int status;
	close(pipe_p2c[0]);
	close(pipe_c2p[1]);
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	char buf[K_PAGESIZE];
	//	while ((loaded = read(pipe_c2p[0], buf, 1)) != 0) {
	while(1) {
	  size_t size = read(pipe_c2p[0], buf, K_PAGESIZE);
	  //	  fprintf(stderr, "size:%d\n", size);
	  if (size > 0) {
		knh_bytes_t t = {{buf}, size};
		knh_Bytes_write(ctx, cwb->ba, t);
	  } else {
		break;
	  }
	};
	wait(&status);
	RETURN_(knh_cwb_newString(ctx, cwb));
  }

#endif

  if(rtype != TYPE_void) {
	if(IS_Tunbox(rtype)) {
	  RETURNi_(KNH_INT0);
	} else {
	  RETURN_(KNH_NULVAL(CLASS_t(rtype)));	  
	}
  }
}

static knh_RawPtr_t *ProcessGlue_getFunc(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_RawPtr_t *po = sfp[0].p;
  knh_Glue_t *glue = (knh_Glue_t*)po->rawptr;
  knh_ProcessGlue_t *pglue = (knh_ProcessGlue_t*)(glue->glueInfo);
  knh_Process_t *proc = (knh_Process_t*)(glue->componentInfo);

  if (proc == NULL) {
	fprintf(stderr, "invalid Lglue\n");
	RETURN_(sfp[3].fo);
  }
  //  const char *symbol = String_to(const char*, sfp[1]);
  knh_Class_t *klass = (knh_Class_t*)sfp[2].o;
  knh_Func_t *fo = sfp[3].fo;

  const knh_ClassTBL_t *tbl = ClassTBL(klass->cid);
  //  knh_ParamArray_t *pa = tbl->cparam;

  fo->h.cTBL= tbl;
  knh_Method_t *mtd = new_Method(ctx, 0, O_cid(klass), MN_LAMBDA, Fmethod_wrapProcess);
  mtd->b->cfunc = (void*)pglue;
  KNH_SETv(ctx, ((mtd)->b)->mp, tbl->cparam);
  KNH_INITv(fo->mtd, mtd);
  return (knh_RawPtr_t*)fo;
}

static knh_GlueSPI_t ProcessGlueSPI = {
  ProcessGlue_getFunc,
  /*  Process_component_free*/ NULL,
  ProcessGlue_free
};

// @Native Glue Clib_genGlue (Glue _)
METHOD Process_genGlue(CTX ctx, knh_sfp_t *sfp _RIX)
{
  knh_Process_t *proc = (knh_Process_t*)((sfp[0].p)->rawptr);
  knh_RawPtr_t *po = sfp[1].p;
  if (proc != NULL) {
	knh_Glue_t *glue = (knh_Glue_t*)po->rawptr;
	glue->glueType = GLUE_TYPE_LOCAL;
	glue->gapi = &ProcessGlueSPI;
	glue->componentInfo = (void*)proc;
	knh_ProcessGlue_t *pglue = (knh_ProcessGlue_t*)KNH_MALLOC(ctx, sizeof(knh_ProcessGlue_t));
	ProcessGlue_init(ctx, pglue);
	DBG_ASSERT(proc->path_size > 0);
	pglue->path = KNH_MALLOC(ctx, proc->path_size * sizeof(char));
	knh_memcpy(pglue->path, proc->path, proc->path_size+1);
	pglue->path_size = proc->path_size;
	glue->glueInfo = (void*)pglue;
	RETURN_(po);
  }
  RETURN_(sfp[1].p);
}

/* ------------------------------------------------------------------------ */


#ifdef _SETUP
/*
DEFAPI(const knh_PackageDef_t*) init(CTX ctx, const knh_PackageLoaderAPI_t *kapi)
{
	kapi->setPackageProperty(ctx, "name", "clib");
	kapi->setPackageProperty(ctx, "version", "0.1");
	RETURN_PKGINFO("konoha.clib");
}
*/

DEFAPI(const knh_PackageDef_t*) init(CTX ctx, const knh_PackageLoaderAPI_t *kapi)
{
	kapi->setPackageProperty(ctx, "name", "dffi");
	kapi->setPackageProperty(ctx, "version", "0.1");
	RETURN_PKGINFO("konoha.dffi");
}

#endif /* _SETUP */

#ifdef __cplusplus
}
#endif
