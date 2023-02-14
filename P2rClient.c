#include "P2rClient.h"
#include "Message.h"

int send_message( const void* buffer, size_t size, void* ctx ) {
    int sock = *((int*)ctx);
    if (send(sock, buffer, size, 0) < 0)
    {
        printf("client: send failed\n");
        return 1;
    }
    return 0;
}

void* P2r_client_test(void* param) {
    int sock;
    struct sockaddr_in server;
    char buffer[4096] = {0};
    int buffer_size = 0;
    asn_enc_rval_t er;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("client: could not create socket\n");
        return 0;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(6666);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("client: connect failed\n");
        return 0;
    }

    for (int i = 0; i < 3; i++ )
    {
        Message_t *message = 0;
       
        message = (Message_t *)calloc(1, sizeof(Message_t));
        if( !message ) {
            break;
        }
        
        message->protocol_version.major_version = 1;
        message->protocol_version.minor_version = i;
        message->message_type = MessageTypes_id_p2r_speed_level_notification;
        message->connection_id.fp_id = i;
        message->connection_id.rm_id = i * 5;
       
        message->parameters.present = 1;
        message->parameters.choice.speed_level_notification.speed = 0.1*i;

        /*
                char errbuf[128];
                size_t errlen = sizeof(errbuf);
                int ret = asn_check_constraints(&asn_DEF_Message, message, errbuf, &errlen);
                if (ret)
                {
                    fprintf(stderr, "Constraint validation failed: %s\n", errbuf);
                }
        */

        /*       char enc_buffer[4096] = {0};
               int enc_buffer_size = 4096;
               Parameters_t *params = (Parameters_t *)calloc(1, sizeof(Parameters_t));
               if( params ) {
                   params->present = 1;
                   params->choice.speed_level_notification = *parameter;
                   er = asn_encode_to_buffer(0, ATS_DER, &asn_DEF_Parameters, params, enc_buffer, enc_buffer_size);
                   if (er.encoded == -1)
                   {
                       perror("failed to encode");
                       printf("Failed to encode %s  %s\n", asn_DEF_Parameters.name, er.failed_type->name);
                   }
                   else
                   {
                       printf("%s encoded in % zd bytes\n", asn_DEF_Parameters.name, er.encoded);
                   }
               }
       */



      
        char enc_buffer[4096] = {0};
        int enc_buffer_size = 4096;
        er = asn_encode_to_buffer(0, ATS_DER, &asn_DEF_Message, message, enc_buffer, enc_buffer_size);
        //er = asn_encode(0, ATS_BER, &asn_DEF_Message, message, send_message, &sock);
        if (er.encoded == -1)
        {
            perror("failed to encode");
            printf("Failed to encode %s  %s\n", asn_DEF_Message.name, er.failed_type->name);
        }
        else
        {
            send_message(enc_buffer, er.encoded, &sock );
            // printf("%s encoded in % zd bytes\n", asn_DEF_Message.name, er.encoded);
        }       
        free(message);
        sleep(1);
    }

    close(sock);
    return 0;
}
