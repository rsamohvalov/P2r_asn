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
#include "Cause.h"

typedef enum _ret
{
    Success = 0,
    NotEnoughMemory = 1,
    TransportInitError = 2,
    ServerIsUnreachable = 3,
    EncodingError = 4,
    Error = 5
} ret_val;

extern long P2r_proto_major;
extern long P2r_proto_minor;
const long fp_id = 11;
char send_buffer[4096] = {0};
size_t send_buffer_size = 4096;

extern ret_val send_message(void *buffer, size_t size, void *ctx);

ret_val ServereEncodeAndSendMessage(Message_t *message, int *sock)
{
    asn_enc_rval_t er;
    ret_val ret = Error;
    er = asn_encode_to_buffer(0, ATS_DER, &asn_DEF_Message, message, send_buffer, send_buffer_size);
    if (er.encoded == -1)
    {
        perror("failed to encode");
        printf("Failed to encode %s  %s\n", asn_DEF_Message.name, er.failed_type->name);
        ret = EncodingError;
    }
    else
    {
        ret = send_message(send_buffer, er.encoded, &sock);
    }
    free(message);
    return ret;
}

ret_val SendP2RSessionTerminationWarningAck(e_Cause cause, int* sock)
{
    Message_t *message = 0;
    message = (Message_t *)calloc(1, sizeof(Message_t));
    if (!message)
    {
        return NotEnoughMemory;
    }
    message->protocol_version.major_version = P2r_proto_major;
    message->protocol_version.minor_version = P2r_proto_minor;
    message->connection_id.fp_id = 0;
    message->connection_id.rm_id = fp_id;

    message->message_type = MessageTypes_id_p2r_session_termination_warning_ack;
    message->parameters.present = Parameters_PR_session_termination_warning_ack;
    message->parameters.choice.session_termination_warning_ack.cause = cause;

    return ServereEncodeAndSendMessage(message, sock);
}

ret_val MessageParser( Message_t* message, int* sock ) {
    asn_fprint(stderr, &asn_DEF_Message, message);
    switch (message->message_type)
    {
    case MessageTypes_id_p2r_session_termination_warning: {
        //return SendP2RSessionTerminationWarningAck(Cause_success, sock );
        break;
    }    
    default:
        break;
    }
}

void *P2r_connection_handler(void *socket_desc)
{
    int sock = *(int *)socket_desc;
    int read_size;
    char client_message[4096];
    asn_dec_rval_t rval;
    Message_t *P2R_message = 0;
    int bytes_processed = 0;
    int more_to_read_offset = 0;

    while ( 1 )
    {
        read_size = 0;

        while ((read_size = recv(sock, client_message + more_to_read_offset, 4096 - more_to_read_offset, 0)) > 0)
        {
            printf("server: received %d  more_to_read_offset: %d\n", read_size, more_to_read_offset);
            memset(&rval, 0, sizeof(asn_dec_rval_t));
            bytes_processed = 0;
            read_size += more_to_read_offset;
            while (bytes_processed < read_size)
            {
                ASN_STRUCT_RESET(asn_DEF_Message, P2R_message);
                printf("decoding...\n");
                rval = asn_decode(0, ATS_DER, &asn_DEF_Message, (void **)&P2R_message, client_message + bytes_processed, read_size - bytes_processed);
                printf("rval.code = %d\n", rval.code);
                switch (rval.code)
                {
                    case RC_OK:
                    {
                        printf("Decoded OK. Consumed %ld bytes of %d. Calling endpoint\n", rval.consumed, read_size - bytes_processed);
                        bytes_processed += rval.consumed;
                        more_to_read_offset = 0;
                        MessageParser(P2R_message, &sock);
                        break;
                    }
                    case RC_WMORE:
                    {
                        printf("Decoded partily. Consumed %ld bytes of %d. Calling endpoint\n", rval.consumed, read_size - bytes_processed);
                        memcpy(client_message, client_message + bytes_processed, read_size - bytes_processed);
                        more_to_read_offset = read_size - bytes_processed;
                        bytes_processed = 9999999;
                        break;
                    }
                    case RC_FAIL:
                    {
                        printf("Serer: error while decoding\n");
                        close(sock);
                        free(socket_desc);
                        return 0;
                    }
                }                
            }
            if (more_to_read_offset)
            {
                continue;
            }
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