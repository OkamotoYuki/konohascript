#include "konoha_mpi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

//## method void System.disableLog();
KMETHOD System_disableLog(CTX ctx, knh_sfp_t *sfp _RIX)
{
	knh_closelog();
	RETURNvoid_();
}

/* ------------------------------------------------------------------------ */

#ifdef _SETUP

static void knh_MPICommunicator_init(CTX ctx, knh_RawPtr_t *o)
{
	knh_MPIComm_t *comm = (knh_MPIComm_t*)o;
	KNH_NOT_ON_MPI(comm);
	KNH_MPI_SIZE(comm) = -1;
	comm->proc_name = NULL;
}

static void knh_MPIRequest_init(CTX ctx, knh_RawPtr_t *o)
{
	knh_MPIRequest_t *mreq = (knh_MPIRequest_t*)o;
	KNH_MPI_REQUEST(mreq) = (MPI_Request*)KNH_MALLOC(ctx, sizeof(MPI_Request));
}

static void knh_MPIRequest_free(CTX ctx, knh_RawPtr_t *o)
{
	knh_MPIRequest_t *mreq = (knh_MPIRequest_t*)o;
	if (!KNH_MPI_REQUEST_IS_NULL(mreq)) {
		MPI_Request_free(KNH_MPI_REQUEST(mreq));
		KNH_FREE(ctx, KNH_MPI_REQUEST(mreq), sizeof(MPI_Request));
	}
}

static void knh_MPIOp_init(CTX ctx, knh_RawPtr_t *o)
{
	knh_MPIOp_t *op = (knh_MPIOp_t*)o;
	KNH_MPI_OP(op) = 0;
}

static void knh_MPI_initWorld(CTX ctx, knh_class_t cid)
{
	int len;
	knh_MPIComm_t *world = new_O(MPIComm, cid);
	static char proc_name[MPI_MAX_PROCESSOR_NAME] = {0};
	world->comm = MPI_COMM_WORLD;
	world->proc_name = (char*)&proc_name;
	MPI_Comm_rank(world->comm, &KNH_MPI_RANK(world));
	MPI_Comm_size(world->comm, &KNH_MPI_SIZE(world));
	MPI_Get_processor_name(world->proc_name, &len);
	knh_addClassConst(ctx, cid, new_String(ctx, "WORLD"), (Object*)world);
}

static knh_IntData_t MPIConstOp[] = {
	{"OP_MAX",  MPI_MAX},
	{"OP_MIN",  MPI_MIN},
	{"OP_SUM",  MPI_SUM},
	{"OP_PROD", MPI_PROD},
	{"OP_LAND", MPI_LAND},
	{"OP_BAND", MPI_BAND},
	{"OP_LOD",  MPI_LOR},
	{"OP_BOR",  MPI_BOR},
	{"OP_LXOR", MPI_LXOR},
	{"OP_BXOR", MPI_BXOR},
	{NULL, 0},
};

static void knh_MPI_initOp(CTX ctx, knh_class_t cid)
{
	knh_IntData_t *d;
	for (d = &MPIConstOp[0]; d->ivalue > 0; d++) {
		knh_MPIOp_t *op = new_O(MPIOp, cid);
		op->op = (MPI_Op)d->ivalue;
		op->func = NULL;
		knh_addClassConst(ctx, cid, new_String(ctx, d->name), (Object*)op);
	}
}

DEFAPI(void) defMPICommunicator(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	cdef->name = "MPICommunicator";
	cdef->init = knh_MPICommunicator_init;
}

DEFAPI(void) defMPIRequest(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	cdef->name = "MPIRequest";
	cdef->init = knh_MPIRequest_init;
	cdef->free = knh_MPIRequest_free;
}

DEFAPI(void) defMPIOp(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	cdef->name = "MPIOp";
	cdef->init = knh_MPIOp_init;
}

DEFAPI(void) constMPICommunicator(CTX ctx, knh_class_t cid, const knh_LoaderAPI_t *kapi)
{
	knh_MPI_initWorld(ctx, cid);
}

DEFAPI(void) constMPIOp(CTX ctx, knh_class_t cid, const knh_LoaderAPI_t *kapi)
{
	knh_MPI_initOp(ctx, cid);
}

DEFAPI(const knh_PackageDef_t*) init(CTX ctx, knh_LoaderAPI_t *kapi)
{
	int init = 0;
	MPI_Initialized(&init);
	if (init) {
		/* init err_handler */
		//static MPI_Errhandler err_hdr;
		//MPI_Errhandler_create(knh_MPICommunicator_errhandler, &err_hdr);
		MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
	}
	kapi->setPackageProperty(ctx, "name", "mpi");
	kapi->setPackageProperty(ctx, "version", "1.0");
	RETURN_PKGINFO("konoha,mpi");
}

#endif /* _SETUP */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
