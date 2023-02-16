#include "P2rClient.h"
#include "Message.h"
#include "Reason.h"



long rm_id = 2;
void *buffer = 0;
size_t size = 0;
int sock;
char connect_if_lost = 1;
struct sockaddr_in server_addr;
const long P2r_proto_major = 1;
const long P2r_proto_minor = 0;

typedef enum _ret
{
  Success = 0,
  NotEnoughMemory = 1,
  TransportInitError = 2,
  ServerIsUnreachable = 3,
  EncodingError = 4,
  Error = 5
} ret_val;

ret_val send_message(void *send_buffer, size_t send_buffer_size, void *ctx)
{
    int sock = *((int *)ctx);
    if (send(sock, send_buffer, send_buffer_size, 0) < 0)
    {
        printf("client: send failed\n");
        return ServerIsUnreachable;
    }
    return Success;
}

Message_t *receive_message( void *buffer, size_t size, void *ctx)
{
    int sock = *((int *)ctx);
    int read_size = 0;
    asn_dec_rval_t rval;
    Message_t *P2R_message = 0;
        if( (read_size = recv(sock, buffer, size, 0)) > 0)
        {
            printf("client: received %d\n", read_size);
                
                printf("decoding...\n");
                rval = asn_decode(0, ATS_DER, &asn_DEF_Message, (void **)&P2R_message, buffer, read_size );
                printf("rval.code = %d\n", rval.code);
                switch (rval.code)
                {
                case RC_OK:
                {
                    printf("Decoded OK. Consumed %ld bytes of %d. Calling endpoint\n", rval.consumed, read_size);
                    return P2R_message;
                }
                case RC_WMORE:
                {
                    printf("Decoded partily. Consumed %ld bytes of %d. Calling endpoint\n", rval.consumed, read_size);
                    break;
                }
                case RC_FAIL:
                {
                    printf("client: error while decoding\n");
                    close(sock);
                    return NULL;
                }
                }
            
        }
        return NULL;
}

void* ConnectThread(void* param) {
    while (connect_if_lost && (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) )
    {
        sleep(5);
    }
    // call restore_connection_callback();
}

ret_val P2rClientInit(long id, char* server, unsigned short port ) {    
    buffer = (char *)malloc(4096);
    if( !buffer) {
        return NotEnoughMemory;
    }
    size = 4096;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("client: could not create socket\n");
        return TransportInitError;
    }

    server_addr.sin_addr.s_addr = inet_addr(server);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("client: connect failed\n");
        return ServerIsUnreachable;
    }

    return Success;
}

ret_val P2rClientRelease() {
    shutdown(sock, SHUT_RD);
    sleep(3);
    close(sock);
    return Success;
}

ret_val EncodeAndSendMessage(Message_t *message)
{
    asn_enc_rval_t er;
    ret_val ret = Error;
    er = asn_encode_to_buffer(0, ATS_DER, &asn_DEF_Message, message, buffer, size);
    if (er.encoded == -1)
    {
        perror("failed to encode");
        printf("Failed to encode %s  %s\n", asn_DEF_Message.name, er.failed_type->name);
        ret = EncodingError;
    }
    else
    {
        ret = send_message(buffer, er.encoded, &sock);
    }
    free(message);
    return ret;
}

ret_val SendP2RSpeedLevelNotification(double speed)
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
    message->connection_id.rm_id = rm_id;

    message->message_type = MessageTypes_id_p2r_speed_level_notification;
    message->parameters.present = Parameters_PR_speed_level_notification;
    message->parameters.choice.speed_level_notification.speed = speed;

    return EncodeAndSendMessage( message );
}

ret_val SendP2RSessionRestoreWarning(long time)
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
    message->connection_id.rm_id = rm_id;

    message->message_type = MessageTypes_id_p2r_session_restore_warning;
    message->parameters.present = Parameters_PR_session_restore_warning;
    message->parameters.choice.session_restore_warning.estimated_time = time;

    return EncodeAndSendMessage(message);
}

ret_val SendP2RSessionTerminationWarningCancel(long warning_id)
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
    message->connection_id.rm_id = rm_id;

    message->message_type = MessageTypes_id_p2r_session_termination_warning_cancel;
    message->parameters.present = Parameters_PR_session_termination_warning_cancel;
    message->parameters.choice.session_termination_warning_cancel.warning_id = warning_id;

    return EncodeAndSendMessage(message);
}

ret_val SendP2RSessionTerminationWarning(long time, long warning_id, e_Reason reason )
{
    ret_val ret = Error;
    Message_t *message = 0;
    message = (Message_t *)calloc(1, sizeof(Message_t));
    if (!message)
    {
        return NotEnoughMemory;
    }
    message->protocol_version.major_version = P2r_proto_major;
    message->protocol_version.minor_version = P2r_proto_minor;
    message->connection_id.fp_id = 0;
    message->connection_id.rm_id = rm_id;

    message->message_type = MessageTypes_id_p2r_session_termination_warning;
    message->parameters.present = Parameters_PR_session_termination_warning;
    message->parameters.choice.session_termination_warning.estimated_time = time;
    message->parameters.choice.session_termination_warning.warning_id = warning_id;
    message->parameters.choice.session_termination_warning.reason = reason;

    ret = EncodeAndSendMessage(message);
    if( ret != Success ) {
        return ret;
    }
    //message = receive_message(buffer, size, &sock);
}

void *P2r_client_test(void *param)
{
    P2rClientInit(1, "127.0.0.1", 6666);

    SendP2RSessionTerminationWarning(10, 555, Reason_planned);
    //sleep(1);
    SendP2RSessionTerminationWarningCancel(555);
    //sleep(1);
    SendP2RSessionTerminationWarning(0, 556, Reason_unplanned);
    //sleep(1);
    SendP2RSessionRestoreWarning(100);
    //sleep(1);
    SendP2RSpeedLevelNotification(123.4);
    //sleep(1);
    SendP2RSpeedLevelNotification(155.6);
    //sleep(1);
    SendP2RSpeedLevelNotification(255.4);
    //sleep(1);
    SendP2RSpeedLevelNotification(100.7);
    //sleep(1);
    SendP2RSessionTerminationWarning(10, 557, Reason_planned);
    //sleep(1);
    P2rClientRelease();

    return 0;
}
