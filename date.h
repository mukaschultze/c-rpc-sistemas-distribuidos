/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DATE_H_RPCGEN
#define _DATE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define DATEPROG 0x3012225
#define DATEVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define BINDATE 1
extern  long * bindate_1(void *, CLIENT *);
extern  long * bindate_1_svc(void *, struct svc_req *);
extern int dateprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define BINDATE 1
extern  long * bindate_1();
extern  long * bindate_1_svc();
extern int dateprog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DATE_H_RPCGEN */
