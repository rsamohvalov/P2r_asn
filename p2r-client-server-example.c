/*
 * Generic converter template for a selected ASN.1 type.
 * Copyright (c) 2005-2017 Lev Walkin <vlm@lionet.info>.
 * All rights reserved.
 * 
 * To compile with your own ASN.1 type, redefine the PDU as shown:
 * 
 * cc -DPDU=MyCustomType -o myDecoder.o -c converter-example.c
 */
#ifdef    HAVE_CONFIG_H
#include <config.h>
#endif
#define __EXTENSIONS__
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>    /* for atoi(3) */
#include <getopt.h>    /* for getopt(3) */
#include <string.h>    /* for strerror(3) */
#include <sysexits.h>    /* for EX_* exit codes */
#include <errno.h>    /* for errno */
#include <unistd.h>    /* for isatty(3) */
#include <asn_application.h>
#include <asn_internal.h>    /* for ASN__DEFAULT_STACK_MAX */


#include "P2rServer.h"
#include "P2rClient.h"

int
main(int ac, char *av[]) {
////////////////////////
{
        pthread_t server_thread;
        unsigned short port = 6666;
        if (pthread_create(&server_thread, NULL, P2r_server_thread, &port) < 0)
        {
            perror("could not create thread");
        }
}
    sleep(1);
{
        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, P2r_client_test, NULL) < 0)
        {
            perror("could not create thread");
           
        }
        else{
            pthread_join(client_thread, 0);
        }
}
    return 0;
///////////////////////
}

