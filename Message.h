/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "P2r"
 * 	found in "P2r.asn1"
 */

#ifndef	_Message_H_
#define	_Message_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ProtocolVersion.h"
#include "MessageTypes.h"
#include "ConnectionId.h"
#include "Parameters.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Message */
typedef struct Message {
	ProtocolVersion_t	 protocol_version;
	MessageTypes_t	 message_type;
	ConnectionId_t	 connection_id;
	Parameters_t	 parameters;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Message_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Message;

#ifdef __cplusplus
}
#endif

#endif	/* _Message_H_ */
#include <asn_internal.h>