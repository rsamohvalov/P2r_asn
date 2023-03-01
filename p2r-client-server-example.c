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


#include "api/P2r_client_api.h"
#include "api/P2r_server_api.h"

int
main(int ac, char *av[]) {
////////////////////////
StopServer();
P2rClientRelease();
return 0;
///////////////////////
}

