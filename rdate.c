
/****************************************************************/
/* rdate.c - client program for remote date service */
#include <stdio.h>
#include <rpc/rpc.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"

int main(int argc, char *argv[]) {
    CLIENT *cl;
    char *server;
    long *lres;
       
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(1);
    }
    server = argv[1];

    /* create client handle */
    if ((cl = clnt_create(server, DATEPROG, DATEVERS, "udp")) == NULL) {
        /* couldn't establish connection with server */
        printf("can't establish connection with host %s\n", server);
        exit(2);
    }
    /* first call the remote procedure bindate() */
    if (( lres = bindate_1(NULL, cl)) == NULL){
        printf(" remote procedure bindate() failure\n");
        exit(3);
    }
    printf("time on host %s = %ld\n", server, *lres);
    
  
    
  
    
    clnt_destroy(cl); /* done with handle */
    return 0;
}
