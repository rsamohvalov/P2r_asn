/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "P2r"
 * 	found in "P2r.asn1"
 */

#ifndef	_P2RConnectionReleaseAck_H_
#define	_P2RConnectionReleaseAck_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Cause.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* P2RConnectionReleaseAck */
typedef struct P2RConnectionReleaseAck {
	Cause_t	 cause;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} P2RConnectionReleaseAck_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_P2RConnectionReleaseAck;
extern asn_SEQUENCE_specifics_t asn_SPC_P2RConnectionReleaseAck_specs_1;
extern asn_TYPE_member_t asn_MBR_P2RConnectionReleaseAck_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _P2RConnectionReleaseAck_H_ */
#include <asn_internal.h>