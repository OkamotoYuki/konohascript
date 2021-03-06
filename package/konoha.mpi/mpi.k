include "lib:gluelink";


/* ------------------------------------------------------------------------ */
/* System API */

@Public void  System.disableLog();  // for ac
@Public Float System.getMPIWtime(); // for MPI_Wtime


/* ------------------------------------------------------------------------ */
/* Array Extra API */

@Public int[]   Array.getShape();
@Public void    Array.reshape(int[] shape);
@Public dynamic Array.cols(int start, int end);
@Public dynamic Array.rows(int start, int end);
@Public dynamic Array.cycle(int rank, int size);
@Public dynamic Array.trans();


/* ------------------------------------------------------------------------ */
/* MPI-1 Basic API */

@Native class MPIComm;
@Native int     MPIComm.getRank();
@Native int     MPIComm.getSize();
@Native String  MPIComm.getProcessorName();
@Native int     MPIComm.barrier();
@Native MPIComm MPIComm.create(int[] ranks);

@Native class MPIData;
@Native MPIData MPIData.new (byte[] data, Class c);
@Native MPIData : (int i);
@Native MPIData : (int[] ia);
@Native MPIData : (float f);
@Native MPIData : (float[] fa);
@Native MPIData : (byte[] ba);
@Native int[]   : (MPIData md);
@Native float[] : (MPIData md);
@Native byte[]  : (MPIData md);
@Native Class   MPIData.getContentClass();
@Native int     MPIData.getSize();
@Native MPIData MPIData.opADD(int offset);

@Native class MPIRequest;
@Native boolean MPIRequest.test();
@Native boolean MPIRequest.wait();
@Native boolean MPIRequest.cancel();

@Native class MPIOp;
@Native MPIOp MPIOp.new(Func<MPIData,MPIData> func, Boolean commutable);


/* ------------------------------------------------------------------------ */
/* Point-to-Point Communication API */

@Native boolean    MPIComm.send(MPIData sdata, int count, int dest_rank, int tag);
@Native boolean    MPIComm.recv(MPIData rdata, int count, int src_rank, int tag);
@Native boolean    MPIComm.sendrecv(MPIData sdata, int count, int dest_rank, int stag,
                                    MPIData rdata, int count, int src_rank, int rtag);
@Native MPIRequest MPIComm.iSend(MPIData sdata, int count, int dest_rank, int tag, MPIRequest _);
@Native MPIRequest MPIComm.iRecv(MPIData rdata, int count, int src_rank, int tag, MPIRequest _);


/* ------------------------------------------------------------------------ */
/* Collective Communication API */

@Native boolean MPIComm.bcast(MPIData sdata, int count, int root_rank);
@Native boolean MPIComm.scatter(MPIData sdata, int scount, MPIData rdata, int rcount, int root_rank);
@Native boolean MPIComm.gather(MPIData sdata, int scount, MPIData rdata, int rcount, int root_rank);
@Native boolean MPIComm.allGather(MPIData sdata, int scount, MPIData rdata, int rcount);
@Native boolean MPIComm.allToAll(MPIData sdata, int scount, MPIData rdata, int rcount);
@Native boolean MPIComm.reduce(MPIData sdata, MPIData rdata, int rcount, MPIOp op, int root_rank);
@Native boolean MPIComm.allReduce(MPIData sdata, MPIData rdata, int rcount, MPIOp op);


/* ------------------------------------------------------------------------ */
/* MPITask Construction */

//@Native void MPIComm.addTask(Path taskpath);
//@Native @Static MPIComm MPIComm.getTaskComm();

/* ======================================================================== */
/* Utility Functions */

using konoha.io.*;

MPIData : (Object o) {
    byte[] bt = new byte[0];
    bt.writeMsgPack(o);
    return new MPIData(bt, o.class);
}
dynamic MPIData.decode(Class c) {
    return ((byte[])this).readMsgPack(0, 0, c);
}
