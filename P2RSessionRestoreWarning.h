/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "P2r"
 * 	found in "P2r.asn1"
 */

#ifndef	_P2RSessionRestoreWarning_H_
#define	_P2RSessionRestoreWarning_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* P2RSessionRestoreWarning */
typedef struct P2RSessionRestoreWarning {
	long	 estimated_time;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} P2RSessionRestoreWarning_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_P2RSessionRestoreWarning;
extern asn_SEQUENCE_specifics_t asn_SPC_P2RSessionRestoreWarning_specs_1;
extern asn_TYPE_member_t asn_MBR_P2RSessionRestoreWarning_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _P2RSessionRestoreWarning_H_ */
#include <asn_internal.h>