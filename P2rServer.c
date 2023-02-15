/*#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>    
#include <pthread.h>
*/
#include "P2rServer.h"

#include <asn_application.h>
#include <asn_internal.h>
#include "Message.h"

void *P2r_connection_handler(void *socket_desc)
{
    int sock = *(int *)socket_desc;
    int read_size;
    char client_message[2000];
    asn_dec_rval_t rval;
    Message_t *P2R_message = 0;

    while ( 1 )
    {
        read_size = 0;

        while( (read_size = recv( sock, client_message, 2000, 0 ) ) > 0 ) {
            ASN_STRUCT_RESET(asn_DEF_Message, P2R_message);
            printf("server: received %d\n", read_size);
            printf("decoding...\n");
            rval = asn_decode(0, ATS_DER, &asn_DEF_Message, (void **)&P2R_message, client_message, read_size);
            printf("rval.code = %d\n", rval.code);
            switch (rval.code) {            
                case RC_OK: {
                    //CALLBACK
                    printf("OK. Calling endpoint\n");
                    asn_fprint(stderr, &asn_DEF_Message, P2R_message);
                    printf("speed level: %2f\n", P2R_message->parameters.choice.speed_level_notification.speed);
                    break;
                }
                case RC_WMORE: {
                    printf("consumed %ld bytes of %d readed\n", rval.consumed, read_size);
                    break;
                }
                case RC_FAIL: {
                    printf("Error while parsing\n");
                    break;
                }
            }
 //               write(sock, client_message, strlen(client_message));
        }
        if (read_size == 0)
        {
            // disconnected
            printf("disconnected\n");
            break;
        }
        else if (read_size == -1)
        {
            printf("recv error\n");
            break;
        }
    }
    shutdown(sock, SHUT_RDWR);
    free(socket_desc);

    return 0;
}

int P2r_server_start(unsigned short port) {
    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        // print the error message
        perror("bind failed. Error");
        return 1;
    }
    printf("bind done \n");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        printf("Connection accepted\n");

        pthread_t sniffer_thread;
        new_sock = (int*)malloc(4);
        *new_sock = client_sock;

        if (pthread_create(&sniffer_thread, NULL, P2r_connection_handler, (void *)new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        // Now join the thread , so that we dont terminate before the thread
        // pthread_join( sniffer_thread , NULL);
        printf("Handler assigned\n");
    }

    if (client_sock < 0)
    {
        printf("accept failed\n");
        return 1;
    }

    return 0;
}

void *P2r_server_thread(void *param) {
    P2r_server_start(*((unsigned short *)param));
    return 0;
}